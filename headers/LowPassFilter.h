//###########################################################################
// LowPassFilter.h
//
// $Copyright: Copyright (C) LDO Motors
//###########################################################################

#ifndef HEADERS_LOWPASSFILTER_H_
#define HEADERS_LOWPASSFILTER_H_

#include "IQmathLib.h"
#include "SysVar.h"

//---------------------------------------------------------------------------
// Macros & Definitions
//
#define LOWPASS_MACRO(v)									\
															\
	v.Out = _IQmpy(v.a0, v.In) + _IQmpy(v.b1, v.prevIn);	\
	v.prevIn = v.Out;										\


//---------------------------------------------------------------------------
// Class definitions
//
class LowPassFilter
{
public:
	_iq a0;			// a0 = 1 - f
	_iq b1;         // b1 = f
	_iq In;   		// Input
	_iq prevIn;   	// previous input
	_iq Out;   		// Output

	LowPassFilter() :
		In(0),
		prevIn(0),
		Out(0)
	{}

	///Recalculates the a, b coefficients
	///x is the low pass filter constant obtained from e^(-2pi * fc)
	///where fc is the -3db cutoff frequency expressed as a fraction of the sampling rate
	void UpdateParams(_iq x)
	{
		a0 = _IQ(1) - x;
		b1 = x;
	}
};

#endif /* HEADERS_LOWPASSFILTER_H_ */
