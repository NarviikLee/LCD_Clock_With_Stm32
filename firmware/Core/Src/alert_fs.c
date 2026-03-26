/*
 * alert_fs.c
 *
 *  Created on: Jul 12, 2024
 *      Author: ihg78
 */
#include "alert_fs.h"
#include "timer_mode.h"
#include "ssd1306.h"
#include "esp32_dht11.h"

// 디버깅용 변수
//static int alarm_check = 0;


// 알람 시간 도달 및 타이머 종료시 부저를 울리는 함수
void start_Boozer(int mode){
	//LCD 초기화 업데이트를 위해
	toggleScreen();
	// 타이머 종료일 경우
	if(mode == 1){
		// 타이머 설정을 OFF로 함 대신 메인 루프에서 타이머 종료를 알림
		setTimerState(0);
	}
	// 부저 울림 시작
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, htim4.Init.Period);
}

// 부저 울림을 종료하는 함수
void end_Boozer(int mode){
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, 0);
	// 모드에 따른 완료 변수 수정함수
	setCompleted(mode);
}

// 알람 시간 체크 함수
void check_Alarm(){
	// 디바이스 시간과 알람 시간 체크
	if((alarm_value[2] == clock_value[2]) && (alarm_value[1] == clock_value[1])){
		// 알람 설정 ON인지 확인
		int alarm_check = getAlarmState();
		if(alarm_check && clock_value[0] == 0){// 알람 설정을 했을 경우
			// 부저를 울림
			start_Boozer(2);
			// 그리고 알람 시간 업데이트 함수 호출
			setAlarmCompleted(1);
		}
	}
}
