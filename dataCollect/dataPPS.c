#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <time.h>
#include <stdint.h>
#include <iostream>
#include <cerrno>
using namespace std;
// Base address and offset for TIMER4 registers
#define TIMER6_BASE 0x48048000
#define TCRR_OFFSET 0x30
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
    // DMTIMER set-up
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
    //Capture Part
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
    //Data gaining with Vin to oscillator = const
    uint32_t TCAR1=timer6_map[TCAR1_OFFSET/4];
    uint32_t TCAR2=timer6_map[TCAR2_OFFSET/4];
    int timestep=10;
    fstream myfile("data.txt");
    if (!myfile.is_open()) {
        cerr << "Unable to open file" << endl;
        return 1;
    }
    myfile<< "Time(s),TCAR1,TCAR2,Difference\n" ;
    struct timespec start_time;
    clock_gettime(CLOCK_REALTIME, &start_time);
    for (int i=0;i<10;i++)
    {
    // Get start time
    struct timespec current_time;
            clock_gettime(CLOCK_REALTIME, &current_time);
    tcar1+=1;
    tcar2+=1;
    double elapsed_time = (current_time.tv_sec - start_time.tv_sec) + 
                                  (current_time.tv_nsec - start_time.tv_nsec) / 1e9;
    printf("Time: %.6f s\n", elapsed_time);
    printf("Captured counter value on first transition: %x\n", tcar1);
    printf("Captured counter value on second transition: %x\n", tcar2);
    myfile << fixed << setprecision(6) << elapsed_time << ","
                   << tcar1 << "," << tcar2 << "\n";
    myfile.flush();
    sleep (1+timestep); // timestep= 10ms
    }   
    //Clear pointer to register
    munmap((void *)timer6_map, getpagesize());
    close(mem_fd);
    return 0;
}
