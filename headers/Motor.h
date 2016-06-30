/*
 * motor.h
 *
 *  Created on: 2016Äê6ÔÂ24ÈÕ
 *      Author: Admin
 */

#ifndef HEADERS_MOTOR_H_
#define HEADERS_MOTOR_H_

#include "Encoder_Test.h"

#define EPWM1A 	EPwm1Regs.CMPA.half.CMPA
#define EPWM1B 	EPwm1Regs.CMPB

#define EPWM2A 	GpioDataRegs.GPADAT.bit.GPIO2
#define EPWM2B 	GpioDataRegs.GPADAT.bit.GPIO3

void Motor_Init(void);
void Motor_Enable(char epwm);
void Motor_Disable(void);

#endif /* HEADERS_MOTOR_H_ */
