#include <linux/module.h>		//module_init  module_exit
#include <linux/init.h>			//__init   __exit
#include <linux/fs.h>			//file_operations   
#include <linux/cdev.h>			//cdev_alloc、cdev_init、cdev_add、cdev_del...
#include <asm/uaccess.h>		//copy_from_user、copy_to_user
#include <linux/string.h>
#include <linux/device.h> 		//udev
#include <mach/regs-gpio.h>		//静态映射需要的虚拟地址映射表
#include <mach/gpio-bank.h>	
#include <linux/ioport.h>
#include <linux/io.h>			


#if 1
#define MYNAME    "test_chrdev"      //"test_chrdev"，设备驱动在lsmod会看到的名字，或cat /proc/devices会看到的名字
                                     //注意和/dev/下的文件来源区分开来（驱动中的类操作或mknod命令来由udev生成的文件）
                                     
/*使用register_chrdev_region注册设备号要用到参数*/
#define TEST_MAX   1
#define MYMAJOR    200
#define TEST_DEV   MKDEV(MYMAJOR,0)  //不能#define TEST_DEV 200，设备号是有类型的(dev_t)
                                     //而且dev_t dev_id = 200;这样赋值也是不合适的（没测试过是否会出错），
                                     //内核驱动源代码使用register_chrdev_region时普遍做法是像这边这样处理

/*使用alloc_chrdev_region   分配设备号要用到参数*/
#define TEST_COUNT 1 
static  dev_t dev_id; 
#endif

static struct cdev  *pcdev;          //使用新接口注册字符设备且使用cdev_alloc时要用到变量，用于保存申请到的cdev结构体大小的内存的地址
static struct class *test_class;     //设备类操作



/*使用内核提供的操作接口使具有可移植性，不再用下面裸机时的方式操作寄存器*/
//#define rGPJ0CON	*((volatile unsigned int *)S5PV210_GPJ0CON)
//#define rGPJ0DAT	*((volatile unsigned int *)S5PV210_GPJ0DAT)

#if 1 
/*使用动态映射需要的寄存器物理地址*/
#define GPJ0CON_PA	0xe0200240
#define GPJ0DAT_PA 	0xe0200244

/*使用动态映射需要的用来存放ioremap的返回值，即存放寄存器映射到虚拟地址的地址*/
/*单个分开映射*/
unsigned int *pGPJ0CON;
unsigned int *pGPJ0DAT;
/*多个同时映射，需要一个基地址*/
static void __iomem *baseaddr;

#define S5P_GPJ0REG(x)		(x)
#define S5P_GPJ0CON			S5P_GPJ0REG(0)
#define S5P_GPJ0DAT			S5P_GPJ0REG(4)

#endif 


char kbuf[100];			// 内核空间的buf		


static int test_chrdev_open(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "test_chrdev_open\n");
	//rGPJ0CON = 0x11111111;
	//rGPJ0DAT = ((0<<3) | (0<<4) | (0<<5));		// 亮
    writel(0x11111111, baseaddr + S5P_GPJ0CON);
	writel(((0<<3) | (0<<4) | (0<<5)), baseaddr + S5P_GPJ0DAT);
    
	return 0;
}

static int test_chrdev_release(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "test_chrdev_release\n");
	
	//rGPJ0DAT = ((1<<3) | (1<<4) | (1<<5));		//灭	
	writel(((1<<3) | (1<<4) | (1<<5)), baseaddr + S5P_GPJ0DAT);
    
	return 0;
}
// 写函数的本质就是将应用层传递过来的数据先复制到内核中，然后将之以正确的方式写入硬件
static ssize_t test_chrdev_write(struct file *file, const char __user *ubuf,
	size_t count, loff_t *ppos)
{
	int retval = -1;
	printk(KERN_INFO "test_chrdev_write\n");
	// 使用该函数将应用层传过来的ubuf中的内容拷贝到驱动空间中的一个buf中
	memset(kbuf, 0, sizeof(kbuf));
	retval = copy_from_user(kbuf, ubuf, count);
	if (retval){
		printk(KERN_ERR "copy_from_user fail\n");
		return -EINVAL;
	}
	printk(KERN_INFO "copy_from_user success..\n");
	
	if (kbuf[0] == '1'){
		//rGPJ0DAT = ((0<<3) | (0<<4) | (0<<5));
        writel(((0<<3) | (0<<4) | (0<<5)), baseaddr + S5P_GPJ0DAT);
	}else if (kbuf[0] == '0'){
		//rGPJ0DAT = ((1<<3) | (1<<4) | (1<<5));
        writel(((1<<3) | (1<<4) | (1<<5)), baseaddr + S5P_GPJ0DAT);
	}	
	
	return 0;
}

ssize_t test_chrdev_read(struct file *file, char __user *ubuf, size_t count, loff_t *ppos)
{
	int retval = -1;
	printk(KERN_INFO "test_chrdev_read\n");
	
	retval = copy_to_user(ubuf, kbuf, count);
	if (retval){
		printk(KERN_ERR "copy_to_user fail\n");
		return -EINVAL;
	}
	printk(KERN_INFO "copy_to_user success..\n");
	
	return 0;
}

//自定义一个file_operations结构体变量，并填充
static const struct file_operations test_fops = {
	.owner		= THIS_MODULE, 
	.open		= test_chrdev_open,	 
	.release	= test_chrdev_release,   
	.write 		= test_chrdev_write,
	.read		= test_chrdev_read,
};

// 模块安装函数
static int __init chrdev_init(void)
{
	int retval = 0;
	printk(KERN_INFO "chrdev_init\n");
#if 0
    //第一步：注册主次设备号
    retval = register_chrdev_region(TEST_DEV, TEST_MAX, MYNAME);
    if (retval) {
	    printk(KERN_ERR "Unable to register minors for %s.\n",MYNAME);
        goto err_reg;
    }
    printk(KERN_INFO "register_chrdev_region success...\n");
#endif 	
	//第一步：分配主次设备号
	retval = alloc_chrdev_region(&dev_id, 0, TEST_COUNT,MYNAME);//不一定要从0开始
	if(retval < 0){
		printk(KERN_ERR "alloc_chrdev_region fail for %s\n",MYNAME);
		goto err_reg;
	}
	printk(KERN_INFO "alloc_chrdev_region success for %s\n",MYNAME);
	printk(KERN_INFO "major = %d. minor = %d.\n",MAJOR(dev_id), MINOR(dev_id));

	//第二步：注册字符设备驱动
	pcdev = cdev_alloc();
	//cdev_init(pcdev, &test_fops);	//关联file_operations结构体
	pcdev->owner = THIS_MODULE;
	pcdev->ops   = &test_fops;
	retval = cdev_add(pcdev, dev_id, TEST_COUNT);//cdev_add完成真正的注册
	if (retval){
		printk(KERN_ERR "Unable to get test_chrdev major %d\n",MYMAJOR);
		goto err_add;
	}
	printk(KERN_INFO "cdev_add success...\n");
	
    //添加设备类操作
	test_class = class_create(THIS_MODULE, "aston_class");
	if (IS_ERR(test_class))
		goto err_class;
	device_create(test_class, NULL, dev_id, NULL, "test1111");//"test1111"，设备在/dev/下的名字
	
	
	//使用动态映射的方式来操作寄存器
#if 0 
	if (!request_mem_region(GPJ0CON_PA, 4, "GPJ0CON"))
		goto err_men;
	if (!request_mem_region(GPJ0DAT_PA, 4, "GPJ0CON"))
		goto err_men;
	
	pGPJ0CON = ioremap(GPJ0CON_PA, 4);
	pGPJ0DAT = ioremap(GPJ0DAT_PA, 4);
	
	*pGPJ0CON = 0x11111111;
	*pGPJ0DAT = ((0<<3) | (0<<4) | (0<<5));		// 亮
#endif 
	//测试1：用静态映射的虚拟地址来操作，测试成功
    //writel(0x11111111, GPJ0CON);
    //writel(((0<<3) | (0<<4) | (0<<5)), GPJ0DAT);
	
	//测试2：用1次ioremap映射多个寄存器得到虚拟地址，测试成功
	if (!request_mem_region(GPJ0CON_PA, 8, "GPJ0BASE"))
		goto err_men;
	baseaddr = ioremap(GPJ0CON_PA, 8);
	
	writel(0x11111111, baseaddr + S5P_GPJ0CON);
	writel(((0<<3) | (0<<4) | (0<<5)), baseaddr + S5P_GPJ0DAT);

	return 0;

/*层次关系理清楚*/    
err_men:
    device_destroy(test_class, dev_id);
    class_destroy(test_class);
err_class:
	cdev_del(pcdev);
err_add:
	unregister_chrdev_region(dev_id, TEST_COUNT);
err_reg:
	return -EINVAL;   
}

//模块卸载函数
static void __exit chrdev_exit(void)
{
	printk(KERN_INFO "chrdev_exit\n");
	
	//第1步解除映射
	iounmap(pGPJ0CON);
	iounmap(pGPJ0DAT);
    //第2步释放资源
	release_mem_region(GPJ0CON_PA, 4);
	release_mem_region(GPJ0DAT_PA, 4);
	
    //第1步删除用户空间下的设备
	device_destroy(test_class, dev_id);
    //第2步删除用户空间下的类
	class_destroy(test_class);
	
	//第1步真正注销字符设备驱动
	cdev_del(pcdev);
	//第2步注销申请的主次设备号	
	unregister_chrdev_region(dev_id, TEST_COUNT);
}


module_init(chrdev_init);
module_exit(chrdev_exit);

// MODULE_xxx这种宏作用是用来添加模块描述信息
MODULE_LICENSE("GPL");				// 描述模块的许可证
MODULE_AUTHOR("aston");				// 描述模块的作者
MODULE_DESCRIPTION("module test");	// 描述模块的介绍信息
MODULE_ALIAS("alias xxx");			// 描述模块的别名信息








