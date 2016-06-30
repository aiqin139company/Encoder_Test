//###########################################################################
// LowPassFilter.c
//
// $Copyright: Copyright (C) LDO Motors
//###########################################################################

#include "LowPassfilter.h"

///Setting
void LowPass_Params(LowPassFilter *v, _iq x)
{
	v->a0 = _IQ(1) - x;
	v->b1 = x;
	v->In = 0;   		// Input
	v->prevIn = 0;   	// previous input
	v->Out = 0;   		// Output
}


///LowPass filter
void LowPass(LowPassFilter *v)
{
	v->Out = _IQmpy(v->a0, v->In) + _IQmpy(v->b1, v->prevIn);
	v->prevIn = v->Out;
}


