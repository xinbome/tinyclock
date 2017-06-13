#include "led.h"
#include "bomb.h"
#include "key.h"
#include "irq.h"
#include "sys.h"
#include "uart.h"
#include "sysc.h"
#include "rtc.h"


/* g_PCLK = 66500000; */

int main(void){

	char c = 0;	
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
	
	while(1)
	{
		//key_test();
		time_printf();	
		c = UART_GetCh();
		UART_SendByte( (int)c );
	}
}


