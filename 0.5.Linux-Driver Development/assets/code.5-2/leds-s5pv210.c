#include <linux/module.h>		// module_init  module_exit
#include <linux/init.h>			// __init   __exit
#include <linux/fs.h>
#include <mach/regs-gpio.h>
#include <mach/gpio-bank.h>
#include <linux/io.h>
#include <linux/ioport.h>
#include <linux/leds.h>         //brightness_set等，这个头文件是驱动框架和我们写的驱动的媒介

#define GPJ0CON		S5PV210_GPJ0CON
#define GPJ0DAT		S5PV210_GPJ0DAT

static struct led_classdev mydev;		// 定义结构体变量

// 这个函数就是要去完成具体的硬件读写任务的
static void s5pv210_led_set(struct led_classdev *led_cdev,
			    enum led_brightness value)	
{
	printk(KERN_INFO "s5pv210_led_set\n");
	
	if (value == LED_OFF){
		// 用户给了个0，希望LED灭
		writel(0x11111111, GPJ0CON);
		writel(((1<<3) | (1<<4) | (1<<5)), GPJ0DAT);
	}else{
		// 用户给的是非0，希望LED亮
		writel(0x11111111, GPJ0CON);
		writel(((0<<3) | (0<<4) | (0<<5)), GPJ0DAT);
	}
}

static int __init s5pv210_led_init(void)
{
	// 用户insmod安装驱动模块时会调用该函数
	// 该函数的主要任务就是去使用led驱动框架提供的设备注册函数来注册一个设备
	int ret = -1;
	
	mydev.name = "myled";
	mydev.brightness = 255;	
	mydev.brightness_set = s5pv210_led_set;
	
	ret = led_classdev_register(NULL, &mydev);
	if (ret < 0) {
		printk(KERN_ERR "led_classdev_register failed\n");
		return ret;
	}
	
	return 0;
}

static void __exit s5pv210_led_exit(void)
{
	led_classdev_unregister(&mydev);
}

module_init(s5pv210_led_init);
module_exit(s5pv210_led_exit);

// MODULE_xxx这种宏作用是用来添加模块描述信息
MODULE_LICENSE("GPL");// 描述模块的许可证
