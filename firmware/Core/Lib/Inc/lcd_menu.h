/*
 * lcd_menu.h
 *
 *  Created on: Jul 17, 2024
 *      Author: ihg78
 */

#ifndef LIB_INC_LCD_MENU_H_
#define LIB_INC_LCD_MENU_H_

#include "ssd1306.h"


// Clock START LCD
void opening();

// Toggle Functions
void toggleScreen();

// UPDATE Data FUNCTIONS ON LCD
void printDefault();
void printClock();
void printDht();
void printCalender();
void print_Set_time();

// MENU SELECT LCD
void menuSelect();

// 타이머 및 알람 출력 LCD
void timer_lcd();
void timer_cancle_lcd();
void alarm_lcd();

// 세팅 LCD 디스플레이 함수
void n_timer_show();
void n_alarm_show();
void n_modify_show();

// 최종 확인 LCD
void check_timer_lcd();
void check_alarm_lcd();
void check_alarm_change_lcd();
void check_modify_lcd();


#endif /* LIB_INC_LCD_MENU_H_ */
