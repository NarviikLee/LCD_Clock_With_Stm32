/*
 * esp32_dht11.c
 *
 *  Created on: 2024. 9. 26.
 *      Author: ihg78
 */

#include "esp32_dht11.h"
#include <string.h>
#define LIMIT_CNT 3

extern UART_HandleTypeDef huart6;
// 디바이스 이름(데이터에 구분을 위하여)
static char device_name[20] ="device_1";

// esp에 전송할 데이터 배열
static char data_send[100];

// 전송 시간 계산을 위한 정적변수
static int send_cnt = 1;

// 시간 수정시 데이터 전송 시간 재설정 함수
void check_send(){
	// 설정한 디바이스 시간 단위
	int ck_hour = clock_value[2];
	// 정적 변수를 통한 데이터 전송 시간 체크
	int send_hour = send_cnt*6;

	// 현재 시간이 전송 시간과 동일할 경우
	if(ck_hour == send_hour){
		// esp32에 데이터 전송
		send_esp32();
		// 다음 시간때를 위한 정적 변수 증가
		send_cnt++;
		// LIMIT_CNT(3)보다 클 경우 0으로 초기화
		// 3으로 잡은 이유는 4일 경우 24시가 되는데 실제 시간상 24시는 존재 X
		// 0시가 다음날로 넘어가는 12시를 뜻함
		if(send_cnt >LIMIT_CNT){
			// 0으로 초기화하여 18시 이후 전송 시간을 다음날로 넘어가는 12시로 초기화
			send_cnt = 0;
		}
	}
}

// 전송 시간 연산 변수 계산 함수
void set_send_cnt(int hour){
	// (매개변수로 입력 받은 설정 시간/6) +1로 하여 데이터전송 시간 설정
	// 예를 들어 12시일 경우 이미 바로 전송을 하지않고 18시에 데이터 전송 시간으로 설정
	int set_cnt = (int)hour/6+1;
	if(set_cnt >LIMIT_CNT){
		send_cnt = 0;
	}else{
		send_cnt = set_cnt;
	}
}

// esp32 데이터 전송 함수
void send_esp32(){
	// 현재 dht11에서 측정한 온도 및 습도 취득
	int temper = (int)getCurrentDHTTemper();
	int hudmity = (int)getCurrentDHTHud();
	// 문자열 결합
	sprintf(data_send,"index:%d,temp:%d,hud:%d,device_name:%49s\n",send_cnt,temper,hudmity,device_name);
	// esp 데이터 전송 통신
	HAL_UART_Transmit(&huart6, (uint8_t *)data_send, strlen(data_send), 100);
}
