#include "PID.h"
#include "CircularBuffer.h"
#include "clockadj.h"
#include "missing.h"
#include "phc_ctl.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdint.h>
#include <iostream>
#include <cerrno>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <linux/ptp_clock.h>
#include <string.h>
#include <errno.h>
#include <iomanip>
#include <fstream>
//#include <time.h>
using namespace std;
// Base address and offset for TIMER6 registers
#define TIMER6_BASE 0x48048000
#define TCRR_OFFSET 0x3C
#define TCLR_OFFSET 0x38
#define CM_PER  0x44E00000
#define TCAR1 0x50
#define IRQENABLE_SET 0x2c
#define IRQSTATUS 0x28
#define CM_PER_TIMER6_CLKCTRL   0xF0
#define CLKSEL_TIMER6_CLK 0x1C
#define TCAR1_OFFSET 0x50
#define TCAR2_OFFSET 0x58

int mem_fd = open("/dev/mem", O_RDWR | O_SYNC);
volatile uint32_t *timer6_CTRL;
volatile uint32_t *timer6_map;

void setuptimer()
{
    mem_fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (mem_fd < 0) 
    {
        perror("Failed to open /dev/mem");
        exit(EXIT_FAILURE);
    }
    timer6_CTRL =(uint32_t*) mmap(NULL, 0x1000, PROT_READ|PROT_WRITE, MAP_SHARED, mem_fd, CM_PER );
    timer6_map =(uint32_t*) mmap(NULL, 0x1000, PROT_READ|PROT_WRITE, MAP_SHARED, mem_fd, TIMER6_BASE );
    timer6_CTRL[CM_PER_TIMER6_CLKCTRL/4] =0x2;
    cout<<"Clock enable module for timer CM_PER:"<<hex<<timer6_CTRL[CM_PER_TIMER6_CLKCTRL/4]<<endl;
    timer6_CTRL[(0x500+0x1C)/4]=0x0;
    cout<<"Clock source of timer6 (=0x0 TCLKIN) and (=0x1) clock_m_osc:" << hex <<timer6_CTRL[(0x500+CLKSEL_TIMER6_CLK)/4]<<endl;
// change from 0x4 to 0x6
    timer6_map[IRQENABLE_SET/4] |=0x4;
    cout <<"Interrupt request register:" << hex << timer6_map[IRQENABLE_SET/4] << endl;
    timer6_map[IRQSTATUS/4] = 0x4;
    cout <<"Interrupt status register:" << hex << timer6_map[IRQSTATUS/4] <<endl;
    cout<<"Control register:" << hex<<timer6_map[TCLR_OFFSET/4]<<endl;
// change from 6103 -> 4941  
  timer6_map[TCLR_OFFSET/4]=0x4943; //0x4103 ; or 0x6103
    cout<<"Control register TCLR of DMTIMER 4 update :" << hex<<timer6_map[TCLR_OFFSET/4]<<endl;
    timer6_map[TCRR_OFFSET/4]=0 ;
    return;
}

#define PID_KP  7.0f
#define PID_KI  3.0f
#define PID_KP_PHC  0.07f
#define PID_KI_PHC  0.03f
#define PID_LIM_MIN  -300.0f
#define PID_LIM_MAX  300.0f
#define PID_LIM_IN_MIN -300.0f
#define PID_LIM_IN_MAX 300.0f
#define PID_PHC_LIM_MIN  -1000000.0f
#define PID_PHC_LIM_MAX  1000000.0f
#define PID_PHC_LIM_IN_MIN -1000.0f
#define PID_PHC_LIM_IN_MAX 1000.0f

#define MCP4725_ADDR 0x60

/******************
 * CPTS registers *
******************/
#define CPTS_BEGIN CPTS_IDVER_REG

#define CPTS_IDVER_REG 0x4A100C00            // CPTS Identification and Version Register
#define CPTS_CONTROL_REG 0x4A100C04          // Time Sync Control Register
//#define CPTS_RFTCLK_SEL_REG 0x4603D008       // Reference Clock Select Register
#define CPTS_TS_PUSH_REG 0x4A100C0C          // Time Stamp Event Push Register
#define CPTS_TS_LOAD_VAL_REG 0x4A100C10      // Time Stamp Load Low Value (lower 32-bits) Register
#define CPTS_TS_LOAD_EN_REG 0x4A100C14       // Time Stamp Load Enable Register
//#define CPTS_TS_COMP_VAL_REG 0x4603D018      // Time Stamp Comparison Low Value (lower 32-bits) Register
//#define CPTS_TS_COMP_LEN_REG 0x4603D01C      // Time Stamp Comparison Length Register
#define CPTS_INTSTAT_RAW_REG 0x4A100C20      // Interrupt Status Raw Register
#define CPTS_INTSTAT_MASKED_REG 0x4A100C24   // Interrupt Status Masked Register
#define CPTS_INT_ENABLE_REG 0x4A100C28       // Interrupt Enable Register Register
//#define CPTS_TS_COMP_NUDGE_REG 0x4603D02C    // Time Stamp Comparison Nudge Value Register
#define CPTS_EVENT_POP_REG 0x4A100C30        // Event Interrupt Pop Register
#define CPTS_EVENT_0_REG 0x4A100C34          // Lower 32-bits of the Event Value Registersize_t length= (size_t)PAGE_SIZE;
#define CPTS_EVENT_1_REG 0x4A100C38          // Lower Middle 32-bits of the Event Value Register    

int main()
{

    setuptimer();
    for (int i=0;i<5;i++)
    {
        cout<<timer6_map[TCRR_OFFSET/4]<<endl;
        sleep(1);
    }
    // set up PI controller parameter 
    PIController pid ={PID_KP, PID_KI,PID_LIM_IN_MIN,PID_LIM_IN_MAX,PID_LIM_MIN, PID_LIM_MAX};
    PIController pid_PHC={PID_KP_PHC, PID_KI_PHC,PID_PHC_LIM_IN_MIN,PID_PHC_LIM_IN_MAX,PID_PHC_LIM_MIN, PID_PHC_LIM_MAX};
    PIController_Init(&pid_PHC);
    PIController_Init(&pid);
    uint32_t setpoint=10000000;
    long setpointPHC=0;
    // DA converter set-up
    int file;
    int adapter_nr = 2; // probably dynamically determined 
    char filename[20];

    snprintf(filename, 19, "/dev/i2c-%d", adapter_nr);
    file = open(filename, O_RDWR);
    if (file < 0) 
    {
    // ERROR HANDLING; you can check errno to see what went wrong
    perror("Failed to open the i2c bus");  
    exit(1);
    }
    if (ioctl(file, I2C_SLAVE, MCP4725_ADDR) < 0) 
    {
        perror("Failed to acquire bus access and/or talk to slave");
        exit(1);
    }
    int offset=2550;
    int result; //offset of DAC value
    double resultPHC=0.0;
    int value=0; // for checking whether adjust PPB is succesful or not
    // File handling  
    ofstream myfile;
    myfile.open("time.txt");
    if (!myfile.is_open()) 
    {
        cerr << "Unable to open file" << endl;
        return 0;
    }
// to store the most 10 recent DA values
    CircularBuffer recent_value(10);
    CircularBuffer recent_value_PHC(5);
// storing previous capture value
    uint32_t preCapture=0;

// CPTS configuration
   
   volatile uint32_t *cpts_Base=(uint32_t*) mmap(NULL, 0x1000, PROT_READ|PROT_WRITE, MAP_SHARED, mem_fd, 0x4A100000 );
    if (cpts_Base == MAP_FAILED)
    {
        printf("Map fail");
        close(mem_fd);
        return -2;
    }
   cpts_Base[0xC04/4]=0xF01;
   cpts_Base[0xC28/4]=0x1;

    //Access PTP
    int ptp_fd = open("/dev/ptp0", O_RDWR);
    if (ptp_fd < 0) {
        perror("Failed to open /dev/ptp0");
        return 1;
    }
    // Get the clock ID for /dev/ptp0
    clockid_t clkid = ((~(clockid_t)ptp_fd) << 3) | 3;
    struct timespec phc_time;
    struct timespec current_time;
	long diff=0;
	long temp=0;
    while(1)
    {   
        if(timer6_map[IRQSTATUS/4]!=0)
        {
                   timer6_map[0x4C/4]= timer6_map[TCAR1_OFFSET/4]+10000005;       
//                            timer6_map[0x4C/4]= preCapture+10000010;
          cout <<"TCAR register:"<<timer6_map[TCAR1_OFFSET/4]<<endl;
          cout << "TMAR register:" <<timer6_map[0x4C/4]<<endl;
      //  clockadj_step(clkid,-50000);
          // set PHC value = system clock initially.
     //  timer6_map[0x4C/4]= timer6_map[TCAR1_OFFSET/4]+0xF00;
//	cout << "Event low register:"<<cpts_Base[0xC34/4]<<endl;
 //       cout << "Event high register:"<<cpts_Base[0xC38/4]<<endl;
//        memset(&phc_time, 0, sizeof(phc_time));
//	clock_gettime(clkid,&phc_time);
//	clock_gettime(CLOCK_REALTIME, &current_time);
//         myfile << current_time.tv_sec << "." << std::setw(9) << std::setfill('0') << current_time.tv_nsec << ",";
//        myfile << phc_time.tv_sec << "." << std::setw(9) << std::setfill('0') << phc_time.tv_nsec << "\n";
      //  myfile << "0x" << hex << setw(8) << setfill('0') << 0 << ",";
      //  myfile << "0x" << hex << setw(8) << setfill('0') << 0 << "\n";
    //    printf("Current Timestamp: %02d:%02d:%02d\n", ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
    //    cout << "captured counter value on previous PPS :"<<hex<< preCapture <<endl ;
    //    cout << "captured counter value on first transition:"<<hex<< timer6_map[TCAR1_OFFSET/4]<<endl ;
//        cout << "captured counter value on second transition:"<<hex<< timer6_map[TCAR2_OFFSET/4]<<endl;
         int cycle = timer6_map[TCAR1_OFFSET/4] - preCapture; 
        cout << "Event low register:"<<cpts_Base[0xC34/4]<<endl;
        cout << "Event high register:"<<cpts_Base[0xC38/4]<<endl;   
    // myfile << ptm->tm_hour << ":" << ptm->tm_min << ":" << ptm->tm_sec << ","
        //       << timer6_map[TCAR1_OFFSET/4] << "," << timer6_map[TCAR2_OFFSET/4] <<","<<cycle <<","<<(offset+result)<<"\n";
      //  myfile << ptm->tm_hour << ":" << ptm->tm_min << ":" << ptm->tm_sec << ","
      //          << preCapture<< "," << timer6_map[TCAR1_OFFSET/4] <<","<<cycle <<","<<(offset+result)<<"\n";
  
        printf("Counter value: %d\n", cycle);
        // add element error value  to buffer
        recent_value.add(cycle-10000000);
        recent_value.printBuffer();

 
     	myfile.flush();
        // switching between fast and slow controller 
         if (recent_value.allValuesSame())
        {
           cout <<"the same"<<endl;
           setAdaptiveTunning(&pid,0.5,0.1);
        }
        else
       {
	   if (abs(cycle-10000000)>1)
           {
               cout <<"not same,fast controller" <<endl;
            setAdaptiveTunning(&pid,7.0,3.0);
	   }
           else
           {
                 cout<<"notsame,slow controller" <<endl;
             setAdaptiveTunning(&pid,0.7,0.3);
            }
        }
        cout<<pid.Kp<<","<<pid.Ki<<endl; 
        result=PIController_Update(&pid,setpoint,cycle);
	printf("PID out value:%d\n",offset+result);
        write_DAC(file,offset+result);
/*
        if ( phc_time.tv_nsec < 500000000 )
        {setpointPHC=0;
	diff=phc_time.tv_nsec;
	} 
        else 
	{
        setpointPHC=1000000000;
	diff=-setpointPHC+phc_time.tv_nsec;        
        }
	temp=diff;
	if (abs(temp) > 10000)
	{
	if (temp > 0)
              {temp=10000;}
	else
              {temp=-10000;}
        }
        recent_value_PHC.add(temp);
      //  recent_value_PHC.printBuffer();
      //  printf ("Average offset:%f\n", recent_value_PHC.calculateAverage());
	clockadj_step(clkid,-50000-recent_value_PHC.calculateAverage());

             setAdaptiveTunning(&pid_PHC,0.7,0.3);
                setAdaptiveTunningPHC(&pid_PHC,-1000,1000);
        //       cout<<"PHC value Kp,Ki:" << pid_PHC.Kp<<","<<pid_PHC.Ki<<endl; 
 
        resultPHC= PIController_Update_PHC(&pid_PHC,0,diff); 
  //      myfile<< resultPHC << "\n";
     //   printf ("Adjusted frequency:%lf\n",resultPHC);
       clockadj_set_freq(clkid,resultPHC);
      //  clockadj_step(clkid,-50000);
	/*
        value=do_freq(clkid, resultPHC);
        if (value < 0) {
        fprintf(stderr, "Failed to adjust the frequency\n");
        } else {
        printf("Frequency adjustment completed successfully.\n");
 	}
*/
        preCapture=timer6_map[TCAR1_OFFSET/4];
	        cout <<"Status register:" <<timer6_map[IRQSTATUS/4]<<endl;
        timer6_map[IRQSTATUS/4] |=0x4;
        cout <<"Status register:" <<timer6_map[IRQSTATUS/4]<<endl;
	}
    }
    munmap((void *)timer6_map,getpagesize());
    munmap((void*) cpts_Base,getpagesize());
    close(mem_fd);
    return 0;
}
