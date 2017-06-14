#include "lcd.h"
#include "pic.h"
#include "utils.h"

/* 窗口0,缓冲区0 */
volatile u16 LCD_BUFFER0[LCD_YSIZE][LCD_XSIZE];

/* 当前缓冲区选择指针 */
volatile u16 (*LCD_BUFFER)[LCD_XSIZE] = LCD_BUFFER0;

/*************************************************************************************************************************
 *函数        :	void LCD_Init(void)
 *功能        :	LCD初始化
 *参数        :	无
 *返回        :	无
 *依赖        : 	底层宏定义
 *时间        :	20130607
 *最后修改时间:	20130607
 *说明        :	初始化TFT LCD
 *************************************************************************************************************************/
void LCD_Init(void){
	
	/* 将引脚功能配置为LCD显示功能 */
	GPICON = 0XAAAAAAAA;
	GPJCON = 0XAAAAAAAA;
	
	/* 将SPCON寄存器中，最低两位设为01，即RGB I/F style */
	SPCON &= ~0x3;
	SPCON |= 0x1;

	/* 视频输出和逻辑瞬态使能禁止+当前帧末尾视频输出和逻辑瞬态使能禁止 */
	rVIDCON0 &= (~(0x1<<1 | 0x1<<0));
	/* 禁止视频输出和VIDEO 控制信号 */
	rWINCON0 &= ~(0x1<<0);
	
	/* (1)MOFPCON:SEL_BYPASS[3] value@0x7410800C  必须设置为0 */
	rMIFPCON &= ~(1 << 3);

	/* 视频主控制器0寄存器配置 */
	rVIDCON0 = VIDCON0_INTERLACE_F + VIDCON0_VIDOUT + VIDCON0_L1_DATA16 \
			+ VIDCON0_L0_DATA16 + VIDCON0_PNRMODE + VIDCON0_CLKVALUP \
			+ VIDCON0_CLKVAL_F + VIDCON0_VCLKFREE + VIDCON0_CLKDIR \
			+ VIDCON0_CLKSEL_F + VIDCON0_ENVID + VIDCON0_ENVID_F;
	/* 视频主控制器1寄存器配置 */
	rVIDCON1 = VIDCON1_IVCLK + VIDCON1_IHSYNC + VIDCON1_IVSYNC + VIDCON1_IVDEN;
	
	/* 视频时序控制0寄存器配置 */
	rVIDTCON0 = VIDTCON0_VBPDE + VIDTCON0_VBPD + VIDTCON0_VFPD + VIDTCON0_VSPW;
	
	/* 视频时序控制1寄存器配置 */
	rVIDTCON1 = VIDTCON1_VFPDE + VIDTCON1_HBPD + VIDTCON1_HFPD + VIDTCON1_HSPW;
	/* 视频时序控制2寄存器配置 */
	rVIDTCON2 = VIDTCON2_LINEVAL + VIDTCON2_HOZVAL;
	
	/* 窗口0控制寄存器配置 */
	rWINCON0 = WINCON0_nWide_Narrow + WINCON0_ENLOCAL + WINCON0_BUFSEL \
			+ WINCON0_BUFAUTOEN + WINCON0_BITSWP + WINCON0_BYTSWP \
			+ WINCON0_HAWSWP + WINCON0_InRGB + WINCON0_BURSTLEN \
			+ WINCON0_BPPMODE_F;
	
	/* 窗口0位置控制A寄存器配置 */
	rVIDOSD0A = VIDOSD0A_OSD_LeftTopX_F + VIDOSD0A_OSD_LeftTopY_F;
	/* 窗口0位置控制B寄存器配置 */
	rVIDOSD0B = VIDOSD0B_OSD_RightBotX_F + VIDOSD0B_OSD_RightBotY_F;

	/* 窗口0位置控制C寄存器配置 */
	rVIDOSD0C = VIDOSD0C_OSDSIZE;

	/* 窗口0缓冲0地址开始 */
	rVIDW00ADD0B0 = (u32) LCD_BUFFER0;
	/* 窗口0缓冲0地址结束 */
	rVIDW00ADD1B0 = (u32) LCD_BUFFER0 + LCD_BUF_SIZE + 1;

	/* 帧缓冲地址2寄存器 */
	/* 虚拟平面的页面宽度此值定义了帧内可可视端口的宽度。PAGEWIDTH 的值必须比突发尺寸大且在字边界范围内。*/
	rVIDW00ADD2 = (0 << 13) | (LCD_HOZVAL * 2);

	/* 选择显示窗口0 */
	rWINCON0 &= ~(0x1<<20);

	/* 选择显存0 */
	LCD_BUFFER = LCD_BUFFER0;

	/* 使能显示输出*/
	/* 视频输出和逻辑瞬态使能+当前帧末尾视频输出和逻辑瞬态使能 */
	rVIDCON0 |= (0x1<<1 | 0x1<<0);
	/* 使能视频输出和VIDEO 控制信号 */
	rWINCON0 |= 0x1<<0;	
}


/*************************************************************************************************************************
 *函数        :	void LCD_ClearScreen(u16 Color)
 *功能        :	LCD清屏函数
 *参数        :	Color:清屏颜色
 *返回        :	无
 *依赖        : 	底层宏定义
 *时间        :	20130607
 *最后修改时间:	20130607
 *说明        :	需要先初始化LCD,颜色值为RGB565
 *************************************************************************************************************************/
void LCD_ClearScreen(u16 Color)
{
	u16 x, y;

	for (x = 0; x < LCD_XSIZE; x++)
	{
		for (y = 0; y < LCD_YSIZE; y++)
		{
			LCD_BUFFER[y][x] = Color;
		}
	}
}


/************************************************************************
 函数名：Paint_Bmp
 功能  ：在LCD屏幕上指定坐标点画一个指定大小的图片
 参数  ：x0,y0:开始坐标 h：图片宽度   v：图片高度  bmp：图片指针
 返回值：无
 注意  ：
 ************************************************************************/
void Paint_Bmp(int x0, int y0, int h, int v, const unsigned char bmp[])
{
	int x, y;
	u32 c;
	int p = 0;

	for (y = y0; y < v + y0; y++)
	{
		for (x = x0; x < h + x0; x++)
		{
			c = bmp[p] | (bmp[p + 1] << 8);
			if ((x < LCD_X_SIZE) && (y < LCD_Y_SIZE))
				LCD_BUFFER[y][x] = c;
			p = p + 2;
		}
	}
}


