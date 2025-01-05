/*
 * lcd_menu.c
 *
 *  Created on: Jul 17, 2024
 *      Author: ihg78
 */


#include <stdio.h>
#include <time.h>

#include "lcd_menu.h"
#include "g_var.h"
#include "timer_mode.h"
#include "Potentiometer.h"
#include "RTC_Functions.h"
#include "timer_funs.h"
#include "dht11.h"


// 메뉴 Y 좌표
static int pos_y[3] = {20,30,40};


// 각각의 모드 디스플레이에 사용할 문자열 배열
static char timer_time[40] = "";
static char alarm_time[40] = "";
static char clock_time[40] = "";
static char second_time[40] = "";
static char calender_time[20] = "";

// 디스플레이
static struct tm *t;
static time_t cal_t;
char *wday[] = { "SUN", "MON", "TUE", "WED",
                 "THU", "FRI", "SAT" };

// 메뉴 선택창 문자 배열
const char *menus[] = {" Cancel Timer"," Timer Mode"," Alarm Setting"," Clock Modify"};

// 선택 창 위치 초기 값
int prevousPos = -1;

// 시작시 부팅 디스플레이 및 DS1302 시간 및 알람 데이터 취득
void opening(){
	SSD1306_GotoXY(10,10);
	// DS1302 램에 저장된 알람 설정 체크
	int ck_alarm_flag=check_Alarm_FLAG();
	if(ck_alarm_flag<1){
		SSD1306_Puts("Alarm Not Set.. ", &Font_7x10, 1);
	}else{
		// 알람이 세팅되어 있다면 알람 시간 가져오기
		SSD1306_Puts("Alarm Set!! ", &Font_7x10, 1);
		get_Alarm();
	}
	SSD1306_GotoXY(10,30);
	// DS1302에 저장된 시간을 디바이스 내부 변수에 변환 및 저장
	init_timer_funs();
	SSD1306_Puts("LOAD COMPLETE", &Font_7x10, 1);
	// 여기서 clock 업데이트 및 RTC 업데이트 필요
	SSD1306_UpdateScreen();
	HAL_Delay(1000);
	SSD1306_Clear();
}

// 날짜 출력 함수
void printCalender(){
	SSD1306_GotoXY(10,10);
	// 디바이스 시간 및 날짜 수정 모드일때 실시간 디스플레이 업데이트
	if(getMode() == 3){
		int s_year = getnYear();
		int s_month = getnMonth();
		int s_day = getnDay();
		// tm 구조체에서 연도는 실제 연도에 -1900을 해야함
		t->tm_year = s_year+100;
		t->tm_mon = s_month;
		t->tm_mday = s_day+1;
	}
	else{ // 일반 디스플레이 모드 및 나머지 모드일때 디바이스에 저장된 현재 시간 값 출력
		*t = get_struct_tm();
	}
	//최종 시간 구조체를 초단위 변수로 변환
	cal_t = mktime(t);
	// 디스플레이할 연도, 월, 일 설정
	int show_year = t->tm_year+1900; // tm구조체에 저장된 연차는 -1900으로 되어있다 (ex:2024 = 124)
	int show_month = t->tm_mon+1; //  tm구조체에 저장된 달은 0부터 시작함(ex:1월=0)
	int show_day = t->tm_mday;
	// 디스플레이 출력을 위해 최종 날짜 변수 문자열에 저장
	sprintf(calender_time,"%d %d%d/%d%d %s",show_year,show_month/10,show_month%10,show_day/10,show_day%10 ,wday[t->tm_wday]);
	// 디스플레이 입력
	SSD1306_Puts(calender_time, &Font_7x10, 1);
}

// 일반 모드 디스플레이 함수
void printDefault(){
	// 날짜 출력 함수
	printCalender();
	// 시간 출력 함수
	printClock();
	// 온 습도 출력 함수
	printDht();
	SSD1306_GotoXY(10,50);
	// 타이머 모드일 경우
	if(getTimerState()){
		int tMin = timer_value[1];
		int tSec = timer_value[0];
		// 초 디스플레이 공간에 타이머 시간 디스플레이 출력
		sprintf(timer_time,"----- %d:%d%d -----",tMin,tSec/10,tSec%10);
		SSD1306_Puts(timer_time, &Font_7x10, 1);
	}else{
		// 현재 초 디스플레이 출력
		sprintf(second_time,"------ %d ------",clock_value[0]);
		SSD1306_Puts(second_time, &Font_7x10, 1);
	}
	SSD1306_UpdateScreen();
}
// 디바이스 현재 시간 디스플레이 함수
void printClock(){
	// 오전 오후 판단 변수
	int am_pm = clock_value[2]/13;
	int s_hour = clock_value[2];
	int s_minute = clock_value[1];
	SSD1306_GotoXY(10,32);
	if(am_pm){
		SSD1306_Puts("PM", &Font_7x10, 1);
		int hour = s_hour-12;
		sprintf(clock_time,"%d%d:%d%d",hour/10,hour%10,s_minute/10,s_minute%10);
	}else{
		SSD1306_Puts("AM", &Font_7x10, 1);
		sprintf(clock_time,"%d%d:%d%d",s_hour/10,s_hour%10,s_minute/10,s_minute%10);
	}
	SSD1306_GotoXY(27,25);
	SSD1306_Puts(clock_time, &Font_11x18, 1);
}
// 온습도 데이터 디스플레이 함수
void printDht(){
	// dht11 모듈에 저장된 온도 및 습도 값 취득
	int temper = (int)getCurrentDHTTemper();
	int hudmity = (int)getCurrentDHTHud();
	char hud[40], temp[40];
	sprintf(hud,"%d%%",hudmity);
	sprintf(temp,"%d'c",temper);
	SSD1306_GotoXY(90,25);
	SSD1306_Puts(temp, &Font_7x10, 1);
	SSD1306_GotoXY(90,37);
	SSD1306_Puts(hud, &Font_7x10, 1);
}

// 알람 설정 단계에서 설정중인 시간 디스플레이 함수
void print_Set_time(){
	int s_hour = getnHour();
	int s_minute = getnMinute();
	int am_pm = s_hour/13;
	SSD1306_GotoXY(10,32);
	if(am_pm){
		SSD1306_Puts("PM", &Font_7x10, 1);
		int hour = s_hour-12;
		sprintf(alarm_time,"%d%d:%d%d",hour/10,hour%10,s_minute/10,s_minute%10);
	}else{
		SSD1306_Puts("AM", &Font_7x10, 1);
		sprintf(alarm_time,"%d%d:%d%d",s_hour/10,s_hour%10,s_minute/10,s_minute%10);
	}
	SSD1306_GotoXY(27,25);
	SSD1306_Puts(alarm_time, &Font_11x18, 1);
}

// LCD 디스플레이 클리어
void toggleScreen(){
	SSD1306_Clear();
}

// 메뉴 선택 LCD 디스플레이 함수
// 현재 선택된 메뉴 위치에 따라 LCD에 메뉴를 출력
void menuSelect(){
	int m_pos = getPos();
	// 선택된 메뉴 위치가 이전 위치와 다를경우(버튼 인터럽트 발생시)
	if(m_pos != prevousPos){
		// LCD 화면을 초기화하여 선택 메뉴 갱신
		toggleScreen();
		// 이전 위치 변경
		prevousPos = m_pos;
	}
	SSD1306_GotoXY(10,10);
	SSD1306_Puts("----------------", &Font_7x10, 1);
	// 메뉴 디스플레이 루프
	// 현재 선택된 메뉴 위치에는 화살표를 표시
	for(int i=1; i<=3; i++){
		char line[20];
		SSD1306_GotoXY(10, pos_y[i-1]);
		if(i == m_pos+1){
			// 타이머가 돌아가는 중이라면 타이머 취소 메뉴로 변경
			if(getTimerState() && i == 1){
				snprintf(line,sizeof(line),">%s",menus[i-1]);
			}
			else{
				snprintf(line,sizeof(line),">%s",menus[i]);
			}
		}else{
			snprintf(line,sizeof(line),"%s",menus[i]);
		}
		SSD1306_Puts(line, &Font_7x10, 1);
	}

	SSD1306_GotoXY(10,50);
	SSD1306_Puts("----------------", &Font_7x10, 1);
	SSD1306_UpdateScreen();
}

// 타이머 취소 LCD 디스플레이 함수
void timer_cancle_lcd(){
	SSD1306_GotoXY(10,10);
	SSD1306_Puts("----------------", &Font_7x10, 1);
	SSD1306_GotoXY(10,20);
	SSD1306_Puts("Timer Mode be", &Font_7x10, 1);
	SSD1306_GotoXY(10,30);
	SSD1306_Puts("Canceled....", &Font_11x18, 1);
	SSD1306_GotoXY(10,50);
	SSD1306_Puts("----------------", &Font_7x10, 1);
	SSD1306_UpdateScreen();
	SSD1306_Clear();
}

// 타이머 종료 LCD 디스플레이 함수
void timer_lcd(){
	SSD1306_GotoXY(10,10);
	SSD1306_Puts("----------------", &Font_7x10, 1);
	SSD1306_GotoXY(15,20);
	SSD1306_Puts("Timer Completed!!", &Font_7x10, 1);
	SSD1306_GotoXY(15,30);
	SSD1306_Puts("Press The", &Font_7x10, 1);
	SSD1306_GotoXY(15,40);
	SSD1306_Puts("Can Button", &Font_7x10, 1);
	SSD1306_GotoXY(10,50);
	SSD1306_Puts("----------------", &Font_7x10, 1);
	SSD1306_UpdateScreen();
}

// 타이머 설정 확인 LCD 디스플레이 함수
void n_timer_show(){
	// 설정중인 분과 초를 디스플레이
	int minute = getnMinute();
	int second = getnSecond();
	sprintf(timer_time,"%d%d:%d%d",minute/10,minute%10,second/10,second%10);
	SSD1306_GotoXY(10,10);
	SSD1306_Puts("----------------", &Font_7x10, 1);
	SSD1306_GotoXY(28,26);
	SSD1306_Puts(timer_time, &Font_11x18, 1);
	SSD1306_GotoXY(10,50);
	SSD1306_Puts("----------------", &Font_7x10, 1);
	SSD1306_UpdateScreen();
}

// 알람 설정 확인 LCD 디스플레이 함수
void n_alarm_show(){
	// 날짜 출력 함수 호출
	printCalender();
	// 현재 설정중인 시간 디스플레이 함수 호출
	print_Set_time();
	SSD1306_GotoXY(10,50);
	SSD1306_Puts("ALARM_SETTING...", &Font_7x10, 1);
	SSD1306_UpdateScreen();
}

// 디바이스 시간 및 날짜 수정 확인 LCD 함수
void n_modify_show(){
	// 날짜 출력 함수 호출
	printCalender();
	// 현재 설정중인 시간 디스플레이 함수 호출
	print_Set_time();
	SSD1306_GotoXY(10,50);
	SSD1306_Puts("...MODIFYING...", &Font_7x10, 1);
	SSD1306_UpdateScreen();
}

// 타이머 최종 확인 LCD 디스플레이
void check_timer_lcd(){
	int minute = getnMinute();
	int second = getnSecond();
	//설정한 타이머 최종 디스플레이
	sprintf(timer_time,"%d%d:%d%d",minute/10,minute%10,second/10,second%10);
	SSD1306_GotoXY(10,10);
	SSD1306_Puts("----------------", &Font_7x10, 1);
	SSD1306_GotoXY(28,26);
	SSD1306_Puts(timer_time, &Font_11x18, 1);
	SSD1306_GotoXY(10,50);
	SSD1306_Puts("OK? Y:SEL N:MENU", &Font_7x10, 1);
	SSD1306_UpdateScreen();
}

// 알람 변경 및 유지 체크 LCD 함수
void check_alarm_change_lcd(){
	// 오전, 오후 판단 변수
	int am_pm = (int)alarm_value[2]/13;
	// 설정한 알람시간 LCD 에 디스플레이
	if(am_pm){
		int hour = alarm_value[2]-12;
		sprintf(alarm_time,"You Set Pm %d%d:%d%d",hour/10,hour%10,alarm_value[1]/10,alarm_value[1]%10);
	}else{
		sprintf(alarm_time,"You Set Am %d%d:%d%d",alarm_value[2]/10,alarm_value[2]%10,alarm_value[1]/10,alarm_value[1]%10);
	}
	SSD1306_GotoXY(3,10);
	SSD1306_Puts("----------------", &Font_7x10, 1);
	SSD1306_GotoXY(3,20);
	// 설정했던 알람 시간을 표시
	SSD1306_Puts(alarm_time, &Font_7x10, 1);
	// you want modify
	SSD1306_GotoXY(3,30);
	// 알람 변경을 하고 싶다면 SELECT 버튼
	SSD1306_Puts("WANT CHANGE SEL", &Font_7x10, 1);
	SSD1306_GotoXY(3,40);
	// 알람을 유지할려면 CANCEL버튼
	SSD1306_Puts("NO CHANGE CAN_B", &Font_7x10, 1);
	SSD1306_GotoXY(3,50);
	SSD1306_Puts("----------------", &Font_7x10, 1);
	SSD1306_UpdateScreen();
}

// 알람 최종 확인 LCD 함수
void check_alarm_lcd()
{
	// 날짜 출력 디스플레이 함수 호출
	printCalender();
	// 설정한 시간 디스플레이 함수 호출
	print_Set_time();
	SSD1306_GotoXY(10,50);
	SSD1306_Puts("OK? Y:SEL N:MENU", &Font_7x10, 1);
	SSD1306_UpdateScreen();
}

// 알람 알림 LCD 디스플레이 함수
void alarm_lcd(){
	SSD1306_GotoXY(10,10);
	SSD1306_Puts("----------------", &Font_7x10, 1);
	SSD1306_GotoXY(15,20);
	SSD1306_Puts("Alarm Completed!!", &Font_7x10, 1);
	SSD1306_GotoXY(15,30);
	SSD1306_Puts("Press The", &Font_7x10, 1);
	SSD1306_GotoXY(15,40);
	SSD1306_Puts("Can Button", &Font_7x10, 1);
	SSD1306_GotoXY(10,50);
	SSD1306_Puts("----------------", &Font_7x10, 1);
	SSD1306_UpdateScreen();

}
// 디바이스 시간 및 날짜 최종 확인 LCD 디스플레이 함수
void check_modify_lcd(){
	printCalender();
	printClock();
	SSD1306_GotoXY(3,50);
	SSD1306_Puts("OK? Y:SEL N:MENU", &Font_7x10, 1);
	SSD1306_UpdateScreen();
}
// Code by Mireu LEE
