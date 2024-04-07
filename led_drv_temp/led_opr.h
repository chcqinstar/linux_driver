#ifndef _LED_OPR_H
#define _LED_OPR_H

struct led_operations
{
    int num;
    int (*init)(int which);             /*函数指针：初始化led，which-哪个led(使用次设备号区分)*/
    int (*ctl)(int which, char status); /*函数指针：控制led，status-led状态：1-on|0-off*/
};

struct led_operations *get_board_led_opr(void);
#endif