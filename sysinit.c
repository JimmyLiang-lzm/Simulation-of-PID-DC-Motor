//Code for AT89C51 Initialization

#include<reg51.h>
#include<sysinit.h>

/*
Timer calculating Formula:
Crystal Frequecy: CF;
Single Instruction Cycle Time: Tsm;
Setting Delay Time: Td;
Calculate Arrange(Based on Timer's Bit):
	[0,65535] => 16bit-Timer;
Tips: AT89C52 is 12 Machine Cycle time = 1 Instruction Period.
1MHZ = 10^6HZ
Formula:
	Tsm = 12/CF;
	M = Td/Tsm;
	Bs = 65536-M.
*/
/*
My Timer Set:
CF = 12MHZ;
Td = 14ms;
Timer Info: 16-bit Timer.
Result:
+------+-------+-----------+----------------+
|Title |Decimal|Hexadecimal|Binary          |
+------+-------+-----------+----------------+
|  Bs  | 51536 |   C950    |1100100101010000|
+------+-------+-----------+----------------+
*/

/*	Definition of Motor Rotation*/
sbit IN1 = P3^0;
sbit IN2 = P3^1;

void sysInit()
{
	/*	Timer/Couter Setting	*/
	TMOD = 0x01;
	/*	Setting T0 Timer (By Formula)	*/
	TH0 = THC0;
	TL0 = TLC0;
	/*	Interrupt Switch Enable	*/
	EA = 1;
	/*	Interrupt of Timer0 Enable	*/
	ET0 = 1;
	/*	Timer0 Enable	*/
	TR0 = 1;
	/*	External Interrupt Enable	*/
	EX0 = 1;
	/*	External Interrupt 0 Trigger Mode: High-Level Trigger	*/
	IT0 = 1;
	/*	Initialize Motor's Rotation	*/
	IN1 = 0;
	IN2 = 0;
}
