#ifndef __UTILS_H__
#define __UTILS_H__

//给指定地址赋整数值
#define Outp32(addr, data)	(*(volatile unsigned int *)(addr) = (data))
//读出指定地址的值
#define Inp32(addr)			(*(volatile unsigned int *)(addr))


void Delay(int times);

#endif//__UTILS_H__
