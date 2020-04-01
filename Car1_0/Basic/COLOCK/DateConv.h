#ifndef _Conv_H_
#define _Conv_H_


#include "main.h"
extern const u8 year_code[];

///月份数据表
extern const u8 day_code1[];
extern const u16 day_code2[];

/*子函数,用于读取数据表中农历月的大月或小月,如果该月为大返回1,为小返回0*/
static u8 get_moon_day ( u8 month_p, u16 table_addr );
void Conversion ( u8 c, u8 year, u8 month, u8 day );


#endif

