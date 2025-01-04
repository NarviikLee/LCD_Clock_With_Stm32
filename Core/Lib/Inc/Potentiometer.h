/*
 * Potentiometer.h
 *
 *  Created on: Jul 16, 2024
 *      Author: ihg78
 */

#ifndef LIB_INC_POTENTIOMETER_H_
#define LIB_INC_POTENTIOMETER_H_

#include "main.h"
#include "g_var.h"

// 100년 설정 계산 변수(3750/100)
#define YEARCONVERT 37
// 12개월 계산 값 변수 (3750/12)
#define MONTHCONVERT 336

// 28일, 29일, 30일, 31일
#define TWEEIGHT 137
#define TWENINE 133
#define THIRTY 128
#define THIRONE 125
//#define CHECK_VALUE 37

// 모듈내 ADC 핸들러 초기화 함수
void init_PotentioMeter(ADC_HandleTypeDef* Poten);

// ADC값 매핑
int mapping_adc(int adc);

// 시간 및 분 설정
void set_Hour();
void set_Minute();
void set_Second();


// 타이머 계산 함수
void cal_Second();
// 타이머 업데이트 함수
void update_timer();


//void set_Second();


// 날짜 설정 함수
void set_Calender(int mode);

#endif /* LIB_INC_POTENTIOMETER_H_ */
