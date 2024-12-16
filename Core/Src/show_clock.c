/*
 * show_clock.c
 *
 *  Created on: 2024. 7. 13.
 *      Author: ihg78
 */

#include "show_clock.h"

static struct tm *t;

void init_clock(void){
	// if can Use a wifi module, get Time from API
	t->tm_year = calender_value[0]-1900;
	t->tm_mon = calender_value[1]-1;
	t->tm_mday = calender_value[2];
	t->tm_hour = clock_value[2];
	t->tm_min = clock_value[1];
	rawtime = mktime(t);
}

void update_clock(int second){
	clock_value[0] = (int)second % 60;
	clock_value[1] = (int)second/ 60;
//	timer_value[2] = second_count / 3600;
}
