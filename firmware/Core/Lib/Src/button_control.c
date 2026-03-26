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

// 위치 저장 변수
static int Pos = 0;
// 이전 모드
//선택한 모드에서 메뉴 선택으로 돌아올 경우에 선택했던 모드에 커서를 놓아야하기 때문에
static int B_mode = 100;
// 현재 모드(선택한 모드 저장값)
static int now_mode;
// 알람시간이거나 타이머가 종료되었는지 판단 변수
static int Boozer_mode;

void main_Check(){
	int mode = getMode();
	// 이전 메뉴와 현재 모드가 다를경우(즉 메뉴 선택 커서 위치가 변경될 경우)
	if(B_mode != mode){
		// LCD 화면 클리어
		toggleScreen();
		// 이전 모드 업데이트
		B_mode = mode;
	}
	// 타이머가 종료되거나 알람시간일 때를 가장 우선순위로 실행되게 해야함
	// 타이머 관련 모듈을 호출하여 타이머와 알람 상태를 가져옴
	if(getTimerCompleted() || getAlarmCompleted()){// 알람 및 타이머 중 하나라도 달성되었을때
		// 타이머가 종료되면 1, 알람시간일 경우 2
		Boozer_mode = getTimerCompleted() == 1 ? 1:(getAlarmCompleted())? 2:0;
		// 타이머 종료 알림 LCD 디스플레이 출력 함수 호출
		if(Boozer_mode == 1){
			timer_lcd();
		}
		// 알람 시간 알림 LCD 디스플레이 출력 함수 호출
		else{
			alarm_lcd();
		}
		// CANCEL버튼 인터럽트를 통해 타이머 종료 및 알람시간 확인
		if(cancel_btn){
			// CANCEL 버튼 상태 초기화
			cancel_btn = 0;
			// 부저 종료
			end_Boozer(Boozer_mode);
			// 부저 모드에 따른 상태 초기화(1: 타이머 종료, 2: 알람시간)
			setCompleted(Boozer_mode);
			// 메인 LCD 화면 디스플레이 모드 변경(시계 화면 출력 모드)
			setMode(-1);
			// LCD 클리어
			toggleScreen();
		}
	}
	// -1일 경우 시계 모드
	else if(mode < 0){
		printDefault();
	}
	// 1보다 클 경우 선택한 모드 관련 프로세스 진행
	else if (mode >= 1){
		sub_Menu();
	}else if (mode == 0){ // 메뉴 선택 관련 모드 프로세스 진행
		sel_Pos_control();
		menuSelect();
	}
	// CANCEL 버튼 인터럽트 발생시
	if(cancel_btn){
		// CANCEL 버튼 상태 초기화
		cancel_btn = 0;
		// 현 상태가 기본 상태일 경우 메뉴 선택으로 모드변경
		if(mode < 0){
			setMode(0);
			Pos = 0;
		}
		// 메뉴 선택 모드일 경우 기본 상태로 모드 변경
		else if (mode == 0){
			setMode(-1);
		}
	}
}

// 메뉴 선택 위치 조정 함수
void sel_Pos_control(){
	// 버튼 별 인터럽트에 따른 선택 커서 이동
	// 업 버튼 인터럽트 발생시
	if(up_btn){
		// 업버튼 상태 초기화
		up_btn = 0;
		// 위치 변수 -1
		// 왜? Y좌표 인덱스는 위로 올라갈수록 낮아지기 때문에
		Pos = getPos()-1;
		// 0보다 작을 경우 맨 아래 메뉴로 커서 이동
		if(Pos <0){
			Pos = 2;
		}
		setPos(Pos);
	}
	// 다운 버튼 인터럽트 발생시
	if(down_btn){
		// 다운 버튼 상태 초기화
		down_btn = 0;
		// 위치 변수 +1
		// 왜? 메뉴 선택 커서가 내려 갈수록 Y좌표 인덱스는 커지기 때문에
		Pos = getPos()+1;
		// 맨 아래 보다 더 내려갈 경우 맨 위로 선택 커서 이동
		if(Pos >2){
			Pos=0;
		}
		setPos(Pos);
	}
	// 선택 버튼 인터럽트 발생시
	if(select_btn){
		// 선택 버튼 상태 초기화
		select_btn = 0;
		// 현재 모드 설정(+1을 하는이유는?)
		// 인덱스가 0이지만 타이머는 모드가 1이어야함
		//즉 선택한 메뉴에 +1을 해야 선택 모드로 디스플레이 및 프로세스가 진행됨
		now_mode = getMode()+Pos+1;
		setMode(getMode()+Pos+1);
		setPos(0);
		HAL_Delay(100);
	}
}

// 메뉴 선택에 따른 프로세스 진행 함수
// Mode(3: 디바이스 시간 및 날짜 수정, 2: 알람 설정, 1: 타이머 설정)
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
