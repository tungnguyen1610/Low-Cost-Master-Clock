#include "PID.h"
#include <stdio.h>
#include <stdint.h>
#include "math.h"
//#include <stdlib.h>
#include <unistd.h> 

void PIController_Init(PIController *pi){
pi->integrator=0.0f;
pi->preError=0.0f;
pi->preMeasure=0;
pi->out=0;
}
double PIController_Update(PIController *pid, double  setpoint, double  measurement)
{
/*error signal*/
double error=setpoint -measurement;
/*proportiona */
double proportional =pid->Kp * error;
pid->integrator += pid->Ki*(error+ pid->preError);  //sampling time=1 second, we get a new counter value
if (pid->integrator > pid->limInMax) {

        pid->integrator = pid->limInMax;

    } else if (pid->integrator < pid->limInMin) {

        pid->integrator = pid->limInMin;

    }

    pid->out= proportional + pid->integrator;

    if (pid->out > pid->limMax) {

        pid->out = pid->limMax;

    } else if (pid->out < pid->limMin) {

        pid->out = pid->limMin;

    }
    pid->preError       = error;
    pid->preMeasure = measurement;
	/* Return controller output */    
    return pid->out;
}
void setAdaptiveTunning (PIController *pid, double valueKp,double valueKi)
{
    pid->Kp=valueKp;
    pid->Ki=valueKi;
}
void setAdaptiveTunningPHC (PIController *pid, double valueMin,double valueMax)
{
    pid->limInMin=valueMin; 
    pid->limInMax=valueMax;
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
/*
double PIController_Update_PHC(PIController *pid, long setpointPHC, long offset)
{
long error=setpointPHC-offset;
double proportional =pid->Kp * error;
double ki_term=pid->Ki * error;
pid->integrator += ki_term;  //sampling time=1 second, we get a new counter value
if (pid->integrator > pid->limInMax) {
        pid->integrator = pid->limInMax;

    } else if (pid->integrator < pid->limInMin) {

        pid->integrator = pid->limInMin;

    }

    pid->out= proportional + pid->integrator;

    if (pid->out > pid->limMax) {

        pid->out = pid->limMax;

    } else if (pid->out < pid->limMin) {

        pid->out = pid->limMin;

    }
    pid->preError       = error;
    pid->preMeasure = offset;
  //  pid->integrator=pid->out;
        /* Return controller output */
   // return pid->out;
//}
