//###########################################################################
// Sci.c
// About Sci Module
//
// $Copyright: Copyright (C) LDO Motors
//###########################################################################
#include "Sci.h"

///SCI_MODULE Initialize
void Sci_Init(void)
{
	/* Configure SCI-A pins MUX*/
	EALLOW;
	GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;     // Enable pull-up for GPIO28  (SCIRXDA)
	GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;
	GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3;   // Asynch input GPIO28 (SCIRXDA)
	GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1;
	GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 1;
	EDIS;

	/* scia_fifo_init */
    EALLOW;
	SciaRegs.SCIFFTX.all=0xE040;
    SciaRegs.SCIFFRX.all=0x2044;
    SciaRegs.SCIFFCT.all=0x0;

	SciaRegs.SCICCR.all =0x0007;   // 1 stop bit,  No loopback
								   // No parity,8 char bits,
								   // async mode, idle-line protocol
	SciaRegs.SCICTL1.all =0x0003;  // enable TX, RX, internal SCICLK,
								   // Disable RX ERR, SLEEP, TXWAKE
	SciaRegs.SCICTL2.all =0x0003;
	SciaRegs.SCICTL2.bit.RXBKINTENA =1;
	SciaRegs.SCIHBAUD    =0x0000;
	SciaRegs.SCILBAUD    =0x0007;
	SciaRegs.SCICTL1.all =0x0023;     // Relinquish SCI from Reset
	EDIS;
}

///TX function
void SCITX(long data)
{
	char i = 0;

	for ( i = 4; i > 0; i -- )
	{
		while( 4 == SciaRegs.SCIFFTX.bit.TXFFST ){}		//waitting for if tx fifo has 4 words
		SciaRegs.SCITXBUF = data>>((i-1)*8);
	}
}

///RX function
long SCIRX(void)
{
	long dat = 0;
	char i;

	for (i = 0; i < 4; i++ )
	{
		while( 0 == SciaRegs.SCIFFRX.bit.RXFFST ){}		//waitting for rx
		dat += (long)( SciaRegs.SCIRXBUF.all ) << i*8;
	}

	return dat;
}
