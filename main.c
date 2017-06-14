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


/* 定义第一栏图片数组,以方便引用 */
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
	gImage_black9,
    gImage_blackyear,
	gImage_blackmon,
	gImage_blackday	
};


/* 定义第二栏图片数组*/
const unsigned char *BigImages[]={
	gImage_bigblack0,
	gImage_bigblack1,
	gImage_bigblack2,
	gImage_bigblack3,
	gImage_bigblack4,
	gImage_bigblack5,
	gImage_bigblack6,
	gImage_bigblack7,	
	gImage_bigblack8,
	gImage_bigblack9,
    gImage_tag	
};



/* g_PCLK = 66500000; */

int main(void){

	//char c = 0;	
	//int i = 0;
	//long a,b,c,d,e,f = 0;
	//long dec_year,dec_mon_,dec_day,dec_hour;	
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
	//set_year(2017);
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
	
	
	while(1)
	{
	

	//年月日第一栏

	Paint_Bmp(20, 20, 51, 80, gImages[2]);
	Paint_Bmp(91, 20, 51, 80, gImages[0]);	
	Paint_Bmp(162,20, 51, 80, gImages[BCD_to_DEC(BCDYEAR)/10]);
	Paint_Bmp(233,20, 51, 80, gImages[BCD_to_DEC(BCDYEAR)%10]);	
	Paint_Bmp(304,20, 51, 80, gImages[10]);	
	Paint_Bmp(375,20, 51, 80, gImages[BCD_to_DEC(BCDMON)/10]);	
	Paint_Bmp(446,20, 51, 80, gImages[BCD_to_DEC(BCDMON)%10]);	
	Paint_Bmp(517,20, 51, 80, gImages[11]);		
	Paint_Bmp(588,20, 51, 80, gImages[BCD_to_DEC(BCDDATE)/10]);			
	Paint_Bmp(659,20, 51, 80, gImages[BCD_to_DEC(BCDDATE)%10]);			
	Paint_Bmp(730,20, 51, 80, gImages[12]);
		
	
	//时分秒
	Paint_Bmp(24, 140, 80, 200, BigImages[BCD_to_DEC(BCDHOUR)/10]);
	Paint_Bmp(128,140, 80, 200, BigImages[BCD_to_DEC(BCDHOUR)%10]);	
	Paint_Bmp(232,200, 50, 80, BigImages[10]);
	Paint_Bmp(306,140, 80, 200, BigImages[BCD_to_DEC(BCDMIN)/10]);	
	Paint_Bmp(410,140, 80, 200, BigImages[BCD_to_DEC(BCDMIN)%10]);	
	Paint_Bmp(514,200, 50, 80, BigImages[10]);	
	Paint_Bmp(588,140, 80, 200, BigImages[BCD_to_DEC(BCDSEC)/10]);	
	Paint_Bmp(692,140, 80, 200, BigImages[BCD_to_DEC(BCDSEC)%10]);


	
	//闹钟
	Paint_Bmp(24, 380, 80, 80, gImages[2]);
	Paint_Bmp(128, 380, 80, 80, gImages[2]);
	//Paint_Bmp(232, 140, 80, 200, gImages[2]);
	Paint_Bmp(306, 380, 80, 80, gImages[2]);
	Paint_Bmp(410, 380, 80, 80, gImages[2]);
	Paint_Bmp(514, 380, 50, 80, gImages[2]);
	Paint_Bmp(588, 380, 80, 80, gImages[2]);						
	Paint_Bmp(692, 380, 80, 80, gImages[2]);		
						
	}

	
		
	
}


