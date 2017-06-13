#include "led.h"
#include "irq.h"
#include "key.h"
#include "utils.h"

void __irq Isr_Eint(void)
{
	Delay(20);                  /* 延时防抖 */
	if(EINT0PEND & 0x1)	
	{	    /* 是否是外部中断第0组0号位，即GPN0=>KEY1*/
		LEDAll_TurnOff();	
		LEDAny_TurnOn(1);	        /* KEY1按下，点亮LED1灯*/
		EINT_Clr0Pend(0);        /* 清除标识位，以便下次判断 */
	}
	else if(EINT0PEND & 0x2)
	{	/* 是否是外部中断第0组1号位，即GPN1=>KEY1*/
		LEDAll_TurnOff();
		LEDAny_TurnOn(2);			
		EINT_Clr0Pend(1);        /* 清除标识位，以便下次判断 */
	}
	else if(EINT0PEND & 0x4)
	{   /* 是否是外部中断第0组2号位，即GPN2=>KEY3*/
		LEDAll_TurnOff();	
		LEDAny_TurnOn(3);	
		EINT_Clr0Pend(2);        /* 清除标识位，以便下次判断 */
	}
	else if(EINT0PEND & 0x8)
	{   /* 是否是外部中断第0组3号位，即GPN3=>KEY4*/
		LEDAll_TurnOff();	
		LEDAny_TurnOn(4);
		EINT_Clr0Pend(3);        /* 清除标识位，以便下次判断 */
	}

	/* 清除中断函数地下备份寄存器，以便下次执行*/
	Outp32(rVIC0ADDR, 0);
	Outp32(rVIC1ADDR, 0);
}



/************************************************************************
函数名：Key_Init
功能  ：按键初始化
参数  ：无
返回值：无
注意  ：
************************************************************************/
void KEYS_Init(void)
{
	unsigned int value = 0;	

	value = GPNCON;       /* 读取GPNCON原始值  */
	value &= ~(0xFF<<0);  /* 清除后8位以方便以下设置数值 */
	value |= 0xAA<<0;     /* 将后8位每两位设置为10，即GPN0至GPN3配置为外部中断 */
	GPNCON = value;       /* 将GPNCON写回寄存器，配置生效 */
	
	EINT_Clr0Pend(0); /* 清除0组0号中断标识位，即GPN0*/
	EINT_Clr0Pend(1); /* 清除0组1号中断标识位，即GPN1*/
	EINT_Clr0Pend(2); /* 清除0组2号中断标识位，即GPN2*/
	EINT_Clr0Pend(3); /* 清除0组3号中断标识位，即GPN3*/

	EINT_Dis0Mask(0); /* 解除0组0号外部中断屏蔽，即打开GPN0中断 */
	EINT_Dis0Mask(1); /* 解除0组1号外部中断屏蔽，即打开GPN1中断 */
	EINT_Dis0Mask(2); /* 解除0组2号外部中断屏蔽，即打开GPN2中断 */
	EINT_Dis0Mask(3); /* 解除0组3号外部中断屏蔽，即打开GPN3中断 */

	/* 注册0号中断的处理函数 */
	INTC_SetISR(0, Isr_Eint);//vic0vectaddr0=adrress(Isr_Eint)
	INTC_Enable(0);  /* 使能0号中断 */
}








