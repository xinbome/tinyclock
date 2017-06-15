#include "led.h"

void LED1_TurnOn(void)
{
	int value = 0;
	value = GPKDAT;
	value &= ~(0x1 <<4);
	GPKDAT = value;	
}

void LED4_TurnOn(void)
{
	int value = 0;
	value = GPKDAT;
	value &= ~(0x1 <<7);
	GPKDAT = value;		
}


void LEDAll_Init(void)
{
	
	//配置GPK4/5/6/7/为输出
	unsigned int value = 0;
	value &= ~(0xFFFF << 16);//将[16:31]位清空为0
	value |= 0x1111 << 16;//每四位置1
	GPKCON0 = value;	
	
}


void LEDAll_TurnOn(void)
{
	
	//所有灯亮
	int value = 0;
	value = GPKDAT;
	value &= ~(0xF <<4);
	GPKDAT = value;
}


void LEDAll_TurnOff(void)
{
	
	//所有灯熄灭
	int value = 0;
	value = GPKDAT;
	value |= 0xF << 4;
	GPKDAT = value;
	
}



void LEDAny_TurnOn(int num)
{
	
	unsigned int value = 0;
	
	if(num < 1)
	{
		num = 1;
	}
	
	if(num > 4)
	{
		num = 4;
	}
	
	value = GPKDAT;
	
	value &= ~( 0x1<<(3+num));
	
	GPKDAT = value;
}



void LEDAny_TurnOff(int num)
{
	
	unsigned int value = 0;
	
	if(num < 1)
	{
		num = 1;
	}
	
	if(num > 4)
	{
		num = 4;
	}
	
	value = GPKDAT;
	
	value |=  0x1<<(3+num);
	
	GPKDAT = value;
}












































