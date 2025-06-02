#include "PID.h"
#include "CircularBuffer.h"
#include "clockadj.h"
#include "missing.h"
#include "phc_ctl.h"
#include "dmtimer.h"
#include "cpts.h"
#include "i2c_com.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h> 
#include <linux/ptp_clock.h>
using namespace std;

// Global variables to store configuration parameters
int SETPOINT =  10000000; // 10 Mhz Clock Frequency
uint32_t OFFSET = 50000; // Estimated DA value for setpoint
int mem_fd = open("/dev/mem", O_RDWR | O_SYNC);

// Function prototypes
void setupPTP(int &ptp_fd,clockid_t &clkid);
void handleAlgorithm (int file,int file_temp, PIController &pid, CircularBuffer &recent_value, uint32_t &preCapture,double &result);
int main(int argc, char *argv[])
{
    int opt;
    // Command line argument interfaces
    while ((opt = getopt(argc, argv, "f:o:")) != -1){
        switch(opt){
        case 'f':
            SETPOINT=(atoi(optarg))*pow(10,3);
            break;
        case 'o':
            OFFSET=atoi(optarg);
            break;
        case ':':
            cout<<"Option needs value, continue with default value" << endl;
            break;
        default:
            cerr<<"Usage:"<<argv[0]<<"-f <frequency> -o <offset> \n";
            cout <<"Process with default value (10Mhz and 50000 DA offset" << endl;
        }
    }
    cout <<"Frequency and offset parameters:"<< SETPOINT << ";"<<OFFSET<<endl;

    setupTimer();
    // Set up PI controller parameter
    PIController pid ={PID_KP, PID_KI,PID_LIM_IN_MIN,PID_LIM_IN_MAX,PID_LIM_MIN, PID_LIM_MAX};
    PIController_Init(&pid);

    // DA converter set-up, "2" -> I2C-2 in BeagleBone
    int file=0;
    setupDAConverter(&file, 2);
    int file_temp=0;
    setupTempSensor(&file_temp,2);
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
       handleAlgorithm (file,file_temp,pid, recent_value, preCapture,result);
       usleep(5000);
    }
    /*unmap memory*/
    munmap((void *)timer6_map,getpagesize());
    munmap((void*) cpts_Base,getpagesize());
    close(mem_fd);
    return 0;
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

void handleAlgorithm (int file, int file_temp, PIController &pid, CircularBuffer &recent_value, uint32_t &preCapture,double &result)
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
    static double temp = 0;  // Counter error accumulation during gate time measurement
    static bool firstCapture = true;  // Track first valid capture
    // Interrupt handling
    if (timer6_map[IRQSTATUS / 4] != 0) {
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
            recent_value.add(cycle);
            if (cycle > 10000100 || cycle < 9999900)
            {
                recent_value.reinitialize();
                printf("Wrong PPS\n");
                preCapture = timer6_map[TCAR1_OFFSET / 4];
                timer6_map[IRQSTATUS / 4] |= 0x4;
                return;
            }
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
            cout <<"size of circular buffer:0x"<<recent_value.getSize()<<endl;
            cout << "Average count:"<<std::fixed<<temp<<endl;
            result= PIController_Update(&pid, SETPOINT, temp);
            printf("PID out value:%lf\n",OFFSET+4*result);
            write_DAC(file, OFFSET+4*result);
            // Read OCXO temperature
            uint8_t buff[3];
            readTemperature(file_temp,buff);
            float current_temp=convert_temp(buff);
            printf("Current temp:%lf",current_temp);
            printf("\n");

            preCapture = timer6_map[TCAR1_OFFSET / 4];
            // Clear interrupt flag
            timer6_map[IRQSTATUS / 4] |= 0x4;

        }
}
