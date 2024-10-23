#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdint.h>
#include <iostream>
using namespace std;
#define  PINCONTROL 0x44E10000
#define conf_gpmc_advn_ale 0x9B4
int main()
{
int mem_fd=open("/dev/mem",O_RDWR | O_SYNC);
if (mem_fd<0){
        perror("Fail to open");
        exit(EXIT_FAILURE);
}
volatile uint32_t *timer4_mode = (uint32_t*) mmap(NULL, 0x1000, PROT_READ|PROT_WRITE, MAP_SHARED, mem_fd, PINCONTROL);
if (timer4_mode == MAP_FAILED)
   {
        cout<<"Failed to get pointer to timer4" <<endl;
        close(mem_fd);
        exit(EXIT_FAILURE);
    }
//timer4_mode[conf_gpmc_advn_ale/4]|=0x5;
cout << "Pin P9.41 configuration register: " << hex << timer4_mode[conf_gpmc_advn_ale/4]<<endl;
return 0;
}
