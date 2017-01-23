####简略View

```c
...
#include <linux/device.h>//class_create | device_create | device_destroy | class_destroy
...

#define TEST_COUNT 1 
static dev_t dev_id; 

static struct cdev  *pcdev;
static struct class *test_class;
......
static int __init chrdev_init(void)
{
    //第一步：分配主次设备号
	int retval = 0;
	retval = alloc_chrdev_region(&dev_id, 0, TEST_COUNT,MYNAME);
	......
	//第二步：注册字符设备驱动
	pcdev = cdev_alloc();
	pcdev->owner = THIS_MODULE;
	pcdev->ops = &test_fops;//关联file_operations结构体
	retval = cdev_add(pcdev, dev_id, TEST_COUNT);//cdev_add完成真正的注册
	......
    // 注册字符设备驱动完成后，添加设备类的操作，以让内核帮我们发信息
	// 给udev，让udev自动创建和删除设备文件
	test_class = class_create(THIS_MODULE, "aston_class");//最后1个参数字符串是类名
	if (IS_ERR(test_class))
		return -EINVAL;
	// 最后1个参数字符串，就是我们将来要在/dev目录下创建的设备文件的名字
	// 所以我们这里要的文件名是/dev/test1111，在/sys/class/aston_class下也有
	device_create(test_class, NULL, dev_id, NULL, "test1111");
    ......
}
static void __exit chrdev_exit(void)
{
	device_destroy(test_class, dev_id);
	class_destroy(test_class);
	cdev_del(pcdev);								//第一步真正注销字符设备驱动
	unregister_chrdev_region(dev_id, TEST_COUNT);	//第二步注销申请的主次设备号
}

...

```
