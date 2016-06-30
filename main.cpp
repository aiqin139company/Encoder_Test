//###########################################################################
// main.c
//
// $Copyright: Copyright (C) LDO Motors
//###########################################################################

#include "string.h"
#include "SysVar.h"
#include "Encoder_Test.h"

// These are defined by the linker
extern Uint16 RamfuncsLoadStart;
extern Uint16 RamfuncsLoadSize;
extern Uint16 RamfuncsRunStart;

Encoder Encoder::encoder = Encoder();

///main function
int main(void)
{
#ifdef FLASH
	memcpy( (Uint16 *)&RamfuncsRunStart, (Uint16 *)&RamfuncsLoadStart,
			(unsigned long)&RamfuncsLoadSize);
	InitFlash();
#endif

	Encoder::encoder.Initialize();
	Encoder::encoder.Execute();

}



