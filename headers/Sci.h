//###########################################################################
// Sci.h
// About Sci Module
//
// $Copyright: Copyright (C) LDO Motors
//###########################################################################

#ifndef HEADERS_SCI_H_
#define HEADERS_SCI_H_

#include "SysVar.h"

class SCI_Module
{
private:

	long dat;
	char i;

public:
	void Initialize(void);
	void SCITX(long data);
	long SCIRX(void);
};

#endif	/* HEADERS_SCI_H_ */

