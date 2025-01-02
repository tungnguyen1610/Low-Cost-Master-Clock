#include "PID.h"
#include "CircularBuffer.h"
#include "clockadj.h"
#include "missing.h"
#include "phc_ctl.h"
#include "dmtimer.h"
#include "cpts.h"
#include <iostream>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <iomanip>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <linux/ptp_clock.h>
using namespace std;
#define MCP4725_ADDR 0x60 //Slave address of DA converter
int main()
{
    int mem_fd = open("/dev/mem", O_RDWR | O_SYNC);
    setuptimer();
    for (int i=0;i<5;i++)
    {
        cout<<timer6_map[TCRR_OFFSET/4]<<endl;
        sleep(1);
    }
    // set up PI controller parameter 
    PIController pid ={PID_KP, PID_KI,PID_LIM_IN_MIN,PID_LIM_IN_MAX,PID_LIM_MIN, PID_LIM_MAX};
    PIController_Init(&pid);
    //DA converter set-up
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
    uint32_t setpoint=10000000;
    int offset=2550;
    int result; //offset of DAC value
    CircularBuffer recent_value(10); //Initialize circular buffer with 10 elements.
    uint32_t preCapture=0; //storing previous capture value
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
    while(1)
    {   
        if(timer6_map[IRQSTATUS/4]!=0)
        {
        timer6_map[0x4C/4]= timer6_map[TCAR1_OFFSET/4] + 10000002;       
        int cycle = timer6_map[TCAR1_OFFSET/4] - preCapture; 
        cout << "Event low register:"<<cpts_Base[0xC34/4]<<endl;
        cout << "Event high register:"<<cpts_Base[0xC38/4]<<endl;
        cout << "Counter differences:"<<cycle<<endl;
        recent_value.add(cycle-10000000);
        recent_value.printBuffer();
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
	cout<<"PID out value:"<<offset+result<<endl;
        write_DAC(file,offset+result);
        preCapture=timer6_map[TCAR1_OFFSET/4];
        /*clear interrupt flag */
        timer6_map[IRQSTATUS/4] |=0x4;
	}
    }
    /*unmap memory*/
    munmap((void *)timer6_map,getpagesize());
    munmap((void*) cpts_Base,getpagesize());
    close(mem_fd);
    return 0;
}
