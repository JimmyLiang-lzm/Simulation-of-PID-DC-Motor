//PID控制代码
//参考资料: https://zhuanlan.zhihu.com/p/84767869

#define T 1
#define kp 1
#define Td 1
#define Ti 1

int 
	Error,Error_last,                            
	Integral_Error,Differential_Error,           
	Proportion_OUT,Integral_OUT,Differential_OUT,
	T,Ti,Td,                                     
        PID_OUT;                               

float 
	Kp,Ki,Kd;

int PID_Controller(float Target,float Feedback)
{
	ki = kp*T*(1/Ti);
	kd = kp*Td*(1/T);
	
	Error = Target - Feedback;
	Integral_Error = Integral_Error + Error;
	Differential_Error = Error - Error_last;
	
	Proportion_OUT = kp * Error;
	Integral_OUT = ki * Integral_Error;
	Differential_OUT = kd * Differential_Error;
	
	PID_OUT = Proportion_OUT + Integral_OUT + Differential_OUT;
	
	return PID_OUT;
}
	
