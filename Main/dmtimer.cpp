#include<iostream>
#include <fcntl.h>        // For open()
#include <sys/mman.h>     // For mmap()
#include "dmtimer.h"
using namespace std;
/*global variable */
volatile uint32_t *timer6_CTRL = NULL;  // Definition and initialization
volatile uint32_t *timer6_map = NULL;   // Definition and initialization
extern int mem_fd ;
void setupTimer()
{
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
    // Enable Interrupt for capture event
    timer6_map[IRQENABLE_SET/4] |=0x4;
    cout <<"Interrupt request register:" << hex << timer6_map[IRQENABLE_SET/4] << endl;
    timer6_map[IRQSTATUS/4] = 0x4;
    cout <<"Interrupt status register:" << hex << timer6_map[IRQSTATUS/4] <<endl;
    cout<<"Current Control register:" << hex<<timer6_map[TCLR_OFFSET/4]<<endl;
    timer6_map[TCLR_OFFSET/4]=0x4943; 
    cout<<"Control register TCLR of DMTIMER 4 update :" << hex<<timer6_map[TCLR_OFFSET/4]<<endl;
    // initial counter=0
    timer6_map[TCRR_OFFSET/4]=0 ;
    return;
}

