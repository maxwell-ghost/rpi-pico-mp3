#ifndef _AUDIO_H
#define _AUDIO_H

/*
----------------------------------------------------------------
这个库调用hal.h(硬件相关的库)，来实现mp3所有跟声音相关的功能
----------------------------------------------------------------
*/

#include "hal.h"
#include "rpi_time.h"

#define NOTE_SEP_TIME 20

enum e_modus {
    F_MAJOR = 0,
    F_SHARP_MAJOR,
    A_MAJOR,
    B_FLAT_MAJOR,
};

enum note_ctrl {
    sep = 8, // 每小节的分隔符 
    con = 9, // 用来代替每小节的分隔符，如果出现连音
    conn = 10, // 用于小节内的连音，connect note

    modus_change = 11, // 用于改变调, 紧接着的用于表示新的调子
};

struct music {
    int8_t *music_script;
    uint32_t note_num;
    enum e_modus modus_type; // 调式
    int bpm; 
    uint8_t base_freq_index; //歌曲演奏的基础频率索引
};

// 表示八度，点
enum eig {
    ddot2 = -2,
    ddot = -1,
    ndot = 0,
    udot = 1,
    udot2 = 2
};

// 表示持续时间，横线
enum dur {
    nbar = 1,
    bar = 2,
    bar2 = 4,
    bar3 = 8
};

/*
初始化pwm硬件，如果成功，返回0，失败返回-1
*/
int init_audio();

/*
播放开机音乐
*/
void play_start_music();


/*
播放一个音符
i为当前音符索引，one_beat_ms由bpm计算
*/
void play_note(uint32_t i, int one_beat_ms, int8_t* music, uint8_t base_freq_index, enum e_modus modus_type);

/*
播放普通音乐
base_freq_index: 歌曲演奏的基础频率索引
*/
void play_music(int8_t* music, uint32_t note_len, int bpm, uint8_t base_freq_index, enum e_modus modus_type );


#endif