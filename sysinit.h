// Header for AT89C52 Motor Control System Initialization
/*
Information of AT89C52 hardware
Crystal frequency: 12MHZ
Use Interrupt: INT0
Use Port: P0,P1,P2,P3
Internal Timer: TMOD => T0
Internal Timer Working Model: 
	16-bit Timer, Control by TRx.
RST: Enable
PSEN: Disable
ALE: Disable
EA: Disable
*/

/*	Header of Address Definition	*/
#include<reg51.h>

/*	Timer Setting	*/
#ifndef THC0
#define THC0 0xF9
#endif
#ifndef TLC0
#define TLC0 0x0F
#endif

/*	Definition of Function	*/
void sysInit();
