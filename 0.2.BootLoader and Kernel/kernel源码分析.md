
## Kernel

> 获取合适的源码包，解压，配置。编译得到zImage

[TOC]

### kernel根目录下各个文件夹及文件的含义
......

### kernel的配置和编译过程
......
### 源代码分析

> 宏观的内核启动过程，从内核的第一句代码开始分析，到内核启动起来，然后到内核启动后去做什么

整体结构

    project
        ├── 执行解压代码，将内核解压到链接地址
        ├── 跳转到内核入口    head.S文件中的ENTRY(stext)
        ├── 汇编阶段：检验启动合法性，建立段式页表并开启MMU以方便使用内存。跳入C阶段
        ├── C阶段（start_kernel）                                                      
              ├── 硬件初始化等
              ├── setup_arch:通过机器码找到对应的machine_desc结构体变量.解析bootargs
              │      ├── ...
              │      ├── 建立MMU所能识别的页表映射关系
              │      ├── 建立gpiolib
              │      └── ...
              └── reset_init
                     ├── 调用kernel_thread 启动init进程kernel_init
                     │                                  ├── ...
                     │                                  ├── do_basic_setup
                     │                                  │        ├── ...
                     │                                  │        ├── driver_init()-> platform_bus_init()
                     │                                  │        ├── ...
                     │                                  │        └── do_initcalls()
                     │                                  ├── ...
                     │                                  ├── ...
                     ├── 调用kernel_thread 启动守护进程kthreadd
                     ├── 开启内核调度系统
                     └── 调用空闲进程（进程0， 属于内核进程）

init进程：一开始在内核态下执行，完成'挂载根文件系统之后'，执行用户空间下的init程序，完成从内核态到用户态的转变

另外：init进程还创建了三个文件描述符作为标准输入、标准输出和标准错误

**详细代码**

```
日后更新
```

      



