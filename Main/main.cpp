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

// Global variables to store configuration parameters
#define MCP4725_ADDR 0x60 //Slave address of DA converter
#define SETPOINT 10000000 // 10 Mhz Clock Frequency
#define OFFSET 2550 // Estimated DA value for setpoint
int mem_fd = open("/dev/mem", O_RDWR | O_SYNC);

// Function prototypes
void setupDAConverter (int &file,int adapter_nr);
void setupPTP(int &ptp_fd,clockid_t &clkid);
void handleAlgorithm (int file, PIController &pid, CircularBuffer &recent_value, uint32_t &preCapture,double &result);

int main()
{
    setupTimer();
    /* for debugging purpose
    for (int i=0;i<5;i++)
    {
        cout<<timer6_map[TCRR_OFFSET/4]<<endl;
        sleep(1);
    }
    */
    // Set up PI controller parameter
    PIController pid ={PID_KP, PID_KI,PID_LIM_IN_MIN,PID_LIM_IN_MAX,PID_LIM_MIN, PID_LIM_MAX};
    PIController_Init(&pid);

    // DA converter set-up, "2" -> I2C-2 in BeagleBone
    int file;
    setupDAConverter(file, 2);

    // Set up PTP clock
    int ptp_fd;
    clockid_t clkid;
    setupPTP(ptp_fd, clkid);

     // Set up Common Platform Time Sync (CPTS)
    setupCPTS();

    // Initialize circular buffer and variables for algorithm
    CircularBuffer recent_value(10);
    uint32_t preCapture=timer6_map[TCAR1_OFFSET/4];
    double result=0;

    while(true)
    {   
       handleAlgorithm (file, pid, recent_value, preCapture,result);
       usleep(5000);
    }
    /*unmap memory*/
    munmap((void *)timer6_map,getpagesize());
    munmap((void*) cpts_Base,getpagesize());
    close(mem_fd);
    return 0;
}

void setupDAConverter(int &file, int adapter_nr)
{
    char filename[20];
    snprintf(filename, sizeof(filename), "/dev/i2c-%d", adapter_nr);

    file = open(filename, O_RDWR);
    if (file < 0) {
        perror("Failed to open the I2C bus");
        exit(EXIT_FAILURE);
    }

    if (ioctl(file, I2C_SLAVE, MCP4725_ADDR) < 0) {
        perror("Failed to acquire bus access or talk to slave");
        exit(EXIT_FAILURE);
    }
}

void setupPTP(int &ptp_fd, clockid_t &clkid)
{
    ptp_fd = open("/dev/ptp0", O_RDWR);
    if (ptp_fd < 0) {
        perror("Failed to open /dev/ptp0");
        exit(EXIT_FAILURE);
    }

    clkid = ((~(clockid_t)ptp_fd) << 3) | 3;
}

void handleAlgorithm (int file, PIController &pid, CircularBuffer &recent_value, uint32_t &preCapture,double &result)
{
    // Add Clock Monotonic Timestamp for Logging
    struct timespec ts;
    if (clock_gettime (CLOCK_MONOTONIC, &ts)==-1)
    {
        perror("clock_gettime failed");
        return;
    }
    // Combine seconds and nanoseconds into a floating-point number
    double time_in_seconds = ts.tv_sec + ts.tv_nsec / 1e9;
    // Persisting gate count and temporary accumulation
//    static int gate = 0;  // Keeps its value across function calls
    static double temp = 0;  // Counter error accumulation during gate time measurement
    static bool firstCapture = true;  // Track first valid capture
    // Interrupt handling
    if (timer6_map[IRQSTATUS / 4] != 0) {
//	    gate++;
            printf("TIME: %.3f seconds\n", time_in_seconds);
            // Assign Match Register Value for PPS Capture
            timer6_map[TMAR_OFFSET/4]= timer6_map[TCAR1_OFFSET/4] + 10000002;
            //Ignore first cycle calculation
        if (firstCapture)
        {
            preCapture = timer6_map[TCAR1_OFFSET / 4];
            firstCapture = false;  // Next time, process normally
            timer6_map[IRQSTATUS / 4] |= 0x4;
            return; // Skip this iteration
        }
            // Perform PID calculation and handle hardware interaction
            int cycle = timer6_map[TCAR1_OFFSET / 4] - preCapture;
            printf("Counter Value:%d\n",cycle);
            if (cycle > 10000100 || cycle < 9999900)
                cycle=10000000;
            recent_value.add(cycle);
            if (recent_value.allValuesSame()) {
                setAdaptiveTunning(&pid, 0.5, 0.1);
            } else 
		{
                if (abs(cycle - SETPOINT) > 1) {
                    setAdaptiveTunning(&pid, 7.0, 3.0);
                } else {
                    setAdaptiveTunning(&pid, 0.7, 0.3);
                }
            }
            temp = recent_value.calculateAvg();
           // printf ("PID input value:%d\n",temp);
           // if (gate == 10)
           // {
            if (abs(temp-10000000)<0.75)
            {
                recent_value.changeSize(50);
            }
	    else
	   {
               recent_value.reinitialize();
           }
            cout <<"size of circular buffer:0x"<<recent_value.getSize()<<endl;
		    cout << "Average count:"<<std::fixed<<temp<<endl;
            result= PIController_Update(&pid, SETPOINT, temp);
                printf("PID out value:%lf\n",OFFSET+result);
                write_DAC(file, round(OFFSET + result));
             //   gate = 0;
              //  temp = 0;
           // }
            preCapture = timer6_map[TCAR1_OFFSET / 4];
            // Clear interrupt flag
            timer6_map[IRQSTATUS / 4] |= 0x4;
        }
}
