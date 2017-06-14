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


/* 定义图片数组,以方便引用 */
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
	//int i = 0;		
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
	
	/* 绘制屏幕底色 */
	LCD_ClearScreen(0xffff);
	
	
	Paint_Bmp(20, 20, 51, 80, gImages[0]);
	Paint_Bmp(91, 20, 51, 80, gImages[1]);	
	Paint_Bmp(162,20, 51, 80, gImages[2]);
	Paint_Bmp(233,20, 51, 80, gImages[3]);	
	Paint_Bmp(304,20, 51, 80, gImages[4]);	
	Paint_Bmp(375,20, 51, 80, gImages[5]);	
	Paint_Bmp(446,20, 51, 80, gImages[6]);	
	Paint_Bmp(517,20, 51, 80, gImages[7]);		
	Paint_Bmp(588,20, 51, 80, gImages[8]);			
	Paint_Bmp(659,20, 51, 80, gImages[9]);			
	Paint_Bmp(730,20, 51, 80, gImages[9]);						
	while(1)
	{
   	//Paint_Bmp(56, 168, 83, 128, gImages[4]);	
   	;	
	}	
		
	
}


