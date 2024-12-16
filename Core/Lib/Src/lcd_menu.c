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

static uint32_t m_toggle_count=0;
static int pos_y[3] = {20,30,40};

static char timer_time[40] = "";
static char alarm_time[40] = "";
static char clock_time[40] = "";
static char second_time[40] = "";
static char calender_time[20] = "";

static struct tm *t;
static time_t cal_t;
char *wday[] = { "SUN", "MON", "TUE", "WED",
                 "THU", "FRI", "SAT" };

const char *menus[] = {" Cancel Timer"," Timer Mode"," Alarm Setting"," Clock Modify"};
int prevousPos = -1;

void opening(){
	SSD1306_GotoXY(10,10);
	if(check_RTC(2)){
		SSD1306_Puts("Alarm Not Set.. ", &Font_7x10, 1);
	}else{
		SSD1306_Puts("Alarm Set!! ", &Font_7x10, 1);
		get_Alarm();
	}
	SSD1306_GotoXY(10,30);
	if(check_RTC(1)){
		SSD1306_Puts("Start_M is Modify", &Font_7x10, 1);
		setMode(3);
	}else{
		init_timer_funs();
		SSD1306_Puts("Start_M is Normal", &Font_7x10, 1);
		// 여기서 clock 업데이트 및 RTC 업데이트 필요
	}
	SSD1306_UpdateScreen();
	HAL_Delay(1000);
	SSD1306_Clear();
}
void startToggle(){
	if(m_toggle_count == 0) m_toggle_count = 4;
}
void printCalender(){
	SSD1306_GotoXY(10,10);
	if(getMode() == 3){
		int s_year = getnYear();
		int s_month = getnMonth();
		int s_day = getnDay();
		t->tm_year = s_year+100;
		t->tm_mon = s_month;
		t->tm_mday = s_day+1;
	}
	else{
		*t = get_struct_tm();
	}
	cal_t = mktime(t);
	int show_year = t->tm_year+1900;
	int show_month = t->tm_mon+1;
	int show_day = t->tm_mday;
	sprintf(calender_time,"%d %d%d/%d%d %s",show_year,show_month/10,show_month%10,show_day/10,show_day%10 ,wday[t->tm_wday]);
	SSD1306_Puts(calender_time, &Font_7x10, 1);
}
void printDefault(){
	printCalender();
	printClock();
	printDht();
	SSD1306_GotoXY(10,50);
	if(getTimerState()){
		int tMin = timer_value[1];
		int tSec = timer_value[0];
		sprintf(timer_time,"----- %d:%d%d -----",tMin,tSec/10,tSec%10);
		SSD1306_Puts(timer_time, &Font_7x10, 1);
	}else{
		sprintf(second_time,"------ %d ------",clock_value[0]);
		SSD1306_Puts(second_time, &Font_7x10, 1);
	}
	SSD1306_UpdateScreen();
}

// Code by Mireu LEE
void printClock(){
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

void printDht(){
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
void toggleScreen(){
	SSD1306_Clear();
}

void menuSelect(){
	int m_pos = getPos();
	if(m_pos != prevousPos){
		toggleScreen();
		prevousPos = m_pos;
	}
	SSD1306_GotoXY(10,10);
	SSD1306_Puts("----------------", &Font_7x10, 1);
	for(int i=1; i<=3; i++){
		char line[20];
		SSD1306_GotoXY(10, pos_y[i-1]);
		if(i == m_pos+1){
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

void n_timer_show(){
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

void n_alarm_show(){
	printCalender();
	print_Set_time();
	SSD1306_GotoXY(10,50);
	SSD1306_Puts("ALARM_SETTING...", &Font_7x10, 1);
	SSD1306_UpdateScreen();
}

void n_modify_show(){
	printCalender();
	print_Set_time();
	SSD1306_GotoXY(10,50);
	SSD1306_Puts("...MODIFYING...", &Font_7x10, 1);
	SSD1306_UpdateScreen();
}

void check_timer_lcd(){
	int minute = getnMinute();
	int second = getnSecond();
	sprintf(timer_time,"%d%d:%d%d",minute/10,minute%10,second/10,second%10);
	SSD1306_GotoXY(10,10);
	SSD1306_Puts("----------------", &Font_7x10, 1);
	SSD1306_GotoXY(28,26);
	SSD1306_Puts(timer_time, &Font_11x18, 1);
	SSD1306_GotoXY(10,50);
	SSD1306_Puts("OK? Y:SEL N:MENU", &Font_7x10, 1);
	SSD1306_UpdateScreen();
}

void check_alarm_change_lcd(){
	int am_pm = (int)alarm_value[2]/13;
	if(am_pm){
		int hour = alarm_value[2]-12;
		sprintf(alarm_time,"You Set Pm %d%d:%d%d",hour/10,hour%10,alarm_value[1]/10,alarm_value[1]%10);
	}else{
		sprintf(alarm_time,"You Set Am %d%d:%d%d",alarm_value[2]/10,alarm_value[2]%10,alarm_value[1]/10,alarm_value[1]%10);
	}
	SSD1306_GotoXY(3,10);
	SSD1306_Puts("----------------", &Font_7x10, 1);
	SSD1306_GotoXY(3,20);
	// 대충 설정한 시간을 표시
	SSD1306_Puts(alarm_time, &Font_7x10, 1);
	// you want modify
	SSD1306_GotoXY(3,30);
	SSD1306_Puts("Want Change time", &Font_7x10, 1);
	SSD1306_GotoXY(3,40);
	SSD1306_Puts("Press the SEL BTN", &Font_7x10, 1);
	SSD1306_GotoXY(3,50);
	SSD1306_Puts("----------------", &Font_7x10, 1);
	SSD1306_UpdateScreen();
}

void check_alarm_lcd()
{
	printCalender();
	print_Set_time();
	SSD1306_GotoXY(10,50);
	SSD1306_Puts("OK? Y:SEL N:MENU", &Font_7x10, 1);
	SSD1306_UpdateScreen();
}

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

void check_modify_lcd(){
	printCalender();
	printClock();
	SSD1306_GotoXY(3,50);
	SSD1306_Puts("OK? Y:SEL N:MENU", &Font_7x10, 1);
	SSD1306_UpdateScreen();
}
