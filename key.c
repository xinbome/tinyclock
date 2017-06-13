#include "led.h"
#include "irq.h"
#include "key.h"
#include "utils.h"

void __irq Isr_Eint(void)
{
	Delay(20);                  /* ��ʱ���� */
	if(EINT0PEND & 0x1)	
	{	    /* �Ƿ����ⲿ�жϵ�0��0��λ����GPN0=>KEY1*/
		LEDAll_TurnOff();	
		LEDAny_TurnOn(1);	        /* KEY1���£�����LED1��*/
		EINT_Clr0Pend(0);        /* �����ʶλ���Ա��´��ж� */
	}
	else if(EINT0PEND & 0x2)
	{	/* �Ƿ����ⲿ�жϵ�0��1��λ����GPN1=>KEY1*/
		LEDAll_TurnOff();
		LEDAny_TurnOn(2);			
		EINT_Clr0Pend(1);        /* �����ʶλ���Ա��´��ж� */
	}
	else if(EINT0PEND & 0x4)
	{   /* �Ƿ����ⲿ�жϵ�0��2��λ����GPN2=>KEY3*/
		LEDAll_TurnOff();	
		LEDAny_TurnOn(3);	
		EINT_Clr0Pend(2);        /* �����ʶλ���Ա��´��ж� */
	}
	else if(EINT0PEND & 0x8)
	{   /* �Ƿ����ⲿ�жϵ�0��3��λ����GPN3=>KEY4*/
		LEDAll_TurnOff();	
		LEDAny_TurnOn(4);
		EINT_Clr0Pend(3);        /* �����ʶλ���Ա��´��ж� */
	}

	/* ����жϺ������±��ݼĴ������Ա��´�ִ��*/
	Outp32(rVIC0ADDR, 0);
	Outp32(rVIC1ADDR, 0);
}



/************************************************************************
��������Key_Init
����  ��������ʼ��
����  ����
����ֵ����
ע��  ��
************************************************************************/
void KEYS_Init(void)
{
	unsigned int value = 0;	

	value = GPNCON;       /* ��ȡGPNCONԭʼֵ  */
	value &= ~(0xFF<<0);  /* �����8λ�Է�������������ֵ */
	value |= 0xAA<<0;     /* ����8λÿ��λ����Ϊ10����GPN0��GPN3����Ϊ�ⲿ�ж� */
	GPNCON = value;       /* ��GPNCONд�ؼĴ�����������Ч */
	
	EINT_Clr0Pend(0); /* ���0��0���жϱ�ʶλ����GPN0*/
	EINT_Clr0Pend(1); /* ���0��1���жϱ�ʶλ����GPN1*/
	EINT_Clr0Pend(2); /* ���0��2���жϱ�ʶλ����GPN2*/
	EINT_Clr0Pend(3); /* ���0��3���жϱ�ʶλ����GPN3*/

	EINT_Dis0Mask(0); /* ���0��0���ⲿ�ж����Σ�����GPN0�ж� */
	EINT_Dis0Mask(1); /* ���0��1���ⲿ�ж����Σ�����GPN1�ж� */
	EINT_Dis0Mask(2); /* ���0��2���ⲿ�ж����Σ�����GPN2�ж� */
	EINT_Dis0Mask(3); /* ���0��3���ⲿ�ж����Σ�����GPN3�ж� */

	/* ע��0���жϵĴ����� */
	INTC_SetISR(0, Isr_Eint);//vic0vectaddr0=adrress(Isr_Eint)
	INTC_Enable(0);  /* ʹ��0���ж� */
}








