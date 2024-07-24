#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdint.h>
#include <iostream>
#include <cerrno>
using namespace std;
// Base address and offset for TIMER4 registers
#define TIMER6_BASE 0x48048000
#define TCRR_OFFSET 0x3C
#define TCLR_OFFSET 0x38
#define CM_PER  0x44E00000
#define TCAR1 0x50
#define IRQENABLE_SET 0x2c
#define IRQSTATUS 0x28
//      _CLK_DETAIL(DMTIMER4_CLK, CM_PER_TIMER4_CLKCTRL, CLKSEL_TIMER4_CLK),
#define CM_PER_TIMER6_CLKCTRL   0xF0
#define CLKSEL_TIMER6_CLK 0x1C
#define TCAR1_OFFSET 0x50
#define TCAR2_OFFSET 0x58
int main() {
    int mem_fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (mem_fd < 0) {
        perror("Failed to open /dev/mem");
        exit(EXIT_FAILURE);
    }
   volatile uint32_t *timer6_CTRL =(uint32_t*) mmap(NULL, 0x1000, PROT_READ|PROT_WRITE, MAP_SHARED, mem_fd, CM_PER );
   volatile uint32_t *timer6_map =(uint32_t*) mmap(NULL, 0x1000, PROT_READ|PROT_WRITE, MAP_SHARED, mem_fd, TIMER6_BASE );
    timer6_CTRL[CM_PER_TIMER6_CLKCTRL/4] =0x2;
    cout<<"Clock enable module for timer CM_PER:"<<hex<<timer6_CTRL[CM_PER_TIMER6_CLKCTRL/4]<<endl;
    timer6_CTRL[(0x500+CLKSEL_TIMER6_CLK)/4]=0x1;
    cout<<"Clock source of timer6 (=0x1) clock_m_osc:" << hex <<timer6_CTRL[(0x500+CLKSEL_TIMER6_CLK)/4]<<endl;
    timer6_map[IRQENABLE_SET/4] |=0x4;
    cout <<"Interrupt request register:" << hex << timer6_map[IRQENABLE_SET/4] << endl;
        timer6_map[IRQSTATUS/4] |=0x4;
    cout <<"Interrupt status register:" << hex << timer6_map[IRQSTATUS/4] <<endl;
    cout<<"Control register:" << hex<<timer6_map[TCLR_OFFSET/4]<<endl;
    //reload counter value
    timer6_map[0x28/4]=0;
    timer6_map[TCLR_OFFSET/4]=0x6103; //0x4103 ; or 0x6103
    cout<<"Control register TCLR of DMTIMER 4 update :" << hex<<timer6_map[TCLR_OFFSET/4]<<endl;
    for (int i=0;i<5;i++)
    {
        cout<<timer6_map[TCRR_OFFSET/4]<<endl;
    }
  while(1){
        if(timer6_map[IRQSTATUS/4]){
        cout << "captured counter value on first transition"<<hex<< timer6_map[TCAR1_OFFSET/4]<<endl ;
        cout << "captured counter value on second transition"<<hex<< timer6_map[TCAR2_OFFSET/4]<<endl;
        uint32_t cycle = timer6_map[TCAR2_OFFSET/4] - timer6_map[TCAR1_OFFSET/4];
        printf("%.2f Hz\n", (float)24000000/cycle);
            // Clear interrupt flag
        timer6_map[IRQSTATUS/4] |=0x4;
        }
    }
   /*
   while (1) 
   {
    if (timer6_map[TCAR1_OFFSET/4]!=0)
    {
    cout << "captured counter value on first transition"<< timer6_map[TCAR1_OFFSET/4]<<endl;
    cout << "captured counter value on second transition"<< timer6_map[TCAR2_OFFSET/4]<<endl;    
    }
            timer6_map[IRQSTATUS/4] |=0x4;
     sleep(1);   
   }
   */
   munmap((void *)timer6_map, getpagesize());
    close(mem_fd);
    return 0;
}
