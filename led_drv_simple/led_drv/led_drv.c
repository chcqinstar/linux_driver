
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

// Major device number
static int major = 0;
// Device structure
static struct class *led_class;

/*registers*/
// GPIO5_3:IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER3:229_0000h base + 14h offset = 0x02290000+0x14
static volatile unsigned int *IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER3;

// GPIO5_GDIR :Base address + 4h offset= 020A_C000+4 =0x020AC004
static volatile unsigned int *GPIO5_GDIR;

// GPIO5:_DR:Base address + 0h offset=020A_C000+0=0x020AC000
static volatile unsigned int *GPIO5_DR;

// write()
static ssize_t led_write(struct file *filp, const char __user *buf, size_t count, loff_t *ppos)
{
    char val;
    int ret;
    /*copy from user:get data from app*/
    ret = copy_from_user(&val, buf, 1);
    if (ret < 0)
    {
        printk("copy_from_user err\n");
    }

    /*set gpio register : out 1/0 */
    if (val)
    {
        /*set gpio to led on*/
        *GPIO5_DR &= ~(1 << 3);
    }
    else
    {
        /*set gpio led off*/
        *GPIO5_DR |= (1 << 3);
    }
    return 1;
}

// open()函数
static int led_open(struct inode *inode, struct file *filp)
{

    // enable gpio ，imx6ull Enabled by default
    // configure pin GPIO5_3 as gpio
    *IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER3 &= ~0xf;
    *IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER3 |= 0x05;

    // configure gpio as output
    *GPIO5_GDIR |= (1 << 3);

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
    printk("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);

    /*Register device driver*/
    major = register_chrdev(0, "100ask_led", &led_fops);

    /*ioremap：map register*/
    // GPIO5_3:IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER3:229_0000h base + 14h offset = 0x02290000+0x14
    IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER3 = ioremap(0x02290000 + 0x14, 4);

    // GPIO5_GDIR :Base address + 4h offset= 020A_C000+4 =0x020AC004
    GPIO5_GDIR = ioremap(0x020AC004, 4);

    // GPIO5:_DR:Base address + 0h offset=020A_C000+0=0x020AC000
    GPIO5_DR = ioremap(0x020AC000, 4);

    /*Create device structure*/
    led_class = class_create(THIS_MODULE, "100ask_led");

    /*Create device node:/dev/100ask_led*/
    device_create(led_class, NULL, MKDEV(major, 0), NULL, "100ask_led");

    return 0;
}

/*export function*/
static void __exit led_exit(void)
{
    iounmap(IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER3);
    iounmap(GPIO5_GDIR);
    iounmap(GPIO5_DR);

    device_destroy(led_class, MKDEV(major, 0));
    class_destroy(led_class);
    unregister_chrdev(major, "100ask_led");
}

module_init(led_init);
module_exit(led_exit);
MODULE_LICENSE("GPL");
