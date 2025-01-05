/*
 * timer_funs.c
 *
 *  Created on: Aug 9, 2024
 *      Author: ihg78
 */

#include "timer_funs.h"
#include "timer_mode.h"
#include "RTC_Functions.h"
#include "g_var.h"
#include "esp32_dht11.h"

static time_t sec_con;
static struct tm current_time;
static Time_s ds1302_time ={0};


// DS1302 시간 데이터 및 알람 설정 취득 함수
// 그리고 현 모듈 정적 변수 업데이트 함수(디바이스 시간 배열 및 알람 배열)
void init_timer_funs(){
	// DS1302 시간 및 알람 설정 취득 함수 호출
	get_DS1302_Time_s();
	// DS1302 시간 데이터-> 디바이스 시간 구조체 변환 함수
	set_static_Time_t();
	// 디바이스 시간 구조체-> 초 변수로 변환 함수
	convert_time_t();
	// 디바이스 시간 업데이트 및 디스플레이 출력
	update_clock_value();
	// 온습도 전송 시간 설정
	set_send_cnt(current_time.tm_hour);
}
// 디바이스 시간 업데이트(DS1302에 저장된 타이머 값을 취득한 이후) 함수
void update_clock_value(){
	clock_value[2] = current_time.tm_hour;
	clock_value[1] = current_time.tm_min;
	clock_value[0] = device_second;
	// 시간이 변경되면 데이터 전송 시간인지 확인
	if(clock_value[1] == 0){
		check_send();
	}
}


// 디바이스 시간 및 날짜 수정 이후디바이스 내부 변수 업데이트 함수
void set_tm_strut(int year,int month, int mday, int hour, int minute){
	current_time.tm_year= year+100;
	current_time.tm_mon = month;
	current_time.tm_mday = mday;
	current_time.tm_hour = hour;
	current_time.tm_min = minute;
	// 데이터 전송 타임 연산 함수 호출
	set_send_cnt(hour);
	// 업데이트한 tm 구조체를 초단위 변수로 변환 및 디바이스 업데이트
	convert_time_t();
}

// DS1302에 저장된 시간 구조체를 디바이스 내부 구조체에 업데이트
void set_static_Time_t(){
	// ds1302_time(Time_s)구조체는 연도 변수 구성이 2000+N이다
	// 그러나 tm 구조체는 연도 변수 구성이 1900+N이다 그러므로 +100을 해서 맞춰주어야함
	current_time.tm_year= (int)ds1302_time.year+100;
	current_time.tm_mon = (int)ds1302_time.month-1;
	// tm 구조체는 월 변수 구성이 0~11이다(1~12), DS1302 저장 구조체에서 월 변수 구성은(1~12)이므로 -1)
	current_time.tm_mday = (int)ds1302_time.date;
	current_time.tm_hour = (int)ds1302_time.hour;
	current_time.tm_min = (int)ds1302_time.min;
	device_second = (int)ds1302_time.sec;
	// tm 구조체 변환에서 요일 설정이 없는 이유는 위 설정을 입력하면 자동으로 연산되기 때문
}

// DS1302에서 데이터를 읽어오고 읽어온 데이터를 current_time에 추가(초까지)
void get_DS1302_Time_s(){
	ds1302_get_time(&ds1302_time);
}

// 시간 수정시 current_time를 업데이트하고 이후에 Time_s 구조체에 입력하고 DS1302에 업데이트
void set_DS1302_Time_s(){
	// ds1302_time(Time_s)구조체는 연도 변수 구성이 2000+N이다
	// 그러나 tm 구조체는 연도 변수 구성이 1900+N이다 그러므로 -100을 해서 맞춰주어야함
	ds1302_time.year = current_time.tm_year-100;
	// tm 구조체는 월 변수 구성이 0~11이다(1~12), DS1302 저장 구조체에서 월 변수 구성은(1~12)이므로 +1)
	ds1302_time.month = current_time.tm_mon+1;
	// 요일구성이 두 구조체가 다름 ds1302_time 구조체는 1~7(월~일)
	// tm 구조체는 0~6(일~토)로 구성되어 있으므로 tm 구조체가 0이면 ds1302 시간 구조체는 7을 입력해주어야하므로
	// 삼항 연산자를 사용함
	ds1302_time.day = current_time.tm_wday < 1? 7:current_time.tm_wday;
	ds1302_time.date= current_time.tm_mday;
	ds1302_time.hour = current_time.tm_hour;
	ds1302_time.min = current_time.tm_min;
	ds1302_set_time(&ds1302_time);
}


// 날짜 구조체 변수 초단위 변수로 변환 함수
void convert_time_t(){
	sec_con = mktime(&current_time);
}
// 초단위 변수 날짜 구조체로 변환 함수
void convert_tm(){
	current_time = *localtime(&sec_con);
}

// 디바이스 날짜 및 시간 데이터 반환 함수
struct tm get_struct_tm(){
	return current_time;
}
// 디바이스 시간 업데이트 함수(1분 단위로 업데이트)
void set_time_t(){
	// 초단위 변수에 60카운트 추가(1분이 추가되었으므로)
	sec_con += minute_cnt;
	// 업데이트 한 초단위 변수를 tm 구조체로 변환
	convert_tm();
	// 그리고 업데이트한 구조체 기반 디바이스 LCD 디스플레이 출력
	update_clock_value();
}

