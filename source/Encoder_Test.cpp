//###########################################################################
// Encoder_Test.c
// About the project of Encoder_Test
//
// $Copyright: Copyright (C) LDO Motors
//###########################################################################
#include "Encoder_Test.h"

///System initialize
void Encoder::Encoder_Init(void)
{
	InitSysCtrl();
	DINT;
	InitPieCtrl();
	IER = 0x00000000;
	IFR = 0x00000000;
	InitPieVectTable();

	//DSP modules initialize
	sci.Sci_Init();
	motor.Motor_Init();
	eCAP.eCAP_Init();

	EINT;   // Enable Global interrupt INTM
	ERTM;   // Enable Global realtime interrupt DBGM
}

///Encode test
void Encoder::Encoder_Execute(void)
{
	while(1)
	{
		flag = sci.SCIRX();
		if ( 0xAAAA == flag )
		{
			epwm = sci.SCIRX();
		}

		if ( 0xA0A0 == flag )
		{
			motor.Motor_Enable(epwm);
		}

		if ( 0x0A0A == flag )
		{
			motor.Motor_Disable();
		}
	}
}




