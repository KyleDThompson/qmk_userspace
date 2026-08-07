/* Workaround for second half not communicating correctly */
#define usb_lld_disconnect_bus(usbp) do {} while(0)

/* enabling LED color changes on both PCBs */
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE

/* prevent no primary on USB dock */
#define SPLIT_WATCHDOG_ENABLE

/* prevent display sleeping */
#ifndef ST7565_TIMEOUT
#define ST7565_TIMEOUT 60000
#endif
