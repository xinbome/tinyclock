#ifndef __IIC_H__
#define __IIC_H__


//--------------I2C 模块-----------------------
#define rIICCON0   (*(volatile unsigned char *)(0x7F004000))
#define rIICCON1   (*(volatile unsigned char *)(0x7F00F000))

#define rIICSTAT0  (*(volatile unsigned char *)(0x7F004004))
#define rIICSTAT1  (*(volatile unsigned char *)(0x7F00F004))

#define rIICADD0   (*(volatile unsigned char *)(0x7F004008))
#define rIICADD1   (*(volatile unsigned char *)(0x7F00F008))

#define rIICADD0   (*(volatile unsigned char *)(0x7F004008))
#define rIICADD1   (*(volatile unsigned char *)(0x7F00F008))

#define rIICDS0    (*(volatile unsigned char *)(0x7F00400C))
#define rIICDS1    (*(volatile unsigned char *)(0x7F00F00C))

#define rIICLC0    (*(volatile unsigned char *)(0x7F004010))
#define rIICLC1    (*(volatile unsigned char *)(0x7F00F010))

#define INT_I2C0				(32+18)

//#define S3C6410_PCLK        66500000
#define IIC_FREQ 400000 //定义I2C总线频率


#define GPBCON  (*((volatile unsigned int *)0x7F008800))
#define GPBDAT   (*((volatile unsigned int *)0x7F008808))
#define GPBPUD   (*((volatile unsigned int *)0x7F00880C))

#define COMPAdd1	0x51200000
#define COMPAdd2	0x51300000

#define	SlaveRX			(0)
#define	SlaveTX			(1)
#define	MasterRX		(2)
#define	MasterTX		(3)

void IIC0_Test(void);
void IIC_Close(void);
void IIC_Read(unsigned char cSlaveAddr, unsigned char cAddr, unsigned char *cData);
void IIC_Write(unsigned char cSlaveAddr, unsigned char cAddr, unsigned char cData);
void IIC_Open(unsigned int ufreq);

#endif

