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
int PIController_Update(PIController *pid, uint32_t setpoint, uint32_t measurement);
void write_DAC (int fd,uint16_t value);
#ifdef __cplusplus
}
#endif
#endif
