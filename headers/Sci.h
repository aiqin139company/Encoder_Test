//###########################################################################
// Sci.h
// About Sci Module
//
// $Copyright: Copyright (C) LDO Motors
//###########################################################################

#ifndef HEADERS_SCI_H_
#define HEADERS_SCI_H_

#include "Encoder_Test.h"

void Sci_Init(void);
void SCITX(long data);
long SCIRX(void);

#endif	/* HEADERS_SCI_H_ */

