/*
 * LowPassFilter.c
 *
 *  Created on: 2016Äê6ÔÂ29ÈÕ
 *      Author: Admin
 */
#include "LowPassfilter.h"

///Setting
void LowPass_Params(LowPassFilter *v, _iq x)
{
	v->a0 = _IQ(1) - x;
	v->b1 = x;
}


///LowPass filter
void LowPass(LowPassFilter *v)
{
	v->Out = _IQmpy(v->a0, v->In) + _IQmpy(v->b1, v->prevIn);
	v->prevIn = v->Out;
}

