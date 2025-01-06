/*
 * RTC_Functions.h
 *
 *  Created on: 2024. 8. 9.
 *      Author: ihg78
 */

#ifndef LIB_INC_RTC_FUNCTIONS_H_
#define LIB_INC_RTC_FUNCTIONS_H_
#include <device_var.h>
#include "main.h"
#include <time.h>
#include "ds1302.h"

// DS1302 를 이용해서 알람 및 DS1302에 내장된 시간 데이터를 가져오거나 설정(modify, 보드 재부팅시 이전 시간가져오기)
int check_Alarm_FLAG();
void set_Alarm_flag(int Flag);
void get_Alarm();
void set_Alarm(int Hour, int Min);

#endif /* LIB_INC_RTC_FUNCTIONS_H_ */
