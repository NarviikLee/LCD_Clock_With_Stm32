/*
 * timer_funs.c
 *
 *  Created on: Aug 9, 2024
 *      Author: ihg78
 */

#include "timer_funs.h"
#include "timer_mode.h"
#include "RTC_Functions.h"
#include "g_var.h"
#include "esp32_dht11.h"

static time_t sec_con;
static struct tm current_time;
static Time_s ds1302_time ={0};


void init_timer_funs(){
	get_DS1302_Time_s();
	set_static_Time_t();
	convert_time_t();
	update_clock_value();
	set_send_cnt(current_time.tm_hour);
}
void update_clock_value(){
	clock_value[2] = current_time.tm_hour;
	clock_value[1] = current_time.tm_min;
	clock_value[0] = device_second;
	//  여기서 온도데이터 업데이트를 진행핼까?
	if(clock_value[1] == 0){
		check_send();
	}
}

void set_tm_strut(int year,int month, int mday, int hour, int minute){
	current_time.tm_year= year+100;
	current_time.tm_mon = month;
	current_time.tm_mday = mday;
	current_time.tm_hour = hour;
	current_time.tm_min = minute;
	set_send_cnt(hour);
	convert_time_t();
}

void set_static_Time_t(){
	current_time.tm_year= (int)ds1302_time.year+100;
	current_time.tm_mon = (int)ds1302_time.month-1;
	current_time.tm_mday = (int)ds1302_time.date;
	current_time.tm_hour = (int)ds1302_time.hour;
	current_time.tm_min = (int)ds1302_time.min;
	device_second = (int)ds1302_time.sec;
}

// DS1302에서 데이터를 읽어오고 읽어온 데이터를 current_time에 추가(초까지)
void get_DS1302_Time_s(){
	ds1302_get_time(&ds1302_time);
}

// 시간 수정시 current_time를 업데이트하고 이후에 Time_s 구조체에 입력하고 DS1302에 업데이트
void set_DS1302_Time_s(){
	ds1302_time.year = current_time.tm_year-100;
	ds1302_time.month = current_time.tm_mon+1;
	ds1302_time.day = current_time.tm_wday < 1? 7:current_time.tm_wday;
	ds1302_time.date= current_time.tm_mday;
	ds1302_time.hour = current_time.tm_hour;
	ds1302_time.min = current_time.tm_min;
	ds1302_set_time(&ds1302_time);
}


void convert_time_t(){
	sec_con = mktime(&current_time);
}

void convert_tm(){
	current_time = *localtime(&sec_con);
}

void set_struct_tm(struct tm * calender){
	current_time = *calender;
}
struct tm get_struct_tm(){
	return current_time;
}

void set_time_t(){
	sec_con += minute_cnt;
	convert_tm();
	update_clock_value();
}

time_t get_time_t(){
	return sec_con;
}

