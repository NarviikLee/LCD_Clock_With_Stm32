/*
 * RTC_Functions.c
 *
 *  Created on: 2024. 8. 9.
 *      Author: ihg78
 */
#include "RTC_Functions.h"
#include "timer_mode.h"

#define ALARM_FLAG 9
#define ALARM_HOUR 10
#define ALARM_MIN 11
static char ram[DS1302_RAM_SIZE];
int check_Alarm_FLAG(){
	int alarm_check = (int)ds1302_read_ram(ALARM_FLAG);
	for(int i = ALARM_FLAG; i<ALARM_MIN+1; i++){
		ram[i] = ds1302_read_ram(i);
	}
	return alarm_check;
}

void set_Alarm_flag(int Flag){
	ds1302_write_ram(ALARM_FLAG, Flag);
}
void get_Alarm(){
	int hour = ram[ALARM_HOUR];
	int minute = ram[ALARM_MIN];
	alarm_value[2] = hour;
	alarm_value[1] = minute;
	alarm_value[0] = 0;
	setAlarmState(1);
}
void set_Alarm(int Hour, int Min){
	set_Alarm_flag(1);
	ds1302_write_ram(ALARM_HOUR, Hour);
	ds1302_write_ram(ALARM_MIN, Min);
}

