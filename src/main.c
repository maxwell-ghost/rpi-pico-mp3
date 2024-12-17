// Copyright (c) 2023 Cesanta Software Limited
// All rights reserved

#include "hal.h"
#include "oled.h"
#include "pinmap.h"
#include "rpi_time.h"
#include "key.h"
#include "audio.h"

#include "syscalls.c"
#include "music_scripts.c"

enum mp3_state {
	S_MENU,
	S_PLAYING,
};

// 与arm内核中中断有关的时间变量，仅可在本文件访问
static volatile uint64_t s_ticks;
// 与led闪烁有关
static volatile bool led_switch = false;
// 与播放界面的...闪烁有关
static volatile bool dot_incr = false;
// 与播放动态效果有关
// 状态变量
static volatile enum mp3_state state = S_MENU;

// 与按键功能有关
extern volatile struct key_state key;

/*
中断处理
0000 0001 0010 0011 0100
*/
void SysTick_Handler(void) { 
	// SyStick IRQ handler, triggered every 1ms
	s_ticks++;
	if ((s_ticks & 0x0F) == 0x0F) {
		// 16ms刷新一次
		oled_refresh();
	}
	// flash oled 
	if ((s_ticks & 0x3FF) == 0x3FF) {
		led_switch = true;
	}
}

/*
获取static变量 s_tick
*/
uint64_t millis(void) { 
	return s_ticks; 
}

void choice_update(struct item *items, int max_item, int* cursor_pos_p) {
	int max_cursor_pos = max_item > 7 ? 6 : max_item-1;

	(*cursor_pos_p)++;
	if ((*cursor_pos_p) < max_item) {
		if ((*cursor_pos_p) <= max_cursor_pos) {
			// 未超出屏幕
			oled_draw_spacing_fix_text(true, " ", 1, 0, (uint8_t)((*cursor_pos_p) - 1));
			oled_draw_spacing_fix_text(true, "*", 1, 0, (uint8_t)((*cursor_pos_p)));
		} else {
			// 超出屏幕
			ui_draw_list(true, 7, items + (*cursor_pos_p) - max_cursor_pos);
		}
	} else {
		// 超出item范围，回到开头
		oled_draw_spacing_fix_text(true, " ", 1, 0, (uint8_t)max_cursor_pos);
		oled_draw_spacing_fix_text(true, "*", 1, 0, 0);
		ui_draw_list(true, (uint8_t)(max_cursor_pos+1), items);
		(*cursor_pos_p) = 0;
	}

}

void menu(struct item *items, int max_item, int* cursor_pos_p) {
	if (key.pressed && (key_process(&key) == 0)) {
		printf("%d pressed %d \n", (int)(key.key_pin), (int)key.long_pressed);

		if (key.key_pin == KEY_Y) {
			choice_update(items, max_item, cursor_pos_p);
		}
		else if (key.key_pin == KEY_R) {
			state = S_PLAYING;
			printf("playing music\n");
			oled_draw_spacing_fix_text(true, "    ", 4, 11, 3);
			oled_draw_spacing_fix_text(true, "PLAY", 4, 11, 4);
			oled_draw_spacing_fix_text(true, "ing.", 4, 11, 5);
			oled_draw_spacing_fix_text(true, "....", 4, 11, 6);
			oled_draw_spacing_fix_text(true, ".", 1, 0, (uint8_t)((*cursor_pos_p)));
		}

		// 必须使用
		key_reset(&key);
		key_enable(true);	
	}
}

void playing(struct item *items, int* cursor_pos_p) {
	printf("%d\n", *cursor_pos_p);

	int one_beat_ms = (60000 / items[*cursor_pos_p].m.bpm);
	uint32_t note_num = items[*cursor_pos_p].m.note_num;
	int8_t *music = items[*cursor_pos_p].m.music_script;
	uint8_t base_freq_index = items[*cursor_pos_p].m.base_freq_index;
	enum e_modus modus_type = items[*cursor_pos_p].m.modus_type;
	
	
	pwm_enable(PWMCH3);
	for (uint32_t i = 0; i < note_num; i++) {
		if (key.pressed && (key_process(&key) == 0)) {
			if (key.key_pin == KEY_R || key.key_pin == KEY_Y) {
				key_reset(&key);
				key_enable(true);	
				break;
			}

			key_reset(&key);
			key_enable(true);	
		}
		if (music[i*3] == modus_change) {
			modus_type = music[(i*3)+1];
			continue;
		}
		play_note(i, one_beat_ms, music, base_freq_index, modus_type);
	}
	pwm_disable(PWMCH3);

	//play_music(items[*cursor_pos_p].m.music_script, items[*cursor_pos_p].m.note_num, items[*cursor_pos_p].m.bpm, 
	//	items[*cursor_pos_p].m.base_freq_index, (items+(*cursor_pos_p))->m.modus_type);
	state = S_MENU;
	oled_draw_spacing_fix_text(true, "    ", 4, 11, 3);
	oled_draw_spacing_fix_text(true, "    ", 4, 11, 4);
	oled_draw_spacing_fix_text(true, "MBox", 4, 11, 5);
	oled_draw_spacing_fix_text(true, "@cat", 4, 11, 6);
	oled_draw_spacing_fix_text(true, "*", 1, 0, (uint8_t)((*cursor_pos_p)));
}

int main(void) {
	clock_init();						 // Init clocks
	uart_init(UART0, 115200, UART_RX, UART_TX);
	gpio_init(LED, GPIO_MODE_OUTPUT, 0); // Init LED
	gpio_init(OLED_RX, GPIO_MODE_AF, 1);
	gpio_init(OLED_CSn, GPIO_MODE_AF, 1);
	gpio_init(OLED_SCK, GPIO_MODE_AF, 1);
	gpio_init(OLED_TX, GPIO_MODE_AF, 1);
	gpio_init(OLED_DC, GPIO_MODE_OUTPUT, 0); // Data or cmd
	gpio_init(OLED_RES, GPIO_MODE_OUTPUT, 0);

	gpio_init(PWM, GPIO_MODE_AF, 4);
	gpio_init(KEY_Y, GPIO_MODE_INPUT, 0);


	spi_init(SPI0);
	init_key(KEY_Y, 0x2);
	init_key(KEY_R, 0x2);

	uart_write_byte(UART0, '>');

	init_audio();
	// 所以最大的到底是多少
	pwm_set_volume(PWMCH3, 0x1ff);
	//play_music(music, 33, 80);
	//play_start_music();

	// 音乐菜单
	struct item items[] = {
		{ "test", 4, { music_test, 33, F_MAJOR, 80, 60 } },
		{ "Faded", 5, { music_script_faded, (sizeof(music_script_faded)/sizeof(int8_t))/3, F_SHARP_MAJOR, 90, 60} },
		{ "Wish Fill", 9, { music_script_wish_fill, (sizeof(music_script_wish_fill)/sizeof(int8_t))/3, A_MAJOR, 66, 60} },
		{ "A TH Year", 9, { music_script_a_th_year, (sizeof(music_script_a_th_year)/sizeof(int8_t))/3, B_FLAT_MAJOR, 139, 60} },
		// { "Pear", 4, NULL, 0 },

		// { "Peach", 5, NULL, 0 },
		// { "Banana", 6, NULL, 0 },
		// { "Plum", 4, NULL, 0 }, 
		// { "Grape", 5, NULL, 0 },

		// { "Pineapple", 9 },
		// { "Coconut", 7 },
		// { "Papaya", 6 }
	};
	int max_item = sizeof(items)/sizeof(struct item);
	int cursor_pos = 0;
	
	// Reset OLED屏幕
	oled_reset();
	oled_init();
	// 填充黑色
	oled_fill(false);

	if (max_item == 0) {
		while(true) {
			if (led_switch) {
				led_switch = false;
				printf("running \n");
				gpio_write(LED, !gpio_read(LED));
			}
		}
	}

	// 画.mp3 logo
	ui_draw_icon();

	// 初始化列表界面
	ui_draw_list(true, (uint8_t)(max_item >= 7 ? 7 : max_item), items);
	ui_draw_cursor(true, (uint8_t)cursor_pos);
	
	// 初始化右下角
	oled_draw_spacing_fix_text(true, "    ", 4, 11, 3);
	oled_draw_spacing_fix_text(true, "    ", 4, 11, 4);
	oled_draw_spacing_fix_text(true, "MBox", 4, 11, 5);
	oled_draw_spacing_fix_text(true, "@cat", 4, 11, 6);
	oled_draw_spacing_fix_text(true, "*", 1, 0, (uint8_t)((cursor_pos)));
	
	while (true) {
		if (led_switch) {
			led_switch = false;
			printf("running \n");
			gpio_write(LED, !gpio_read(LED));
		}
		switch (state) {
		case S_MENU:
			menu(items, max_item, &cursor_pos);
			break;
		case S_PLAYING:
			playing(items, &cursor_pos);
			break;
		default:
			break;
		}
	}

	return 0;
}



