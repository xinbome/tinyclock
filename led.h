#ifndef __LED_H__
#define __LED_H__

//led作为测试按键驱动以及debug用

#define GPKCON0  (*((volatile unsigned int *)0x7F008800))
#define GPKCON1  (*((volatile unsigned int *)0x7F008804))
#define GPKDAT   (*((volatile unsigned int *)0x7F008808))
#define GPKPUD   (*((volatile unsigned int *)0x7F00880C))

void LED4_TurnOn(void);
void LED1_TurnOn(void);




void LEDAny_Init(int num);
void LEDAny_TurnOn(int num);
void LEDAny_TurnOff(int num);


void LEDAll_TurnOn(void);
void LEDAll_TurnOff(void);


#endif
