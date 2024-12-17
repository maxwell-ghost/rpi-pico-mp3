#include "hal.h"

/* GPIO 相关 */
void gpio_init(uint16_t pin, uint8_t mode, uint8_t fn) {
    int no = PINNO(pin);
    if (mode == GPIO_MODE_INPUT) {
        SIO->GPIO_OE &= ~BIT(no);
        IO_BANK0->gpio[no].CTRL = 5;
    } else if (mode == GPIO_MODE_OUTPUT) {
        SIO->GPIO_OE |= BIT(no);
        IO_BANK0->gpio[no].CTRL = 5;
    } else if (mode == GPIO_MODE_AF) {
        IO_BANK0->gpio[no].CTRL = fn;
    }
}

void gpio_write(uint16_t pin, bool val) {
    if (val) {
        SIO->GPIO_OUT |= BIT(PINNO(pin));
    } else {
        SIO->GPIO_OUT &= ~BIT(PINNO(pin));
    }
}

void gpio_set_irq_enabled(uint16_t pin, uint32_t events, bool enabled) {
    
    // 设置raw intrrupt, 清理伪中断？？？？
    IO_BANK0->INTR[pin / 8] = events << (4 * (pin % 8));
    // 设置INTE寄存器
    if (enabled) {
        IO_BANK0->PROC[0].INTE[pin / 8] |= (events << 4 * (pin % 8));
    } else {
        IO_BANK0->PROC[0].INTE[pin / 8] &= ~(events << 4 * (pin % 8));
    }

    if (enabled) irq_set_enabled(IO_IRQ_BANK0, true);
}

void irq_set_enabled(uint32_t num, bool enabled) {
    uint32_t mask = 1u << num;
    if (enabled) {
        NVIC->ICPR = mask;
        NVIC->ISER = mask;
    } else {
        NVIC->ICER = mask;
    }
}

void spi_write_bytes(struct spi *spi, volatile uint8_t *src, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        while(!spi_is_writable(spi))
            (void)0;
        spi->DR = (uint32_t)src[i];
    }

    while (spi_is_readable(spi))
        (void)spi->DR;
    while (spi_is_busy(spi))
        (void)0;
    while (spi_is_readable(spi))
        (void)spi->DR;

    spi->ICR = 0x00000001;

}

void spi_write_byte(struct spi *spi, uint8_t byte) {
    spi_write_bytes(spi, &byte, 1);
}
