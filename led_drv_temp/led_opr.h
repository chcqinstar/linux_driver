#ifndef _LED_OPR
#define _LED_OPT

struct led_operations
{
    int (*init)(int which);            /*初始化led，which-哪个led(使用次设备号区分)*/
    int (*ctl)(int which, int status); /*控制led，status-led状态：1-on|0-off*/
};

struct led_operations *get_board_led_opr(void);
#endif