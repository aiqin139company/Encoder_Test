//###########################################################################
// Encoder_Test.c
// About the project of Encoder_Test
//
// $Copyright: Copyright (C) LDO Motors
//###########################################################################
#include "Encoder_Test.h"

//System initialize
void System_Init(void)
{
#ifdef FLASH
	memcpy( (Uint16 *)&RamfuncsRunStart, (Uint16 *)&RamfuncsLoadStart,
			(unsigned long)&RamfuncsLoadSize);

	InitFlash();
#endif

	InitSysCtrl();
	DINT;
	InitPieCtrl();
	IER = 0x00000000;
	IFR = 0x00000000;
	InitPieVectTable();

	Hardware_Module_Init();
	Interrupt_Enable();
}

///Enable gobal interrupt
void Interrupt_Enable(void)
{
	EINT;   // Enable Global interrupt INTM
	ERTM;   // Enable Global realtime interrupt DBGM
}

///Hardware and dsp module initialize
void Hardware_Module_Init(void)
{
	//modules initial
	Sci_Init();
	Motor_Init();
	eCAP_Init();
}






