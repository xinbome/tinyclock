#include "sysc.h"
#include "utils.h"


unsigned char	g_System_Revision, g_System_Pass, g_SYNCACK;
unsigned int    g_APLL, g_MPLL, g_ARMCLK, g_HCLKx2, g_HCLK, g_PCLK;

//////////
// Function Name : SYSC_GetClkInform
// Function Description : This function gets common clock information
// Input : NONE 
// Output : NONE
// Version : 
void SYSC_GetClkInform( void)
{
	unsigned char muxApll, muxMpll, muxSync;
	unsigned char divApll, divHclkx2, divHclk, divPclk;
	unsigned short pllM, pllP, pllS;
	unsigned int temp;
	
	////
	// clock division ratio	
	temp = Inp32(rCLK_DIV0);
	divApll = temp & 0xf;
	divHclkx2 = (temp>>9) & 0x7;
	divHclk = (temp>>8) & 0x1;
	divPclk = (temp>>12) & 0xf;

	////
	// Operating Mode
	temp = Inp32(rOTHERS);
	temp = (temp>>8)&0xf;
	if(temp)
	{
		g_SYNCACK = 1;
	}
	else
	{
		g_SYNCACK = 0;
	}
	
	////
	// ARMCLK
	muxApll = Inp32(rCLK_SRC) & 0x1;
	if(muxApll)	//FOUT
	{			
		temp = Inp32(rAPLL_CON);
		pllM = (temp>>16)&0x3ff;
		pllP = (temp>>8)&0x3f;
		pllS = (temp&0x7);

		g_APLL = ((FIN>>pllS)/pllP)*pllM;
	}
	else	//FIN
	{
		g_APLL = FIN;
	}
	
	g_ARMCLK = g_APLL/(divApll+1);
	
	////
	// HCLK
	muxSync = (Inp32(rOTHERS)>>7) & 0x1;
	if(muxSync)	//synchronous mode
	{
		g_HCLKx2 = g_APLL/(divHclkx2+1);
		
		temp = Inp32(rMPLL_CON);
		pllM = (temp>>16)&0x3ff;
		pllP = (temp>>8)&0x3f;
		pllS = (temp&0x7);

		g_MPLL = ((FIN>>pllS)/pllP)*pllM;
	}
	else
	{
		muxMpll = (Inp32(rCLK_SRC)>>1) & 0x1;
		if(muxMpll)	//FOUT
		{						
			temp = Inp32(rMPLL_CON);
			pllM = (temp>>16)&0x3ff;
			pllP = (temp>>8)&0x3f;
			pllS = (temp&0x7);

			g_MPLL = ((FIN>>pllS)/pllP)*pllM;
		}
		else	//FIN
		{
			g_MPLL = FIN;
		}
		g_HCLKx2 = g_MPLL/(divHclkx2+1);		
	}
	
	g_HCLK = g_HCLKx2/(divHclk+1);
	
	////
	// PCLK
	g_PCLK = g_HCLKx2/(divPclk+1);

	return;
	
}

