
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

/* Major device number   */
static int major = 0;
/* Device structure */
static struct class *led_class;
/* 定义指向led_opr的指针 */
static struct led_operations *p_led_opr;

static ssize_t led_read(struct file *filp, char __user *buf, size_t count, loff_t *ppos)
{

    printk("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);

    return 0;
}

/*write(fd,&val,1);*/
static ssize_t led_write(struct file *filp, const char __user *buf, size_t count, loff_t *ppos)
{

    char status;
    int ret;
    /*获取inode -> 获取minor*/
    struct inode *inode = file_inode(filp);
    int minor = iminor(inode);
    printk("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);

    /*copy from user:get data from app*/
    ret = copy_from_user(&status, buf, 1);
    if (ret < 0)
    {
        printk("copy_from_user err\n");
    }

    /*根据次设备号和status控制led*/
    p_led_opr->ctl(minor, status);

    return 1;
}

static int led_open(struct inode *inode, struct file *filp)
{
    int minor;

    /* 获取次设备号 */
    minor = iminor(inode);
    printk("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);

    /* 根据次设备号和status初始化led */
    p_led_opr->init(minor);

    return 0;
}

static int led_release(struct inode *node, struct file *file)
{
    printk("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
    return 0;
}

/*file_operations*/
static struct file_operations led_fops = {
    .owner = THIS_MODULE,
    .read = led_read,
    .write = led_write,
    .open = led_open,
    .release = led_release,
};

/*Entry function*/
static int __init led_init(void)
{
    int i;

    printk("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);

    /*Register device driver*/
    major = register_chrdev(0, "100ask_led", &led_fops);

    /*Create device structure*/
    led_class = class_create(THIS_MODULE, "100ask_led_class");

    //获取结构体p_led_opr,从而获取单板控制led的函数
    p_led_opr = get_board_led_opr();

    /*Create device nodes:/dev/100ask_ledi*/
    for (i = 0; i < p_led_opr->num; i++)
    {
        device_create(led_class, NULL, MKDEV(major, i), NULL, "100ask_led%d", i);
    }

    return 0;
}

/*export function*/
static void __exit led_exit(void)
{
    int i;

    for (i = 0; i < p_led_opr->num; i++)
    {
        device_destroy(led_class, MKDEV(major, i));
    }

    class_destroy(led_class);
    unregister_chrdev(major, "100ask_led");
}

module_init(led_init);
module_exit(led_exit);
MODULE_LICENSE("GPL");
