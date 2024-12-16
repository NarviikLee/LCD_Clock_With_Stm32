/*
 * RTC_Functions.c
 *
 *  Created on: 2024. 8. 9.
 *      Author: ihg78
 */
#include "RTC_Functions.h"
#include "timer_mode.h"
#define CALENDER_L RTC_BKP_DR1
#define CALENDER_H RTC_BKP_DR2
#define ALARM_HOUR RTC_BKP_DR3
#define ALARM_MIN RTC_BKP_DR4
#define ALARM_FLAG RTC_BKP_DR5

static RTC_HandleTypeDef * r_hrtc;
static int c_state = -1;

void init_rtc(RTC_HandleTypeDef * hrtc){
	r_hrtc = hrtc;
}

int check_RTC(int mode){
	int What_mode = mode;
	switch(What_mode){
	case 1:
		HAL_PWR_EnableBkUpAccess();
		if(HAL_RTCEx_BKUPRead(r_hrtc, CALENDER_H) == 0 && HAL_RTCEx_BKUPRead(r_hrtc, CALENDER_L) == 0){
			c_state = 1;
		}
		else{
			// 여기서 시간 업데이트가 필요해 보여 아니면 RTC 쪽으로 타이머를 조정하거나
			c_state = 0;
		}
		HAL_PWR_DisableBkUpAccess();
		break;

	case 2:
		HAL_PWR_EnableBkUpAccess();
		if(HAL_RTCEx_BKUPRead(r_hrtc, ALARM_FLAG) == 0){
			c_state = 1;
		}
		else{
			c_state = 0;
		}
		HAL_PWR_DisableBkUpAccess();
		break;

	}
	return c_state;
}
void get_Alarm(){
	if (check_RTC(2) == 0){
		HAL_PWR_EnableBkUpAccess();
		int hour = HAL_RTCEx_BKUPRead(r_hrtc, ALARM_HOUR);
		int minute = HAL_RTCEx_BKUPRead(r_hrtc, ALARM_MIN);
		int alert_mode = HAL_RTCEx_BKUPRead(r_hrtc, ALARM_FLAG);
		alarm_value[2] = hour;
		alarm_value[1] = minute;
		alarm_value[0] = 0;
		setAlarmState(alert_mode);
		HAL_PWR_DisableBkUpAccess();
	}
}
void set_Alarm(int Hour, int Min){
	HAL_PWR_EnableBkUpAccess();
	HAL_RTCEx_BKUPWrite(r_hrtc, ALARM_HOUR, (uint32_t)Hour);
	HAL_RTCEx_BKUPWrite(r_hrtc, ALARM_MIN, (uint32_t)Min);
	HAL_RTCEx_BKUPWrite(r_hrtc, ALARM_FLAG, (uint32_t)1);
	HAL_PWR_DisableBkUpAccess();
}

void BackupTimeToRTC(time_t currentTime) {
	HAL_PWR_EnableBkUpAccess();
    // 하위 32비트를 RTC 백업 레지스터에 저장
    HAL_RTCEx_BKUPWrite(r_hrtc, RTC_BKP_DR1, (uint32_t)(currentTime & 0xFFFFFFFF));
    // 상위 32비트를 RTC 백업 레지스터에 저장
    HAL_RTCEx_BKUPWrite(r_hrtc, RTC_BKP_DR2, (uint32_t)((currentTime >> 32) & 0xFFFFFFFF));
    HAL_PWR_DisableBkUpAccess();
}

time_t RestoreTimeFromRTC() {
	HAL_PWR_EnableBkUpAccess();
    // 하위 32비트를 RTC 백업 레지스터에서 읽음
    uint32_t low = HAL_RTCEx_BKUPRead(r_hrtc, RTC_BKP_DR1);
    // 상위 32비트를 RTC 백업 레지스터에서 읽음
    uint32_t high = HAL_RTCEx_BKUPRead(r_hrtc, RTC_BKP_DR2);
    HAL_PWR_DisableBkUpAccess();
    // 상위 32비트를 왼쪽으로 32비트 이동한 후, 하위 32비트와 결합하여 64비트 데이터로 복원
    return ((time_t)high << 32) | low;
}
