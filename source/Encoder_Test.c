//###########################################################################
// Encoder_Test.c
// About the project of Encoder_Test
//
// $Copyright: Copyright (C) LDO Motors
//###########################################################################
#include "Encoder_Test.h"

///System initialize
void Encoder_Init(void)
{
	InitSysCtrl();
	DINT;
	InitPieCtrl();
	IER = 0x00000000;
	IFR = 0x00000000;
	InitPieVectTable();

	//DSP modules initialize
	Sci_Init();
	Motor_Init();
	eCAP_Init();

	EINT;   // Enable Global interrupt INTM
	ERTM;   // Enable Global realtime interrupt DBGM
}

///Encode test
void Encoder_Execute(void)
{
	long flag = 0;
	char epwm = 0;

	while(1)
	{
		flag = SCIRX();
		if ( 0xAAAA == flag )
		{
			epwm = SCIRX();
		}

		if ( 0xA0A0 == flag )
		{
			PIE_eCAP_CNT();
			Motor_Enable(epwm);
		}

		if ( 0x0A0A == flag )
		{
			Motor_Disable();
		}
	}
}




