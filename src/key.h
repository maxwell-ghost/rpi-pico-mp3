#ifndef _KEY_H
#define _KEY_H

/*
----------------------------------------------------------------
关于按键的各种功能在此模块内实现，底层接口是hal库。
向上层提供抽象
----------------------------------------------------------------

如何使用，将如下结构放入while大循环中
if (key.pressed && (key_process(&key) == 0)) {
    
    // 你的代码
    // 可以使用key_state类型变量来确定按键pin和按下类型
    
    // 必须使用
	key_reset(&key);
	key_enable(true);	
}
*/

#include "hal.h"
#include "pinmap.h"
#include "rpi_time.h"

struct key_state {
    bool pressed;
    uint16_t key_pin;
    bool long_pressed;
};

enum { NO_KEY = 41 };

// 初始化按键中断，初始化后可以直接使用
static inline void init_key(uint16_t pin, uint32_t events) {
    gpio_set_irq_enabled(pin, events, true); // 使能gpio中断
    irq_set_enabled(IO_IRQ_BANK0, true); // 使能13号中断
}

// 关闭或者开启中断
static inline void key_enable(bool enabled) {
    irq_set_enabled(IO_IRQ_BANK0, enabled);
}

/*
检测到按键按下，即key.pressed == true 后调用
如果是一次有效的按下，key.key_pin 设置为有效值，无效值为 NO_KEY = 41
long_pressed被设置，默认是true

如果按下有效，则会返回0, 否则返回 -1

此函数会阻塞
*/
int key_process();


//key_state变量复位
void key_reset();




#endif