#include "led_opr.h"
#include <asm/io.h>
#include <linux/kernel.h>

/*定义虚拟地址*/

static volatile unsigned int *CCM_CCGR1;

static volatile unsigned int *IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER3;
static volatile unsigned int *GPIO5_GDIR;
static volatile unsigned int *GPIO5_DR;

static int board_led_init(int which)
{
    unsigned int val;
    printk("%s %s %d,led %d\n", __FILE__, __FUNCTION__, __LINE__, which);
    if (which == 0) // imx6ull只有一个led，num=0；次设备号minor=0
    {
        if (!CCM_CCGR1) //如果CCM_CCGR1为空指针，则映射
        {
            /*地址映射*/
            /*CCM_CCGR1[CG15] 0x20C406C*/
            CCM_CCGR1 = ioremap(0x20C406C, 4);
            /*GPIO5_3:IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER3:229_0000h base + 14h offset = 0x02290000+0x14*/
            IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER3 = ioremap(0x02290000 + 0x14, 4);
            /*GPIO5_GDIR :Base address + 4h offset= 020A_C000+4 =0x020AC004*/
            GPIO5_GDIR = ioremap(0x020AC000 + 0x4, 4);
            /*GPIO5:_DR:Base address + 0h offset=020A_C000+0=0x020AC000*/
            GPIO5_DR = ioremap(0x020AC000 + 0, 4);
        }
        /* GPIO5_IO03 */
        /* 使能GPIO5
         * set CCM to enable GPIO5
         * CCM_CCGR1[CG15] 0x20C406C
         * bit[31:30] = 0b11 (实际imx6ull默认该位为11，既GPIO5默认使能)
         */
        *CCM_CCGR1 |= (3 << 30);

        /* 设置GPIO5_IO03用于GPIO
         * set IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER3
         *      to configure GPIO5_IO03 as GPIO
         * IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER3  0x2290014
         * bit[3:0] = 0b0101 alt5
         */
        val = *IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER3;
        val &= (~(0xf)); // 0b0101含0，需要清除之前可能出现的1
        val |= (0x5);
        *IOMUXC_SNVS_SW_MUX_CTL_PAD_SNVS_TAMPER3 = val; //通过val中间量减少对寄存器的读写操作

        /* 设置GPIO5_IO03作为output引脚
         * set GPIO5_GDIR to configure GPIO5_IO03 as output
         * GPIO5_GDIR  0x020AC000 + 0x4
         * bit[3] = 0b1
         */
        *GPIO5_GDIR |= (1 << 3);
    }

    return 0;
}

static int board_led_ctl(int which, char status)
{
    printk("%s %s %d,led %d,%s\n", __FILE__, __FUNCTION__, __LINE__, which, status ? "on" : "off");
    if (which == 0)
    {
        if (status == 1)
        {
            /* d. 设置GPIO5_DR输出低电平
             * set GPIO5_DR to configure GPIO5_IO03 output 0
             * GPIO5_DR 0x020AC000 + 0
             * bit[3] = 0b0
             */
            *GPIO5_DR &= ~(1 << 3);
        }
        else if (status == 0)
        {
            /* e. 设置GPIO5_IO3输出高电平
             * set GPIO5_DR to configure GPIO5_IO03 output 1
             * GPIO5_DR 0x020AC000 + 0
             * bit[3] = 0b1
             */
            *GPIO5_DR |= (1 << 3);
        }
    }

    return 0;
}

static struct led_operations board_led_opr = {
    .num = 1,
    .init = board_led_init,
    .ctl = board_led_ctl,
};

struct led_operations *get_board_led_opr(void)
{
    return &board_led_opr;
}