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

static int M_Clock_Conver = 63;
static int H_Clock_Convert = 156;
static int con_Calender[2] = {YEARCONVERT,MONTHCONVERT};
//static int con_days[12] = {136,151,136,141,136,141,136,136,141,136,141,136};
static int con_days[12] = {THIRONE,TWEEIGHT,THIRONE,THIRTY,THIRONE,THIRTY,THIRONE,THIRONE,THIRTY,THIRONE,THIRTY,THIRONE};

static int cal_Seconds[3] = {1,60,3600};


static uint16_t m_adc_value;

//static float m_voltage;
static int a_hour_value;
static int t_minute_value;
static int t_second_value;

void init_PotentioMeter(ADC_HandleTypeDef* Poten){
	m_adci = Poten;
}
int mapping_adc(int adc){
	int map_adc = (adc<300)? 0:((adc-300)>3750)? 3750:(adc-300);
	return map_adc;
}
void check_adc_change(){
	HAL_ADC_Start(m_adci);
	HAL_ADC_PollForConversion(m_adci, 500);
	m_adc_value = mapping_adc(HAL_ADC_GetValue(m_adci));
	a_hour_value = (int)(m_adc_value/CHECK_VALUE);
}


void set_Hour(){
	HAL_ADC_Start(m_adci);
	HAL_ADC_PollForConversion(m_adci, 500);
	m_adc_value = mapping_adc(HAL_ADC_GetValue(m_adci));
	a_hour_value = (int)(m_adc_value/H_Clock_Convert);
	setnHour(a_hour_value);
	if(getMode() == 2){
		n_alarm_show();
	}else if(getMode() == 3){
		n_modify_show();
	}
}

void set_Minute(){
	HAL_ADC_Start(m_adci);
	HAL_ADC_PollForConversion(m_adci, 500);
	m_adc_value = mapping_adc(HAL_ADC_GetValue(m_adci));
	t_minute_value = (int)(m_adc_value/M_Clock_Conver);
	setnMinute(t_minute_value);
	if(getMode() == 1){
		n_timer_show();
	}else if (getMode() == 2){
		n_alarm_show();
	}else if(getMode() == 3){
		n_modify_show();
	}
}

void set_Second(){
	HAL_ADC_Start(m_adci);
	HAL_ADC_PollForConversion(m_adci, 500);
	m_adc_value = mapping_adc(HAL_ADC_GetValue(m_adci));
	t_second_value = (int)(m_adc_value/M_Clock_Conver);
	setnSecond(t_second_value);
	n_timer_show();
}

void set_Calender(int mode){
	HAL_ADC_Start(m_adci);
	HAL_ADC_PollForConversion(m_adci, 500);
	m_adc_value = mapping_adc(HAL_ADC_GetValue(m_adci));
	if(mode == 0){
		//modify_Year
		setnYear((int)(m_adc_value/con_Calender[mode]));
	}else if(mode == 1){
		// modify Month
		setnMonth((int)(m_adc_value/con_Calender[mode]));
	}
	else if(mode == 2){
		//modify days( Year is leap year and Month is Feb, days Range is 0~29)
		if(getnYear()%4 == 0 && getnMonth() == 1){
			setnDay((int)(m_adc_value/TWENINE));
		}else{
			setnDay((int)(m_adc_value/con_days[getnMonth()]));
		}
	}
	n_modify_show();
}


void cal_Second(){
	for(int i = 2; i>=0; i--){
		Timer_Second += timer_value[i] * cal_Seconds[i];
		timer_value[i] = 0 ;
	}
	update_timer();
}
void update_timer(){
	timer_value[1] = (int)Timer_Second/60;
	timer_value[0] = (int)Timer_Second%60;
}

