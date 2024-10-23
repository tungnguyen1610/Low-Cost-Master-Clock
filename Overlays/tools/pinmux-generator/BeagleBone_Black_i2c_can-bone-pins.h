

#define gpio_P9_19 &gpio0 13
#define gpio_P9_20 &gpio0 12

#define P9_19(mode) AM33XX_IOPAD(0x097c, mode)  /* D17: uart1_rtsn */
#define P9_20(mode) AM33XX_IOPAD(0x0978, mode)  /* D18: uart1_ctsn */
