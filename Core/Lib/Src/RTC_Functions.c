/*
 * RTC_Functions.c
 *
 *  Created on: 2024. 8. 9.
 *      Author: ihg78
 */
#include "RTC_Functions.h"
#include "timer_mode.h"

// 알람 데이터 저장 RAM 주소(임의로 설정함)
#define ALARM_FLAG 9
#define ALARM_HOUR 10
#define ALARM_MIN 11
static char ram[DS1302_RAM_SIZE];

// 전원 리부팅 전 알람 설정 유무 확인 함수
int check_Alarm_FLAG(){
	// DS1302 램에 저장된 플래그 값 취득
	int alarm_check = (int)ds1302_read_ram(ALARM_FLAG);
	// 사용한 램 주소(3개) 를 모듈 배열에 저장
	for(int i = ALARM_FLAG; i<ALARM_MIN+1; i++){
		ram[i] = ds1302_read_ram(i);
	}
	return alarm_check;
}
// 알람 설정 데이터 업데이트
void set_Alarm_flag(int Flag){
	ds1302_write_ram(ALARM_FLAG, Flag);
}
//  디바이스 알람 관련 정보업데이트 함수
void get_Alarm(){
	// ram에 저장한 알람 시간, 분 취득
	int hour = ram[ALARM_HOUR];
	int minute = ram[ALARM_MIN];
	// 디바이스 알람 배열 업데이트
	alarm_value[2] = hour;
	alarm_value[1] = minute;
	alarm_value[0] = 0;
	// 알람 설정 상태 업데이트
	setAlarmState(1);
}

// 알람 설정 모드에서 설정한 알람 시간 및 분 단위 설정 함수
void set_Alarm(int Hour, int Min){
	// 알람 설정 업데이트
	set_Alarm_flag(1);
	// DS1302 RAM에 설정 시간 및 분 단위 업데이트
	ds1302_write_ram(ALARM_HOUR, Hour);
	ds1302_write_ram(ALARM_MIN, Min);
	// 디바이스 변수 업데이트
	alarm_value[2] = Hour;
	alarm_value[1] = Min;
}

