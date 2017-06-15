#include "bomb.h"
#include "utils.h"


void init()
{
	GPFCON = GPFCON & (~(0x1 << (29)));//29位0，其余1 GPF14
	GPFCON = GPFCON|(0x1 <<(2*14));//28位1,01表示输出
	GPFPUD = GPFPUD & (~(0x3 << (2*14)));
	GPFDAT &= ~(0x1<<14);	
}

void bombon()
{
	//尝试了一下，如果这里和下面直接GPFDAT |= 0x1<<14这样对寄存器操作，蜂鸣器不会响	
    unsigned int value = 0;	
	value = GPFDAT;     
	/*将GPFDAT的4号位设1，控制端输出高电平BEE*/
	value |= 0x1<<14;
	GPFDAT = value;	   
}

void bomboff()
{	
 	unsigned int value = 0;
	value = GPFDAT;     
	/*将GPFDAT的4号位设清空为零，GPF14输出低电平*/
	value &= ~(0x1 << 14);
	GPFDAT = value;	   
}

void bomb()
{
	init();		
	bombon();
	Delay(5000);	
	bomboff();

}
