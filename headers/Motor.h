//###########################################################################
// Motor.h
// Manager the motor
//
// $Copyright: Copyright (C) LDO Motors
//###########################################################################

#ifndef HEADERS_MOTOR_H_
#define HEADERS_MOTOR_H_

#include "SysVar.h"

#define EPWM1A 	EPwm1Regs.CMPA.half.CMPA
#define EPWM1B 	EPwm1Regs.CMPB

#define EPWM2A 	GpioDataRegs.GPADAT.bit.GPIO2
#define EPWM2B 	GpioDataRegs.GPADAT.bit.GPIO3


class Motor_Module
{
private:

public:

	void Initialize(void);
	void Enable(char epwm);
	void Disable(void);
	void EPWM_Init(int CLKDIV, int TBPRD, int CMP);

};



#endif /* HEADERS_MOTOR_H_ */
