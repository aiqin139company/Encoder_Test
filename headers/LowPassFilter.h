//###########################################################################
// LowPassFilter.h
//
// $Copyright: Copyright (C) LDO Motors
//###########################################################################

#ifndef HEADERS_LOWPASSFILTER_H_
#define HEADERS_LOWPASSFILTER_H_

#include "Encoder_Test.h"
#include "IQMathLib.h"

typedef struct LowPass
{
	_iq a0;			// a0 = 1 - f
	_iq b1;         // b1 = f
	_iq In;   		// Input
	_iq prevIn;   	// previous input
	_iq Out;   		// Output
}LowPassFilter;

void LowPass_Params(LowPassFilter *v, _iq x);
void LowPass(LowPassFilter *v);

#endif /* HEADERS_LOWPASSFILTER_H_ */
