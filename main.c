//Main Program for Motor Control System
/*本程序涉及晶振频率为12MHZ,如果使用其他晶振频率则需要更改定时器频率*/

#include<reg51.h>
#include<stdio.h>
#include<sysinit.h>

#define uchar unsigned char
#define uint unsigned int
#define MAX_RPM 256
#define kp 7
#define kd 14
#define ki 1

/*	电机正反转控制端	*/
sbit IN1 = P3^0;
sbit IN2 = P3^1;

/*	电机运转端	*/
sbit PWM_CL = P3^3;

/*	电机控按钮定义	*/
sbit ON_OFF = P3^4;						//电机运转/停止按钮
sbit UP = P3^5;								//电机加速
sbit DOWN = P3^6;							//电机减速
sbit CPL = P3^7;							//电机正反转

float 
	Error,Error_last,                            
	Integral_Error,Differential_Error,           
	Proportion_OUT,Integral_OUT,Differential_OUT;
int
  PID_OUT;                               

int CPLs = 1;									//正反转标志
int SpeedSet = 205;						//设定转速
uint Inpluse=0;
float SpeedCalc=0;						//脉冲计数
unsigned char code ByteCode[] = {0x3F, 0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};		//共阴极数码管0-9段码
unsigned char Num_Buffer[8] = {0,0,0,0,0,0,0,0};	//显示数据缓存
uint code Gear[6] = {10,20,30,40,50,60};


void delay(uchar x)
{
	uint i,j;
	for(i=x;i>0;i--)
	{
		for(j=50;j>0;j--);
	}
}

void setSpeed()
{
	if(DOWN==0)
	{
		delay(200);	//消抖
		if(DOWN==0)
		{
			SpeedSet+=10;
			if(SpeedSet>=254) SpeedSet = 254;
			while(DOWN==0);
		}
	}
	if(UP==0)
	{
		delay(200);
		if(UP==0)
		{
			SpeedSet-=10;
			if(SpeedSet<=1) SpeedSet = 1;
			while(UP==0);
		}
	}
	if(CPL==0)
	{
		delay(200);
		if(CPL==0)
		{
			if(CPLs==0)
			{
				CPLs = 1;
				IN1 = 1;
				IN2 = 0;
				while(CPL==0);
			}
			else if(CPLs==1)
			{
				CPLs = 0;
				IN1 = 0;
				IN2 = 1;
				while(CPL==0);
			}
		}
	}
	if(ON_OFF==0)
	{
		delay(200);
		if(ON_OFF==0)
		{
			if(PWM_CL==0)
			{
				PWM_CL = 1;
				IN1 = 1;
				IN2 = 1;
				while(ON_OFF==0);
			}
			else if(PWM_CL==1)
			{
				PWM_CL = 0;
				if(CPLs==0)
				{
					IN1 = 0;
					IN2 = 1;
				}
				else if(CPLs==1)
				{
					IN1 = 1;
					IN2 = 0;
				}
				while(ON_OFF==0);
			}
		}
	}
}

int PID_Controller(float Target,float Feedback)
{
	float out;
	Error = Target - Feedback;
	Integral_Error = Integral_Error + Error;
	Differential_Error = Error - Error_last;
	Error_last = Error;
	
	Proportion_OUT = kp * Error;
	Integral_OUT = ki * Integral_Error;
	Differential_OUT = kd * Differential_Error;
	
	out = Proportion_OUT + Integral_OUT + Differential_OUT;
	
//	PID_OUT = (int)(out+0.5);
	
	if(out<=5) out = 5;
	else if (out>=760) PID_OUT = 760;
	
	PID_OUT = (int)out;
	
	return PID_OUT;
}

void SegRefresh()
{
	int SS;
	SS = (int)3*(255-SpeedSet);
	Num_Buffer[0] = SS/1000;
	Num_Buffer[1] = SS%1000/100;
	Num_Buffer[2] = SS%100/10;
	Num_Buffer[3] = SS%10;
	Num_Buffer[4] = (int)SpeedCalc/1000;
	Num_Buffer[5] = (int)SpeedCalc%1000/100;
	Num_Buffer[6] = (int)SpeedCalc%100/10;
	Num_Buffer[7] = (int)SpeedCalc%10;
}


void main()
{
	sysInit();
	while(1)
	{
		setSpeed();		//按键设定速度
		SegRefresh();
	}
}

void int0() interrupt 0
{
	Inpluse++;			//采集脉冲信号
}

void t0() interrupt 1
{
	static unsigned char Bit=0;
	static unsigned int time=0;
	TH0 = THC0;
	TL0 = TLC0;
	
	Bit++;
	time++;			//转速测量周期
	if(Bit>=8) Bit=0;
	P0 = 0xff;
	P2 = ByteCode[Num_Buffer[Bit]];		//显示段码
	switch(Bit)
	{
		case 0:P0=0x7f;break;
		case 1:P0=0xbf;break;
		case 2:P0=0xdf;break;
		case 3:P0=0xef;break;
		case 4:P0=0xf7;break;
		case 5:P0=0xfb;break;
		case 6:P0=0xfd;break;
		case 7:P0=0xfe;break;
	}
	if(time>100)
	{
		time = 0;
		SpeedCalc = Inpluse;
		Inpluse = 0;
//		P1 = 255-(PID_Controller((255-SpeedSet)*3,SpeedCalc))/3;
		P1 = 255-PID_Controller((255-SpeedSet),SpeedCalc/3);
	}
}
