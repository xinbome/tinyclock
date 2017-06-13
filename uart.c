#include <stdarg.h>
#include <stdio.h>

#include "uart.h"

/************************************************************************
函数名：Uart_Init
功能  ：串口引脚及波特率的初始化
参数  ：无
返回值：无
注意  ：
************************************************************************/
void UART_Init(void)
{
	/* GPA0->RXD[0]   GPA1->TXD[0]; */
	GPACON &= ~(0xFF<<0);
	GPACON |= 0x22<<0;

	/* normal mode operation,No parity,One stop bit per frame */
	ULCON0 &= ~(0x3<<0);
	ULCON0 |= (0x3<<0);

	UCON0  &= ~(0xF<<0);
	UCON0  |= (1<<2)|(1<<0);

	/* 波特率 
		DIV_VAL=(PCLK/(bps x 16))-1
		DIV_VAL =(66500000/(115200x16))-1
				=35.08
	*/
	UBRDIV0 = 35;
	
	/*  x/16 = 0.08
		x=1   =>   UDIVSLOT0 0x80
	*/	
	UDIVSLOT0 = 0x80;

}


/************************************************************************
 函数名：Uart_SendByte
功能  ：向串口发送一个字节的数据
参数  ：data：要发送的数据
返回值：无
注意  ：
************************************************************************/
void UART_SendByte(int data)
{
	//if UTRSTAT0.1==1,means that the transmit buffer register is empty
	while(!(UTRSTAT0 & 0x2));
	{
		UTXH0 = data;
	}
}

/************************************************************************
函数名：Uart_SendString
功能  ：向串口发送一个字符串
参数  ：*p ：字符串首地址
返回值：无
注意  ：
************************************************************************/
void UART_SendString(char *p)
{
	while(*p)
	{
		UART_SendByte(*p++);
	}
}

/************************************************************************
函数名：Uart_GetCh
功能  ：从串口中接受一个字节的数据，等待到串口有数据
参数  ：无
返回值：接收到的数据
注意  ：
************************************************************************/
char UART_GetCh(void)//Get Char
{
	//if UTRSTAT0.0==1，means that the recrive buffer register contains the value date,we can read it already
	while(!(UTRSTAT0 & 0x1))
		;

	return URXH0;
}

/************************************************************************
函数名：Uart_GetKey
功能  ：与Uart_GetCh相比，这个函数的实时性高，当串口没数据的时候，并不会等待
参数  ：无
返回值：0:失败   非0：成功
注意  ：
************************************************************************/
char UART_GetKey(void)
{
	if(UTRSTAT0 & 0x1)
		return URXH0;
	return 0;
}

/************************************************************************
函数名：Uart_Printf
功能  ：跟printf函数功能类似
参数  ：*fmt：格式    ...:不定参数
返回值：字符串指针
注意  ：va_list等宏定义在stdarg.h，vsprintf定义在stdio.h中
************************************************************************/
void UART_Printf(char *fmt,...)
{
	va_list ap;
	char string[256];
	va_start(ap,fmt);//获取可变参数的第一个参数的地址，保存到ap中
	vsprintf(string,fmt,ap);
	UART_SendString(string);
	va_end(ap);//清空va_list可变参数列表
}
