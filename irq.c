#include "irq.h"
#include "utils.h"

/*******************************************************
函数名：INTC_Enable
功能  ：使能某一中断
参数  ：int_num:中断源号
返回值：无
注意  ：
********************************************************/
void INTC_Enable(unsigned int intNum)
{
	unsigned int temp = 0;

	/* 0~32号中断由VIC0设置 */
	if(intNum<32){
		temp = Inp32(rVIC0INTENABLE);    /* 读取VIC0INTENABLE原始值 */
		temp |= (1<<intNum);             /* 将相应设置为1，使能中断 */
		Outp32(rVIC0INTENABLE, temp);    /* 写回VIC0INTENABLE值，设置生效*/
	}
	/* 32~64号中断由VIC1设置 */
	else if(intNum > 32 && intNum < 63){
		temp = Inp32(rVIC1INTENABLE);   /* 读取VIC1INTENABLE原始值 */
		temp |= (1<<(intNum-32));       /* 将相应设置为1，使能中断 */
		Outp32(rVIC1INTENABLE, temp);   /* 写回VIC0INTENABLE值，设置生效*/
	}

	return;
}


/*******************************************************
函数名：INTC_SetIntISR
功能  ：设置某一个中断源的ISR地址
参数  ：intNum：中断源号   (*isr)(void) __irq；指向中断处理函数的函数指针
返回值：无
注意  ：中断源号最大为63
********************************************************/
void INTC_SetISR(unsigned int intNum, void (*isr)(void) __irq)
{
    /* 0~32号中断由VIC0设置 */
    if(intNum < 32){
		/* 将函数地址写入中断号对应位置 */
        Outp32(rVIC0VECTADDR + 4*intNum, (unsigned)isr);
    }
	/* 32~64号中断由VIC1设置 */
    else if(intNum > 32 && intNum < 63){
        /* 将函数地址写入中断号对应位置 */
		Outp32(rVIC1VECTADDR + 4*(intNum-32), (unsigned)isr);
    }
}


/************************************************************************
函数名：Eint_Clr0Pend
功能  ：清除中断悬起位，方法是向对应位写1
参数  ：uEINT_No：中断索引号
返回值：无
注意  ：
************************************************************************/
void EINT_Clr0Pend(unsigned int uEINT_No ){
	unsigned int value = 0;
	value  = EINT0PEND;       /* 读取EINT0MASK寄存器原始值   */
	value |= 0x1<<uEINT_No;   /* 向对应位写1，实现清标识清除 */
	EINT0PEND = value;        /* 写回EINT0MASK值，设置生效   */
}

/************************************************************************
函数名：Eint_Dis0Mask
功能  ：除能Eint[27:0]中断屏蔽位
参数  ：uEINT_No：中断索引号
返回值：无
注意  ：
************************************************************************/
void EINT_Dis0Mask(unsigned int uEINT_No ){
	unsigned int value = 0;
	
	value = EINT0MASK;          /* 读取EINT0MASK寄存器原始值 */
	value &= ~(0x1<<uEINT_No);  /* 将对应位清为0，解除屏蔽   */
	EINT0MASK = value;          /* 写回EINT0MASK值，设置生效 */
}

