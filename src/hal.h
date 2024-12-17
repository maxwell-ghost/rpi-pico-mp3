#ifndef _HAL_H
#define _HAL_H

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#define BIT(x) (1UL << (x))
#define PIN(bank, num) ((((bank) - 'A') << 8) | (num))
#define PINNO(pin) ((pin) &255)
#define PINBANK(pin) ((pin) >> 8)

// Arm核心内部的timer，见2.4
struct systick {
    volatile uint32_t CTRL, LOAD, VAL, CALIB;
};
#define SYSTICK ((struct systick *) 0xe000e010)

// eXecute In Place
struct xip_ssi {
    volatile uint32_t CTRLR0, CTRLR1, SSIENR, MWCR, SER, BAUDR, TXFTLR, RXFTLR,
        TXFLR, RXFLR, SR, IMR, ISR, RISR, TXOICR, RXOICR, RXUICR, MSTICR, ICR,
        DMACR, DMATDLR, DMARDLR, IDR, SSI_VERSION_ID, DR0, RESERVED[35],
        RX_SAMPLE_DLY, SPI_CTRLR0, TXD_DRIVE_EDGE;
};
#define XIP_SSI ((struct xip_ssi *) 0x18000000)

// ？
struct scb {
    volatile uint32_t CPUID, ICSR, VTOR, AIRCR, SCR, CCR;  // Incomplete
};
#define SCB ((struct scb *) 0xe000ed00)

// System clock
// FREQUENCY = ((FREF / REFDIV) × FBDIV / (POSTDIV1 × POSTDIV2))
//          REF    FBDIV   VCO      PDIV1   PDIV2   RESULT
// SYS PLL: 12MHz * 133 = 1596MHz /   6   /   2  =  133MHz
// USB PLL: 12MHz * 100 = 1200MHz /   5   /   5  =  48MHz
enum { F_REF = 12000000, F_REFDIV = 1 };
enum { F_SYS_FBDIV = 133, F_SYS_POSTDIV1 = 6, F_SYS_POSTDIV2 = 2 };
enum { F_USB_FBDIV = 100, F_USB_POSTDIV1 = 5, F_USB_POSTDIV2 = 5 };
#define F_SYS \
    ((F_REF / F_REFDIV) * F_SYS_FBDIV / (F_SYS_POSTDIV1 * F_SYS_POSTDIV2))
#define F_USB \
    ((F_REF / F_REFDIV) * F_USB_FBDIV / (F_USB_POSTDIV1 * F_USB_POSTDIV2))

// 时钟部分，见手册2.15
struct clocks {
    struct {
        volatile uint32_t CTRL, DIV, SELECTED;
    } GPOUT0, GPOUT1, GPOUT2, GPOUT3, REF, SYS, PERI, USB, ADC, RTC;
    volatile uint32_t SYS_RESUS_CTRL, SYS_RESUS_STATUS, FC0_REF_KHZ, FC0_MIN_KHZ,
        FC0_MAX_KHZ, FC0_DELAY, FC0_INTERVAL, FC0_SRC, FC0_STATUS, FC0_REST,
        WAKE_EN0, WAKE_EN1, SLEEP_EN0, SLEEP_EN1, ENABLED0, ENABLED1, INTR, INTE,
        INTF, INTS;
};
#define CLOCKS ((struct clocks *) 0x40008000)

// 外部晶振部分，详细见手册2.15 2.16
struct xosc {
    volatile uint32_t CTRL, STATUS, DORMANT, STARTUP, RESERVED[3], COUNT;
};
#define XOSC ((struct xosc *) 0x40024000)

// 锁相环部分，详细见2.18
struct pll {
    volatile uint32_t CS, PWR, FBDIV_INT, PRIM;
};
#define PLL_SYS ((struct pll *) 0x40028000)
#define PLL_USB ((struct pll *) 0x4002c000)

// SIO接口
struct sio {
    volatile uint32_t CPUID, GPIO_IN, GPIO_HI_IN, RESERVED, GPIO_OUT,
        GPIO_OUT_SET, GPIO_OUT_CLR, GPIO_OUT_XOR, GPIO_OE, GPIO_OE_SET,
        GPIO_OE_CLR, GPIO_OE_XOR, GPIO_HI_OUT, GPIO_HI_OUT_SET, GPIO_HI_OUT_CLR,
        GPIO_HI_OUT_XOR, GPIO_HI_OE, GPIO_HI_OE_SET, GPIO_HI_OE_CLR,
        GPIO_HI_OE_XOR, FIFO_ST, FIFO_WR, FIFO_RD, SPINLOCK_ST, DIV_UDIVIDEND,
        DIV_UDIVISOR, DIV_SDIVIDEND, DIV_SDIVISOR, DIV_QUOTIENT, DIV_REMAINDER;
};
#define SIO ((struct sio *) 0xd0000000)

// 负责初始化外设的寄存器
struct resets {
    volatile uint32_t RESET, WDSEL, DONE;
};
#define RESETS ((struct resets *) 0x4000c000)

// 串口相关
struct uart {
    volatile uint32_t DR, RSR, RESERVED[4], FR, RESERVED1[1], ILPR, IBRD, FBRD,
        LCR_H, CR, IFLS, IMSC, RIS, MIS, ICR, DMACR, RESERVED2[997], PERIPHID[4],
        PERIPHCELLID[4];
};
#define UART0 ((struct uart *) 0x40034000)
#define UART1 ((struct uart *) 0x40038000)


/*
----------------------------------------------------------------
这里是和GPIO相关的
----------------------------------------------------------------
*/
// IOBANK相关
struct io_bank {
    struct {
        volatile uint32_t STATUS, CTRL;
    } gpio[30];
    volatile uint32_t INTR[4];
    struct {
        volatile uint32_t INTE[4], INTF[4], INTS[4];
    } PROC[2];
    volatile uint32_t DORMANT_WAKE_INTE[4], DORMANT_WAKE_INTF[4],
        DORMANT_WAKE_INTS[4];
};
#define IO_BANK0 ((struct io_bank *) 0X40014000)

// GPIO mode
enum { GPIO_MODE_INPUT, GPIO_MODE_OUTPUT, GPIO_MODE_AF, GPIO_MODE_ANALOG };

/*
gpio管脚初始化，pin为GPx，mode为以上四种，fn(功能)需要查看手册
fn负责 是否为SPI PWM ...
*/
void gpio_init(uint16_t pin, uint8_t mode, uint8_t fn);

/*
gpio写出值
*/
void gpio_write(uint16_t pin, bool val);

// GPIO读
static inline bool gpio_read(uint16_t pin) { return SIO->GPIO_IN & BIT(pin); }

/*
GPIO设置中断，pin为GPx，events为 
x x x x ，每位为二进制，分别对应 边缘高触发 边缘低触发 高触发 低触发
*/ 
void gpio_set_irq_enabled(uint16_t pin, uint32_t events, bool enabled);

// GPIO承认中断，在设置为边缘触发后必须调用此函数才会停止中断触发
static inline void gpio_acknowledge_irq(uint16_t pin, uint32_t events) {
    IO_BANK0->INTR[pin / 8] = events << (4 * (pin % 8));
}

/*
----------------------------------------------------------------
这里是和NVIC中断相关的
----------------------------------------------------------------
*/
enum {
    IO_IRQ_BANK0 = 13
};
struct nvic {
    // Interrupt Set-Enable Register
    // 0xffffffff [31:0]  SETENA       (0x00000000) Interrupt set-enable bits
    uint32_t ISER;
 
    uint32_t _pad0[31];
 
    // Interrupt Clear-Enable Register
    // 0xffffffff [31:0]  CLRENA       (0x00000000) Interrupt clear-enable bits
    uint32_t ICER;
 
    uint32_t _pad1[31];
 
    // Interrupt Set-Pending Register
    // 0xffffffff [31:0]  SETPEND      (0x00000000) Interrupt set-pending bits
    uint32_t ISPR;
 
    uint32_t _pad2[31];
 
    // Interrupt Clear-Pending Register
    // 0xffffffff [31:0]  CLRPEND      (0x00000000) Interrupt clear-pending bits
    uint32_t ICPR;
 
    uint32_t _pad3[95];
 
    // (Description copied from array index 0 register M0PLUS_NVIC_IPR0 applies similarly to other array indexes)
    // Interrupt Priority Register 0
    // 0xc0000000 [31:30] IP_3         (0x0) Priority of interrupt 3
    // 0x00c00000 [23:22] IP_2         (0x0) Priority of interrupt 2
    // 0x0000c000 [15:14] IP_1         (0x0) Priority of interrupt 1
    // 0x000000c0 [7:6]   IP_0         (0x0) Priority of interrupt 0
    uint32_t IPR[8];
};
#define NVIC ((struct nvic *) 0xe000e100)

/*
设置中断的使能，这里参考官方的sdk
num为中断号，参考startup.c中的中断以及手册
此处非mcu内核内部中断，为中断控制器控制的外部中断
*/
void irq_set_enabled(uint32_t num, bool enabled);



// 负责外设的初始化，每个部分4个字节, 见2.14
static inline void enable_subsystem(uint32_t bits) {
    // 将对应的外设的位置为0，开始Reset
    RESETS->RESET &= ~bits;      // 取反对应位为0，相与让对应位归零
    // 等待Reset完成
    while ((RESETS->DONE & bits) == 0) (void) 0;    // 等待对应位变为0
}


// 负责初始化各种时钟和使能外设
static inline void clock_init(void) {
    XOSC->CTRL = 2720;         // XOSC frequency range 1-15 MHz
    XOSC->STARTUP = 47;        // About 1 ms, see 2.16.3
    XOSC->CTRL |= 4011 << 12;  // Enable XOSC
    while ((XOSC->STATUS & BIT(31)) == 0) (void) 0;  // Wait until enabled

    enable_subsystem(BIT(12));  // Reset SYS PLL
    PLL_SYS->FBDIV_INT = F_SYS_FBDIV;
    PLL_SYS->PRIM = (F_SYS_POSTDIV1 << 16) | (F_SYS_POSTDIV2 << 12);
    PLL_SYS->PWR &= ~(BIT(0) | BIT(3) | BIT(5));    // Power up
    while ((PLL_SYS->CS & BIT(31)) == 0) (void) 0;  // Wait

    // enable_subsystem(BIT(13));  // Reset USB PLL
    // PLL_USB->FBDIV_INT = F_USB_FBDIV;
    // PLL_USB->PRIM = (F_USB_POSTDIV1 << 16) | (F_USB_POSTDIV2 << 12);
    // PLL_USB->PWR &= ~(BIT(0) | BIT(3) | BIT(5));    // Power up
    // while ((PLL_USB->CS & BIT(31)) == 0) (void) 0;  // Wait

    CLOCKS->REF.CTRL = (2 << 0);             // REF source is XOSC
    CLOCKS->SYS.CTRL = (0 << 5) | (1 << 0);  // SYS source is CLKSYS_AUX
    CLOCKS->PERI.CTRL = BIT(11) | (0 << 5);  // PERI clock enable, source SYS
    // CLOCKS->USB.CTRL = BIT(11) | (0 << 5);   // USB clock enable, source USB PLL
    // CLOCKS->ADC.CTRL = BIT(11) | (0 << 5);   // ADC clock enable, source USB PLL
    // CLOCKS->RTC.DIV = (48 << 8);             // RTC divider: 12 / 48 = 0.25Mhz
    // CLOCKS->RTC.CTRL = BIT(11) | (3 << 5);   // RTC clock enable, source XOSC

    enable_subsystem(BIT(5) | BIT(8));  // IO_BANK0 and PADS_BANK0

    SYSTICK->LOAD = F_SYS / 1000 - 1;
    SYSTICK->VAL = 0;
    SYSTICK->CTRL = BIT(0) | BIT(1) | BIT(2);  // Enable SysTick
}

// 串口初始化
static inline void uart_init(struct uart *uart, unsigned baud, uint16_t rx,
                             uint16_t tx) {
    enable_subsystem(uart == UART0 ? BIT(22) : BIT(23));
    uint32_t div = (8 * F_SYS / baud);       // Baud rate divisor
    uart->IBRD = div >> 7;                   // Set integer part
    uart->FBRD = ((div & 0x7f) + 1) / 2;     // Set float part
    uart->LCR_H = BIT(4) | BIT(5) | BIT(6);  // FIFO, 8-bit, 1 stop, no parity
    uart->CR = BIT(0) | BIT(8) | BIT(9);     // Enable, TX, RX
    uart->DMACR = BIT(0) | BIT(1);           // Enable DREQ
    gpio_init(rx, GPIO_MODE_AF, 2);          // Set RX/TX pins to use the UART
    gpio_init(tx, GPIO_MODE_AF, 2);          // alternate function - 2
}

// 发送一个字节
static inline void uart_write_byte(struct uart *uart, uint8_t byte) {
    while (uart->FR & BIT(5)) (void) 0;  // Wait while TX FIFO is full
    uart->DR = byte;
}

static inline void uart_write_buf(struct uart *uart, char *buf, size_t len) {
    while (len-- > 0) { uart_write_byte(uart, *(uint8_t *) buf++); }
};

// spi
struct spi {
    // Control register 0, SSPCR0 on page 3-4
    // 0x0000ff00 [15:8]  : SCR (0): Serial clock rate
    // 0x00000080 [7]     : SPH (0): SSPCLKOUT phase, applicable to Motorola SPI frame format only
    // 0x00000040 [6]     : SPO (0): SSPCLKOUT polarity, applicable to Motorola SPI frame format only
    // 0x00000030 [5:4]   : FRF (0): Frame format: 00 Motorola SPI frame format
    // 0x0000000f [3:0]   : DSS (0): Data Size Select: 0000 Reserved, undefined operation
    volatile uint32_t CR0;

    // Control register 1, SSPCR1 on page 3-5
    // 0x00000008 [3]     : SOD (0): Slave-mode output disable
    // 0x00000004 [2]     : MS (0): Master or slave mode select
    // 0x00000002 [1]     : SSE (0): Synchronous serial port enable: 0 SSP operation disabled
    // 0x00000001 [0]     : LBM (0): Loop back mode: 0 Normal serial port operation enabled
    volatile uint32_t CR1;

    // Data register, SSPDR on page 3-6
    // 0x0000ffff [15:0]  : DATA (0): Transmit/Receive FIFO: Read Receive FIFO
    volatile uint32_t DR;

    // Status register, SSPSR on page 3-7
    // 0x00000010 [4]     : BSY (0): PrimeCell SSP busy flag, RO: 0 SSP is idle
    // 0x00000008 [3]     : RFF (0): Receive FIFO full, RO: 0 Receive FIFO is not full
    // 0x00000004 [2]     : RNE (0): Receive FIFO not empty, RO: 0 Receive FIFO is empty
    // 0x00000002 [1]     : TNF (1): Transmit FIFO not full, RO: 0 Transmit FIFO is full
    // 0x00000001 [0]     : TFE (1): Transmit FIFO empty, RO: 0 Transmit FIFO is not empty
    volatile uint32_t SR;

    // Clock prescale register, SSPCPSR on page 3-8
    // 0x000000ff [7:0]   : CPSDVSR (0): Clock prescale divisor
    volatile uint32_t CPSR;

    // Interrupt mask set or clear register, SSPIMSC on page 3-9
    // 0x00000008 [3]     : TXIM (0): Transmit FIFO interrupt mask: 0 Transmit FIFO half empty or less condition interrupt is masked
    // 0x00000004 [2]     : RXIM (0): Receive FIFO interrupt mask: 0 Receive FIFO half full or less condition interrupt is masked
    // 0x00000002 [1]     : RTIM (0): Receive timeout interrupt mask: 0 Receive FIFO not empty and no read prior to timeout...
    // 0x00000001 [0]     : RORIM (0): Receive overrun interrupt mask: 0 Receive FIFO written to while full condition...
    volatile uint32_t IMSC;

    // Raw interrupt status register, SSPRIS on page 3-10
    // 0x00000008 [3]     : TXRIS (1): Gives the raw interrupt state, prior to masking, of the SSPTXINTR interrupt
    // 0x00000004 [2]     : RXRIS (0): Gives the raw interrupt state, prior to masking, of the SSPRXINTR interrupt
    // 0x00000002 [1]     : RTRIS (0): Gives the raw interrupt state, prior to masking, of the SSPRTINTR interrupt
    // 0x00000001 [0]     : RORRIS (0): Gives the raw interrupt state, prior to masking, of the SSPRORINTR interrupt
    volatile uint32_t RIS;

    // Masked interrupt status register, SSPMIS on page 3-11
    // 0x00000008 [3]     : TXMIS (0): Gives the transmit FIFO masked interrupt state, after masking, of the SSPTXINTR interrupt
    // 0x00000004 [2]     : RXMIS (0): Gives the receive FIFO masked interrupt state, after masking, of the SSPRXINTR interrupt
    // 0x00000002 [1]     : RTMIS (0): Gives the receive timeout masked interrupt state, after masking, of the SSPRTINTR interrupt
    // 0x00000001 [0]     : RORMIS (0): Gives the receive over run masked interrupt status, after masking, of the...
    volatile uint32_t MIS;

    // Interrupt clear register, SSPICR on page 3-11
    // 0x00000002 [1]     : RTIC (0): Clears the SSPRTINTR interrupt
    // 0x00000001 [0]     : RORIC (0): Clears the SSPRORINTR interrupt
    volatile uint32_t ICR;

    // DMA control register, SSPDMACR on page 3-12
    // 0x00000002 [1]     : TXDMAE (0): Transmit DMA Enable
    // 0x00000001 [0]     : RXDMAE (0): Receive DMA Enable
    volatile uint32_t DMACR;
};

#define SPI0 ((struct spi *) 0x4003c000)
#define SPI1 ((struct spi *) 0x40040000)

// clk_peri use clk_sys, that is 133mhz
static inline void spi_set_format(struct spi *spi) {
    //uint32_t freq_in = F_SYS;
    //uint8_t prescale, postdiv;

    // disable spi, clear SSE field of CR1
    spi->CR1 &= ~(1UL << 1);


    // Set clock of spi: F_SYS / 4
    spi->CPSR = 4UL; // prescale
    spi->CR0 &= ~(0xffUL << 8); // clear bit 15:8
    spi->CR0 |= (1UL << 8); // postdiv


    // Set data size: 8
    spi->CR0 &= ~(0xfUL << 0);
    spi->CR0 |= (0x7UL << 0);

    // SSPCLKOUT phase:0 polarity:0
    spi->CR0 &= ~(0x3UL << 6);

    // enable spi, set SSE field of CR to 1
    spi->CR1 |= (1UL << 1);

    // Find prescale
    // for (prescale = 2; prescale <= 254; prescale += 2) {
    //     if (freq_in < (prescale + 2) * 256 * baudrate)
    //         break;
    // }


}


static inline void spi_init(struct spi *spi) {
    enable_subsystem(spi == SPI0 ? BIT(16) : BIT(17));
    spi_set_format(spi);
}

inline bool spi_is_busy(struct spi *spi) {
    return (spi->SR & (1UL << 4));
}

inline bool spi_is_writable(struct spi *spi) {
    return (spi->SR & (1UL << 1)); // TNF
}

inline bool spi_is_readable(struct spi *spi) {
    return (spi->SR & (1UL << 2)); // RNE
}

void spi_write_bytes(struct spi *spi, volatile uint8_t *src, size_t len);

void spi_write_byte(struct spi *spi, uint8_t byte);


/* PWM 相关 */

struct pwm {
    // Control and status register
    // 0x00000080 [7]     : PH_ADV (0): Advance the phase of the counter by 1 count, while it is running
    // 0x00000040 [6]     : PH_RET (0): Retard the phase of the counter by 1 count, while it is running
    // 0x00000030 [5:4]   : DIVMODE (0)
    // 0x00000008 [3]     : B_INV (0): Invert output B
    // 0x00000004 [2]     : A_INV (0): Invert output A
    // 0x00000002 [1]     : PH_CORRECT (0): 1: Enable phase-correct modulation
    // 0x00000001 [0]     : EN (0): Enable the PWM channel
    volatile uint32_t CSR;

    // PWM_CH0_DIV
    // INT and FRAC form a fixed-point fractional number
    // 0x00000ff0 [11:4]  : INT (1)
    // 0x0000000f [3:0]   : FRAC (0)
    volatile uint32_t DIV;

    // PWM_CH0_CTR
    // Direct access to the PWM counter
    // 0x0000ffff [15:0]  : CH0_CTR (0)
    volatile uint32_t CTR;

    // PWM_CH0_CC
    // Counter compare values
    // 0xffff0000 [31:16] : B (0)
    // 0x0000ffff [15:0]  : A (0)
    volatile uint32_t CC;

    // PWM_CH0_TOP
    // Counter wrap value
    // 0x0000ffff [15:0]  : CH0_TOP (0xffff)
    volatile uint32_t TOP;
};

#define PWMCH3 ((struct pwm *) 0x4005003c)

static inline void pwm_init(struct pwm* pwm_slice) {
    if (pwm_slice == PWMCH3) {
        enable_subsystem(BIT(14));
    } else {
        printf("Not support now!\n");
    }

    pwm_slice->CSR = 0; // Disable pwm
    pwm_slice->CTR = 0; // Direct to pwm counter
    pwm_slice->CC = 0x00000000; // compared value
    pwm_slice->TOP = 0x0000ffff; // Max conut
    pwm_slice->DIV = (8UL << 4); // 8倍分频
    pwm_slice->CSR = (1UL << 0); // 启用PWM
}

static inline void pwm_set_freq(struct pwm* pwm_slice, uint8_t div_int, uint8_t div_frac) {
    pwm_slice->DIV = (uint32_t)((div_int << 4) + div_frac);
}

// direct set freq, 直接设置频率
static inline void pwm_dset_freq(struct pwm* pwm_slice, uint16_t note) {
    pwm_slice->DIV = (uint32_t)(note);
}

// 最高255
static inline void pwm_set_volume(struct pwm* pwm_slice, uint16_t volume) {
    pwm_slice->CC = (uint32_t)volume; // compared value
}

static inline void pwm_enable(struct pwm* pwm_slice) {
    pwm_slice->CSR = (1UL << 0);
}

static inline void pwm_disable(struct pwm* pwm_slice) {
    pwm_slice->CSR = (0UL << 0);
}

#endif