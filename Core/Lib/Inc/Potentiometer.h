/*
 * Potentiometer.h
 *
 *  Created on: Jul 16, 2024
 *      Author: ihg78
 */

#ifndef LIB_INC_POTENTIOMETER_H_
#define LIB_INC_POTENTIOMETER_H_

#include "main.h"
#include "g_var.h"

#define YEARCONVERT 37
#define MONTHCONVERT 336

#define TWEEIGHT 137
#define TWENINE 133
#define THIRTY 128
#define THIRONE 125
#define CHECK_VALUE 37

void init_PotentioMeter(ADC_HandleTypeDef* Poten);
// ADC Check_Function ->
void check_adc_change();
int mapping_adc(int adc);

// Timer Setting Functions
void set_Minute();
void set_Second();
void cal_Second();
void update_timer();

// Alarm Setting Functions
void set_Hour();
void set_AMinute();
//void set_Second();

// alarm Setting
void update_clock();

// modify Functions
void set_Calender(int mode);

#endif /* LIB_INC_POTENTIOMETER_H_ */
