#ifndef _LCD_H
#define _LCD_H

#include "irq.h"
#include "utils.h"

#define GPECON  (*((volatile unsigned int *)0x7F008080))
#define GPEDAT  (*((volatile unsigned int *)0x7F008084))

#define GPICON  (*((volatile unsigned int *)0x7F008100))
#define GPJCON  (*((volatile unsigned int *)0x7F008120))
#define SPCON   (*((volatile unsigned int *)0x7F0081A0))

/*  ����MIFPCON���ƼĴ��� */
#define rMIFPCON S3C6410_SFR32(0x7410800c) 


#define LCD_LINEVAL 480		//��ֱ�ֱ���
#define LCD_HOZVAL	800		//ˮƽ�ֱ���

#define LCD_VBPD           	(21)//���ݸ������Ĳ��������⼸�������7������
#define LCD_VFPD           	(22)//���ݸ������Ĳ��������⼸��
#define LCD_VSPW           	(2)////���ݸ������Ĳ��������⼸��
#define LCD_HBPD           	(44)////���ݸ������Ĳ��������⼸��
#define LCD_HFPD           	(210)//���ݸ������Ĳ��������⼸��
#define LCD_HSPW           	(2)////���ݸ������Ĳ��������⼸��


//LCD �ߴ�
#define LCD_X_SIZE     (800)//���ݸ������Ĳ��������⼸��
#define LCD_Y_SIZE     (480)//���ݸ������Ĳ��������⼸��
#define LCD_XSIZE     (800)//���ݸ������Ĳ��������⼸��
#define LCD_YSIZE     (480)//���ݸ������Ĳ��������⼸��
#define	LCD_BUF_SIZE	(LCD_X_SIZE*LCD_YSIZE)		//��������С


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//����
//��Ƶ��������0�Ĵ���VIDCON0
#define VIDCON0_INTERLACE_F		(0 << 29)	//����
#define VIDCON0_VIDOUT			(0 << 26)	//RGB�ӿ�
#define VIDCON0_L1_DATA16		(0 << 23)	//I80 (LDI1)���16bitģʽ
#define VIDCON0_L0_DATA16		(0 << 20)	//I80 (LDI0)���16bitģʽ
#define VIDCON0_PNRMODE			(0 << 17)	//��ʾ��ʽ RGB��ʽ
#define VIDCON0_CLKVALUP		(1 << 16)	//ѡ��CLKVAL_F ����ʱ����� ,֡��ʼʱ����
#define VIDCON0_CLKVAL_F		(3 << 6)	//ʱ�ӷ�Ƶ,���66MHz	VCLK=��Ƶʱ��Դ/��CLKVAL+1�� CLKVAL>=1
#define VIDCON0_VCLKFREE		(1 << 5)	//VCLK �������п��ƣ�ֻ����RGB IF ģʽ����Ч��:��������ģʽ
#define VIDCON0_CLKDIR			(1 << 4)	//��CLKVAL_F �Ĵ�������ʱ��Դ
#define VIDCON0_CLKSEL_F		(0 << 2)	//ѡ��ʱ��Դ,HCLK = 133MHz
#define VIDCON0_ENVID			(0 << 1)	//��Ƶ�������ʾ�����źŽ�ֹ
#define VIDCON0_ENVID_F			(0 << 0)	//��Ƶ�������ʾ�����źŽ�ֹ

//��Ƶ��������1�Ĵ���VIDCON1
#define VIDCON1_IVCLK			(0 << 7)	//ʱ����������Ч
#define VIDCON1_IHSYNC			(1 << 6)	//HSYNC����
#define VIDCON1_IVSYNC			(1 << 5)	//VSYNC����
#define VIDCON1_IVDEN			(0 << 4)	//DE�źŲ�����

//��Ƶʱ�����0�Ĵ���VIDTCON0
#define VIDTCON0_VBPDE			(0 << 24)			//��֡��ʼ������ֱ�����ǲ���е��������ڴ�ֱͬ������֮��ֻ��YVU �ӿڣ�
#define VIDTCON0_VBPD			((LCD_VBPD - 1) << 16)
#define VIDTCON0_VFPD			((LCD_VFPD - 1) << 8)
#define VIDTCON0_VSPW			((LCD_VSPW - 1) << 0)
//��Ƶʱ�����1�Ĵ���VIDTCON1
#define VIDTCON1_VFPDE			(0 << 24)			//��֡ĩβ������ֱǰ���ǲ���е��������ڴ�ֱͬ������֮ǰ��ֻ��YVU �ӿڣ�
#define VIDTCON1_HBPD			((LCD_HBPD - 1) << 16)
#define VIDTCON1_HFPD			((LCD_HFPD - 1) << 8)
#define VIDTCON1_HSPW			((LCD_HSPW - 1) << 0)
//��Ƶʱ�����2�Ĵ���VIDTCON2
#define VIDTCON2_LINEVAL		((LCD_LINEVAL - 1) << 11)
#define VIDTCON2_HOZVAL			((LCD_HOZVAL - 1) << 0)
//����0���ƼĴ���WINCON0
#define WINCON0_nWide_Narrow	(0 << 16)		//��������ֵ��Χѡ���YCbCr ��RGB ����ɫ�ռ�ת����ʽ��YCbCr ��Χ��2��00, YCbCr խ��Χ��2��11,��Χ��Y/Cb/Cr:2514-0խ��Χ:Y:2314-16,Cb/Cr:240-16
#define WINCON0_ENLOCAL			(0 << 22)		//ѡ�����ݷ��ʷ�ʽ:ר��DMA
#define WINCON0_BUFSEL			(0 << 20)		//����������Ϊ0
#define WINCON0_BUFAUTOEN		(0 << 19) 		//˫�������Զ�����λ,��BUFSEL����
#define WINCON0_BITSWP			(0 << 18)		//λ������ֹ
#define WINCON0_BYTSWP			(0 << 17)		//�ֽڽ�����ֹ
#define WINCON0_HAWSWP			(1 << 16)		//���ӽ���ʹ��
#define WINCON0_InRGB			(0 << 13)		//��λָ��Դͼ���������ɫ�ռ䣨ֻ��ENLOCALI ��Ч��:RGB
#define WINCON0_BURSTLEN		(0 << 9)		//DMA ��ͻ����󳤶�ѡ��:16BYTE
#define WINCON0_BPPMODE_F		(5 << 2)		//16bit RGB565
//����0λ�ÿ���A�Ĵ���VIDOSD0A
#define VIDOSD0A_OSD_LeftTopX_F	(0 << 11)		//���Ͻǵ�OSD ͼ�����غ�����Ļ����
#define VIDOSD0A_OSD_LeftTopY_F (0 << 0)		//���Ͻǵ�OSD ͼ������������Ļ���꣨���ڽӿ�TV������ԣ����ֵ������������Ļy ����ֵ��һ��λ�á�Y ����ֵ�ĳ�ʼλ�ñ���Ϊż����
//����0λ�ÿ���B�Ĵ���VIDOSD0B
#define VIDOSD0B_OSD_RightBotX_F	((LCD_HOZVAL - 1) << 11)	//���½ǵ�OSD ͼ�����غ�����Ļ����
#define VIDOSD0B_OSD_RightBotY_F	((LCD_LINEVAL - 1) << 0) 	//���½ǵ�OSD ͼ������������Ļ���꣨���ڽӿ�TV������ԣ����ֵ������������Ļy ����ֵ��һ��λ�á�Y ����ֵ�ĳ�ʼλ�ñ���Ϊ������
//����0λ�ÿ���C�Ĵ���VIDOSD0C
#define VIDOSD0C_OSDSIZE		(LCD_HOZVAL * LCD_LINEVAL)		//���ڳߴ�=��*������)


//LCD Frame Rate
#define LCD_FRM_RATE     		60	//LCD Frame Rate (Hz)
//LCD֡������ʼ��ַ
#define LCD_FBUF_ST   	0x52000000
//LCD SFR Write/Read, offset ��lcd.h�ж���
#define LcdcOutp32(offset, x) 	Outp32(LCD_BASE+offset, x)
#define LcdcInp32(offset) 	Inp32(LCD_BASE+offset)

#define	S3C6410_SFR32(add)	(*((volatile unsigned long int*)(add)))	//ֱ��ӳ��
#define	S3C6410_SFR16(add)	(*((volatile unsigned short*)(add)))	//ֱ��ӳ��
#define	S3C6410_SFR8(add)	(*((volatile unsigned char *)(add)))	//ֱ��ӳ��
//��ʾ������(TFT_LCD������)
//SFR �ڴ�ӳ��
//		�Ĵ��� 			��ַ 							 ��/д 			���� 									��λֵ
#define	rVIDCON0   		S3C6410_SFR32(0x77100000)		//   ��/д 		��Ƶ����0 �Ĵ����� 						0x0000_0000
#define	rVIDCON1   		S3C6410_SFR32(0x77100004)		//   ��/д 		��Ƶ����1 �Ĵ��� 						0x0000_0000
#define	rVIDCON2   		S3C6410_SFR32(0x77100008)		//   ��/д 		��Ƶ����2 �Ĵ��� 						0x0000_0000
#define	rVIDTCON0   	S3C6410_SFR32(0x77100010)		//   ��/д 		��Ƶʱ�����0 �Ĵ��� 					0x0000_0000
#define	rVIDTCON1   	S3C6410_SFR32(0x77100014)		//   ��/д 		��Ƶʱ�����1 �Ĵ��� 					0x0000_0000
#define	rVIDTCON2   	S3C6410_SFR32(0x77100018)		//   ��/д 		��Ƶʱ�����2 �Ĵ��� 					0x0000_0000
#define	rWINCON0   		S3C6410_SFR32(0x77100020)		//   ��/д 		���ڿ���0 �Ĵ��� 						0x0000_0000
#define	rWINCON1   		S3C6410_SFR32(0x77100024)		//   ��/д 		���ڿ���1 �Ĵ��� 						0x0000_0000
#define	rWINCON2   		S3C6410_SFR32(0x77100028)		//   ��/д 		���ڿ���2 �Ĵ��� 						0x0000_0000
#define	rWINCON3   		S3C6410_SFR32(0x7710002C)		//   ��/д 		���ڿ���3 �Ĵ��� 						0x0000_0000
#define	rWINCON4   		S3C6410_SFR32(0x77100030)		//   ��/д 		���ڿ���4 �Ĵ��� 						0x0000_0000
#define	rVIDOSD0A   	S3C6410_SFR32(0x77100040)		//   ��/д 		��Ƶ����0 ��λ�ÿ��ƼĴ��� 				0x0000_0000
#define	rVIDOSD0B   	S3C6410_SFR32(0x77100044)		//   ��/д 		��Ƶ����0 ��λ�ÿ��ƼĴ��� 				0x0000_0000
#define	rVIDOSD0C   	S3C6410_SFR32(0x77100048)		//   ��/д 		��Ƶ����0 �ĳߴ���ƼĴ��� 				0x0000_0000
#define	rVIDOSD1A   	S3C6410_SFR32(0x77100050)		//   ��/д 		��Ƶ����1 ��λ�ÿ��ƼĴ��� 				0x0000_0000
#define	rVIDOSD1B   	S3C6410_SFR32(0x77100054)		//   ��/д 		��Ƶ����1 ��λ�ÿ��ƼĴ��� 				0x0000_0000
#define	rVIDOSD1C   	S3C6410_SFR32(0x77100058)		//   ��/д 		��Ƶ����1 ��alpha ���ƼĴ��� 			0x0000_0000
#define	rVIDOSD1D   	S3C6410_SFR32(0x7710005C)		//   ��/д 		��Ƶ����1 �ĳߴ���ƼĴ��� 				0x0000_0000
#define	rVIDOSD2A   	S3C6410_SFR32(0x77100060)		//   ��/д 		��Ƶ����2 ��λ�ÿ��ƼĴ��� 				0x0000_0000
#define	rVIDOSD2B   	S3C6410_SFR32(0x77100064)		//   ��/д 		��Ƶ����2 ��λ�ÿ��ƼĴ��� 				0x0000_0000
#define	rVIDOSD2C   	S3C6410_SFR32(0x77100068)		//   ��/д 		��Ƶ����2 ��alpha ���ƼĴ���			0x0000_0000
#define	rVIDOSD2D   	S3C6410_SFR32(0x7710006C)		//   ��/д 		��Ƶ����2 �ĳߴ���ƼĴ��� 				0x0000_0000
#define	rVIDOSD3A   	S3C6410_SFR32(0x77100070)		//   ��/д 		��Ƶ����3 ��λ�ÿ��ƼĴ��� 				0x0000_0000
#define	rVIDOSD3B   	S3C6410_SFR32(0x77100074)		//   ��/д 		��Ƶ����3 ��λ�ÿ��ƼĴ��� 				0x0000_0000
#define	rVIDOSD3C   	S3C6410_SFR32(0x77100078)		//   ��/д 		��Ƶ����3 ��alpha ���ƼĴ��� 			0x0000_0000
#define	rVIDOSD4A   	S3C6410_SFR32(0x77100080)		//   ��/д 		��Ƶ����4 ��λ�ÿ��ƼĴ��� 				0x0000_0000
#define	rVIDOSD4B   	S3C6410_SFR32(0x77100084)		//   ��/д 		��Ƶ����4 ��λ�ÿ��ƼĴ��� 				0x0000_0000
#define	rVIDOSD4C   	S3C6410_SFR32(0x77100088)		//   ��/д 		��Ƶ����4 ��alpha ���ƼĴ��� 			0x0000_0000
#define	rVIDW00ADD0B0  	S3C6410_SFR32(0x771000A0)		//   ��/д 		����0 �Ļ�������ʼ��ַ�Ĵ�����������0	0x0000_0000
#define	rVIDW00ADD0B1  	S3C6410_SFR32(0x771000A4)		//   ��/д 		����0 �Ļ�������ʼ��ַ�Ĵ�����������1	0x0000_0000
#define	rVIDW01ADD0B0  	S3C6410_SFR32(0x771000A8)		//   ��/д 		����1 �Ļ�������ʼ��ַ�Ĵ�����������0	0x0000_0000
#define	rVIDW01ADD0B1  	S3C6410_SFR32(0x771000AC)		//   ��/д 		����1 �Ļ�������ʼ��ַ�Ĵ�����������1	0x0000_0000
#define	rVIDW02ADD0   	S3C6410_SFR32(0x771000B0)		//   ��/д 		����2 �Ļ�������ʼ��ַ�Ĵ��� 			0x0000_0000
#define	rVIDW03ADD0   	S3C6410_SFR32(0x771000B8)		//   ��/д 		����3 �Ļ�������ʼ��ַ�Ĵ��� 			0x0000_0000
#define	rVIDW04ADD0   	S3C6410_SFR32(0x771000C0)		//   ��/д 		����4 �Ļ�������ʼ��ַ�Ĵ��� 			0x0000_0000
#define	rVIDW00ADD1B0  	S3C6410_SFR32(0x771000D0)		//   ��/д 		����0 �Ļ�������ʼ��ַ�Ĵ�����������0	0x0000_0000
#define	rVIDW00ADD1B1  	S3C6410_SFR32(0x771000D4)		//   ��/д 		����0 �Ļ�������ʼ��ַ�Ĵ�����������1	0x0000_0000
#define	rVIDW01ADD1B0  	S3C6410_SFR32(0x771000D8)		//   ��/д 		����1 �Ļ�������ʼ��ַ�Ĵ���,������0	0x0000_0000
#define	rVIDW01ADD1B1  	S3C6410_SFR32(0x771000DC)		//   ��/д 		����1 �Ļ�������ʼ��ַ�Ĵ�����������1	0x0000_0000
#define	rVIDW02ADD1   	S3C6410_SFR32(0x771000E0)		//   ��/д 		����2 �Ļ�������ʼ��ַ�Ĵ��� 			0x0000_0000
#define	rVIDW03ADD1   	S3C6410_SFR32(0x771000E8)		//   ��/д 		����3 �Ļ�������ʼ��ַ�Ĵ��� 			0x0000_0000
#define	rVIDW04ADD1   	S3C6410_SFR32(0x771000F0)		//   ��/д 		����4 �Ļ�������ʼ��ַ�Ĵ��� 			0x0000_0000
#define	rVIDW00ADD2   	S3C6410_SFR32(0x77100100)		//   ��/д 		����0 �Ļ�������ʼ��ַ�Ĵ��� 			0x0000_0000
#define	rVIDW01ADD2   	S3C6410_SFR32(0x77100104)		//   ��/д 		����1 �Ļ�������ʼ��ַ�Ĵ��� 			0x0000_0000
#define	rVIDW02ADD2   	S3C6410_SFR32(0x77100108)		//   ��/д 		����2 �Ļ�������ʼ��ַ�Ĵ��� 			0x0000_0000
#define	rVIDW03ADD2   	S3C6410_SFR32(0x7710010C)		//   ��/д 		����3 �Ļ�������ʼ��ַ�Ĵ��� 			0x0000_0000
#define	rVIDW04ADD2   	S3C6410_SFR32(0x77100110)		//   ��/д 		����4 �Ļ�������ʼ��ַ�Ĵ��� 			0x0000_0000
#define	rVIDINTCON0   	S3C6410_SFR32(0x77100130)		//   ��/д 		ָ�������жϿ��ƼĴ��� 					0x03F0_0000
#define	rVIDINTCON1   	S3C6410_SFR32(0x77100134)		//   ��/д 		��Ƶ�ж����ҿ��ƼĴ��� 					0x0000_0000
#define	rW1KEYCON0   	S3C6410_SFR32(0x77100140)		//   ��/д 		Color key ���ƼĴ��� 					0x0000_0000
#define	rW1KEYCON1   	S3C6410_SFR32(0x77100144)		//   ��/д 		Color key ֵ�Ĵ��� 						0x0000_0000
#define	rW2KEYCON0   	S3C6410_SFR32(0x77100148)		//   ��/д 		Color key ���ƼĴ��� 					0x0000_0000
#define	rW2KEYCON1   	S3C6410_SFR32(0x7710014C)		//   ��/д 		Color key ֵ�Ĵ��� 						0x0000_0000
#define	rW3KEYCON0   	S3C6410_SFR32(0x77100150)		//   ��/д 		Color key ���ƼĴ��� 					0x0000_0000
#define	rW3KEYCON1   	S3C6410_SFR32(0x77100154)		//   ��/д 		Color key ֵ�Ĵ��� 						0x0000_0000
#define	rW4KEYCON0   	S3C6410_SFR32(0x77100158)		//   ��/д 		Color key ���ƼĴ��� 					0x0000_0000
#define	rW4KEYCON1   	S3C6410_SFR32(0x7710015C)		//   ��/д 		Color key ֵ�Ĵ��� 						0x0000_0000
#define	rDITHMODE   	S3C6410_SFR32(0x77100170)		//   ��/д 		����ģʽ�Ĵ��� 							0x0000_0000
#define	rWIN0MAP   		S3C6410_SFR32(0x77100180)		//   ��/д 		������ɫ���� 							0x0000_0000
#define	rWIN1MAP   		S3C6410_SFR32(0x77100184)		//   ��/д 		������ɫ���� 							0x0000_0000
#define	rWIN2MAP   		S3C6410_SFR32(0x77100188)		//   ��/д 		������ɫ���� 							0x0000_0000
#define	rWIN3MAP   		S3C6410_SFR32(0x7710018C)		//   ��/д 		������ɫ���� 							0x0000_0000
#define	rWIN4MAP   		S3C6410_SFR32(0x77100190)		//   ��/д 		������ɫ���� 							0x0000_0000
#define	rWPALCON   		S3C6410_SFR32(0x771001A0)		//   ��/д 		���ڵ�ɫ����ƼĴ��� 					0x0000_0000
#define	rTRIGCON   		S3C6410_SFR32(0x771001A4)		//   ��/д 		I80/RGB �������ƼĴ��� 					0x0000_0000
#define	rITUIFCON0   	S3C6410_SFR32(0x771001A8)		//   ��/д 		ITU(BT.601)�ӿڿ��� 					0x0000_0000
#define	rI80IFCONA0   	S3C6410_SFR32(0x771001B0)		//   ��/д 		��LDI ��I80 �ӿڿ���0 					0x0000_0000
#define	rI80IFCONA1   	S3C6410_SFR32(0x771001B4)		//   ��/д 		��LDI ��I80 �ӿڿ���0 					0x0000_0000
#define	rI80IFCONB0   	S3C6410_SFR32(0x771001B8)		//   ��/д 		��LDI ��I80 �ӿڿ���1 					0x0000_0000
#define	rI80IFCONB1   	S3C6410_SFR32(0x771001BC)		//   ��/д 		��LDI ��I80 �ӿڿ���1 					0x0000_0000
#define	rLDI_CMDCON0   	S3C6410_SFR32(0x771001D0)		//   ��/д 		I80 �ӿ�LDI �������0 					0x0000_0000
#define	rLDI_CMDCON1   	S3C6410_SFR32(0x771001D4)		//   ��/д 		I80 �ӿ�LDI �������1 					0x0000_0000
#define	rSIFCCON0   	S3C6410_SFR32(0x771001E0)		//   ��/д 		LCD I80 ϵͳ�ӿ��ֲ�������� 			0x0000_0000
#define	rSIFCCON1   	S3C6410_SFR32(0x771001E4)		//   ��/д 		LCD I80 ϵͳ�ӿ��ֲ���������д����		0x0000_0000
#define	rSIFCCON2   	S3C6410_SFR32(0x771001E8)		//   ��/д 		LCD I80 ϵͳ�ӿ��ֲ��������ݶ�����2		δ����
#define	rLDI_CMD0   	S3C6410_SFR32(0x77100280)		//   ��/д 		I80 �ӿ�LDI ����0 						0x0000_0000
#define	rLDI_CMD1   	S3C6410_SFR32(0x77100284)		//   ��/д 		I80 �ӿ�LDI ����1 						0x0000_0000
#define	rLDI_CMD2   	S3C6410_SFR32(0x77100288)		//   ��/д 		I80 �ӿ�LDI ����2 						0x0000_0000
#define	rLDI_CMD3   	S3C6410_SFR32(0x7710028C)		//   ��/д 		I80 �ӿ�LDI ����3 						0x0000_0000
#define	rLDI_CMD4   	S3C6410_SFR32(0x77100290)		//   ��/д 		I80 �ӿ�LDI ����4 						0x0000_0000
#define	rLDI_CMD5   	S3C6410_SFR32(0x77100294)		//   ��/д 		I80 �ӿ�LDI ����5 						0x0000_0000
#define	rLDI_CMD6   	S3C6410_SFR32(0x77100298)		//   ��/д 		I80 �ӿ�LDI ����6 						0x0000_0000
#define	rLDI_CMD7   	S3C6410_SFR32(0x7710029C)		//   ��/д 		I80 �ӿ�LDI ����7 						0x0000_0000
#define	rLDI_CMD8   	S3C6410_SFR32(0x771002A0)		//   ��/д 		I80 �ӿ�LDI ����8 						0x0000_0000
#define	rLDI_CMD9   	S3C6410_SFR32(0x771002A4)		//   ��/д 		I80 �ӿ�LDI ����9 						0x0000_0000
#define	rLDI_CMD10   	S3C6410_SFR32(0x771002A8)		//   ��/д 		I80 �ӿ�LDI ����10 						0x0000_0000
#define	rLDI_CMD11   	S3C6410_SFR32(0x771002AC)		//   ��/д 		I80 �ӿ�LDI ����11 						0x0000_0000
#define	rW2PDATA01   	S3C6410_SFR32(0x77100300)		//   ��/д 		����0��1 �Ĵ���2 ��ɫ������ 			0x0000_0000
#define	rW2PDATA23   	S3C6410_SFR32(0x77100304)		//   ��/д 		����2��3 �Ĵ���2 ��ɫ������ 			0x0000_0000
#define	rW2PDATA45   	S3C6410_SFR32(0x77100308)		//   ��/д 		����4��5 �Ĵ���2 ��ɫ������ 			0x0000_0000
#define	rW2PDATA67   	S3C6410_SFR32(0x7710030C)		//   ��/д 		����6��7 �Ĵ���2 ��ɫ������ 			0x0000_0000
#define	rW2PDATA89   	S3C6410_SFR32(0x77100310)		//   ��/д 		����8��9 �Ĵ���2 ��ɫ������ 			0x0000_0000
#define	rW2PDATAAB   	S3C6410_SFR32(0x77100314)		//   ��/д 		����A��B �Ĵ���2 ��ɫ������ 			0x0000_0000
#define	rW2PDATACD   	S3C6410_SFR32(0x77100318)		//   ��/д 		����C��D �Ĵ���2 ��ɫ������ 			0x0000_0000
#define	rW2PDATAEF   	S3C6410_SFR32(0x7710031C)		//   ��/д 		����E��F �Ĵ���2 ��ɫ������ 			0x0000_0000
#define	rW3PDATA01   	S3C6410_SFR32(0x77100320)		//   ��/д 		����0��1 �Ĵ���3 ��ɫ������ 			0x0000_0000
#define	rW3PDATA23   	S3C6410_SFR32(0x77100324)		//   ��/д 		����2��3 �Ĵ���3 ��ɫ������ 			0x0000_0000
#define	rW3PDATA45   	S3C6410_SFR32(0x77100328)		//   ��/д 		����4��5 �Ĵ���3 ��ɫ������ 			0x0000_0000
#define	rW3PDATA67   	S3C6410_SFR32(0x7710032C)		//   ��/д 		����6��7 �Ĵ���3 ��ɫ������ 			0x0000_0000
#define	rW3PDATA89   	S3C6410_SFR32(0x77100330)		//   ��/д 		����8��9 �Ĵ���3 ��ɫ������ 			0x0000_0000
#define	rW3PDATAAB   	S3C6410_SFR32(0x77100334)		//   ��/д 		����A��B �Ĵ���3 ��ɫ������ 			0x0000_0000
#define	rW3PDATACD   	S3C6410_SFR32(0x77100338)		//   ��/д 		����C��D �Ĵ���3 ��ɫ������ 			0x0000_0000
#define	rW3PDATAEF   	S3C6410_SFR32(0x7710033C)		//   ��/д 		����E��F �Ĵ���3 ��ɫ������ 			0x0000_0000
#define	rW4PDATA01   	S3C6410_SFR32(0x77100340)		//   ��/д 		����0��1 �Ĵ���4 ��ɫ������ 			0x0000_0000
#define	rW4PDATA23   	S3C6410_SFR32(0x77100344)		//   ��/д 		����2��3 �Ĵ���4 ��ɫ������ 			0x0000_0000

#define SetLCD_Windows0()	(rWINCON0 &= ~(0x1<<20))	//��ʾ����0
#define SetLCD_Windows1()	(rWINCON0 |= (0x1<<20)		//��ʾ����1
#define GetLCD_Windows()	((rWINCON0 & (0x1<<21)) ? 1 : 0)	//��ȡ��ǰ����ʾ���ں�

void LCD_Init(void);
void LCD_ClearScreen(unsigned short Color);
void Paint_Bmp(int x0, int y0, int h, int v, const unsigned char bmp[]);
void Lcd_Display_LOGO(void);

/* Type defines */
typedef unsigned int		u32;
typedef unsigned short		u16;
typedef unsigned char		u8;

typedef signed int			s32;
typedef signed short		s16;
typedef signed char			s8;

typedef float fp32;
typedef double fp64;



#endif
