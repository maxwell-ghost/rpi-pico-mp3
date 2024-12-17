#include "audio.h"

// -12 -11 -10 -9 -8 -7 -6 -5 -4 -3 -2 -1     0 1  2 3  4 5 6  7 8  9 10 11
// C   C#  D   D# E  F  F# G  G# A  A# B |||| C C# D D# E F F# G G# A A# B
uint16_t all_notes[] = {
	0x07c2, 0x0753, 0x06ea, 0x0685, 0x0628, 0x05cf, 0x057c, 0x052d, 0x04e3, 0x049d, 0x045a, 0x041c, //C0
	0x03e1, 0x03a9, 0x0375, 0x0343, 0x0314, 0x02e8, 0x02be, 0x0297, 0x0272, 0x024e, 0x022d, 0x020e, //C1
	0x01f0, 0x01d5, 0x01ba, 0x01a1, 0x018a, 0x0174, 0x015f, 0x014b, 0x0139, 0x0127, 0x0117, 0x0107, //C2
	0x00f8, 0x00ea, 0x00dd, 0x00d1, 0x00c5, 0x00ba, 0x00af, 0x00a6, 0x009c, 0x0094, 0x008b, 0x0083, //C3 这个如果作为主音，效果很不好，蜂鸣器在频率低的时候效果很差
	0x007c, 0x0075, 0x006f, 0x0068, 0x0063, 0x005d, 0x0058, 0x0053, 0x004e, 0x004a, 0x0046, 0x0042, //C4 main(48), 尽量往高频走
	0x003e, 0x003b, 0x0037, 0x0034, 0x0031, 0x002e, 0x002c, 0x0029, 0x0027, 0x0025, 0x0023, 0x0021, //C5 
	0x001f, 0x001d, 0x001c, 0x001a, 0x0019, 0x0017, 0x0016, 0x0015, 0x0014, 0x0012, 0x0011, 0x0010, //C6
	};


// 11:14 INT, 3:0 FRAC
int modus[][7] = {
	{ -7, -5, -3, -2, 0, 2, 4 }, 
	{ -6, -4, -2, -1, 1, 3, 5 },
	{ -3, -1, 1, 2, 4, 6, 8 },
	{ -2, 0, 2, 3, 5, 7, 9 }
};

int init_audio() {
    pwm_init(PWMCH3);
	pwm_disable(PWMCH3);
    return 0;
}


// void play_music(int8_t* music, uint32_t note_len, int bpm, uint8_t base_freq_index, enum e_modus modus_type ) {
	
// 	int one_beat_ms = (60000 / bpm);
// 	printf("Play %d \n", one_beat_ms);
// 	pwm_enable(PWMCH3);
// 	for (uint32_t i = 0; i < note_len; i++) {
// 		// 遇到休止音符
// 		printf("Play one note\n");
// 		if (music[i*3] == 0) {
// 			pwm_disable(PWMCH3);
// 			wait_ms((uint32_t)one_beat_ms - 20); // 减20用于减去演奏间隔
// 			pwm_enable(PWMCH3);
// 		} else {
// 			pwm_dset_freq(PWMCH3, all_notes[ base_freq_index + (modus[modus_type][music[i*3] - 1]) + 12*music[i*3+1] ]);
// 			wait_ms((uint32_t) ( (one_beat_ms / music[i*3+2]) - 20 ) );
// 		}

// 		pwm_disable(PWMCH3);
// 		wait_ms(20);
// 		pwm_enable(PWMCH3);
		
// 	}
// 	pwm_disable(PWMCH3);
// }

void play_note(uint32_t i, int one_beat_ms, int8_t* music, uint8_t base_freq_index, enum e_modus modus_type) {
	switch (music[i*3])
		{
		case conn:
			// 音符间连接
			return;
			break;
		case con:
			// 小节连接
			return;
			break;
		case sep:
			break;
		case 0: // 休止符
			pwm_disable(PWMCH3);
			wait_ms((uint32_t)one_beat_ms - NOTE_SEP_TIME);
			break;
		default: // 1 2 3 4 5 6 7
			pwm_dset_freq(PWMCH3, all_notes[ base_freq_index + (modus[modus_type][music[i*3] - 1]) + 12*music[i*3+1] ]);
			wait_ms((uint32_t) ( (one_beat_ms / music[i*3+2]) - NOTE_SEP_TIME ) ); // 减去演奏间隔
			break;
		}

		// 这里用来延时演奏间隔
		// 如果遇见点或者横线
		if (music[(i+1)*3] == con || music[(i+1)*3] == conn) {
			wait_ms(NOTE_SEP_TIME);
		} else {
			// 正常音符的演奏间隔
			pwm_disable(PWMCH3);
			wait_ms(NOTE_SEP_TIME);
			pwm_enable(PWMCH3);
		}
}

void play_music(int8_t* music, uint32_t note_len, int bpm, uint8_t base_freq_index, enum e_modus modus_type) {
	
	int one_beat_ms = (60000 / bpm);
	printf("Play %d \n", one_beat_ms);
	pwm_enable(PWMCH3);

	for (uint32_t i = 0; i < note_len; i++) {
		switch (music[i*3])
		{
		case conn:
			// 音符间连接
			continue;
			break;
		case con:
			// 小节连接
			continue;
			break;
		case sep:
			break;
		case 0: // 休止符
			pwm_disable(PWMCH3);
			wait_ms((uint32_t)one_beat_ms - NOTE_SEP_TIME);
			break;
		default: // 1 2 3 4 5 6 7
			pwm_dset_freq(PWMCH3, all_notes[ base_freq_index + (modus[modus_type][music[i*3] - 1]) + 12*music[i*3+1] ]);
			wait_ms((uint32_t) ( (one_beat_ms / music[i*3+2]) - NOTE_SEP_TIME ) ); // 减去演奏间隔
			break;
		}

		// 这里用来延时演奏间隔
		// 如果遇见点或者横线
		if (music[(i+1)*3] == con || music[(i+1)*3] == conn) {
			wait_ms(NOTE_SEP_TIME);
		} else {
			// 正常音符的演奏间隔
			pwm_disable(PWMCH3);
			wait_ms(NOTE_SEP_TIME);
			pwm_enable(PWMCH3);
		}
	}
	pwm_disable(PWMCH3);
}

void play_start_music() {
    pwm_enable(PWMCH3);
    pwm_set_volume(PWMCH3, 4096);
	//buf[0] = 0x01;
	pwm_set_freq(PWMCH3, 4, 10);
	//while (!timer_expired(&timer, 1000, millis())) (void)0;
	wait_ms(1000);

	//buf[0] = 0x03;
	pwm_set_freq(PWMCH3, 4, 2);
	wait_ms(1000);

	//buf[0] = 0x07;
	pwm_set_freq(PWMCH3, 3, 14);
	wait_ms(1000);

	//buf[0] = 0x0f;
	pwm_set_freq(PWMCH3, 3, 7);
	wait_ms(1000);
	pwm_disable(PWMCH3);
}