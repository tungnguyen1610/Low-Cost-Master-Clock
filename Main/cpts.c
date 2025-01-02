#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>        // For open()
#include <sys/mman.h>     // For mmap()
#include "cpts.h"
//Allocate memory
volatile uint32_t *cpts_Base = NULL ;
void setupCPTS()
{
    int mem_fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (mem_fd < 0)
    {
        perror("Failed to open /dev/mem");
        exit(EXIT_FAILURE);
    }
    cpts_Base=(uint32_t*) mmap(NULL, 0x1000, PROT_READ|PROT_WRITE, MAP_SHARED, mem_fd, CPTS_BASE);
    cpts_Base[(CPTS_CONTROL_REG-CPTS_BASE)/4]=0xF01;
    cpts_Base[(CPTS_INT_ENABLE_REG-CPTS_BASE)/4]=0x1;
}
