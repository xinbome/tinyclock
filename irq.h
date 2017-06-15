#ifndef __IRQ_H__
#define __IRQ_H__


#define VIC0_BASE				(0x71200000)
#define VIC1_BASE				(0x71300000)

// VIC0
#define	rVIC0IRQSTATUS			(VIC0_BASE + 0x00)
#define	rVIC0FIQSTATUS			(VIC0_BASE + 0x04)
#define	rVIC0RAWINTR			(VIC0_BASE + 0x08)
#define	rVIC0INTSELECT			(VIC0_BASE + 0x0c)
#define	rVIC0INTENABLE			(VIC0_BASE + 0x10)
#define	rVIC0INTENCLEAR			(VIC0_BASE + 0x14)
#define	rVIC0SOFTINT			(VIC0_BASE + 0x18)
#define	rVIC0SOFTINTCLEAR		(VIC0_BASE + 0x1c)
#define	rVIC0PROTECTION			(VIC0_BASE + 0x20)
#define	rVIC0SWPRIORITYMASK		(VIC0_BASE + 0x24)
#define	rVIC0PRIORITYDAISY		(VIC0_BASE + 0x28)

#define rVIC0VECTADDR			(VIC0_BASE + 0x100)

#define rVIC0VECPRIORITY		(VIC0_BASE + 0x200)

#define rVIC0ADDR				(VIC0_BASE + 0xf00)
#define rVIC0PERID0				(VIC0_BASE + 0xfe0)
#define rVIC0PERID1				(VIC0_BASE + 0xfe4)
#define rVIC0PERID2				(VIC0_BASE + 0xfe8)
#define rVIC0PERID3				(VIC0_BASE + 0xfec)
#define rVIC0PCELLID0			(VIC0_BASE + 0xff0)
#define rVIC0PCELLID1			(VIC0_BASE + 0xff4)
#define rVIC0PCELLID2			(VIC0_BASE + 0xff8)
#define rVIC0PCELLID3			(VIC0_BASE + 0xffc)

// VIC1
#define	rVIC1IRQSTATUS			(VIC1_BASE + 0x00)
#define	rVIC1FIQSTATUS			(VIC1_BASE + 0x04)
#define	rVIC1RAWINTR			(VIC1_BASE + 0x08)
#define	rVIC1INTSELECT			(VIC1_BASE + 0x0c)
#define	rVIC1INTENABLE			(VIC1_BASE + 0x10)
#define	rVIC1INTENCLEAR			(VIC1_BASE + 0x14)
#define	rVIC1SOFTINT			(VIC1_BASE + 0x18)
#define	rVIC1SOFTINTCLEAR		(VIC1_BASE + 0x1c)
#define	rVIC1PROTECTION			(VIC1_BASE + 0x20)
#define	rVIC1SWPRIORITYMASK		(VIC1_BASE + 0x24)
#define	rVIC1PRIORITYDAISY		(VIC1_BASE + 0x28)

#define rVIC1VECTADDR			(VIC1_BASE + 0x100)
#define rVIC1VECPRIORITY		(VIC1_BASE + 0x200)

#define rVIC1ADDR				(VIC1_BASE + 0xf00)
#define rVIC1PERID0				(VIC1_BASE + 0xfe0)
#define rVIC1PERID1				(VIC1_BASE + 0xfe4)
#define rVIC1PERID2				(VIC1_BASE + 0xfe8)
#define rVIC1PERID3				(VIC1_BASE + 0xfec)
#define rVIC1PCELLID0			(VIC1_BASE + 0xff0)
#define rVIC1PCELLID1			(VIC1_BASE + 0xff4)
#define rVIC1PCELLID2			(VIC1_BASE + 0xff8)
#define rVIC1PCELLID3			(VIC1_BASE + 0xffc)

#define EINT0MASK  (*((volatile unsigned int *)0x7F008920))
#define EINT0PEND  (*((volatile unsigned int *)0x7F008924))

void INTC_Enable(unsigned int intNum);
void INTC_SetISR(unsigned int intNum, void (*isr)(void) __irq);

void EINT_Clr0Pend(unsigned int uEINT_No );
void EINT_Dis0Mask(unsigned int uEINT_No );

#endif//__IRQ_H__
