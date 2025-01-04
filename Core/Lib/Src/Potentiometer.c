/*
 * Potentiometer.c
 *
 *  Created on: Jul 16, 2024
 *      Author: ihg78
 */
#include "Potentiometer.h"
#include "timer_mode.h"
#include "lcd_menu.h"

static ADC_HandleTypeDef * m_adci;


//B501의 경우 ADC 값을 입력 받으면 0~4896까지 받아올 수 있었음
// 그런데 불안정하게 데이터를 받아왔기에 매핑을 통해 0~ 3750까지로 매핑
static int M_Clock_Conver = 63; // 3750/60 = 63
static int H_Clock_Convert = 156; // 3750/ 24 = 156

// 년 단위, 월 단위 계산 변수 저장 배열
static int con_Calender[2] = {YEARCONVERT,MONTHCONVERT};
// 1~12월 까지의 계산 변수 배열(윤년도 포함)
static int con_days[12] = {THIRONE,TWEEIGHT,THIRONE,THIRTY,THIRONE,THIRTY,THIRONE,THIRONE,THIRTY,THIRONE,THIRTY,THIRONE};

// 타이머 설정을 계산을 위한 단위별 초(초단위, 분단위, 시간단위)
// 시간 단위 계산을 쓸 생각은 없지만, 사용할 수도 있으니 저장
static int cal_Seconds[3] = {1,60,3600};

// 가변저항 데이터 저장 변수
static uint16_t m_adc_value;

// 설정한 시간, 분, 초 단위 데이터 저장 변수
static int a_hour_value;
static int t_minute_value;
static int t_second_value;

// 모듈에서 사용할 ADC 핸들러를 초기화하는 함수
void init_PotentioMeter(ADC_HandleTypeDef* Poten){
	m_adci = Poten;
}

// ADC 매핑 함수
int mapping_adc(int adc){
	// 0의 값이 나오기 힘들고, 300이하는 불안하게 잡히므로 300이하의 값은 0으로, 3750초과값은 3750으로
	int map_adc = (adc<300)? 0:((adc-300)>3750)? 3750:(adc-300);
	return map_adc;
}

//가변저항 시간 단위 설정 함수
void set_Hour(){
	HAL_ADC_Start(m_adci);
	HAL_ADC_PollForConversion(m_adci, 500);
	// 매핑 함수를 이용한 ADC값 보정
	m_adc_value = mapping_adc(HAL_ADC_GetValue(m_adci));
	// 시간 계산 변수를 이용한 시간 단위 계산
	a_hour_value = (int)(m_adc_value/H_Clock_Convert);
	// 현재 설정 단위 변수 업데이트(디스플레이 출력을 위해)
	setnHour(a_hour_value);
	// 모드에 따른 디스플레이 출력 변경(2: 알람, 3: 시간 설정)
	if(getMode() == 2){
		//알람 설정 LCD 디스플레이
		n_alarm_show();
	}else if(getMode() == 3){
		// 시간 변경 LCD 디스플레이
		n_modify_show();
	}
}
// 분 단위 입력 함수
void set_Minute(){
	HAL_ADC_Start(m_adci);
	HAL_ADC_PollForConversion(m_adci, 500);
	// 매핑 함수를 이용한 ADC값 보정
	m_adc_value = mapping_adc(HAL_ADC_GetValue(m_adci));
	// 분 단위 계산 변수를 이용한 분 단위 계산
	t_minute_value = (int)(m_adc_value/M_Clock_Conver);
	// 현재 설정 단위 변수 업데이트(디스플레이 출력을 위해)
	setnMinute(t_minute_value);
	// 모드에 따른 디스플레이 출력 변경(1: 타이머 2: 알람, 3: 시간 설정)
	if(getMode() == 1){
		n_timer_show();
	}else if (getMode() == 2){
		n_alarm_show();
	}else if(getMode() == 3){
		n_modify_show();
	}
}
// 초 단위 입력 함수(타이머 설정을 위한 함수)
void set_Second(){
	HAL_ADC_Start(m_adci);
	HAL_ADC_PollForConversion(m_adci, 500);
	// 매핑 함수를 이용한 ADC값 보정
	m_adc_value = mapping_adc(HAL_ADC_GetValue(m_adci));
	// 초 단위 계산 변수를 이용한 초 단위 계산
	t_second_value = (int)(m_adc_value/M_Clock_Conver);
	// 현재 설정 단위 변수 업데이트(디스플레이 출력을 위해)
	setnSecond(t_second_value);
	// 타이머 설정 LCD 디스플레이
	n_timer_show();
}

// 날짜 설정 함수
void set_Calender(int mode){
	HAL_ADC_Start(m_adci);
	HAL_ADC_PollForConversion(m_adci, 500);
	// 매핑 함수를 이용한 ADC값 보정
	m_adc_value = mapping_adc(HAL_ADC_GetValue(m_adci));
	// 모드에 따른 설정 단위 변경(0: 연도 단위, 1: 월 단위, 2: 일 단위)
	if(mode == 0){
		//modify_Year
		setnYear((int)(m_adc_value/con_Calender[mode]));
	}else if(mode == 1){
		// modify Month
		setnMonth((int)(m_adc_value/con_Calender[mode]));
	}
	else if(mode == 2){
		//윤년 계산 및 설정한 월에 따른 일수 계산
		if(getnYear()%4 == 0 && getnMonth() == 1){// 윤년일 때 2월 계산
			setnDay((int)(m_adc_value/TWENINE));
		}else{//달에 따른 일수 계산
			setnDay((int)(m_adc_value/con_days[getnMonth()]));
		}
	}
	n_modify_show();
}

// 설정한 타이머 분과 초를 초단위로 연산 함수
void cal_Second(){
	for(int i = 2; i>=0; i--){
		// 타이머 초 전역 변수(계산을 초 단위로 하기 위해)
		Timer_Second += timer_value[i] * cal_Seconds[i];
		timer_value[i] = 0 ;
	}
	// 설정한 타이머 디바이스 전역 변수 업데이트
	update_timer();
}

// 메인 디스플레이에서 타이머 표시를 위한 연산 함수
void update_timer(){
	timer_value[1] = (int)Timer_Second/60;
	timer_value[0] = (int)Timer_Second%60;
}

