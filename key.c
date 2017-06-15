#include "led.h"
#include "key.h"
#include "utils.h"



/*查询*/
void key_init(void)
{
	int value;
	value = GPNCON;
	value &= ((~(0x03<<8))&(~(0x03<<4))&(~(0x03<<2))&(~(0x03<<0)));
	GPNCON = value;
	//GPNDAT &= 0x0f;
}


int key_test(void)
{
	int flag = 0;

			
	//未按	
	if((GPNDAT&0x0F) == 0x0F)
	{
		LEDAll_Init();
		LEDAll_TurnOff();
		flag = 0;	
		
	}
		

	//0b0111,按下4号键		
	if((GPNDAT&0x0F) == 0x07)
	{


		//bomb();

		LEDAll_Init();			
		LEDAny_TurnOn(4);
		flag = 4;
	}

	//0b1011,按下3号键
	if((GPNDAT&0x0F) == 0x0B)
	{

		//bomb();

		LEDAll_Init();			
		LEDAny_TurnOn(3);
		flag = 3;			
	}

		
	//0b1101,按下2号键
	if((GPNDAT&0x0F) == 0x0D)
	{

		//bomb();
		LEDAll_Init();			
		LEDAny_TurnOn(2);
		flag = 2;			
	}


	//0b1110,按下1号键
	if((GPNDAT&0x0F) == 0x0E)
	{

		//bomb();
		LEDAll_Init();			
		LEDAny_TurnOn(1);
		flag = 1; 			
	}
	
	//0b1100,同时按下1,2两号键
	if((GPNDAT&0x0F) == 0x0C)
	{


		flag = -1; 			
	}
	
	
	//0b0011,同时按下3,4两号键
	if((GPNDAT&0x0F) == 0x03)
	{


		flag = -2; 			
	}
	
			
	return flag;				

}



