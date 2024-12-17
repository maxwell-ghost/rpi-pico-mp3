#include "rpi_time.h"

uint64_t timer = 0;


void wait_ms(uint32_t ms) {
	// 空循环
	while(!timer_expired(&timer, ms, millis())) (void)0;
	timer = 0; // 重置计时器
}