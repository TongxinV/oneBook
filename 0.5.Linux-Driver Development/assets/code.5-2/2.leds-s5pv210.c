#include <linux/leds.h>  
......
static struct led_classdev mydev1;			// 定义结构体变量
static struct led_classdev mydev2;			// 定义结构体变量
static struct led_classdev mydev3;			// 定义结构体变量

// 这个函数就是要去完成具体的硬件读写任务的
static void s5pv210_led1_set(struct led_classdev *led_cdev,
			    enum led_brightness value)
{
......
static void s5pv210_led2_set(struct led_classdev *led_cdev,
			    enum led_brightness value)
{
	......
static void s5pv210_led3_set(struct led_classdev *led_cdev,
			    enum led_brightness value)
{
	printk(KERN_INFO "s5pv210_led3_set\n");
	
	writel(0x11111111, GPJ0CON);
	
	// 在这里根据用户设置的值来操作硬件
	// 用户设置的值就是value
	if (value == LED_OFF){
		// 用户给了个0，希望LED灭
		//writel(0x11111111, GPJ0CON);
		// 读改写三部曲
		writel((readl(GPJ0DAT) | (1<<5)), GPJ0DAT);
	}else{
		// 用户给的是非0，希望LED亮
		//writel(0x11111111, GPJ0CON);
		writel((readl(GPJ0DAT) & ~(1<<5)), GPJ0DAT);
	}
}
static int __init s5pv210_led_init(void)
{
	int ret = -1;
	
	// led1
	mydev1.name = "led1";
	mydev1.brightness = 255;	
	mydev1.brightness_set = s5pv210_led1_set;
	
	ret = led_classdev_register(NULL, &mydev1);
	......
	// led2
	mydev2.name = "led2";
	mydev2.brightness = 255;	
	mydev2.brightness_set = s5pv210_led2_set;
	
	ret = led_classdev_register(NULL, &mydev2);
	......
	// led3
	......
	return 0;
}
static void __exit s5pv210_led_exit(void)
{
	led_classdev_unregister(&mydev1);
	led_classdev_unregister(&mydev2);
	led_classdev_unregister(&mydev3);
}

module_init(s5pv210_led_init);
module_exit(s5pv210_led_exit);

// MODULE_xxx这种宏作用是用来添加模块描述信息
MODULE_LICENSE("GPL");							// 描述模块的许可证
