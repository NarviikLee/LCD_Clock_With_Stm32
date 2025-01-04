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
static char device_name[20] ="device_1";
static char data_send[100];
static int send_cnt = 1;

void check_send(){
	int ck_hour = clock_value[2];
	int send_hour = send_cnt*6;
	if(ck_hour == send_hour){
		send_esp32();
		send_cnt++;
		if(send_cnt >LIMIT_CNT){
			send_cnt = 0;
		}
	}
}
void set_send_cnt(int hour){
	int set_cnt = (int)hour/6+1;
	if(set_cnt >LIMIT_CNT){
		send_cnt = 0;
	}else{
		send_cnt = set_cnt;
	}
}

void send_esp32(){
	int temper = (int)getCurrentDHTTemper();
	int hudmity = (int)getCurrentDHTHud();
	sprintf(data_send,"index:%d,temp:%d,hud:%d,device_name:%49s\n",send_cnt,temper,hudmity,device_name);
	HAL_UART_Transmit(&huart6, (uint8_t *)data_send, strlen(data_send), 100);
}
