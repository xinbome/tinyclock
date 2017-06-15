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

/* 定义第三栏图片数组*/
const unsigned char *ThirdImages[]={
	gImage_thirdcolor0,
	gImage_thirdcolor1,
	gImage_thirdcolor2,
	gImage_thirdcolor3,
	gImage_thirdcolor4,
	gImage_thirdcolor5,
	gImage_thirdcolor6,
	gImage_thirdcolor7,
	gImage_thirdcolor8,
	gImage_thirdcolor9,
	gImage_thirdnao,
	gImage_thirdzhong	
};




/* g_PCLK = 66500000; */

int main(void){

	//char c = 0;	
	//int i = 0;
	//long a,b,c,d,e,f = 0;
	long hour,minute = 0;
	long uyear = BCD_to_DEC(BCDYEAR); 
	long umonth =  BCD_to_DEC(BCDMON);
	long udate =  BCD_to_DEC(BCDDATE);
	long uhour =  BCD_to_DEC(BCDHOUR);
	long uminute =  BCD_to_DEC(BCDMIN);
	long usec =  BCD_to_DEC(BCDSEC);	
	hour = 18;
	minute = 4; 
			
	//int flag = 0;
	SYSC_GetClkInform();
		
	UART_Init();
	
	//UART_Printf("TEST:%ld\r\n", g_PCLK);
	
	write_open();

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
	
		key_init();
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
		Paint_Bmp(24, 380, 80, 80, 	ThirdImages[10]);
		Paint_Bmp(128, 380, 80, 80, ThirdImages[11]);
		//Paint_Bmp(232, 140, 80, 200, gImages[2]);
		Paint_Bmp(306, 380, 80, 80, ThirdImages[hour/10]);
		Paint_Bmp(410, 380, 80, 80, ThirdImages[hour%10]);
		Paint_Bmp(514, 380, 50, 80, BigImages[10]);
		Paint_Bmp(588, 380, 80, 80, ThirdImages[minute/10]);						
		Paint_Bmp(692, 380, 80, 80, ThirdImages[minute%10]);
		
		
		
		//1键位增加系统时间分钟，2键位减少系统时间分钟
		if(key_test() == 1)
		{
			uminute++;
			if(uminute == 60)
			{
				uhour++;
				uminute = 0;
				if(uhour == 24)
				{
					uhour = 0;
					//udate++;这里有个bug,每个月天数都不一样，我晚上写个详细的算法来更改日期
				}
			}
		}
			
		
		
		if(key_test() == 2)
		{
			uminute--;
			if(uminute == -1)
			{
				uhour--;
				uminute = 59;
				if(uhour == 0)
				{
					uhour = 23;
					//udate--;这里还缺一个详细的算法
				}
			}
		}	
			
		
		
		
		
		//3键位增加闹钟分钟，4键位减少闹钟分钟	
		if(key_test() == 3)
		{
			minute++;
			if(minute == 60)
			{
				hour++;
				minute = 0;
				if(hour == 24)
				{
					hour = 0;
				}
			}
		}
		
		if(key_test() == 4)
		{
			minute--;
			if(minute == -1)
			{
				hour--;
				minute = 59;
				if(hour == 0)
				{
					hour = 23;
				}
			}
		}
		
		
		
		write_open();//RTCCON[0]=1,开放写的权限

		set_min(uminute);

		set_hour(uhour);

		set_date(udate);

		set_month(umonth);


		set_year(uyear);


		write_close();//RTCCON[0]=0,关闭写的权限



		
		
		//这判断式也决定了只要一按键，闹钟就会不响，闹钟每次响也只会响1分钟
		if((minute == BCD_to_DEC(BCDMIN))&& (hour == BCD_to_DEC(BCDHOUR)))		
		{
			bomb();
	        //key_test();
		}
		
		//一二两号键同按,进入新界面	
		if(key_test() == -1)
		{
			LCD_ClearScreen(0xffff);		
			while(1)
			{
				if(key_test() != 0)
				{
					break;
				}
				
				Paint_Bmp(156, 200, 80, 80, ThirdImages[BCD_to_DEC(BCDHOUR)/10]);
				Paint_Bmp(260, 200, 80, 80, ThirdImages[BCD_to_DEC(BCDHOUR)%10]);
				Paint_Bmp(364, 200, 50, 80, BigImages[10]);
				Paint_Bmp(438, 200, 80, 80, ThirdImages[BCD_to_DEC(BCDMIN)/10]);						
				Paint_Bmp(542, 200, 80, 80, ThirdImages[BCD_to_DEC(BCDMIN)%10]);				
				
			}
			LCD_ClearScreen(0xffff);			
		}
		
		
		if(key_test() == -2)
		{
			LCD_ClearScreen(0xffff);		
			while(1)
			{
				if(key_test() != 0)
				{
					break;
				}
				
				//闹钟
				Paint_Bmp(24, 200, 80, 80, 	ThirdImages[10]);
				Paint_Bmp(128,200, 80, 80, ThirdImages[11]);
				//Paint_Bmp(232, 140, 80, 200, gImages[2]);
				Paint_Bmp(306,200, 80, 80, ThirdImages[hour/10]);
				Paint_Bmp(410,200, 80, 80, ThirdImages[hour%10]);
				Paint_Bmp(514,200, 50, 80, BigImages[10]);
				Paint_Bmp(588,200, 80, 80, ThirdImages[minute/10]);						
				Paint_Bmp(692,200, 80, 80, ThirdImages[minute%10]);
			}
			LCD_ClearScreen(0xffff);			
		}		
				
	
	}
	


}


