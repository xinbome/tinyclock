#include "led.h"
#include "key.h"
#include "utils.h"



/*��ѯ*/
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
	int bomb_count = 0;
	key_init();
	
	while(1)
	{			
		//δ��	
		if((GPNDAT&0x0F) == 0x0F)
		{
			LEDAll_Init();
			LEDAll_TurnOff();			
		}
		

		//0b0111,����4�ż�		
		if((GPNDAT&0x0F) == 0x07)
		{
			bomb_count = 4;
			while(bomb_count--)
			{
				bomb();
			}
			LEDAll_Init();			
			LEDAny_TurnOn(4);			
		}

		//0b1011,����3�ż�
		if((GPNDAT&0x0F) == 0x0B)
		{
			bomb_count = 3;
			while(bomb_count--)
			{
				bomb();
			}
			LEDAll_Init();			
			LEDAny_TurnOn(3);			
		}

		
		//0b1101,����2�ż�
		if((GPNDAT&0x0F) == 0x0D)
		{
			bomb_count = 2;
			while(bomb_count--)
			{
				bomb();
			}
			LEDAll_Init();			
			LEDAny_TurnOn(2);			
		}


		//0b1110,����1�ż�
		if((GPNDAT&0x0F) == 0x0E)
		{
			bomb_count = 1;
			while(bomb_count--)
			{
				bomb();
			}
			LEDAll_Init();			
			LEDAny_TurnOn(1);			
		}
						
	}
}



