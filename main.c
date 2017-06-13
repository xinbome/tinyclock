#include "led.h"
#include "bomb.h"
#include "key.h"
#include "irq.h"
#include "sys.h"


int main(void){

	SYSTEM_EnableIRQ(); /* ʹ��CSPR�Ĵ�����ϵͳIRQ */
	SYSTEM_EnableVIC(); /* ʹ��VICʸ���жϼĴ���   */

	LEDAll_Init();     
	
	KEYS_Init();       	
	while(1)
	{
	
		;
	}     
	
	return 0;
}


