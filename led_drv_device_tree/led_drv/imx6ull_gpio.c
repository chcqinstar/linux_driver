#include "led_resource.h"
#include "leddrv.h"
#include "linux/of.h"
#include <linux/device.h>
#include <linux/errno.h>
#include <linux/fs.h>
#include <linux/gfp.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/kmod.h>
#include <linux/major.h>
#include <linux/miscdevice.h>
#include <linux/mod_devicetable.h>
#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/platform_device.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/stat.h>
#include <linux/tty.h>

static int g_ledpins[100];
static int g_ledcnt = 0;

static int imx6ull_led_init(int which) /* 初始化LED, which-哪个LED */
{
    // printk("%s %s line %d, led %d\n", __FILE__, __FUNCTION__, __LINE__, which);

    printk("init gpio: group %d, pin %d\n", GROUP(g_ledpins[which]), PIN(g_ledpins[which]));
    switch (GROUP(g_ledpins[which]))
    {
    case 0: {
        printk("init pin of group 0 ...\n");
        break;
    }
    case 1: {
        printk("init pin of group 1 ...\n");
        break;
    }
    case 2: {
        printk("init pin of group 2 ...\n");
        break;
    }
    case 3: {
        printk("init pin of group 3 ...\n");
        break;
    }
    }

    return 0;
}

static int imx6ull_led_ctl(int which, char status) /* 控制LED, which-哪个LED, status:1-亮,0-灭 */
{
    // printk("%s %s line %d, led %d, %s\n", __FILE__, __FUNCTION__, __LINE__,
    // which, status ? "on" : "off");
    printk("set led %s: group %d, pin %d\n", status ? "on" : "off", GROUP(g_ledpins[which]), PIN(g_ledpins[which]));

    switch (GROUP(g_ledpins[which]))
    {
    case 0: {
        printk("set pin of group 0 ...\n");
        break;
    }
    case 1: {
        printk("set pin of group 1 ...\n");
        break;
    }
    case 2: {
        printk("set pin of group 2 ...\n");
        break;
    }
    case 3: {
        printk("set pin of group 3 ...\n");
        break;
    }
    }

    return 0;
}

static struct led_operations imx6ull_led_opr = {
    .init = imx6ull_led_init,
    .ctl = imx6ull_led_ctl,
};

struct led_operations *get_board_led_opr(void)
{
    return &imx6ull_led_opr;
}
/*当设备树中存在多个设备节点的compatible属性匹配成功时，
内核通常会为每个匹配成功的设备节点创建一个对应的设备对象(*pdev)，
并调用该驱动程序的probe函数多次，每次传递不同的设备对象作为参数。*/
static int imx6ull_gpio_probe(struct platform_device *pdev)
{
    int err = 0;
    struct device_node *np;
    int led_pin;
    np = pdev->dev.of_node;
    if (!np)
    {
        return -1;
    }
    err = of_property_read_u32(np, "pin", &led_pin);

    g_ledpins[g_ledcnt] = led_pin;
    led_class_create_device(g_ledcnt);
    g_ledcnt++;

    return 0;
}

static int imx6ull_gpio_remove(struct platform_device *pdev)
{
    int i;
    int err = 0;
    int led_pin;
    struct device_node *np;
    int ret = 0;
    np = pdev->dev.of_node;
    if (!np)
    {
        return -1;
    }
    err = of_property_read_u32(np, "pin", &led_pin);
    for (i = 0; i < g_ledcnt; i++)
    {
        if (g_ledpins[i] == led_pin)
        {
            led_class_destroy_device(i);
            g_ledpins[i] = -1;
            break;
        }
    }
    for (i = 0; i < g_ledcnt; i++)
    {
        if (g_ledpins[i] != -1)
            ret = 1;
    }
    if (ret == 1)
    {
        g_ledcnt = 0;
    }

    return 0;
}
static struct of_device_id imx6ull_led_match[] = {
    {
        .compatible = "100ask,leddrv",
    },
    {},
};

MODULE_DEVICE_TABLE(of, imx6ull_led_match);

static struct platform_driver imx6ull_gpio_driver = {
    .probe = imx6ull_gpio_probe,
    .remove = imx6ull_gpio_remove,
    .driver = {.name = "100ask_led", .of_match_table = imx6ull_led_match},
};

static int __init imx6ull_gpio_drv_init(void)
{
    int err;

    err = platform_driver_register(&imx6ull_gpio_driver);
    register_led_operations(&imx6ull_led_opr);

    return 0;
}

static void __exit imx6ull_gpio_drv_exit(void)
{
    platform_driver_unregister(&imx6ull_gpio_driver);
}

module_init(imx6ull_gpio_drv_init);
module_exit(imx6ull_gpio_drv_exit);
MODULE_LICENSE("GPL");
