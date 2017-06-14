#ifndef __RTC_H__
#define __RTC_H__


#define RTCCON  (*((volatile unsigned long *)0x7E005040))
#define BCDSEC   (*((volatile unsigned long *)0x7E005070))
#define BCDMIN   (*((volatile unsigned long *)0x7E005074))
#define BCDHOUR   (*((volatile unsigned long *)0x7E005078))
#define BCDDATE   (*((volatile unsigned long *)0x7E00507C))
#define BCDDAY   (*((volatile unsigned long *)0x7E005080))
#define BCDMON  (*((volatile unsigned long *)0x7E005084))
#define BCDYEAR   (*((volatile unsigned long *)0x7E005088))


long DEC_to_BCD(long DEC_Code);//10进制值转bcd

long BCD_to_DEC(long BCD_Code);//bcd转10进制

//long year_convert_to_BCD(long DEC);


//long year_convert_to_DEC(long BCD);


void time_printf(void);

void write_open(void);//RTCCON[0]=1,开放写的权限

void write_close(void);//RTCCON[0]=0,关闭写的权限

void set_sec(int DEC_sec);

void set_min(int DEC_min);

void set_hour(int DEC_hour);

void set_week(int DEC_week);

void set_date(int DEC_date);


void set_month(int DEC_month);

void set_year(int DEC_year);




#endif
