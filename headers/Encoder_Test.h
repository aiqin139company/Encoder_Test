/*
 * SysVar.h
 *
 *  Created on: 2016Äê6ÔÂ30ÈÕ
 *      Author: Admin
 */

#ifndef HEADERS_ENCODER_TEST_H_
#define HEADERS_ENCODER_TEST_H_

#include "Sci.h"
#include "LowPassfilter.h"
#include "eCAP.h"
#include "Motor.h"
#include "IQmathLib.h"

class Encoder
{
private:
	//Members
	long flag;
	char epwm;

	SCI_Module sci;
	Motor_Module motor;
	eCAP_Module eCAP;

public:

	static Encoder encoder;

	void Encoder_Init(void);
	void Encoder_Execute(void);
};



#endif /* HEADERS_ENCODER_TEST_H_ */
