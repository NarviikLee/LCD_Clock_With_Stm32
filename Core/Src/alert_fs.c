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

static int alarm_check = 0;
void start_Boozer(int mode){
	toggleScreen();
	if(mode ==1){
		setTimerState(0);
	}
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, htim4.Init.Period);
	setCompleted(mode);
}

void end_Boozer(int mode){
	if(mode == 1){
		alert_mode = 0;
	}else{
		alarm_check = 0;
	}
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, 0);
	setCompleted(mode);
}

void check_Alarm(){
	if((alarm_value[2] == clock_value[2]) && (alarm_value[1] == clock_value[1])){
		if(!alarm_check && clock_value[0] == 0){
			alarm_check = 1;
			start_Boozer(2);
			setAlarmCompleted(1);
		}
	}
}
