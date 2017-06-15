#ifndef __SYSC_H__
#define __SYSC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#define SYSCON_BASE				(0x7E00F000)
#define	FIN						12000000

//
#define rAPLL_LOCK			(SYSCON_BASE+0x000)
#define rMPLL_LOCK			(SYSCON_BASE+0x004)
#define rEPLL_LOCK			(SYSCON_BASE+0x008)
#define rAPLL_CON			(SYSCON_BASE+0x00c)
#define rMPLL_CON			(SYSCON_BASE+0x010)
#define rEPLL_CON0			(SYSCON_BASE+0x014)
#define rEPLL_CON1			(SYSCON_BASE+0x018)
#define rCLK_SRC			(SYSCON_BASE+0x01c)
#define rCLK_SRC2			(SYSCON_BASE+0x10c)
#define rCLK_DIV0			(SYSCON_BASE+0x020)
#define rCLK_DIV1			(SYSCON_BASE+0x024)
#define rCLK_DIV2			(SYSCON_BASE+0x028)
#define rCLK_OUT			(SYSCON_BASE+0x02c)
#define rHCLK_GATE			(SYSCON_BASE+0x030)
#define rPCLK_GATE			(SYSCON_BASE+0x034)
#define rSCLK_GATE			(SYSCON_BASE+0x038)
#define rMEM0_CLK_GATE		(SYSCON_BASE+0x03c)

//
#define rAHB_CON0			(SYSCON_BASE+0x100)
#define rAHB_CON1			(SYSCON_BASE+0x104)
#define rAHB_CON2			(SYSCON_BASE+0x108)
#define rSDMA_SEL			(SYSCON_BASE+0x110)
#define rSW_RST				(SYSCON_BASE+0x114)
#define rSYS_ID				(SYSCON_BASE+0x118)
#define rMEM_SYS_CFG		(SYSCON_BASE+0x120)
#define rQOS_OVERRIDE0		(SYSCON_BASE+0x124)
#define rQOS_OVERRIDE1		(SYSCON_BASE+0x128)
#define rMEM_CFG_STAT		(SYSCON_BASE+0x12c)
//
#define rPWR_CFG			(SYSCON_BASE+0x804)
#define rEINT_MASK			(SYSCON_BASE+0x808)
#define rNORMAL_CFG			(SYSCON_BASE+0x810)
#define rSTOP_CFG			(SYSCON_BASE+0x814)
#define rSLEEP_CFG			(SYSCON_BASE+0x818)
#define rSTOP_MEM_CFG		(SYSCON_BASE+0x81C)
#define rOSC_FREQ			(SYSCON_BASE+0x820)
#define rOSC_STABLE			(SYSCON_BASE+0x824)
#define rPWR_STABLE			(SYSCON_BASE+0x828)
#define rFPC_STABLE			(SYSCON_BASE+0x82c)
#define rMTC_STABLE			(SYSCON_BASE+0x830)
#define rBUS_CACHEABLE_CON	(SYSCON_BASE+0x838)

// 
#define rOTHERS				(SYSCON_BASE+0x900)
#define rRST_STAT			(SYSCON_BASE+0x904)
#define rWAKEUP_STAT		(SYSCON_BASE+0x908)
#define rBLK_PWR_STAT		(SYSCON_BASE+0x90c)
#define rINFORM0			(SYSCON_BASE+0xA00)
#define rINFORM1			(SYSCON_BASE+0xA04)
#define rINFORM2			(SYSCON_BASE+0xA08)
#define rINFORM3			(SYSCON_BASE+0xA0c)
#define rINFORM4			(SYSCON_BASE+0xA10)
#define rINFORM5			(SYSCON_BASE+0xA14)
#define rINFORM6			(SYSCON_BASE+0xA18)
#define rINFORM7			(SYSCON_BASE+0xA1c)

extern unsigned char	g_System_Revision, g_System_Pass, g_SYNCACK;
extern unsigned int 	g_MPLL, g_ARMCLK, g_HCLK, g_PCLK, g_MCLK;


void SYSC_GetClkInform( void);

#ifdef __cplusplus
}
#endif

#endif //__SYSC_H__

