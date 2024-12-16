/*
 * button_control.c
 *
 *  Created on: Jul 17, 2024
 *      Author: ihg78
 */
#include "button_control.h"
#include "timer_mode.h"
#include "lcd_menu.h"
#include "subControl.h"
#include "alert_fs.h"

static int Pos = 0;
static int B_mode = 100;
static int now_mode;


void main_Check(){
	int mode = getMode();
	if(B_mode != mode){
		toggleScreen();
		B_mode = mode;
	}
	// timer가 완료되면 가장 우선순위로 실행되게 해야함
	if(getTimerCompleted() || getAlarmCompleted()){
		int Boozer_mode = getTimerCompleted() == 1 ? 1:(getAlarmCompleted())? 2:0;
		// mode == 1 (Timer Lcd and Event), mode == 2 (Alarm LCd and Event)
		if(Boozer_mode == 1){
			timer_lcd();
		}
		else{
			alarm_lcd();
		}
		if(cancel_btn){
			cancel_btn = 0;
			end_Boozer(Boozer_mode);
			setCompleted(Boozer_mode);
			setMode(-1);
			toggleScreen();
		}
	}
	else if(mode < 0){
		printDefault();
	}
	else if (mode >= 1){
		sub_Menu();
	}else if (mode == 0){
		sel_Pos_control();
		menuSelect();
	}
	if(cancel_btn){
		cancel_btn = 0;
		//if SubMenu or Normal Mode, Return to MenuSelect
//		if((getMode()>0) || (getMode() < 0)){
//			setMode(0);
//			Pos = 0;
//		}
		if(mode < 0){
			setMode(0);
			Pos = 0;
		}
		// -1은 노말 모드 인데, 버튼을 눌렀다는 것은  0 메뉴 셀렉으로 변경
		// if MenuSelect Mode, return to Normal Mode
		else if (mode == 0){
			setMode(-1);
		}
	}
}


void sel_Pos_control(){
	if(up_btn){
		up_btn = 0;
		Pos = getPos()-1;
		if(Pos <0){
			Pos = 2;
		}
		setPos(Pos);
	}
	if(down_btn){
		down_btn = 0;
		Pos = getPos()+1;
		if(Pos >2){
			Pos=0;
		}
		setPos(Pos);
	}
	if(select_btn){
		select_btn = 0;
		now_mode = getMode()+Pos+1;
		setMode(getMode()+Pos+1);
		setPos(0);
		judge_timer();
		HAL_Delay(100);
	}
}

void sub_Menu(){
	if(getMode() >2){
		modify_Process();
	}
	else if (getMode() >1){
		alarm_Process();
	}else if(getMode() >0){
		timer_Process();
	}
}

void judge_timer(){
	if(getTimerState() && getMode()==1){
		// 타이머가 취소되었다는 LCD를 띄우고 clear
		timer_cancle_lcd();
		setTimerState(0);
		setMode(0);
		Timer_Second = 0;
	}
}
