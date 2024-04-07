
#include "led_opr.h"
#include <asm/io.h>
#include <asm/uaccess.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/export.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/poll.h>
#include <linux/slab.h>
#include <linux/stddef.h>
#include <linux/wait.h>

#define LED_NUM 2

/* Major device number   */
static int major = 0;
/* Device structure */
static struct class *led_class;
/* 定义指向led_opr的指针 */
static struct led_operations *p_led_opr;

static ssize_t led_write(struct file *filp, const char __user *buf, size_t count, loff_t *ppos)
{

    char status;
    int ret;

    printk("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);

    /*copy from user:get data from app*/
    ret = copy_from_user(&status, buf, 1);
    if (ret < 0)
    {
        printk("copy_from_user err\n");
    }

    return 1;
}

static int led_open(struct inode *inode, struct file *filp)
{
    int minor;

    /* 获取次设备号 */
    minor = iminor(inode);
    printk("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);

    /* 根据次设备号初始化led */
    p_led_opr->init(minor);

    return 0;
}

/*file_operations*/
static struct file_operations led_fops = {
    .owner = THIS_MODULE,
    .write = led_write,
    .open = led_open,
};

/*Entry function*/
static int __init led_init(void)
{
    int i;

    printk("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);

    /*Register device driver*/
    major = register_chrdev(0, "100askled", &led_fops);

    /*Create device structure*/
    led_class = class_create(THIS_MODULE, "100askled_class");

    /*Create device nodes:/dev/100ask_ledi*/
    for (i = 0; i < LED_NUM; i++)
    {
        device_create(led_class, NULL, MKDEV(major, i), NULL, "100askled%d", i);
    }
    //获取led_opr
    p_led_opr = get_board_led_opr();
    return 0;
}

/*export function*/
static void __exit led_exit(void)
{
    int i;

    for (i = 0; i < LED_NUM; i++)
    {
        device_destroy(led_class, MKDEV(major, i));
    }

    class_destroy(led_class);
    unregister_chrdev(major, "100askled");
}

module_init(led_init);
module_exit(led_exit);
MODULE_LICENSE("GPL");
