#ubuntu的内核源码树，如果要编译在ubuntu中安装的模块就打开这2个
#KERN_VER = $(shell uname -r)
#KERN_DIR = /lib/modules/$(KERN_VER)/build	

		
# 开发板的linux内核的源码树目录
KERN_DIR = /root/driver/kernel

obj-m	+= module_test.o

all:
	make -C $(KERN_DIR) M=`pwd` modules 
	arm-linux-gcc app.c -o app

cp:
	cp *.ko /root/porting_x210/rootfs/rootfs/driver_test
	cp app /root/porting_x210/rootfs/rootfs/driver_test
	

.PHONY: clean	
clean:
	make -C $(KERN_DIR) M=`pwd` modules clean
	rm -rf app

