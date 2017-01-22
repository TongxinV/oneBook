/****** 该次改动：系统分配设备号 | 倒影式错误处理 | cdev_alloc ******/
#include <linux/module.h>		// module_init  module_exit
#include <linux/init.h>		// __init   __exit
#include <linux/fs.h>			// file_operations   
#include <linux/cdev.h>		//cdev_alloc、cdev_init、cdev_add、cdev_del...
#include <asm/uaccess.h>		//copy_from_user、copy_to_user
#include <linux/string.h>

#include <mach/regs-gpio.h>	//虚拟地址映射
#include <mach/gpio-bank.h>	

#include <linux/io.h>			//动态映射
#include <linux/ioport.h>

#define rGPJ0CON	*((volatile unsigned int *)S5PV210_GPJ0CON)
#define rGPJ0DAT	*((volatile unsigned int *)S5PV210_GPJ0DAT)

#define GPJ0CON_PA	0xe0200240
#define GPJ0DAT_PA 	0xe0200244

#define MYMAJOR  200
#define TEST_DEV  MKDEV(MYMAJOR,0)
#define TEST_MAX  1
#define MYNAME    "test_chrdev"

#define TEST_COUNT 1 //(TEST_MAX意义一样，但我还是想在定义一个，好区别吧)
static dev_t dev_id; //(TEST_DEV意义一样，但我还是想在定义一个，好区别吧)

char kbuf[100];			// 内核空间的buf

//static struct cdev test_cdev;
static struct cdev *pcdev;

static int test_chrdev_open(struct inode *inode, struct file *file)
{
......
static int test_chrdev_release(struct inode *inode, struct file *file)
{
......
// 写函数的本质就是将应用层传递过来的数据先复制到内核中，然后将之以正确的方式写入硬件
static ssize_t test_chrdev_write(struct file *file, const char __user *ubuf,
	size_t count, loff_t *ppos)
{
	......
ssize_t test_chrdev_read(struct file *file, char __user *ubuf, size_t count, loff_t *ppos)
{
	......
//自定义一个file_operations结构体变量，并填充
static const struct file_operations test_fops = {
	.owner		= THIS_MODULE, 
	.open		= test_chrdev_open,	 
	.release		= test_chrdev_release,   
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
	retval = register_chrdev_region(TEST_DEV, TEST_MAX,MYNAME);
	if (retval){
		printk(KERN_ERR "Unable to register minors for %s.\n",MYNAME);
		return -EINVAL;
	}
	printk(KERN_INFO "register_chrdev_region success...\n");
	
	//第二步：注册字符设备驱动
	pcdev = cdev_alloc();
	//cdev_init(pcdev, &test_fops);	//关联file_operations结构体
	pcdev->owner = THIS_MODULE;
	pcdev->ops = &test_fops;
	retval = cdev_add(pcdev, TEST_DEV, TEST_MAX);//cdev_add完成真正的注册
	if (retval){
		printk(KERN_ERR "Unable to get test_chrdev major %d\n",MYMAJOR);
		return -EINVAL;
	}
	printk(KERN_INFO "cdev_add success...\n");
#endif

	//第一步：分配主次设备号
	//int retval = 0;
	retval = alloc_chrdev_region(&dev_id, 0, TEST_COUNT,MYNAME);
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
	pcdev->ops = &test_fops;
	retval = cdev_add(pcdev, dev_id, TEST_COUNT);//cdev_add完成真正的注册
	if (retval){
		printk(KERN_ERR "Unable to get test_chrdev major %d\n",MYMAJOR);
		goto err_add;
	}
	printk(KERN_INFO "cdev_add success...\n");
	
	// 使用动态映射的方式来操作寄存器
	if (!request_mem_region(GPJ0CON_PA, 4, "GPJ0CON"))
		goto err_men;
	if (!request_mem_region(GPJ0DAT_PA, 4, "GPJ0CON"))
		goto err_men;

	return 0;
err_men:
	cdev_del(pcdev);
err_add:
	unregister_chrdev_region(dev_id, TEST_COUNT);
err_reg:
	return -EINVAL;   
}
// 模块卸载函数
static void __exit chrdev_exit(void)
{
	printk(KERN_INFO "chrdev_exit\n");
	//在module_exit宏调用的函数中去注销字符设备驱动

	//第一步真正注销字符设备驱动 | 用cdev_del
	cdev_del(pcdev);
	//第二步注销申请的主次设备号	
	unregister_chrdev_region(dev_id, TEST_COUNT);
}

module_init(chrdev_init);
module_exit(chrdev_exit);

// MODULE_xxx这种宏作用是用来添加模块描述信息
MODULE_LICENSE("GPL");				// 描述模块的许可证










