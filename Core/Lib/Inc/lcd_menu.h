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
void startToggle();
void toggleScreen();

// UPDATE Data FUNCTIONS ON LCD
void printDefault();
void printClock();
void printDht();
void printCalender();
void print_Set_time();

// MENU SELECT LCD
void menuSelect();

// TIMER On LCD
void timer_lcd();
void timer_cancle_lcd();
void alarm_lcd();

// Setting Check LCD
void n_timer_show();
void n_alarm_show();
void n_modify_show();

// Check LCD
void check_timer_lcd();
void check_alarm_lcd();
void check_alarm_change_lcd();
void check_modify_lcd();


#endif /* LIB_INC_LCD_MENU_H_ */
