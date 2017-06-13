#include "rtc.h"


char *day[8] = 
{
	"","Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"
};


long DEC_to_BCD(long DEC_Code){
	int temp;
	
	if(DEC_Code > 99){return 0;}
	temp = DEC_Code/10;
	temp <<= 4;
	temp += DEC_Code%10;
	return temp; 	
}


long BCD_to_DEC(long BCD_Code){
	return ((BCD_Code >> 4)*10+(BCD_Code&0x0f));
}

/*
long year_convert_to_BCD(long DEC){
	long temp1,temp2,total;
	temp2 = DEC % 100;
	temp1 = DEC/100;
	total = DEC_to_BCD(temp1) << 8 + DEC_to_BCD(temp2);	 
	return total;
	
}

long year_convert_to_DEC(long BCD){
	long temp1,temp2,total;
	temp1 = BCD >> 8;
	temp2 = BCD & 0x00FF;
	total = BCD_to_DEC(temp1) * 100 + BCD_to_DEC(temp2);
	return total;
}

*/
void time_printf(void)
{
	long uyear,umonth,udate,uhour,umin,usec,uday;
	Delay(20);
	uyear = BCD_to_DEC(BCDYEAR) + 2000;
	umonth = BCD_to_DEC(BCDMON);	
	udate = BCD_to_DEC(BCDDATE);	
	uhour = BCD_to_DEC(BCDHOUR);
	umin = BCD_to_DEC(BCDMIN);
	usec = BCD_to_DEC(BCDSEC);
	uday = BCD_to_DEC(BCDDAY);
	
	UART_Printf("%2ld:%2ld:%2ld\t %10s, %2ld/%2ld/%4ld\n",uhour,umin,usec,day[uday],umonth,udate,uyear);
}

void write_open(void)
{
	unsigned int value = 0;
	
	value = RTCCON;
	value |= 0x1;
	
	RTCCON = value;		
}


void write_close(void)
{
	unsigned int value = 0;
	
	value = RTCCON;
	value &= ~0x1;
	
	RTCCON = value;		
}


void set_sec(int DEC_sec)
{
	BCDSEC = DEC_to_BCD(DEC_sec);
}

void set_min(int DEC_min)
{
	BCDMIN = DEC_to_BCD(DEC_min);	
}

void set_hour(int DEC_hour)
{
	BCDHOUR = DEC_to_BCD(DEC_hour);
}

void set_day(int DEC_day)
{
	BCDDAY = DEC_to_BCD(DEC_day);	
}

void set_date(int DEC_date)
{
	BCDDATE = DEC_to_BCD(DEC_date);	
}


void set_month(int DEC_month)
{
	BCDMON = DEC_to_BCD(DEC_month);	
}

void set_year(int DEC_year)
{
	if(DEC_year > 2000) 
	{		
		BCDYEAR = DEC_to_BCD(DEC_year - 2000);
	}
}