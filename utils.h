#ifndef __UTILS_H__
#define __UTILS_H__

//��ָ����ַ������ֵ
#define Outp32(addr, data)	(*(volatile unsigned int *)(addr) = (data))
//����ָ����ַ��ֵ
#define Inp32(addr)			(*(volatile unsigned int *)(addr))


void Delay(int times);

#endif//__UTILS_H__
