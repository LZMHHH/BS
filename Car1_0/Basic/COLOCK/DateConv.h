#ifndef _Conv_H_
#define _Conv_H_


#include "main.h"
extern const u8 year_code[];

///�·����ݱ�
extern const u8 day_code1[];
extern const u16 day_code2[];

/*�Ӻ���,���ڶ�ȡ���ݱ���ũ���µĴ��»�С��,�������Ϊ�󷵻�1,ΪС����0*/
static u8 get_moon_day ( u8 month_p, u16 table_addr );
void Conversion ( u8 c, u8 year, u8 month, u8 day );


#endif

