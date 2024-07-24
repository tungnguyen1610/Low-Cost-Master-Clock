#include "PID.h"
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
    timer6_map[IRQENABLE_SET/4] |=0x4;
    cout <<"Interrupt request register:" << hex << timer6_map[IRQENABLE_SET/4] << endl;
        timer6_map[IRQSTATUS/4] |=0x4;
    cout <<"Interrupt status register:" << hex << timer6_map[IRQSTATUS/4] <<endl;
    cout<<"Control register:" << hex<<timer6_map[TCLR_OFFSET/4]<<endl;
    timer6_map[TCLR_OFFSET/4]=0x6103; //0x4103 ; or 0x6103
    cout<<"Control register TCLR of DMTIMER 4 update :" << hex<<timer6_map[TCLR_OFFSET/4]<<endl;
    timer6_map[TCRR_OFFSET/4]=0 ;
    return;
}
#define PID_KP  0.7f
#define PID_KI  0.3f
#define PID_LIM_MIN  -50.0f
#define PID_LIM_MAX  50.0f

#define MCP4725_ADDR 0x60
int main()
{
    setuptimer();
   for (int i=0;i<5;i++)
    {
        cout<<timer6_map[TCRR_OFFSET/4]<<endl;
        sleep(1);
    }
    /*set up PI controller parameter*/ 
    PIController pid ={PID_KP, PID_KI,PID_LIM_MIN, PID_LIM_MAX};
    PIController_Init(&pid);
    uint32_t setpoint=10000000;
    /*DA converter set-up*/
    int file;
    int adapter_nr = 2; /* probably dynamically determined */
    char filename[20];

    snprintf(filename, 19, "/dev/i2c-%d", adapter_nr);
    file = open(filename, O_RDWR);
    if (file < 0) 
    {
  /* ERROR HANDLING; you can check errno to see what went wrong */
    perror("Failed to open the i2c bus");  
    exit(1);
    }
    if (ioctl(file, I2C_SLAVE, MCP4725_ADDR) < 0) 
    {
        perror("Failed to acquire bus access and/or talk to slave");
        exit(1);
    }
    int result;
    while(1)
    {
        if(timer6_map[IRQSTATUS/4]!=0)
        {
        cout << "captured counter value on first transition:"<<hex<< timer6_map[TCAR1_OFFSET/4]<<endl ;
        cout << "captured counter value on second transition:"<<hex<< timer6_map[TCAR2_OFFSET/4]<<endl;
        uint32_t cycle = timer6_map[TCAR2_OFFSET/4] - timer6_map[TCAR1_OFFSET/4];
        printf("Counter value: %d\n", cycle);
        printf("%.2f Hz\n", (float)10000000/cycle);
            // Clear interrupt flag
        //timer6_map[IRQSTATUS/4] |=0x4;
        result=PIController_Update(&pid,setpoint,cycle);
	printf("PID out value:%d\n",result);
        write_DAC(file,2450+result);
        timer6_map[IRQSTATUS/4] |=0x4;
        }
    }
    
    return 0;
}
