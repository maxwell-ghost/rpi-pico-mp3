#ifndef _RPI_TIME_H
#define _RPI_TIME_H

/*
----------------------------------------------------------------
关于时间的各种功能，向上层(oled audio)提供抽象
----------------------------------------------------------------
*/
#include "hal.h"

extern uint64_t millis(void);

// t: expiration time, prd: period, now: current time. Return true if expired
static inline bool timer_expired(uint64_t *t, uint32_t prd, uint64_t now)
{
    if (now + prd < *t)
        *t = 0; // Time wrapped? Reset timer
    if (*t == 0)
        *t = now + prd; // Firt poll? Set expiration
    if (*t > now)
        return false;                             // Not expired yet, return
    *t = (now - *t) > prd ? now + prd : *t + prd; // Next expiration time
    return true;                                  // Expired, return true
}

/*
阻塞对应的ms
一个wrapper, 调用timer_expired中
*/
void wait_ms(uint32_t ms);

#endif
