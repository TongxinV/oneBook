/*
 * 静态映射操作LED    Author:TongxinV    E-mail:liyanbin0027@163.com
 */
#include <linux/module.h>		// module_init  module_exit
#include <linux/init.h>			// __init   __exit
#include <linux/fs.h>           // file_operations
#include <asm/uaccess.h>		//copy_from_user、copy_to_user
#include <mach/regs-gpio.h>		//虚拟地址映射
#include <mach/gpio-bank.h>		
#include <linux/string.h>

#define MYMAJOR		200
#define MYNAME		"testchar"

#define GPJ0CON		S5PV210_GPJ0CON   
#define GPJ0DAT		S5PV210_GPJ0DAT

#define rGPJ0CON	*((volatile unsigned int *)GPJ0CON)
#define rGPJ0DAT	*((volatile unsigned int *)GPJ0DAT)

int mymajor;
char kbuf[100];			// 内核空间的buf

static int test_chrdev_open(struct inode *inode, struct file *file)
{
	// 这个函数中真正应该放置的是打开这个设备时的硬件操作代码部分，比如初始化什么的
	printk(KERN_INFO "test_chrdev_open\n");

	rGPJ0CON = 0x11111111;
	rGPJ0DAT = ((0<<3) | (0<<4) | (0<<5));		// 亮
	return 0;
}

static int test_chrdev_release(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "test_chrdev_release\n");
	rGPJ0DAT = ((1<<3) | (1<<4) | (1<<5));     //灭	
    return 0;
}

ssize_t test_chrdev_read(struct file *file, char __user *ubuf, size_t count, loff_t *ppos)
{
	int ret = -1;
	printk(KERN_INFO "test_chrdev_read\n");
	
	ret = copy_to_user(ubuf, kbuf, count);
	if (ret){
		printk(KERN_ERR "copy_to_user fail\n");
		return -EINVAL;
	}
	printk(KERN_INFO "copy_to_user success..\n");
	
	return 0;
}





// 写函数的本质就是将应用层传递过来的数据先复制到内核中，然后将之以正确的方式写入硬件
static ssize_t test_chrdev_write(struct file *file, const char __user *ubuf,
	size_t count, loff_t *ppos)
{
	int ret = -1;
	
	printk(KERN_INFO "test_chrdev_write\n");

	// 使用该函数将应用层传过来的ubuf中的内容拷贝到驱动空间中的一个buf中
	//memcpy(kbuf, ubuf);		// 不行，因为2个不在一个地址空间中
	memset(kbuf, 0, sizeof(kbuf));
	ret = copy_from_user(kbuf, ubuf, count);
	if (ret){
		printk(KERN_ERR "copy_from_user fail\n");
		return -EINVAL;
	}
	printk(KERN_INFO "copy_from_user success..\n");
	
	if (kbuf[0] == '1'){
		rGPJ0DAT = ((0<<3) | (0<<4) | (0<<5));
	}else if (kbuf[0] == '0'){
		rGPJ0DAT = ((1<<3) | (1<<4) | (1<<5));
	}	
	
	return 0;
}

// 自定义一个file_operations结构体变量，并且去填充
static const struct file_operations test_fops = {
	.owner		= THIS_MODULE,				// 惯例，直接写即可
	
	.open		= test_chrdev_open,			// 将来应用open打开这个设备时实际调用的
	.release	= test_chrdev_release,			// 就是这个.open对应的函数
	.write 		= test_chrdev_write,
	.read		= test_chrdev_read,
};

// 模块安装函数
static int __init chrdev_init(void)
{	
	printk(KERN_INFO "chrdev_init helloworld init\n");

	// 在module_init宏调用的函数中去注册字符设备驱动
	// major传0进去表示要让内核帮我们自动分配一个合适的空白的没被使用的主设备号
	// 内核如果成功分配就会返回分配的主设备好；如果分配失败会返回负数
	mymajor = register_chrdev(0, MYNAME, &test_fops);
	if (mymajor < 0)
	{
		printk(KERN_ERR "register_chrdev fail\n");
		return -EINVAL;
	}
	printk(KERN_INFO "register_chrdev success... mymajor = %d.\n", mymajor);
	
	return 0;
}



// 模块下载函数
static void __exit chrdev_exit(void)
{
	printk(KERN_INFO "chrdev_exit helloworld exit\n");
	
	// 在module_exit宏调用的函数中去注销字符设备驱动
	unregister_chrdev(mymajor, MYNAME);
}

module_init(chrdev_init);
module_exit(chrdev_exit);

// MODULE_xxx这种宏作用是用来添加模块描述信息
MODULE_LICENSE("GPL");				// 描述模块的许可证
MODULE_AUTHOR("aston");				// 描述模块的作者
MODULE_DESCRIPTION("module test");	// 描述模块的介绍信息
MODULE_ALIAS("alias xxx");			// 描述模块的别名信息
