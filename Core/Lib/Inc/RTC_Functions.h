/*
 * RTC_Functions.h
 *
 *  Created on: 2024. 8. 9.
 *      Author: ihg78
 */

#ifndef LIB_INC_RTC_FUNCTIONS_H_
#define LIB_INC_RTC_FUNCTIONS_H_
#include "main.h"
#include <time.h>
#include "g_var.h"

void init_rtc(RTC_HandleTypeDef * hrtc);

int check_RTC(int mode);
void get_Alarm();
void set_Alarm(int Hour, int Min);
void BackupTimeToRTC(time_t currentTime);
time_t RestoreTimeFromRTC();
#endif /* LIB_INC_RTC_FUNCTIONS_H_ */
