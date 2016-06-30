//###########################################################################
// Sci.h
// About Sci Module
//
// $Copyright: Copyright (C) LDO Motors
//###########################################################################

#ifndef _Sci_H_
#define _Sci_H_

#include "Encoder_Test.h"

void Sci_Init(void);
void SCITX(long data);
long SCIRX(void);

__interrupt void SCI_RX_ISR(void);

#endif

