//###########################################################################
// Encoder_Test.c
// About the project of Encoder_Test
//
// $Copyright: Copyright (C) LDO Motors
//###########################################################################
#include "Encoder_Test.h"

///System initialize
void Encoder::Initialize(void)
{
	InitSysCtrl();
	DINT;
	InitPieCtrl();
	IER = 0x00000000;
	IFR = 0x00000000;
	InitPieVectTable();

	//DSP modules initialize
	sci.Initialize();
	motor.Initialize();
	eCAP.Initialize();

	EINT;   // Enable Global interrupt INTM
	ERTM;   // Enable Global realtime interrupt DBGM
}

///Encode test
void Encoder::Execute(void)
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
			motor.Enable(epwm);
		}

		if ( 0x0A0A == flag )
		{
			motor.Disable();
		}
	}
}




