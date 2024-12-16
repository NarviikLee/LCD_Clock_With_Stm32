/*
 * SubControl.h
 *
 *  Created on: 2024. 7. 21.
 *      Author: ihg78
 */

#ifndef LIB_INC_SUBCONTROL_H_
#define LIB_INC_SUBCONTROL_H_
#include "main.h"
#include "g_var.h"
#include <stdbool.h>

bool handleButtonPress(int *process_case, int increment) ;

void processTimerMinute();
void processTimerSecond();
void processTimerReview();

void processAlarmChangeCheck();
void processAlarmHour(int *input_Process_case);
void processAlarmMinute(int *input_Process_case);
void processAlarmReview();
void processAlarmFinalization();

void processModifyCalender(int *input_Process_case);
void processModifyCheck(int *input_Process_case);
void processModifyFinalization();

void timer_Process();
void alarm_Process();
void modify_Process();
void change_Show();


#endif /* LIB_INC_SUBCONTROL_H_ */
