#ifndef __BOMB_H__
#define __BOMB_H__

//µÎµÎµÄ·äÃùÆ÷£¬ÎÒ½ÐËübomb

#define GPFCON (*((volatile unsigned int*)0X7F0080A0))
#define GPFDAT (*((volatile unsigned int*)0X7F0080A4))
#define GPFPUD (*((volatile unsigned int*)0X7F0080A8))

void init(void);

void bomb(void);


void bomboff(void);

void bomboff(void);

#endif
