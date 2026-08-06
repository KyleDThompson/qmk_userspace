/* Workaround for second half not communicating correctly */
#define usb_lld_disconnect_bus(usbp) do {} while(0)