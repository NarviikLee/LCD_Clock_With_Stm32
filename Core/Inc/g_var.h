/*
 * g_var.h
 *
 *  Created on: Jul 12, 2024
 *      Author: ihg78
 */

#ifndef INC_G_VAR_H_
#define INC_G_VAR_H_

#include "main.h"
#include <time.h>


// 버튼 인터럽트를 위한 전역 변수
extern uint8_t up_btn;
extern uint8_t down_btn;
extern uint8_t select_btn;
extern uint8_t cancel_btn;


//디바이스내에 날짜, 시계 시간, 타이머, 알람 값들을 저장할 배열
extern int calender_value[3];
extern int clock_value[3];
extern int timer_value[3];
extern int alarm_value[3];

// 알람 및 타이머 감지 변수(타이머가 종료되었는가? 알람 시간에 도달했는가?)
extern uint8_t alert_mode;

// 타이머 초 저장 변수
extern int Timer_Second;

// 기기에서 측정 중인 초
extern int device_second;


#endif /* INC_G_VAR_H_ */
