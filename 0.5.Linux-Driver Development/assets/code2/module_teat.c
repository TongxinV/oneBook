#include <linux/module.h>	    // module_init  module_exit
#include <linux/init.h>		    // __init   __exit
#include <linux/fs.h>		    // file_operations   
#include <linux/cdev.h>		    //cdev_alloc、cdev_init、cdev_add、cdev_del...



#define MYNMAJOR  200
#define TEST_DEV MKDEV(MYMAJOR,0)
#define TEST_MAX 1
#define MYNAME    "test_chrdev"

static struct cdev test_cdev;

//file_operations结构体变量中填充的函数指针的实体，函数的格式要遵守
static int test_chrdev_open(struct inode *inode, struct file *file)
{
    ......
static int test_chrdev_release(struct inode *inode, struct file *file)
{
    ......

//自定义一个file_operations结构体变量，并填充
static const struct file_operations test_fops = {
	.owner	= THIS_MODULE,  //惯例，所有的驱动都有这一个，这也是这结构体中唯一一个不是函数指针的元素

	.open   = test_chrdev_open,	   //将来应用open打开这个这个设备时实际调用的函数

	.release= test_chrdev_release,   //对应close，为什么不叫close呢？详见后面release和close的区别的讲解
};

/*********************************************************************************/

// 模块安装函数
static int __init chrdev_init(void)
{	
	printk(KERN_INFO "chrdev_init\n");

	// 在module_init宏调用的函数中去注册字符设备驱动
#if 0
	// major传0进去表示要让内核帮我们自动分配一个合适的空白的没被使用的主设备号
	// 内核如果成功分配就会返回分配的主设备好；如果分配失败会返回负数
	mymajor = register_chrdev(0, MYNAME, &test_fops);
	if (mymajor < 0){
		printk(KERN_ERR "register_chrdev fail\n");
		return -EINVAL;
	}
	printk(KERN_INFO "register_chrdev success... mymajor = %d.\n", mymajor);
#endif	

    //使用新的cdev接口来注册字符设备驱动
    //新的接口注册字符设备驱动需要两步
    //第一步：注册/分配主次设备号 | 用register_chrdev_region
  
    int retval;
    retval = register_chrdev_region(TEST_DEV, TEST_MAX, MYNAME);
    if (retval) {
	    printk(KERN_ERR "Unable to register minors for %s.\n",MYNAME);
	    //goto out;
        return -EINVAL;
    }
    printk(KERN_INFO "register_chrdev_region success...\n");

    //第二步：注册字符设备驱动
    cdev_init(&test_cdev, &test_fops);	//关联file_operations结构体

    retval = cdev_add(&test_cdev, TEST_DEV, TEST_MAX);
    //cdev_add完成真正的注册
    if (retval) {
	    printk(KERN_ERR "Unable to get test_chrdev major %d\n",MYMAJOR);
	    //goto error_cdev;
        return -EINVAL;
    }
    printk(KERN_INFO "cdev_add success...\n");

	return 0;
}

// 模块卸载函数
static void __exit chrdev_exit(void)
{
	printk(KERN_INFO "chrdev_exit\n");
    //在module_exit宏调用的函数中去注销字符设备驱动
#if 0
    //实验1，在我们这里不写东西的时候，rmmod 后lsmod 查看确实是没了，但是cat /proc/device	  发现设备号还是被占着
    unregister_chrdev(MYNMAJOR, MYNAME);  //参数就两个
    //检测返回值
    ......
#endif

    //使用新的接口来注销字符设备驱动
    //新的接口注销字符设备驱动也需要两步
    //第一步真正注销字符设备驱动 | 用cdev_del
    cdev_del(&test_cdev);
    //第二步注销申请的主次设备号	
    unregister_chrdev_region(TEST_DEV, TEST_MAX);

    return 0;
}
/*********************************************************************************/

module_init(chrdev_init);         //insmod 时调用
module_exit(chrdev_exit);		    //rmmod  时调用

// MODULE_xxx这种宏作用是用来添加模块描述信息
MODULE_LICENSE("GPL");		    // 描述模块的许可证





















