#include "led.h"

void LED1_TurnOn(void)
{
	//GPKDAT = 0XFFEF;
	int value = 0;
	value = GPKDAT;
	value &= ~(0x1 <<4);
	GPKDAT = value;	
}

void LED4_TurnOn(void)
{
	//GPKDAT = 0XFF7F;
	int value = 0;
	value = GPKDAT;
	value &= ~(0x1 <<7);
	GPKDAT = value;		
}


void LEDAll_Init(void)
{
	
	//GPKCON0 = 0x11112222;
	//����GPK4/5/6/7/Ϊ���
	unsigned int value = 0;
	value &= ~(0xFFFF << 16);//��[16:31]λ���Ϊ0
	value |= 0x1111 << 16;//ÿ��λ��1
	GPKCON0 = value;	
	
}


void LEDAll_TurnOn(void)
{
	
	//GPKDAT = 0xFF0F;
	//���е���
	int value = 0;
	value = GPKDAT;
	value &= ~(0xF <<4);
	GPKDAT = value;
}


void LEDAll_TurnOff(void)
{
	
	//GPKDAT = 0xFFFF;
	//���е�Ϩ��
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












































