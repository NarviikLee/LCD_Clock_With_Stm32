/*
 * timer_funs.h
 *
 *  Created on: Aug 9, 2024
 *      Author: ihg78
 */

#ifndef LIB_INC_TIMER_FUNS_H_
#define LIB_INC_TIMER_FUNS_H_
#include <time.h>
#define minute_cnt 60

void init_timer_funs();

void get_RTC_Time_t();
void set_RTC_Time_t();

void convert_time_t();
void convert_tm();

void set_tm_strut(int year,int month, int wday, int hour, int minute);
void set_struct_tm(struct tm * calender);
struct tm get_struct_tm();

void set_time_t();
time_t get_time_t();

void update_clock_value();
void update_alarm_value();

#endif /* LIB_INC_TIMER_FUNS_H_ */
