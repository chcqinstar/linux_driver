#include "linux/export.h"
#include <linux/device.h>
#include <linux/errno.h>
#include <linux/fs.h>
#include <linux/gfp.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/kmod.h>
#include <linux/major.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/stat.h>
#include <linux/stddef.h>
#include <linux/tty.h>
#include <linux/uaccess.h>

// 1、确定输设备号
// 2、实现open/read/write等函数
// 3、声明file_operations结构体，并填入open/read/write函数
// 4、注册驱动程序，将file_operations结构体告知内核
// 5、使用入口/出口函数注册/卸载驱动程序
// 6、其他完善：提供设备信息，自动创建设备节点

MODULE_AUTHOR("CHC");
MODULE_DESCRIPTION("hello_drv");
MODULE_LICENSE("GPL"); //声明程序尊守开源协议“GPL”(必要)

#define MIN(a, b) (a < b ? a : b)
// 1、确定输设备号
static int major = 0; //取0，让内核确定主设备号
static char kernel_buf[1024];
static struct class *hello_drv_class;

// 2、实现open/read/write等函数

/*
struct file *file: 指向表示打开文件的结构体的指针。
char __user *user_buffer:指向用户空间缓冲区的指针
size_t count:要读取的字节数。
loff_t *ppos:指向文件偏移量的指针。文件偏移量表示从文件的哪个位置开始读取数据。
*/
//用户将kernel_buf中数据读到buf中
static ssize_t hello_drv_read(struct file *file, char __user *buf, size_t size, loff_t *ppos)
{
    int ret;
    printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
    ret = copy_to_user(buf, kernel_buf, MIN(1024, size));
    if (ret < 0)
    {
        printk("read失败\n");
    }
    else
    {
        printk("read成功，复制字节数：%d\n", ret);
    }
    return MIN(1024, size); //返回已处理数据长度
}

/*
write函数和read函数类似
*/
//将user的buf数据拷贝到kernel_buf中
static ssize_t hello_drv_write(struct file *file, const char __user *buf, size_t size, loff_t *ppos)
{
    int ret;
    printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
    ret = copy_from_user(kernel_buf, buf, MIN(1024, size));
    if (ret < 0)
    {
        printk("write失败\n");
    }
    else
    {
        printk("write成功,复制字节数：%d\n", ret);
    }
    return MIN(1024, size); //返回已处理数据长度
}

static int hello_drv_open(struct inode *inode, struct file *file)
{
    printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
    return 0; //成功则返回0
}
static int hello_drv_release(struct inode *inode, struct file *file)
{
    printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
    return 0; //成功则返回0
}

// 3、声明file_operations结构体，并填入open/read/write函数
static const struct file_operations hello_drv_ops = {
    .owner = THIS_MODULE,
    .open = hello_drv_open,
    .read = hello_drv_read,
    .write = hello_drv_write,
    .release = hello_drv_release,
};

// 4、注册驱动程序，将file_operations结构体告知内核
// 5、使用入口/出口函数注册/卸载驱动程序

static int __init hello_drv_init(void)
{
    int err;
    struct device *dev;
    printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
    /*
    注册设备
    major:设备号，取0则由内核分配设备号
    name：驱动程序名称
    fops：file_operations结构体
    */
    major = register_chrdev(0, "hello_drv", &hello_drv_ops);
    if (major >= 0)
    {
        printk("驱动程序注册成功，主设备号：%d\n", major);
    }
    else
    {
        printk("驱动程序注册失败\n");
    }
    //创建设备类结构体
    hello_drv_class = class_create(THIS_MODULE, "hello_drv");
    err = PTR_ERR(hello_drv_class);
    if (IS_ERR(hello_drv_class))
    {
        printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
        unregister_chrdev(major, "hello_drv");
        return -1;
    }

    /*创建设备节点，并注册到sysfs中
    class：指向设备类结构体的指针，用于指定新创建设备节点所属的设备类。
    parent：指向父设备的指针，通常为NULL。
    devt：设备号，用于标识设备节点。MKDEV()用于将主、次设备号合成devt格式的设备号
    drvdata：指向与设备相关的数据的指针。
    fmt：设备节点名称的格式字符串。
    */
    dev = device_create(hello_drv_class, NULL, MKDEV(major, 0), NULL, "hello_drv");
    if (dev == NULL)
    {
        printk("设备节点创建失败\n");
    }
    else
    {
        printk("设备节点创建成功\n");
    }
    return 0;
}

static void __exit hello_drv_exit(void)
{
    printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
    //销毁设备节点
    device_destroy(hello_drv_class, MKDEV(major, 0));
    //销毁设备结构体
    class_destroy(hello_drv_class);
    //卸载设备
    unregister_chrdev(major, "hello_drv");
}

// 6、其他完善：提供设备信息，自动创建设备节点

module_init(hello_drv_init);
module_exit(hello_drv_exit)