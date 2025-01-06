/*
 * esp32_dht11.h
 *
 *  Created on: 2024. 9. 26.
 *      Author: ihg78
 */

#ifndef LIB_INC_ESP32_DHT11_H_
#define LIB_INC_ESP32_DHT11_H_
#include <device_var.h>
#include "main.h"
#include "dht11.h"
//esp32 유선 통신 관련 함수들
void set_send_cnt(int hour);
void check_send();
void send_esp32();

#endif /* LIB_INC_ESP32_DHT11_H_ */
