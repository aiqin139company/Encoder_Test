//###########################################################################
// eCAP.c
// About eCAP Module
//
// $Copyright: Copyright (C) LDO Motors
//###########################################################################
#include <eCAP.h>

Uint32 period = 0;
Uint32 limit_H = 0;
Uint32 limit_L = 0;
LowPassFilter LP;

#ifdef TEST_PIN
#define T_Pin  GpioDataRegs.GPBDAT.bit.GPIO39
void Test_Pin(void)
{
	EALLOW;
	GpioCtrlRegs.GPBMUX1.bit.GPIO39 = 0;
	GpioCtrlRegs.GPBDIR.bit.GPIO39 = 1;
	GpioDataRegs.GPBDAT.bit.GPIO39 = 0;
	EDIS;
}
#endif

///eCAP_MODULE Initialize
void eCAP_Init(void)
{
#ifdef TEST_PIN
	Test_Pin();
#endif
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

	LowPass_Params(&LP,_IQ(0.005));
}

///eCAP_CEVT1 Interrupt handler1
__interrupt void eCAP_CNT(void)
{
#ifdef TEST_PIN
	T_Pin = 1;
#endif
	static int cnt = 0;
	cnt ++;
	if ( cnt > 2000 )
	{
		LP.In = ECap1Regs.CAP1;
		LowPass(&LP);
	}

	if( COUNT == cnt )
	{
		cnt = 0;
		limit_H = LP.Out + LP.Out * 0.15;
		limit_L = LP.Out - LP.Out * 0.15;
		SCITX(LP.Out);
		PIE_eCAP_ISR();
	}

	//CLR Interrupt Flag
	eCAP_ACK();

#ifdef TEST_PIN
	T_Pin = 0;
#endif
}


///eCAP_CEVT1 Interrupt handler2
__interrupt void eCAP_ISR(void)
{
	period = ECap1Regs.CAP1;

	if ( !(limit_H > period && limit_L < period) )
	{
		SCITX(0xffff);
	}

	//CLR Interrupt Flag
	eCAP_ACK();

}


