/*
 * g_var.h
 *
 *  Created on: Jul 12, 2024
 *      Author: ihg78
 */

#ifndef INC_G_VAR_H_
#define INC_G_VAR_H_

#include "main.h"
#include <time.h>

extern uint8_t up_btn;
extern uint8_t down_btn;
extern uint8_t select_btn;
extern uint8_t cancel_btn;

extern int calender_value[3];
extern int clock_value[3];
extern int timer_value[3];
extern int alarm_value[3];


extern uint8_t alert_mode;

extern int Timer_Second;
extern int default_second;

extern time_t rawtime;

#endif /* INC_G_VAR_H_ */
