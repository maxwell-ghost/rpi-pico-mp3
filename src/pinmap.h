#ifndef _PINMAP_H
#define _PINMAP_H

/*
----------------------------------------------------------------
管理管脚映射
----------------------------------------------------------------
*/

enum {
    OLED_RX = 0,
	OLED_CSn = 1,
	OLED_SCK = 2,
	OLED_TX = 3,

	OLED_DC = 4,
	OLED_RES = 5,
    
    PWM = 6, // PWMCH3_A;

	LED = 15,
    UART_TX = 16,
	UART_RX = 17,

	KEY_Y = 18,
	KEY_R = 19

};

#endif