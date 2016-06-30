/*
 * common.h
 *
 *  Created on: 2016��6��22��
 *      Author: Admin
 */

#ifndef HEADERS_ENCODER_TEST_H_
#define HEADERS_ENCODER_TEST_H_

#include "DSP2803x_Device.h"
#include "DSP2803x_Examples.h"
#include "eCAP.h"
#include "ePWM.h"
#include "Sci.h"
#include "LowPassfilter.h"
#include "Motor.h"

// These are defined by the linker
extern Uint16 RamfuncsLoadStart;
extern Uint16 RamfuncsLoadSize;
extern Uint16 RamfuncsRunStart;

void System_Init(void);
void Interrupt_Enable(void);
void Hardware_Module_Init(void);

#endif /* HEADERS_ENCODER_TEST_H_ */
