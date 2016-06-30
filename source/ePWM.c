//###########################################################################
// ePWM.c
// About ePWM Module
//
// $Copyright: Copyright (C) LDO Motors
//###########################################################################

#include <ePWM.h>

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



