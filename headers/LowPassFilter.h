//###########################################################################
// LowPassFilter.h
//
// $Copyright: Copyright (C) LDO Motors
//###########################################################################

#ifndef HEADERS_LOWPASSFILTER_H_
#define HEADERS_LOWPASSFILTER_H_

#include "Encoder_Test.h"
#include "IQmathLib.h"

typedef struct LowPass
{
	_iq a0;			// a0 = 1 - f
	_iq b1;         // b1 = f
	_iq In;   		// Input
	_iq prevIn;   	// previous input
	_iq Out;   		// Output
}LowPassFilter;

///Setting
#define LowPass_Params(v,x)	\
{							\
	v.a0 = _IQ(1) - x;		\
	v.b1 = x;				\
	v.In = 0;   			\
	v.prevIn = 0;   		\
	v.Out = 0;   			\
}

///LowPass_Reinit
#define LowPass_Reinit(v) 	\
{							\
	v.In = 0;				\
	v.prevIn = 0;			\
	v.Out = 0;				\
}

///LowPass filter
#define LowPass(v)											\
{															\
	v.Out = _IQmpy(v.a0, v.In) + _IQmpy(v.b1, v.prevIn);	\
	v.prevIn = v.Out;										\
}

#endif /* HEADERS_LOWPASSFILTER_H_ */
