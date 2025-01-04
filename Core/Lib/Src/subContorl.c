/*
 * subContorl.c
 *
 *  Created on: 2024. 7. 21.
 *      Author: ihg78
 */

#include <stdbool.h>
#include "subControl.h"
#include "Potentiometer.h"
#include "lcd_menu.h"
#include "timer_mode.h"
#include "timer_funs.h"
#include "RTC_Functions.h"
// t_Process_case 0 is minute, 1 is second, 2 is timer_value_update and Calculate second
static int t_Process_case = 0;
// a_Process_case 0 is check the alarm(if alarm State is On, Start the from step 0 ), 1 = second step .... n= n+1 Step
static int a_Process_case = 0;
// m_Process case is Modify the Clock's Hour and Minute Process_number, 0 is hour Modify, 1 is Minute Modify,
// i think Add a mode, year,month,day Modify Modes
static int m_Process_case = 0;


// 버튼 컨트롤 함수(SEL버튼을 누르는가, CANCEL 버튼을 누르는가 체크)
bool handleButtonPress(int *process_case, int increment) {
    if (select_btn) {
        select_btn = 0;  // 버튼 인터럽트 초기화
        if(*process_case >99){ // 알람 초기화 및 변경 체크 상태일 경우
        	// 알람 시간 변경을 위해 알람 프로세스 진행 및 알람 설정 초기화
        	setAlarmState(0);
        	set_Alarm_flag(0);
			*process_case = 0;
		}else{
			// 다음 단계 진행
			*process_case += increment;
		}
        return true;  // 1은 true
    }else if (cancel_btn){
    	cancel_btn = 0; // 버튼 인터럽트 초기화
    	if(*process_case >99){// 기존 알람 데이터 유지
    		// 메뉴 선택창으로 모드 변경
    		setMode(0);
    	}else{
    		// 이전 단계로 진행
    		*process_case -= increment;
    	}
    	if(*process_case < 0){
    		// 0단계보다 이전 단계로 진행시 디스플레이 모드로 모드 변경
    		*process_case=0;
    		// 0모드 -> 디스플레이 모드
    		setMode(0);
    	}
    	return false;  // 0은 false
    }
}

// 타이머 분 단위 설정 단계
void processTimerMinute() {
	// 가변저항을 이용한 분 단위 설정
    set_Minute();
    if (handleButtonPress( &t_Process_case, 1)== true) {
    	// 디바이스 타이머 배열에 저장
        timer_value[1] = getnMinute();
    }
}
// 타이머 초 단위 설정 단계
void processTimerSecond() {
	// 가변저항을 이용한 초 단위 설정
    set_Second();
    if (handleButtonPress(&t_Process_case, 1) == true) {
    	// 디바이스 타이머 배열에 저장
        timer_value[0] = getnSecond();
    }
}


// 타이머 최종 확인 단계
void processTimerReview() {
	// 타이머 최종 확인 디스플레이 출력
    check_timer_lcd();
    if (handleButtonPress(&t_Process_case, 1)== true) {
    	//디바이스 내 타이머 변수 업데이트
        cal_Second();
        t_Process_case = 0;
        // 타이머 시작
        setTimerState(1);
        // 설정 단위 변수 초기화
        setnMinute(0);
        setnSecond(0);
        setMode(-1);
    }
}


// 알람 수정 및 리셋 확인 단계
void processAlarmChangeCheck() {
	check_alarm_change_lcd();
    if (handleButtonPress(&a_Process_case, 1)== true) {
    	// 알람 설정 초기화
        setAlarmState(0);
        // 다음 단계 LCD 출력을 위한 LCD 클리어
        toggleScreen();
    }
}

// 알람 시간 단위 설정 단계
void processAlarmHour(int *input_Process_case) {
	// 가변저항을 이용한 시간 단위 설정
    set_Hour();
    if (handleButtonPress(input_Process_case, 1) == true) {
    	int mode = getMode();
    	// 알람 설정일 경우 디바이스 내부 알람 변수에 저장
    	if(mode==2){
    		alarm_value[2] = getnHour();
    	}else if(mode==3){
        // 시간 변경일 경우 디바이스 시간 변수에 저장
    		clock_value[2] = getnHour();
    	}
    }
}

// 알람 분 단위 설정 단계
void processAlarmMinute(int *input_Process_case){
	// 가변저항을 이용한 분 단위 설정
    set_Minute();
    if (handleButtonPress(input_Process_case, 1) == true) {
    	// 현재 무슨 메뉴인가를 체크(2:알람 설정, 3:디바이스 시간 및 날짜 수정)
    	int mode = getMode();
    	if(mode == 2){
    		alarm_value[1] = getnMinute();
    	}else if(mode ==3){
    		clock_value[1] = getnMinute();
    	}
    }
}

// 알람 최종 확인 단계
void processAlarmReview() {
	// 최종 확인 디스플레이 출력
    check_alarm_lcd();
    handleButtonPress( &a_Process_case, 1);
}


// 설정한 알람 적용 단계
void processAlarmFinalization() {
	// 알람 설정 ON
	setAlarmState(1);
	// 설정한 시간단위와 분 단위를 변수에 저장
	int aHour = getnHour();
	int aMin = getnMinute();
	// 알람 설정 상태 및 시간, 분등을 DS1302 램에 저장 및 디바이스 내 알람 배열에 저장
	set_Alarm(aHour,aMin);
	// 설정 시간 단위 및 분 단위 초기화
    setnHour(0);
    setnMinute(0);
    // Setting LCD 디스플레이 임시 출력
    n_alarm_show();
    // 디스플레이 출력 모드로 변경
    setMode(-1);
    // 단계 초기화
    a_Process_case = 0;
}

// 날짜 수정 단계
void processModifyCalender(int *input_Process_case){
	// 가변저항을 이용한 날짜 수정
	set_Calender(*input_Process_case);
	handleButtonPress(input_Process_case, 1);
}

// 디바이스 날짜 및 시간 수정 최종 확인
void processModifyCheck(int *input_Process_case){
	// 확인 디스플레이 출력
	check_modify_lcd();
	handleButtonPress(input_Process_case, 1);
}

// 알람 적용 단계
void processModifyFinalization(){
	// 디바이스 내부 변수에 설정한 날짜 및 시간 업데이트
	set_tm_strut(getnYear(),getnMonth(),getnDay()+1,clock_value[2],clock_value[1]);
	// DS1302 시간 데이터 업데이트
	set_DS1302_Time_s();
	// 디바이스 초 단위 초기화
	device_second = 0;
	setMode(-1);
	m_Process_case = 0;
}

void timer_Process() {
    switch (t_Process_case) {
        case 0:
            processTimerMinute();
            break;
        case 1:
            processTimerSecond();
            break;
        case 2:
            processTimerReview();
            break;
    }
}

void alarm_Process() {
	// 알람이 설정된 상태라면 알람 수정 및 초기화 체크 단계로 변경
    if (getAlarmState()) {
        a_Process_case = 100;
    }
    switch (a_Process_case) {
        case 0:
            processAlarmHour(&a_Process_case);
            break;
        case 1:
            processAlarmMinute(&a_Process_case);
            break;
        case 2:
            processAlarmReview();
            break;
        case 3:
            processAlarmFinalization();
            break;
        case 100: // 알람 수정 확인 단계
			processAlarmChangeCheck();
			break;
    }
}
void modify_Process(){
	switch(m_Process_case){
	case 0 :
		processModifyCalender(&m_Process_case);
		break;
	case 1:
		processModifyCalender(&m_Process_case);
		break;
	case 2:
		// show the Check the OLED
		processModifyCalender(&m_Process_case);
		break;
	case 3:
		processAlarmHour(&m_Process_case);
		break;
	case 4:
		processAlarmMinute(&m_Process_case);
		break;
	case 5:
		processModifyCheck(&m_Process_case);
		break;
	case 6:
		processModifyFinalization();
		break;
	}
}
