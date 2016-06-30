//###########################################################################
// main.c
//
// $Copyright: Copyright (C) LDO Motors
//###########################################################################

#include "SysVar.h"
#include "Encoder_Test.h"

// These are defined by the linker
extern Uint16 RamfuncsLoadStart;
extern Uint16 RamfuncsLoadSize;
extern Uint16 RamfuncsRunStart;

Encoder Encoder::Encoder = Encoder();

///main function
int main(void)
{
#ifdef FLASH1
	memcpy( (Uint16 *)&RamfuncsRunStart, (Uint16 *)&RamfuncsLoadStart,
			(unsigned long)&RamfuncsLoadSize);
	InitFlash();
#endif

	Encoder::Encoder.Encoder_Init();
	Encoder::Encoder.Encoder_Execute();

}



