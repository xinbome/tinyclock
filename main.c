#include "led.h"
#include "bomb.h"
#include "key.h"
#include "irq.h"
#include "sys.h"
#include "uart.h"
#include "sysc.h"
#include "rtc.h"
#include "lcd.h"
#include "pic.h"
#include "utils.h"


/* ����ͼƬ����,�Է������� */
const unsigned char *gImages[]={
	gImage_black0,
	gImage_black1,
	gImage_black2,
	gImage_black3,
	gImage_black4,
	gImage_black5,
	gImage_black6,
	gImage_black7,	
	gImage_black8,
	gImage_black9
};




/* g_PCLK = 66500000; */

int main(void){

	//char c = 0;	
	int i = 0;		
	SYSC_GetClkInform();
		
	UART_Init();
	
	//UART_Printf("TEST:%ld\r\n", g_PCLK);
	
	write_open();
	//set_sec(0);
	//set_min(6);
	//set_hour(23);
	//set_day(3);
	//set_date(13);
	//set_month(6);
	set_year(2017);
	write_close();
	time_printf();
	
	/*while(1)
	{
		//key_test();
		time_printf();	
		c = UART_GetCh();
		UART_SendByte( (int)c );
	}*/
	
	
	LCD_Init();
	
	/* ������Ļ��ɫ */
	LCD_ClearScreen(0xffff);	
	
	/* ѭ�� */
	while(1){
	
		/* 0~10ѭ������ */
		if(i>=10){
			i = 0;
		}
		
		/* ���Ƽ�����Ӧ������ͼƬ */
		Paint_Bmp(56, 40, 83, 128, gImages[i]);
		i++;
		
		/* ��ʱ */
		Delay(100000);		
	}	
}


