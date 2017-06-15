#include "irq.h"
#include "iic.h"
#include "utils.h"
#include "uart.h"

static volatile unsigned char *g_PcIIC_BUFFER;
static volatile unsigned int   g_uIIC_PT;
static volatile unsigned int   g_uIIC_DATALEN;
static volatile unsigned char  g_cIIC_STAT0;
static volatile unsigned char  g_cIIC_SlaveRxDone;
static volatile unsigned char  g_cIIC_SlaveTxDone;

static volatile unsigned char g_PCLK;

static void IIC_Delay(unsigned int u)
{
	volatile int i, j;
	for (j = 0; j < u; j++)
	{
		for (i = 0; i < 1000; i++)
		{
		}
	}
}

void __irq Isr_IIC(void)
{
	unsigned char cCnt;
	unsigned int uTemp0 = 0;

	g_cIIC_STAT0 = rIICSTAT0;

	switch ((g_cIIC_STAT0 >> 6) & 0x3)
	{
	case SlaveRX:
		if (g_uIIC_PT < 101)		// Edited by SOP on 2008/05/23
		{			
			g_PcIIC_BUFFER[g_uIIC_PT++] = rIICDS0;
			IIC_Delay(100);

			uTemp0 = rIICCON0;
			uTemp0 &= ~(1 << 4);			//	Clear pending bit to resume
			uTemp0 &= ~(1 << 7);// Disable Ack generation, Added by SOP on 04/11/2008
			rIICCON0 = uTemp0;

			if (g_uIIC_PT > 100)
			{
				rIICSTAT0 = 0x0;			// Stop Int

				uTemp0 = rIICCON0;
				uTemp0 &= ~(1 << 4);			//	Clear pending bit to resume
				rIICCON0 = uTemp0;

				g_cIIC_SlaveRxDone = 1;

				IIC_Delay(1);			//	wait until Stop Condition is in effect

				//Uart_Printf("*** IIC0 ISR SlaveRX\r\n");		// For Debugging
				break;
			}
			break;
		}
	case SlaveTX:
		if (g_uIIC_PT > 100)
		{
			rIICSTAT0 = 0xd0;		//	Stop Master Tx condition, ACK flag clear

			uTemp0 = rIICCON0;
			uTemp0 &= ~(1 << 4);			//	Clear pending bit to resume
			rIICCON0 = uTemp0;

			g_cIIC_SlaveTxDone = 1;

			IIC_Delay(1);				//	wait until Stop Condition is in effect
			break;
		}

		rIICDS0 = g_PcIIC_BUFFER[g_uIIC_PT++];
		for (cCnt = 0; cCnt < 10; cCnt++)
			;	//	for setup time (rising edge of IICSCL)
		IIC_Delay(100);

		uTemp0 = rIICCON0;
		uTemp0 &= ~(1 << 4);			//	Clear pending bit to resume
		rIICCON0 = uTemp0;

//			Uart_Printf("*** IIC0 ISR SlaveTX\r\n");		// For Debugging
		break;

	case MasterRX:
//			Uart_Printf("*** Entering IIC0 ISR MasterRX\r\n");		// For Debugging

		if (g_uIIC_PT > 0)
			g_PcIIC_BUFFER[g_uIIC_PT - 1] = rIICDS0;

		g_uIIC_PT++;

		if (g_uIIC_PT == g_uIIC_DATALEN)
		{
			uTemp0 = rIICCON0;
			uTemp0 |= (1 << 7);			// Enable Ack generation
			rIICCON0 = uTemp0;	//
		}
		else if (g_uIIC_PT > g_uIIC_DATALEN)
		{
			// Added by SOP on 04/11/2008 -----
			uTemp0 = rIICCON0;
			uTemp0 &= ~(1 << 7);			// Disable Ack generation
			rIICCON0 = uTemp0;	//
			//----------------------------------

			rIICSTAT0 = 0x90;		//	Stop Master Rx condition
		}

		uTemp0 = rIICCON0;
		uTemp0 &= ~(1 << 4);			//	Clear pending bit to resume
		rIICCON0 = uTemp0;

		IIC_Delay(1);		// wait until the stop condition takes effect.
		//Uart_Printf("*** Ended IIC0 ISR MasterRX\r\n");		// For Debugging
		break;

		//Outp32(rIICSTAT0,0xB0);				//	Master Rx Start.

	case MasterTX:
		if (g_uIIC_PT < g_uIIC_DATALEN)
		{
			rIICDS0 = g_PcIIC_BUFFER[g_uIIC_PT];
		}
		else
		{
			// Added by SOP on 04/11/2008 -----
			uTemp0 = rIICCON0;
			uTemp0 &= ~(1 << 7);			// Disable Ack generation
			rIICCON0 = uTemp0;	//
			//----------------------------------

			rIICSTAT0 = 0xd0;	// Stop Master Tx condition, ACK flag clear
			g_uIIC_PT++;	// Added For Test by SOP on 2008/05/27
		}

		g_uIIC_PT++;
		uTemp0 = rIICCON0;
		uTemp0 &= ~(1 << 4);			//	Clear pending bit to resume
		rIICCON0 = uTemp0;

		IIC_Delay(1);// wait until Stop Condition is in effect, Need to here IIC_Delay(1)
		break;
	}

	g_cIIC_STAT0 &= 0xf;
	
	//清除rVIC0ADDR，该寄存器按位记录哪个VIC0中断源曾发生了中断
	Outp32(rVIC0ADDR, 0);
	Outp32(rVIC1ADDR, 0);	
}


//Hz order. freq(Hz) = PCLK/16/clk_divider
void IIC_Open(unsigned int ufreq)		
{
	unsigned int uSelClkSrc;
	unsigned int uClkValue;

//	UART_Printf("\r\n*** IIC0 Setting Frequency: %d Hz\r\n", ufreq);

	INTC_SetISR(INT_I2C0, Isr_IIC);
	INTC_Enable(INT_I2C0);

	GPBCON |= 2 << 20;		//GPB5 I2C SCL[0]
	GPBCON |= 2 << 24;		//GPB6 I2C SDA[0]
	GPBPUD |= 2 << 10;		//10=上拉使能
	GPBPUD |= 2 << 12;		//10=上拉使能

	if ((((g_PCLK >> 4) / ufreq) - 1) > 0xf)
	{
		uSelClkSrc = 1;
		uClkValue = ((g_PCLK >> 9) / ufreq) - 1;		//	PCLK/512/freq
	}
	else
	{
		uSelClkSrc = 0;
		uClkValue = ((g_PCLK >> 4) / ufreq) - 1;		//	PCLK/16/freq
	}

	//Prescaler IICCLK=PCLK/16, Enable interrupt, Transmit clock value Tx clock=IICCLK/16
	rIICCON0 = (uSelClkSrc << 6) | (1 << 5) | (uClkValue & 0xf);
	rIICADD0 = 0xc0;		//	Slave address = [7:1]

	rIICSTAT0 = 0x10;		//	IIC bus data output enable(Rx/Tx)
	rIICLC0 = 0x4;		        //	SDA Filter Enable,delayed 0clks
}

unsigned char IIC_Status(void)	//	Return IIC Status Register value at last interrupt occur.
{
	return g_cIIC_STAT0;
}

void IIC_Wait(void)					//	Waiting for the command takes effect.
{										//	But not for IIC bus free.
	while (g_uIIC_PT <= g_uIIC_DATALEN)
		;
}

void IIC_SetWrite(unsigned char cSlaveAddr, unsigned char *pData, unsigned int uDataLen)
{
	unsigned int uTmp1;

	uTmp1 = rIICSTAT0;

	//	Wait until IIC bus is free or Arbitration successful.
	while ((uTmp1 & (1 << 5)) || (uTmp1 & (1 << 3)))
	{
		uTmp1 = rIICSTAT0;
	}

	g_PcIIC_BUFFER = pData;
	g_uIIC_PT = 0;
	g_uIIC_DATALEN = uDataLen;

	uTmp1 = rIICCON0;
	uTmp1 |= (1 << 7);				// ACK Enable
	rIICCON0 = uTmp1;				// Ack generation Enable
	rIICDS0 = cSlaveAddr;
	rIICSTAT0 = 0xf0;				// Master Tx Start.

	IIC_Wait();		// Added by SOP on 2008/04/10
}

void IIC_SetRead(unsigned char cSlaveAddr, unsigned char *pData, unsigned int uDataLen)
{
	unsigned int uTmp0;
	unsigned int uTmp3;

	uTmp0 = rIICSTAT0;

	//	Wait until IIC bus is free.
	while ((uTmp0 & (1<<5)) || (uTmp0 & (1<<3)))
	{
		uTmp0 = rIICSTAT0;
	}

	g_PcIIC_BUFFER = pData;
	g_uIIC_PT = 0;
	g_uIIC_DATALEN = uDataLen;

	uTmp3 = rIICCON0;
	uTmp3 |= (1 << 7);
	rIICCON0, uTmp3;				//	Ack generation Enable
	rIICDS0 = cSlaveAddr;

	rIICSTAT0 = 0xB0;				//	Master Rx Start.

	IIC_Wait();						// Added by SOP on 2008/04/10
}


void IIC_Write(unsigned char cSlaveAddr, unsigned char cAddr, unsigned char cData)
{
	unsigned char cD[2];

	cD[0] = cAddr;
	cD[1] = cData;

	//	Polling for an ACK signal from Serial EEPROM.
	do
	{
		// Need to time for EEPROM
		IIC_Delay(30);
		IIC_SetWrite(cSlaveAddr, 0, 0);
	} while (IIC_Status() & 0x1);

	IIC_SetWrite(cSlaveAddr, cD, 2);
}

void IIC_Read(unsigned char cSlaveAddr, unsigned char cAddr, unsigned char *cData)
{
	//	Polling for an ACK signal from SerialEEPROM.
	do		
	{
		IIC_SetWrite(cSlaveAddr, 0, 0);
	} while (IIC_Status() & 0x1);

	/* Following EEPROM random address access procedure */
	IIC_SetWrite(cSlaveAddr, &cAddr, 1);
	IIC_SetRead(cSlaveAddr, cData, 1);
}

void IIC_Close(void)
{
	rIICSTAT0 = 0x0;                	//	IIC bus data output disable(Rx/Tx)
	GPBCON &= ~(2 << 20);      //GPB5 I2C SCL[0]
	GPBCON &= ~(2 << 24);      //GPB6 I2C SDA[0]
	GPBPUD &= ~(2 << 10);      //10=上拉使能
	GPBPUD &= ~(2 << 12);      //10=上拉使能
}

void IIC0_Test(void)
{
	unsigned int uCnt, uCntErr = 0, uLoop = 0, uFixcnt = 0;
	unsigned char cData;
	unsigned int uMin = 0x0;
	unsigned int uMax = 0xff;			// KS24C080C: 1KB (8Kbit) = 0x3e8

//	UART_Printf("[ IIC0 Test using Serial EEPROM (AT24C08) ]\r\n");

	IIC_Open(400000);

//	UART_Printf("\nWrite (0x%x ~ 0x%x) and read back from EEPROM (AT24C08)\r\n",uMin, (uMax - 1));
		
	for(uCnt=uMin; uCnt<uMax; uCnt++)
	{
		IIC_Write(0xa0, uCnt, 0x95);
	}
		
		
	for (uCnt=uMin; uCnt<uMax; uCnt++)
	{
		cData = 0;

		IIC_Write(0xa0, uCnt, uCnt);
		IIC_Read(0xa1, uCnt, &cData);

		// If Bus Arbitration failed, So recovery Work Around by SOP on 2008/05/27
		while ((unsigned char) uCnt != cData)
		{			
			IIC_Write(0xa0, uCnt, uCnt);
			IIC_Read(0xa1, uCnt, &cData);
			uFixcnt++;
		}

		// UART_Printf("%02x ", cData);
		if ((uCnt & 0xf) == 0xf){
			UART_Printf("\r\n");
		}
			
	}

	IIC_Close();

	if (uCntErr == 0)
	{
		UART_Printf("\r\nPass: %d Looping (%d Data Repaired)\r\n", uLoop,uFixcnt);
	}
	else
	{
		UART_Printf("\r\n *** Fail: %d count !!!\r\n", uCntErr);
	}
}

