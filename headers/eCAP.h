//###########################################################################
// eCAP.h
// About eCAP module
//
// $Copyright: Copyright (C) LDO Motors
//###########################################################################

#ifndef HEADERS_ECAP_H_
#define HEADERS_ECAP_H_

#include "Encoder_Test.h"

#define COUNT 4000

#define eCAP_ACK()					\
	ECap1Regs.ECCLR.bit.CEVT1 = 1;	\
	ECap1Regs.ECCLR.bit.INT = 1;	\
	ECap1Regs.ECCTL2.bit.REARM = 1;	\
	PieCtrlRegs.PIEACK.bit.ACK4 = 1;

#define PIE_eCAP_CNT()					\
	EALLOW;								\
	PieVectTable.ECAP1_INT = &eCAP_CNT;	\
	EDIS;

#define PIE_eCAP_ISR()					\
	EALLOW;								\
	PieVectTable.ECAP1_INT = &eCAP_ISR;	\
	EDIS;

void eCAP_Init(void);
__interrupt void eCAP_CNT(void);
__interrupt void eCAP_ISR(void);

#endif /* HEADERS_ECAP_H_ */
