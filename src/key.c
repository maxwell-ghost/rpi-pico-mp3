#include "key.h"

volatile struct key_state key = { false, NO_KEY, false };


void IO_BANK0_IRQHandler(void) {
    // 不要再中断后调用延时，因为延时也是需要中断来计时，如果
    // 调用，则程序会卡住，因为时间会停止不动
    for (uint8_t i = 0; i < 4; i++) {
        for (uint8_t j = 0; j < 8; j++) {
            uint32_t result = IO_BANK0->PROC[0].INTS[i] & (0xf << j*4);
            if (result) key.key_pin = (uint16_t)(i*8 + j);
        }
    }
	printf("%lx %lx %lx %lx\n", IO_BANK0->PROC[0].INTS[0], IO_BANK0->PROC[0].INTS[1], \
	IO_BANK0->PROC[0].INTS[2], IO_BANK0->PROC[0].INTS[3]);
    key_enable(false);
    key.pressed = true;
}

int key_process() {
    key.pressed = false;
    wait_ms(20);
    // loop_cnt用于判断长按还是短按，且按键不会一直触发
    int loop_cnt = 0;

    // 读取按键，从这里返回为正常读取
    while(gpio_read(key.key_pin)) {
        wait_ms(10);

        // 如果读取到高电平，则会增加累计时间
        if (gpio_read(key.key_pin)) {
            loop_cnt++;
        } else {
            // 这里按键松开
            if (loop_cnt > 30) key.long_pressed = true;
            else key.long_pressed = false;
            return 0;
        }
        
    }

    // 从这里返回说明按键误触
    // 这里一定要加上key_enable(true)，否则如果出现抖动，gpio中断将会被禁用
    key_reset();
    key_enable(true);
    return -1;
}

//key_state变量复位
void key_reset() {
    key.pressed = false;
    key.key_pin = NO_KEY;
    key.long_pressed = false;
}