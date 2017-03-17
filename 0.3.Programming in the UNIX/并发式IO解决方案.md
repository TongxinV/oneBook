并发式IO解决方案
------

[TOC]

* [非阻塞式IO(有本质的缺陷)](#非阻塞式)
* [IO多路复用(select/poll)](#IO多路复用)
* [异步IO(signal/sigaction)](#异步)

### 非阻塞式IO

> 有本质缺陷，简单介绍如何利用fcntl设置flag，可略过

程序示例：[非阻塞式IO](https://github.com/TongxinV/oneBook/blob/master/0.3.Programming%20in%20the%20UNIX/assets/001/%E9%9D%9E%E9%98%BB%E5%A1%9E%E5%BC%8F%E5%AE%9E%E7%8E%B0.png)


### IO多路复用(select/poll)

> 外部阻塞式(select\poll函数)，内部非阻塞式自动轮询多路阻塞式IO

**select**函数介绍：

![select函数][2-1]

![select示例][2-2]


**poll**函数介绍：

![poll函数][2-3]

![poll示例][2-4]



### 异步IO(signal/sigaction)


1. 何为异步IO

(1)可以认为：异步IO就是操作系统用软件实现的一套中断响应系统<br>
(2)异步IO的工作方法是：当前进程注册一个异步IO事件（使用signal注册一个信号SIGIO的处理函数），然后当前进程可以正常处理自己的事情，当异步事件发生后当前进程会收到一个SIGIO信号从而执行与SIGIO信号相绑定的处理函数去处理这个异步事件


2. 涉及的函数：

(1)fcntl（F_GETFL、F_SETFL、**O_ASYNC**、**F_SETOWN**）

    O_ASYNC： 指示当前这个文件描述符fd可以接受异步通知
    F_SETOWN：设置接收<在文件描述符fd上产生的SIGIO 或 SIGURG信号>的进程或进程组

(2)signal或者sigaction（注册当前进程的SIGIO信号捕获函数）	

    #include <signal.h>
    typedef void (*sighandler_t)(int);
    sighandler_t signal(int signum, sighandler_t handler);
    
    关于函数返回值:signal的返回值在出错时为SIG_ERR，绑定成功时返回旧的捕获函数
    以下文件位于/usr/include/i386-linux-gnu/bits/signum.h
    #define SIG_ERR ((__sighandler_t) -1)           /* Error return.  */
    #define SIG_DFL ((__sighandler_t) 0)            /* Default action.  */
    #define SIG_IGN ((__sighandler_t) 1)            /* Ignore signal.  */

3. 示例代码

![异步IO][3-1]



[2-1]:https://raw.githubusercontent.com/TongxinV/oneBook/master/0.3.Programming%20in%20the%20UNIX/assets/001/select%E5%87%BD%E6%95%B0.png
[2-2]:https://raw.githubusercontent.com/TongxinV/oneBook/master/0.3.Programming%20in%20the%20UNIX/assets/001/select%E7%A4%BA%E4%BE%8B.png
[2-3]:https://raw.githubusercontent.com/TongxinV/oneBook/master/0.3.Programming%20in%20the%20UNIX/assets/001/poll%E5%87%BD%E6%95%B0.png
[2-4]:https://raw.githubusercontent.com/TongxinV/oneBook/master/0.3.Programming%20in%20the%20UNIX/assets/001/poll%E7%A4%BA%E4%BE%8B.png
[3-1]:https://raw.githubusercontent.com/TongxinV/oneBook/master/0.3.Programming%20in%20the%20UNIX/assets/001/%E5%BC%82%E6%AD%A5IO%E7%A4%BA%E4%BE%8B.png









