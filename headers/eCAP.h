//###########################################################################
// eCAP.h
// About eCAP module
//
// $Copyright: Copyright (C) LDO Motors
//###########################################################################

#ifndef HEADERS_ECAP_H_
#define HEADERS_ECAP_H_

#include "SysVar.h"
#include "LowPassFilter.h"
#include "Sci.h"

#define eCAP_ACK()					\
	ECap1Regs.ECCLR.bit.CEVT1 = 1;	\
	ECap1Regs.ECCLR.bit.INT = 1;	\
	ECap1Regs.ECCTL2.bit.REARM = 1;	\
	PieCtrlRegs.PIEACK.bit.ACK4 = 1;

#define PIE_eCAP_CNT()					\
	EALLOW;								\
	PieVectTable.ECAP1_INT = &eCAP_CNT;	\
	EDIS;								\

#define PIE_eCAP_ISR()					\
	EALLOW;								\
	PieVectTable.ECAP1_INT = &eCAP_ISR;	\
	EDIS;								\

#define EncoderError 0xFFFF

class eCAP_Module
{
private:
	Uint32 period;
	Uint32 limit_H;
	Uint32 limit_L;
	LowPassFilter LP;
	SCI_Module sci;
	static eCAP_Module instance;

public:

	eCAP_Module();
	static eCAP_Module *Instance();

	void eCAP_Init(void);
	static __interrupt void eCAP_CNT(void);
	static __interrupt void eCAP_ISR(void);
};


#endif /* HEADERS_ECAP_H_ */
