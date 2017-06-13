#include "irq.h"
#include "utils.h"

/*******************************************************
��������INTC_Enable
����  ��ʹ��ĳһ�ж�
����  ��int_num:�ж�Դ��
����ֵ����
ע��  ��
********************************************************/
void INTC_Enable(unsigned int intNum)
{
	unsigned int temp = 0;

	/* 0~32���ж���VIC0���� */
	if(intNum<32){
		temp = Inp32(rVIC0INTENABLE);    /* ��ȡVIC0INTENABLEԭʼֵ */
		temp |= (1<<intNum);             /* ����Ӧ����Ϊ1��ʹ���ж� */
		Outp32(rVIC0INTENABLE, temp);    /* д��VIC0INTENABLEֵ��������Ч*/
	}
	/* 32~64���ж���VIC1���� */
	else if(intNum > 32 && intNum < 63){
		temp = Inp32(rVIC1INTENABLE);   /* ��ȡVIC1INTENABLEԭʼֵ */
		temp |= (1<<(intNum-32));       /* ����Ӧ����Ϊ1��ʹ���ж� */
		Outp32(rVIC1INTENABLE, temp);   /* д��VIC0INTENABLEֵ��������Ч*/
	}

	return;
}


/*******************************************************
��������INTC_SetIntISR
����  ������ĳһ���ж�Դ��ISR��ַ
����  ��intNum���ж�Դ��   (*isr)(void) __irq��ָ���жϴ������ĺ���ָ��
����ֵ����
ע��  ���ж�Դ�����Ϊ63
********************************************************/
void INTC_SetISR(unsigned int intNum, void (*isr)(void) __irq)
{
    /* 0~32���ж���VIC0���� */
    if(intNum < 32){
		/* ��������ַд���жϺŶ�Ӧλ�� */
        Outp32(rVIC0VECTADDR + 4*intNum, (unsigned)isr);
    }
	/* 32~64���ж���VIC1���� */
    else if(intNum > 32 && intNum < 63){
        /* ��������ַд���жϺŶ�Ӧλ�� */
		Outp32(rVIC1VECTADDR + 4*(intNum-32), (unsigned)isr);
    }
}


/************************************************************************
��������Eint_Clr0Pend
����  ������ж�����λ�����������Ӧλд1
����  ��uEINT_No���ж�������
����ֵ����
ע��  ��
************************************************************************/
void EINT_Clr0Pend(unsigned int uEINT_No ){
	unsigned int value = 0;
	value  = EINT0PEND;       /* ��ȡEINT0MASK�Ĵ���ԭʼֵ   */
	value |= 0x1<<uEINT_No;   /* ���Ӧλд1��ʵ�����ʶ��� */
	EINT0PEND = value;        /* д��EINT0MASKֵ��������Ч   */
}

/************************************************************************
��������Eint_Dis0Mask
����  ������Eint[27:0]�ж�����λ
����  ��uEINT_No���ж�������
����ֵ����
ע��  ��
************************************************************************/
void EINT_Dis0Mask(unsigned int uEINT_No ){
	unsigned int value = 0;
	
	value = EINT0MASK;          /* ��ȡEINT0MASK�Ĵ���ԭʼֵ */
	value &= ~(0x1<<uEINT_No);  /* ����Ӧλ��Ϊ0���������   */
	EINT0MASK = value;          /* д��EINT0MASKֵ��������Ч */
}

