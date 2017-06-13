#include "led.h"
#include "bomb.h"
#include "key.h"
#include "irq.h"
#include "sys.h"


int main(void){

	SYSTEM_EnableIRQ(); /* 使能CSPR寄存器中系统IRQ */
	SYSTEM_EnableVIC(); /* 使能VIC矢量中断寄存器   */

	LEDAll_Init();     
	
	KEYS_Init();       	
	while(1)
	{
	
		;
	}     
	
	return 0;
}


