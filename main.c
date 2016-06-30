//###########################################################################
// main.c
//
// $Copyright: Copyright (C) LDO Motors
//###########################################################################

#include "Encoder_Test.h"

int main(void)
{
	long flag = 0;
	char epwm = 0;

	System_Init();

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



