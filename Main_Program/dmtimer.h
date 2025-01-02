#ifndef DMTIMER_H
#define DMTIMER_H

#define TIMER6_BASE 0x48048000
#define TCRR_OFFSET 0x3C
#define TCLR_OFFSET 0x38
#define CM_PER  0x44E00000
#define TCAR1 0x50
#define IRQENABLE_SET 0x2C
#define IRQSTATUS 0x28
#define CM_PER_TIMER6_CLKCTRL 0xF0
#define CLKSEL_TIMER6_CLK 0x1C
#define TCAR1_OFFSET 0x50
#define TCAR2_OFFSET 0x58

extern volatile uint32_t *timer6_CTRL;
extern volatile uint32_t *timer6_map;
#ifdef __cplusplus
extern "C" {
#endif
void setuptimer();
#ifdef __cplusplus
}
#endif
#endif

