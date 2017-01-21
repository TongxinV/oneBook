> 这里我们还未利用udev来创建设备文件和删除设备文件，所以需要

    insmod xxx（模块安装） -- > mknod /dev/test c 200 0 （cat /proc/devices 查看驱动设备号作为mknod的参数，这里为200）
    ls  /dev/xxx -l 查看关联好的设备文件 
