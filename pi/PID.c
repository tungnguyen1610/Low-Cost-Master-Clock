#include "PID.h"
#include <stdio.h>
#include <stdint.h>
#include "math.h"
#include <stdlib.h>
#include <unistd.h>
void PIController_Init(PIController *pi){
pi->integrator=0.0f;
pi->preError=0.0f;
pi->preMeasure=0;
pi->out=0;
}
int PIController_Update(PIController *pid, uint32_t  setpoint, uint32_t  measurement)
{
/*error signal*/
int error=setpoint -measurement;
/*proportiona */
double proportional =pid->Kp * error;
pid->integrator += 0.5f*pid->Ki*(error+ pid->preError);  //sampling time=1 second, we get a new counter value
    pid->out= proportional + pid->integrator;

    if (pid->out > pid->limMax) {

        pid->out = pid->limMax;

    } else if (pid->out < pid->limMin) {

        pid->out = pid->limMin;

    }
    pid->preError       = error;
    pid->preMeasure = measurement;
	/* Return controller output */
    int result=round (pid->out);    
    return result;
}
void write_DAC (int fd,uint16_t value)
{
    uint8_t buff[10];
    buff[0]=0x60; //register address 0x60
    buff[1]=(value >> 4) & (0xFF);
    buff[2]=(value << 4) & (0xFF);
    if (write(fd, buff, 3) != 3) {
    /* ERROR HANDLING: i2c transaction failed */
     perror("Failed to write to the i2c bus");
        exit(1);
     }
}
