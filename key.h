#ifndef __KEY_H__
#define __KEY_H__


#define GPNCON  (*((volatile unsigned int *)0x7F008830))
#define GPNDAT  (*((volatile unsigned int *)0x7F008834))
#define GPNPUD  (*((volatile unsigned int *)0x7F008838))



/*≤È—Ø*/
void key_init(void);
void key_test(void);


#endif


