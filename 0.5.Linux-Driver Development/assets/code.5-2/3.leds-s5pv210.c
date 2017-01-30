#include <linux/module.h>		// module_init  module_exit
#include <linux/init.h>		// __init   __exit
#include <linux/fs.h>			// file_operations
#include <linux/cdev.h>		//cdev_alloc、cdev_init、cdev_add、cdev_del...
#include <asm/uaccess.h>			//copy_from_user、copy_to_user
#include <linux/string.h>
#include <mach/regs-gpio.h>		//虚拟地址映射
#include <mach/gpio-bank.h>
#include <linux/io.h>				//动态映射
#include <linux/ioport.h>
#include <linux/leds.h>         //brightness_set等
#include <mach/gpio.h>		  //S5PV210_GPJ0(_nr)\#include <asm-generic/gpio.h>等

#define GPJ0CON		S5PV210_GPJ0CON
#define GPJ0DAT		S5PV210_GPJ0DAT

#define GPIO_LED1	S5PV210_GPJ0(3)  //unsigned 类型？

static struct led_classdev mydev;		// 定义结构体变量

// 这个函数就是要去完成具体的硬件读写任务的
static void s5pv210_led_set(struct led_classdev *led_cdev,
			    enum led_brightness value)	
{
	printk(KERN_INFO "s5pv210_led_set\n");
	
	// 在这里根据用户设置的值来操作硬件
	// 用户设置的值就是value
	if (value == LED_OFF){
		// 用户给了个0，希望LED灭
		//writel(0x11111111, GPJ0CON);
		//writel(((1<<3) | (1<<4) | (1<<5)), GPJ0DAT);
		gpio_set_value(GPIO_LED1, 1);//硬件决定了这边写1 灭，不过正常要宏定义
}else{
		// 用户给的是非0，希望LED亮
		//writel(0x11111111, GPJ0CON);
		//writel(((0<<3) | (0<<4) | (0<<5)), GPJ0DAT);
gpio_set_value(GPIO_LED1, 0);
	}
}

static int __init s5pv210_led_init(void)
{
	// 用户insmod安装驱动模块时会调用该函数
	// 该函数的主要任务就是去使用led驱动框架提供的设备注册函数来注册一个设备
	int ret = -1;
	
// 在这里去申请驱动用到的各种资源，当前驱动中就是GPIO资源
	if (gpio_request(GPIO_LED1, "led1_gpj0.3")) {
		printk(KERN_ERR "gpio_request failed\n");
	} else {
		// 申请的同时做一些相应的初始化
// 设置为输出模式，并且默认输出1让LED灯灭
		gpio_direction_output(GPIO_LED1, 1);
	}
	
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

gpio_free(GPIO_LED1);
}

module_init(s5pv210_led_init);
module_exit(s5pv210_led_exit);

// MODULE_xxx这种宏作用是用来添加模块描述信息
MODULE_LICENSE("GPL");							// 描述模块的许可证
