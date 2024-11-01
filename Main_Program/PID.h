#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H
#include <math.h>
#include "stdint.h"
#ifdef __cplusplus
extern "C" {
#endif
typedef struct {
double Kp;
double Ki;
/*integrator limit*/
double limInMin;
double limInMax;
/*Output limit */
double limMin;
double limMax;
/*float T sampling time*/
/*Controller memory */
double integrator;
double preError;
double preMeasure;
/*output*/
double out;
}PIController;
void PIController_Init(PIController *pi);
int PIController_Update(PIController *pid, long setpoint, long measurement);
void setAdaptiveTunning (PIController *pid, double valueKp,double valueKi);
void setAdaptiveTunningPHC (PIController *pid, double valueMin,double valueMax);
double PIController_Update_PHC(PIController *pid, long setpoint, long offset);
/*
Function to wrtie value to I2C bus
*/
void write_DAC (int fd,uint16_t value);
#ifdef __cplusplus
}
#endif
#endif
