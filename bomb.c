#include "bomb.h"



void msDelay(int time)
{
	
	volatile unsigned int i,j;
	for(i = 0;i < 20000;i++)
		for(j = 0;j < time;j++);
}



void init()
{
	GPFCON = GPFCON & (~(0x1 << (29)));//29位0，其余1 GPF14
	GPFCON = GPFCON|(0x1 <<(2*14));//28位1,01表示输出
	GPFPUD = GPFPUD & (~(0x3 << (2*14)));
	//GPFDAT = 0x0000;
	GPFDAT &= ~(0x1<<14);	
}

void bombon()
{
	
    unsigned int value = 0;	
	value = GPFDAT;     /*读取GPFCON0原值*/
	/*将GPFDAT的4号位设清空为零，GPF14输出低电平，BEE*/
	value |= 0x1<<14;
	GPFDAT = value;	   /*将修改后的值写回寄存器，使设置生效*/
}

void bomboff()
{	
 	unsigned int value = 0;
	value = GPFDAT;     /*读取GPFCON0原值*/
	/*将GPFDAT的4号位设清空为零，GPF14输出低电平，BEE*/
	value &= ~(0x1 << 14);
	GPFDAT = value;	   /*将修改后的值写回寄存器，使设置生效*/
}

void bomb()
{
		
	bombon();
	msDelay(10);	
	bomboff();
	bombon();
	msDelay(5);		
	bomboff();
	

}
