#include "lcd.h"
#include "pic.h"
#include "utils.h"

/* ����0,������0 */
volatile u16 LCD_BUFFER0[LCD_YSIZE][LCD_XSIZE];

/* ��ǰ������ѡ��ָ�� */
volatile u16 (*LCD_BUFFER)[LCD_XSIZE] = LCD_BUFFER0;

/*************************************************************************************************************************
 *����        :	void LCD_Init(void)
 *����        :	LCD��ʼ��
 *����        :	��
 *����        :	��
 *����        : 	�ײ�궨��
 *ʱ��        :	20130607
 *����޸�ʱ��:	20130607
 *˵��        :	��ʼ��TFT LCD
 *************************************************************************************************************************/
void LCD_Init(void){
	
	/* �����Ź�������ΪLCD��ʾ���� */
	GPICON = 0XAAAAAAAA;
	GPJCON = 0XAAAAAAAA;
	
	/* ��SPCON�Ĵ����У������λ��Ϊ01����RGB I/F style */
	SPCON &= ~0x3;
	SPCON |= 0x1;

	/* ��Ƶ������߼�˲̬ʹ�ܽ�ֹ+��ǰ֡ĩβ��Ƶ������߼�˲̬ʹ�ܽ�ֹ */
	rVIDCON0 &= (~(0x1<<1 | 0x1<<0));
	/* ��ֹ��Ƶ�����VIDEO �����ź� */
	rWINCON0 &= ~(0x1<<0);
	
	/* (1)MOFPCON:SEL_BYPASS[3] value@0x7410800C  ��������Ϊ0 */
	rMIFPCON &= ~(1 << 3);

	/* ��Ƶ��������0�Ĵ������� */
	rVIDCON0 = VIDCON0_INTERLACE_F + VIDCON0_VIDOUT + VIDCON0_L1_DATA16 \
			+ VIDCON0_L0_DATA16 + VIDCON0_PNRMODE + VIDCON0_CLKVALUP \
			+ VIDCON0_CLKVAL_F + VIDCON0_VCLKFREE + VIDCON0_CLKDIR \
			+ VIDCON0_CLKSEL_F + VIDCON0_ENVID + VIDCON0_ENVID_F;
	/* ��Ƶ��������1�Ĵ������� */
	rVIDCON1 = VIDCON1_IVCLK + VIDCON1_IHSYNC + VIDCON1_IVSYNC + VIDCON1_IVDEN;
	
	/* ��Ƶʱ�����0�Ĵ������� */
	rVIDTCON0 = VIDTCON0_VBPDE + VIDTCON0_VBPD + VIDTCON0_VFPD + VIDTCON0_VSPW;
	
	/* ��Ƶʱ�����1�Ĵ������� */
	rVIDTCON1 = VIDTCON1_VFPDE + VIDTCON1_HBPD + VIDTCON1_HFPD + VIDTCON1_HSPW;
	/* ��Ƶʱ�����2�Ĵ������� */
	rVIDTCON2 = VIDTCON2_LINEVAL + VIDTCON2_HOZVAL;
	
	/* ����0���ƼĴ������� */
	rWINCON0 = WINCON0_nWide_Narrow + WINCON0_ENLOCAL + WINCON0_BUFSEL \
			+ WINCON0_BUFAUTOEN + WINCON0_BITSWP + WINCON0_BYTSWP \
			+ WINCON0_HAWSWP + WINCON0_InRGB + WINCON0_BURSTLEN \
			+ WINCON0_BPPMODE_F;
	
	/* ����0λ�ÿ���A�Ĵ������� */
	rVIDOSD0A = VIDOSD0A_OSD_LeftTopX_F + VIDOSD0A_OSD_LeftTopY_F;
	/* ����0λ�ÿ���B�Ĵ������� */
	rVIDOSD0B = VIDOSD0B_OSD_RightBotX_F + VIDOSD0B_OSD_RightBotY_F;

	/* ����0λ�ÿ���C�Ĵ������� */
	rVIDOSD0C = VIDOSD0C_OSDSIZE;

	/* ����0����0��ַ��ʼ */
	rVIDW00ADD0B0 = (u32) LCD_BUFFER0;
	/* ����0����0��ַ���� */
	rVIDW00ADD1B0 = (u32) LCD_BUFFER0 + LCD_BUF_SIZE + 1;

	/* ֡�����ַ2�Ĵ��� */
	/* ����ƽ���ҳ���ȴ�ֵ������֡�ڿɿ��Ӷ˿ڵĿ�ȡ�PAGEWIDTH ��ֵ�����ͻ���ߴ�������ֱ߽緶Χ�ڡ�*/
	rVIDW00ADD2 = (0 << 13) | (LCD_HOZVAL * 2);

	/* ѡ����ʾ����0 */
	rWINCON0 &= ~(0x1<<20);

	/* ѡ���Դ�0 */
	LCD_BUFFER = LCD_BUFFER0;

	/* ʹ����ʾ���*/
	/* ��Ƶ������߼�˲̬ʹ��+��ǰ֡ĩβ��Ƶ������߼�˲̬ʹ�� */
	rVIDCON0 |= (0x1<<1 | 0x1<<0);
	/* ʹ����Ƶ�����VIDEO �����ź� */
	rWINCON0 |= 0x1<<0;	
}


/*************************************************************************************************************************
 *����        :	void LCD_ClearScreen(u16 Color)
 *����        :	LCD��������
 *����        :	Color:������ɫ
 *����        :	��
 *����        : 	�ײ�궨��
 *ʱ��        :	20130607
 *����޸�ʱ��:	20130607
 *˵��        :	��Ҫ�ȳ�ʼ��LCD,��ɫֵΪRGB565
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
 ��������Paint_Bmp
 ����  ����LCD��Ļ��ָ������㻭һ��ָ����С��ͼƬ
 ����  ��x0,y0:��ʼ���� h��ͼƬ���   v��ͼƬ�߶�  bmp��ͼƬָ��
 ����ֵ����
 ע��  ��
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


