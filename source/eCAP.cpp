//###########################################################################
// eCAP.c
// About eCAP Module
//
// $Copyright: Copyright (C) LDO Motors
//###########################################################################
#include "eCAP.h"

///Constructor
eCAP_Module::eCAP_Module() :
	period(0),
	limit_H(0),
	limit_L(0)
{
}

eCAP_Module eCAP_Module::instance = eCAP_Module();

///
eCAP_Module* eCAP_Module::Instance()
{
	return &instance;
}


///eCAP_MODULE Initialize
void eCAP_Module::eCAP_Init(void)
{
	//GPIO Config
	EALLOW;
	GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0;     // Enable pull-up on GPIO19 (CAP1)
	GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 0;   // Synch to SYSCLKOUT GPIO19 (CAP1)
	GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 3;    // Configure GPIO19 as CAP1
	EDIS;

	//Interrupt Config
	EALLOW;
	PieVectTable.ECAP1_INT = &eCAP_CNT;
	IER |= M_INT4;						// Enable CPU INT4 which is connected to ECAP1-4 INT:
	PieCtrlRegs.PIEIER4.bit.INTx1 = 1;	// Enable eCAP INTn in the PIE: Group 3 interrupt 1-6
	EDIS;

	// Code snippet for CAP mode Delta Time, Rising and Falling
	// edge triggers
	// Initialization Time
	//=======================
	// ECAP module 1 config
	EALLOW;
	ECap1Regs.ECEINT.all = 0x0000;             // Disable all capture interrupts
	ECap1Regs.ECCLR.all = 0xFFFF;              // Clear all CAP interrupt flags
	ECap1Regs.ECCTL1.bit.CAPLDEN = 0;          // Disable CAP1-CAP4 register loads
	ECap1Regs.ECCTL2.bit.TSCTRSTOP = 0;        // Make sure the counter is stopped

	// Configure peripheral registers
	ECap1Regs.ECCTL2.bit.CONT_ONESHT = 1;      // One-shot
	ECap1Regs.ECCTL2.bit.STOP_WRAP = 0;        // Stop at 1 event
	ECap1Regs.ECCTL1.bit.CAP1POL = 0;          // Rising edge
	ECap1Regs.ECCTL1.bit.CTRRST1 = 1;          // Difference operation
	ECap1Regs.ECCTL2.bit.SYNCI_EN = 1;         // Enable sync in
	ECap1Regs.ECCTL2.bit.SYNCO_SEL = 0;        // Pass through
	ECap1Regs.ECCTL1.bit.CAPLDEN = 1;          // Enable capture units

	ECap1Regs.ECCTL2.bit.TSCTRSTOP = 1;        // Start Counter
	ECap1Regs.ECCTL2.bit.REARM = 1;            // arm one-shot
	ECap1Regs.ECCTL1.bit.CAPLDEN = 1;          // Enable CAP1-CAP4 register loads
	ECap1Regs.ECEINT.bit.CEVT1 = 1;            // 1 event = interrupt
	EDIS;

	LP.UpdateParams(_IQ(0.005));
}

///eCAP_CEVT1 Interrupt handler1
///sampling an gerenal period
__interrupt void eCAP_Module::eCAP_CNT(void)
{
	static int cnt = 0;
	cnt ++;
	if ( cnt > 2000 && cnt < 5000 )
	{
		instance.LP.In = ECap1Regs.CAP1;
		LOWPASS_MACRO(instance.LP);
	}

	if( 5000 == cnt )
	{
		instance.limit_H = instance.LP.Out + instance.LP.Out * 0.5;
		instance.limit_L = instance.LP.Out - instance.LP.Out * 0.5;
		instance.sci.SCITX(instance.LP.Out);
	}

	if ( 6000 == cnt )
	{
		cnt = 0;
		PIE_eCAP_ISR();
	}

	//CLR Interrupt Flag
	eCAP_ACK();
}


///eCAP_CEVT1 Interrupt handler2
///compared with the general period
__interrupt void eCAP_Module::eCAP_ISR(void)
{
	instance.period = ECap1Regs.CAP1;

	if ( ( instance.period > instance.limit_H )
		|| ( instance.period < instance.limit_L ) )
	{
		instance.sci.SCITX(EncoderError);
	}

	//CLR Interrupt Flag
	eCAP_ACK();
}


