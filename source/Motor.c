//###########################################################################
// Motor.c
// Manager the motor
//
// $Copyright: Copyright (C) LDO Motors
//###########################################################################
#include <Motor.h>

///Motor Initialize
void Motor_Init(void)
{
	//Gpio Config
	EALLOW;
	GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 0;
	GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 0;
	GpioCtrlRegs.GPADIR.bit.GPIO2 = 1;
	GpioCtrlRegs.GPADIR.bit.GPIO3 = 1;
	GpioDataRegs.GPADAT.bit.GPIO2 = 0;
	GpioDataRegs.GPADAT.bit.GPIO3 = 0;
	EDIS;

	//ePWM module initialize
	EPWM_Init(10,400,300);
	Motor_Disable();
}

///ePWM Module Initialize
void EPWM_Init(int CLKDIV, int TBPRD, int CMP)
{
	//GPIO Config
	EALLOW;
	GpioCtrlRegs.GPAPUD.bit.GPIO0 = 1;    // Disable pull-up on GPIO0 (EPWM1A)
	GpioCtrlRegs.GPAPUD.bit.GPIO1 = 1;    // Disable pull-up on GPIO1 (EPWM1B)
	GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;   // Configure GPIO0 as EPWM1A
	GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;   // Configure GPIO1 as EPWM1B
	EDIS;

	//ePWM config
	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;	//ETWPM Module TBCLK enable/sync
	EDIS;

	EALLOW;
	EPwm1Regs.TBPRD = TBPRD; 			// Period = 601 TBCLK counts
	EPwm1Regs.CMPA.half.CMPA = CMP; 	// Compare A = 350 TBCLK counts
	EPwm1Regs.CMPB = CMP; 				// Compare B = 350 TBCLK counts

	EPwm1Regs.TBPHS.all = 0; 			// Set Phase register to zero
	EPwm1Regs.TBCTR = 0; 				// clear TB counter
	EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;
	EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;

	EPwm1Regs.TBCTL.bit.CLKDIV = CLKDIV;

	EPwm1Regs.AQCTLA.bit.ZRO = AQ_SET;
	EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;
	EPwm1Regs.AQCTLB.bit.ZRO = AQ_SET;
	EPwm1Regs.AQCTLB.bit.CBU = AQ_CLEAR;
	EDIS;
}

///enable motor to running
void Motor_Enable(char epwm)
{
	EPWM1A = epwm;
	EPWM1B = epwm;
}

///stopping motor
void Motor_Disable(void)
{
	EPWM1A = 0;
	EPWM1B = 0;
}




