#include "key.h"


void key_init(void)
{
	int value;
	value = GPNCON;
	value &= ((~(0x03<<8))&(~(0x03<<4))&(~(0x03<<2))&(~(0x03<<0)));
	GPNCON = value;
	//GPNDAT &= 0x0f;
}


void key_test(void)
{
	key_init();
	while(1)
	{			
		if((GPNDAT&0x0F) == 0x0F)//Î´°´
		{
			LEDAll_Init();
			LEDAny_TurnOn(3);
			LEDAll_Init();				
		}
		else //°´ÏÂ
		{

			bomb();					
			//LEDAll_TurnOn();
			//LEDAll_TurnOff();	
			//LED4_TurnOn();
			//LED1_TurnOn();
		}
	}
}

