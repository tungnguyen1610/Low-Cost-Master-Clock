#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H
#include <math.h>
#include "stdint.h"
#define PID_KP  7.0f
#define PID_KI  3.0f
#define PID_LIM_MIN  -1000.0f
#define PID_LIM_MAX  1000.0f
#define PID_LIM_IN_MIN -2000.0f
#define PID_LIM_IN_MAX 2000.0f
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
double PIController_Update(PIController *pid, double setpoint, double measurement);
void setAdaptiveTunning (PIController *pid, double valueKp,double valueKi);
void setAdaptiveTunningPHC (PIController *pid, double valueMin,double valueMax);
double PIController_Update_PHC(PIController *pid, long setpoint, long offset);
//void write_DAC (int fd,uint16_t value);
#ifdef __cplusplus
}
#endif
#endif
