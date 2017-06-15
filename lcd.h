#ifndef _LCD_H
#define _LCD_H

#include "irq.h"
#include "utils.h"

#define GPECON  (*((volatile unsigned int *)0x7F008080))
#define GPEDAT  (*((volatile unsigned int *)0x7F008084))

#define GPICON  (*((volatile unsigned int *)0x7F008100))
#define GPJCON  (*((volatile unsigned int *)0x7F008120))
#define SPCON   (*((volatile unsigned int *)0x7F0081A0))

/*  定义MIFPCON控制寄存器 */
#define rMIFPCON S3C6410_SFR32(0x7410800c) 


#define LCD_LINEVAL 480		//垂直分辨率
#define LCD_HOZVAL	800		//水平分辨率

#define LCD_VBPD           	(21)//根据各个屏的参数设置这几个这个是7寸屏的
#define LCD_VFPD           	(22)//根据各个屏的参数设置这几个
#define LCD_VSPW           	(2)////根据各个屏的参数设置这几个
#define LCD_HBPD           	(44)////根据各个屏的参数设置这几个
#define LCD_HFPD           	(210)//根据各个屏的参数设置这几个
#define LCD_HSPW           	(2)////根据各个屏的参数设置这几个


//LCD 尺寸
#define LCD_X_SIZE     (800)//根据各个屏的参数设置这几个
#define LCD_Y_SIZE     (480)//根据各个屏的参数设置这几个
#define LCD_XSIZE     (800)//根据各个屏的参数设置这几个
#define LCD_YSIZE     (480)//根据各个屏的参数设置这几个
#define	LCD_BUF_SIZE	(LCD_X_SIZE*LCD_YSIZE)		//缓冲区大小


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//配置
//视频主控制器0寄存器VIDCON0
#define VIDCON0_INTERLACE_F		(0 << 29)	//渐行
#define VIDCON0_VIDOUT			(0 << 26)	//RGB接口
#define VIDCON0_L1_DATA16		(0 << 23)	//I80 (LDI1)输出16bit模式
#define VIDCON0_L0_DATA16		(0 << 20)	//I80 (LDI0)输出16bit模式
#define VIDCON0_PNRMODE			(0 << 17)	//显示格式 RGB格式
#define VIDCON0_CLKVALUP		(1 << 16)	//选择CLKVAL_F 更新时序控制 ,帧开始时控制
#define VIDCON0_CLKVAL_F		(3 << 6)	//时钟分频,最大66MHz	VCLK=视频时钟源/（CLKVAL+1） CLKVAL>=1
#define VIDCON0_VCLKFREE		(1 << 5)	//VCLK 自由运行控制（只有在RGB IF 模式下有效）:自由运行模式
#define VIDCON0_CLKDIR			(1 << 4)	//用CLKVAL_F 寄存器划分时钟源
#define VIDCON0_CLKSEL_F		(0 << 2)	//选择时钟源,HCLK = 133MHz
#define VIDCON0_ENVID			(0 << 1)	//视频输出及显示控制信号禁止
#define VIDCON0_ENVID_F			(0 << 0)	//视频输出及显示控制信号禁止

//视频主控制器1寄存器VIDCON1
#define VIDCON1_IVCLK			(0 << 7)	//时钟上升沿有效
#define VIDCON1_IHSYNC			(1 << 6)	//HSYNC反向
#define VIDCON1_IVSYNC			(1 << 5)	//VSYNC反向
#define VIDCON1_IVDEN			(0 << 4)	//DE信号不反向

//视频时序控制0寄存器VIDTCON0
#define VIDTCON0_VBPDE			(0 << 24)			//在帧开始处，垂直后沿是不活动行的数量，在垂直同步过程之后（只对YVU 接口）
#define VIDTCON0_VBPD			((LCD_VBPD - 1) << 16)
#define VIDTCON0_VFPD			((LCD_VFPD - 1) << 8)
#define VIDTCON0_VSPW			((LCD_VSPW - 1) << 0)
//视频时序控制1寄存器VIDTCON1
#define VIDTCON1_VFPDE			(0 << 24)			//在帧末尾处，垂直前沿是不活动行的数量，在垂直同步过程之前（只对YVU 接口）
#define VIDTCON1_HBPD			((LCD_HBPD - 1) << 16)
#define VIDTCON1_HFPD			((LCD_HFPD - 1) << 8)
#define VIDTCON1_HSPW			((LCD_HSPW - 1) << 0)
//视频时序控制2寄存器VIDTCON2
#define VIDTCON2_LINEVAL		((LCD_LINEVAL - 1) << 11)
#define VIDTCON2_HOZVAL			((LCD_HOZVAL - 1) << 0)
//窗口0控制寄存器WINCON0
#define WINCON0_nWide_Narrow	(0 << 16)		//根据输入值范围选择从YCbCr 到RGB 的颜色空间转换等式。YCbCr 宽范围是2’00, YCbCr 窄范围是2’11,宽范围：Y/Cb/Cr:2514-0窄范围:Y:2314-16,Cb/Cr:240-16
#define WINCON0_ENLOCAL			(0 << 22)		//选择数据访问方式:专用DMA
#define WINCON0_BUFSEL			(0 << 20)		//缓冲区设置为0
#define WINCON0_BUFAUTOEN		(0 << 19) 		//双缓冲区自动控制位,由BUFSEL控制
#define WINCON0_BITSWP			(0 << 18)		//位交换禁止
#define WINCON0_BYTSWP			(0 << 17)		//字节交换禁止
#define WINCON0_HAWSWP			(1 << 16)		//半子交换使能
#define WINCON0_InRGB			(0 << 13)		//此位指明源图像的输入颜色空间（只对ENLOCALI 有效）:RGB
#define WINCON0_BURSTLEN		(0 << 9)		//DMA 的突发最大长度选择:16BYTE
#define WINCON0_BPPMODE_F		(5 << 2)		//16bit RGB565
//窗口0位置控制A寄存器VIDOSD0A
#define VIDOSD0A_OSD_LeftTopX_F	(0 << 11)		//左上角的OSD 图像像素横向屏幕坐标
#define VIDOSD0A_OSD_LeftTopY_F (0 << 0)		//左上角的OSD 图像像素纵向屏幕坐标（对于接口TV输出而言，这个值必须设置在屏幕y 坐标值的一半位置。Y 坐标值的初始位置必须为偶数）
//窗口0位置控制B寄存器VIDOSD0B
#define VIDOSD0B_OSD_RightBotX_F	((LCD_HOZVAL - 1) << 11)	//右下角的OSD 图像像素横向屏幕坐标
#define VIDOSD0B_OSD_RightBotY_F	((LCD_LINEVAL - 1) << 0) 	//右下角的OSD 图像像素纵向屏幕坐标（对于接口TV输出而言，这个值必须设置在屏幕y 坐标值的一半位置。Y 坐标值的初始位置必须为奇数）
//窗口0位置控制C寄存器VIDOSD0C
#define VIDOSD0C_OSDSIZE		(LCD_HOZVAL * LCD_LINEVAL)		//窗口尺寸=高*宽（字数)


//LCD Frame Rate
#define LCD_FRM_RATE     		60	//LCD Frame Rate (Hz)
//LCD帧缓冲起始地址
#define LCD_FBUF_ST   	0x52000000
//LCD SFR Write/Read, offset 在lcd.h中定义
#define LcdcOutp32(offset, x) 	Outp32(LCD_BASE+offset, x)
#define LcdcInp32(offset) 	Inp32(LCD_BASE+offset)

#define	S3C6410_SFR32(add)	(*((volatile unsigned long int*)(add)))	//直接映射
#define	S3C6410_SFR16(add)	(*((volatile unsigned short*)(add)))	//直接映射
#define	S3C6410_SFR8(add)	(*((volatile unsigned char *)(add)))	//直接映射
//显示控制器(TFT_LCD控制器)
//SFR 内存映射
//		寄存器 			地址 							 读/写 			描述 									复位值
#define	rVIDCON0   		S3C6410_SFR32(0x77100000)		//   读/写 		视频控制0 寄存器器 						0x0000_0000
#define	rVIDCON1   		S3C6410_SFR32(0x77100004)		//   读/写 		视频控制1 寄存器 						0x0000_0000
#define	rVIDCON2   		S3C6410_SFR32(0x77100008)		//   读/写 		视频控制2 寄存器 						0x0000_0000
#define	rVIDTCON0   	S3C6410_SFR32(0x77100010)		//   读/写 		视频时序控制0 寄存器 					0x0000_0000
#define	rVIDTCON1   	S3C6410_SFR32(0x77100014)		//   读/写 		视频时序控制1 寄存器 					0x0000_0000
#define	rVIDTCON2   	S3C6410_SFR32(0x77100018)		//   读/写 		视频时序控制2 寄存器 					0x0000_0000
#define	rWINCON0   		S3C6410_SFR32(0x77100020)		//   读/写 		窗口控制0 寄存器 						0x0000_0000
#define	rWINCON1   		S3C6410_SFR32(0x77100024)		//   读/写 		窗口控制1 寄存器 						0x0000_0000
#define	rWINCON2   		S3C6410_SFR32(0x77100028)		//   读/写 		窗口控制2 寄存器 						0x0000_0000
#define	rWINCON3   		S3C6410_SFR32(0x7710002C)		//   读/写 		窗口控制3 寄存器 						0x0000_0000
#define	rWINCON4   		S3C6410_SFR32(0x77100030)		//   读/写 		窗口控制4 寄存器 						0x0000_0000
#define	rVIDOSD0A   	S3C6410_SFR32(0x77100040)		//   读/写 		视频窗口0 的位置控制寄存器 				0x0000_0000
#define	rVIDOSD0B   	S3C6410_SFR32(0x77100044)		//   读/写 		视频窗口0 的位置控制寄存器 				0x0000_0000
#define	rVIDOSD0C   	S3C6410_SFR32(0x77100048)		//   读/写 		视频窗口0 的尺寸控制寄存器 				0x0000_0000
#define	rVIDOSD1A   	S3C6410_SFR32(0x77100050)		//   读/写 		视频窗口1 的位置控制寄存器 				0x0000_0000
#define	rVIDOSD1B   	S3C6410_SFR32(0x77100054)		//   读/写 		视频窗口1 的位置控制寄存器 				0x0000_0000
#define	rVIDOSD1C   	S3C6410_SFR32(0x77100058)		//   读/写 		视频窗口1 的alpha 控制寄存器 			0x0000_0000
#define	rVIDOSD1D   	S3C6410_SFR32(0x7710005C)		//   读/写 		视频窗口1 的尺寸控制寄存器 				0x0000_0000
#define	rVIDOSD2A   	S3C6410_SFR32(0x77100060)		//   读/写 		视频窗口2 的位置控制寄存器 				0x0000_0000
#define	rVIDOSD2B   	S3C6410_SFR32(0x77100064)		//   读/写 		视频窗口2 的位置控制寄存器 				0x0000_0000
#define	rVIDOSD2C   	S3C6410_SFR32(0x77100068)		//   读/写 		视频窗口2 的alpha 控制寄存器			0x0000_0000
#define	rVIDOSD2D   	S3C6410_SFR32(0x7710006C)		//   读/写 		视频窗口2 的尺寸控制寄存器 				0x0000_0000
#define	rVIDOSD3A   	S3C6410_SFR32(0x77100070)		//   读/写 		视频窗口3 的位置控制寄存器 				0x0000_0000
#define	rVIDOSD3B   	S3C6410_SFR32(0x77100074)		//   读/写 		视频窗口3 的位置控制寄存器 				0x0000_0000
#define	rVIDOSD3C   	S3C6410_SFR32(0x77100078)		//   读/写 		视频窗口3 的alpha 控制寄存器 			0x0000_0000
#define	rVIDOSD4A   	S3C6410_SFR32(0x77100080)		//   读/写 		视频窗口4 的位置控制寄存器 				0x0000_0000
#define	rVIDOSD4B   	S3C6410_SFR32(0x77100084)		//   读/写 		视频窗口4 的位置控制寄存器 				0x0000_0000
#define	rVIDOSD4C   	S3C6410_SFR32(0x77100088)		//   读/写 		视频窗口4 的alpha 控制寄存器 			0x0000_0000
#define	rVIDW00ADD0B0  	S3C6410_SFR32(0x771000A0)		//   读/写 		窗口0 的缓冲区开始地址寄存器，缓冲区0	0x0000_0000
#define	rVIDW00ADD0B1  	S3C6410_SFR32(0x771000A4)		//   读/写 		窗口0 的缓冲区开始地址寄存器，缓冲区1	0x0000_0000
#define	rVIDW01ADD0B0  	S3C6410_SFR32(0x771000A8)		//   读/写 		窗口1 的缓冲区开始地址寄存器，缓冲区0	0x0000_0000
#define	rVIDW01ADD0B1  	S3C6410_SFR32(0x771000AC)		//   读/写 		窗口1 的缓冲区开始地址寄存器，缓冲区1	0x0000_0000
#define	rVIDW02ADD0   	S3C6410_SFR32(0x771000B0)		//   读/写 		窗口2 的缓冲区开始地址寄存器 			0x0000_0000
#define	rVIDW03ADD0   	S3C6410_SFR32(0x771000B8)		//   读/写 		窗口3 的缓冲区开始地址寄存器 			0x0000_0000
#define	rVIDW04ADD0   	S3C6410_SFR32(0x771000C0)		//   读/写 		窗口4 的缓冲区开始地址寄存器 			0x0000_0000
#define	rVIDW00ADD1B0  	S3C6410_SFR32(0x771000D0)		//   读/写 		窗口0 的缓冲区开始地址寄存器，缓冲区0	0x0000_0000
#define	rVIDW00ADD1B1  	S3C6410_SFR32(0x771000D4)		//   读/写 		窗口0 的缓冲区开始地址寄存器，缓冲区1	0x0000_0000
#define	rVIDW01ADD1B0  	S3C6410_SFR32(0x771000D8)		//   读/写 		窗口1 的缓冲区开始地址寄存器,缓冲区0	0x0000_0000
#define	rVIDW01ADD1B1  	S3C6410_SFR32(0x771000DC)		//   读/写 		窗口1 的缓冲区开始地址寄存器，缓冲区1	0x0000_0000
#define	rVIDW02ADD1   	S3C6410_SFR32(0x771000E0)		//   读/写 		窗口2 的缓冲区开始地址寄存器 			0x0000_0000
#define	rVIDW03ADD1   	S3C6410_SFR32(0x771000E8)		//   读/写 		窗口3 的缓冲区开始地址寄存器 			0x0000_0000
#define	rVIDW04ADD1   	S3C6410_SFR32(0x771000F0)		//   读/写 		窗口4 的缓冲区开始地址寄存器 			0x0000_0000
#define	rVIDW00ADD2   	S3C6410_SFR32(0x77100100)		//   读/写 		窗口0 的缓冲区开始地址寄存器 			0x0000_0000
#define	rVIDW01ADD2   	S3C6410_SFR32(0x77100104)		//   读/写 		窗口1 的缓冲区开始地址寄存器 			0x0000_0000
#define	rVIDW02ADD2   	S3C6410_SFR32(0x77100108)		//   读/写 		窗口2 的缓冲区开始地址寄存器 			0x0000_0000
#define	rVIDW03ADD2   	S3C6410_SFR32(0x7710010C)		//   读/写 		窗口3 的缓冲区开始地址寄存器 			0x0000_0000
#define	rVIDW04ADD2   	S3C6410_SFR32(0x77100110)		//   读/写 		窗口4 的缓冲区开始地址寄存器 			0x0000_0000
#define	rVIDINTCON0   	S3C6410_SFR32(0x77100130)		//   读/写 		指明视屏中断控制寄存器 					0x03F0_0000
#define	rVIDINTCON1   	S3C6410_SFR32(0x77100134)		//   读/写 		视频中断悬挂控制寄存器 					0x0000_0000
#define	rW1KEYCON0   	S3C6410_SFR32(0x77100140)		//   读/写 		Color key 控制寄存器 					0x0000_0000
#define	rW1KEYCON1   	S3C6410_SFR32(0x77100144)		//   读/写 		Color key 值寄存器 						0x0000_0000
#define	rW2KEYCON0   	S3C6410_SFR32(0x77100148)		//   读/写 		Color key 控制寄存器 					0x0000_0000
#define	rW2KEYCON1   	S3C6410_SFR32(0x7710014C)		//   读/写 		Color key 值寄存器 						0x0000_0000
#define	rW3KEYCON0   	S3C6410_SFR32(0x77100150)		//   读/写 		Color key 控制寄存器 					0x0000_0000
#define	rW3KEYCON1   	S3C6410_SFR32(0x77100154)		//   读/写 		Color key 值寄存器 						0x0000_0000
#define	rW4KEYCON0   	S3C6410_SFR32(0x77100158)		//   读/写 		Color key 控制寄存器 					0x0000_0000
#define	rW4KEYCON1   	S3C6410_SFR32(0x7710015C)		//   读/写 		Color key 值寄存器 						0x0000_0000
#define	rDITHMODE   	S3C6410_SFR32(0x77100170)		//   读/写 		抖动模式寄存器 							0x0000_0000
#define	rWIN0MAP   		S3C6410_SFR32(0x77100180)		//   读/写 		窗口颜色控制 							0x0000_0000
#define	rWIN1MAP   		S3C6410_SFR32(0x77100184)		//   读/写 		窗口颜色控制 							0x0000_0000
#define	rWIN2MAP   		S3C6410_SFR32(0x77100188)		//   读/写 		窗口颜色控制 							0x0000_0000
#define	rWIN3MAP   		S3C6410_SFR32(0x7710018C)		//   读/写 		窗口颜色控制 							0x0000_0000
#define	rWIN4MAP   		S3C6410_SFR32(0x77100190)		//   读/写 		窗口颜色控制 							0x0000_0000
#define	rWPALCON   		S3C6410_SFR32(0x771001A0)		//   读/写 		窗口调色板控制寄存器 					0x0000_0000
#define	rTRIGCON   		S3C6410_SFR32(0x771001A4)		//   读/写 		I80/RGB 触发控制寄存器 					0x0000_0000
#define	rITUIFCON0   	S3C6410_SFR32(0x771001A8)		//   读/写 		ITU(BT.601)接口控制 					0x0000_0000
#define	rI80IFCONA0   	S3C6410_SFR32(0x771001B0)		//   读/写 		主LDI 的I80 接口控制0 					0x0000_0000
#define	rI80IFCONA1   	S3C6410_SFR32(0x771001B4)		//   读/写 		子LDI 的I80 接口控制0 					0x0000_0000
#define	rI80IFCONB0   	S3C6410_SFR32(0x771001B8)		//   读/写 		主LDI 的I80 接口控制1 					0x0000_0000
#define	rI80IFCONB1   	S3C6410_SFR32(0x771001BC)		//   读/写 		子LDI 的I80 接口控制1 					0x0000_0000
#define	rLDI_CMDCON0   	S3C6410_SFR32(0x771001D0)		//   读/写 		I80 接口LDI 命令控制0 					0x0000_0000
#define	rLDI_CMDCON1   	S3C6410_SFR32(0x771001D4)		//   读/写 		I80 接口LDI 命令控制1 					0x0000_0000
#define	rSIFCCON0   	S3C6410_SFR32(0x771001E0)		//   读/写 		LCD I80 系统接口手册命令控制 			0x0000_0000
#define	rSIFCCON1   	S3C6410_SFR32(0x771001E4)		//   读/写 		LCD I80 系统接口手册命令数据写控制		0x0000_0000
#define	rSIFCCON2   	S3C6410_SFR32(0x771001E8)		//   读/写 		LCD I80 系统接口手册命令数据读控制2		未定义
#define	rLDI_CMD0   	S3C6410_SFR32(0x77100280)		//   读/写 		I80 接口LDI 命令0 						0x0000_0000
#define	rLDI_CMD1   	S3C6410_SFR32(0x77100284)		//   读/写 		I80 接口LDI 命令1 						0x0000_0000
#define	rLDI_CMD2   	S3C6410_SFR32(0x77100288)		//   读/写 		I80 接口LDI 命令2 						0x0000_0000
#define	rLDI_CMD3   	S3C6410_SFR32(0x7710028C)		//   读/写 		I80 接口LDI 命令3 						0x0000_0000
#define	rLDI_CMD4   	S3C6410_SFR32(0x77100290)		//   读/写 		I80 接口LDI 命令4 						0x0000_0000
#define	rLDI_CMD5   	S3C6410_SFR32(0x77100294)		//   读/写 		I80 接口LDI 命令5 						0x0000_0000
#define	rLDI_CMD6   	S3C6410_SFR32(0x77100298)		//   读/写 		I80 接口LDI 命令6 						0x0000_0000
#define	rLDI_CMD7   	S3C6410_SFR32(0x7710029C)		//   读/写 		I80 接口LDI 命令7 						0x0000_0000
#define	rLDI_CMD8   	S3C6410_SFR32(0x771002A0)		//   读/写 		I80 接口LDI 命令8 						0x0000_0000
#define	rLDI_CMD9   	S3C6410_SFR32(0x771002A4)		//   读/写 		I80 接口LDI 命令9 						0x0000_0000
#define	rLDI_CMD10   	S3C6410_SFR32(0x771002A8)		//   读/写 		I80 接口LDI 命令10 						0x0000_0000
#define	rLDI_CMD11   	S3C6410_SFR32(0x771002AC)		//   读/写 		I80 接口LDI 命令11 						0x0000_0000
#define	rW2PDATA01   	S3C6410_SFR32(0x77100300)		//   读/写 		索引0，1 的窗口2 调色板数据 			0x0000_0000
#define	rW2PDATA23   	S3C6410_SFR32(0x77100304)		//   读/写 		索引2，3 的窗口2 调色板数据 			0x0000_0000
#define	rW2PDATA45   	S3C6410_SFR32(0x77100308)		//   读/写 		索引4，5 的窗口2 调色板数据 			0x0000_0000
#define	rW2PDATA67   	S3C6410_SFR32(0x7710030C)		//   读/写 		索引6，7 的窗口2 调色板数据 			0x0000_0000
#define	rW2PDATA89   	S3C6410_SFR32(0x77100310)		//   读/写 		索引8，9 的窗口2 调色板数据 			0x0000_0000
#define	rW2PDATAAB   	S3C6410_SFR32(0x77100314)		//   读/写 		索引A，B 的窗口2 调色板数据 			0x0000_0000
#define	rW2PDATACD   	S3C6410_SFR32(0x77100318)		//   读/写 		索引C，D 的窗口2 调色板数据 			0x0000_0000
#define	rW2PDATAEF   	S3C6410_SFR32(0x7710031C)		//   读/写 		索引E，F 的窗口2 调色板数据 			0x0000_0000
#define	rW3PDATA01   	S3C6410_SFR32(0x77100320)		//   读/写 		索引0，1 的窗口3 调色板数据 			0x0000_0000
#define	rW3PDATA23   	S3C6410_SFR32(0x77100324)		//   读/写 		索引2，3 的窗口3 调色板数据 			0x0000_0000
#define	rW3PDATA45   	S3C6410_SFR32(0x77100328)		//   读/写 		索引4，5 的窗口3 调色板数据 			0x0000_0000
#define	rW3PDATA67   	S3C6410_SFR32(0x7710032C)		//   读/写 		索引6，7 的窗口3 调色板数据 			0x0000_0000
#define	rW3PDATA89   	S3C6410_SFR32(0x77100330)		//   读/写 		索引8，9 的窗口3 调色板数据 			0x0000_0000
#define	rW3PDATAAB   	S3C6410_SFR32(0x77100334)		//   读/写 		索引A，B 的窗口3 调色板数据 			0x0000_0000
#define	rW3PDATACD   	S3C6410_SFR32(0x77100338)		//   读/写 		索引C，D 的窗口3 调色板数据 			0x0000_0000
#define	rW3PDATAEF   	S3C6410_SFR32(0x7710033C)		//   读/写 		索引E，F 的窗口3 调色板数据 			0x0000_0000
#define	rW4PDATA01   	S3C6410_SFR32(0x77100340)		//   读/写 		索引0，1 的窗口4 调色板数据 			0x0000_0000
#define	rW4PDATA23   	S3C6410_SFR32(0x77100344)		//   读/写 		索引2，3 的窗口4 调色板数据 			0x0000_0000

#define SetLCD_Windows0()	(rWINCON0 &= ~(0x1<<20))	//显示窗口0
#define SetLCD_Windows1()	(rWINCON0 |= (0x1<<20)		//显示窗口1
#define GetLCD_Windows()	((rWINCON0 & (0x1<<21)) ? 1 : 0)	//获取当前的显示窗口号

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
