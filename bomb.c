#include "bomb.h"
#include "utils.h"


void init()
{
	GPFCON = GPFCON & (~(0x1 << (29)));//29λ0������1 GPF14
	GPFCON = GPFCON|(0x1 <<(2*14));//28λ1,01��ʾ���
	GPFPUD = GPFPUD & (~(0x3 << (2*14)));
	GPFDAT &= ~(0x1<<14);	
}

void bombon()
{
	//������һ�£�������������ֱ��GPFDAT |= 0x1<<14�����ԼĴ���������������������	
    unsigned int value = 0;	
	value = GPFDAT;     
	/*��GPFDAT��4��λ��1�����ƶ�����ߵ�ƽBEE*/
	value |= 0x1<<14;
	GPFDAT = value;	   
}

void bomboff()
{	
 	unsigned int value = 0;
	value = GPFDAT;     
	/*��GPFDAT��4��λ�����Ϊ�㣬GPF14����͵�ƽ*/
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
