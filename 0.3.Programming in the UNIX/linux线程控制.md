linux线程控制
---

[TOC]


* linux线程引入
* linux线程控制
* linux线程同步

### linux线程引入

1.使用进程技术的优势

```
(1)CPU时分复用，单核心CPU可以实现宏观上的并行<br>
(2)实现多任务系统需求（多任务的需求是客观的）
```
2.使用进程技术的劣势

```
(1)进程间切换开销大<br>
(2)进程间通信麻烦而且效率低
```
3.解决方案就是线程技术

```
(1)线程技术保留了进程技术实现多任务的特性<br>
(2)线程的改进就是在线程间切换和线程间通信上提升了效率<br>
(3)多线程在多核心CPU上面更有优势<br>
```
4.使用线程技术同时读取键盘和鼠标

**pthread_create**:

![](https://raw.githubusercontent.com/TongxinV/oneBook/master/0.3.Programming%20in%20the%20UNIX/assets/002/pthread_create.png)

简单示例代码：[pthread_create.c](https://github.com/TongxinV/oneBook/blob/master/0.3.Programming%20in%20the%20UNIX/assets/002/pthread_create.c)


### linux线程控制

#### 线程创建与回收

(1)pthread_create   主线程用来创造子线程的
(2)pthread_join		主线程用来等待（阻塞）回收子线程

    子进程可能会去申请资源，那就意味着线程将来结束的时候主进程	要回收资源
    
(3)pthread_detach	主线程用来分离子线程

    分离后主线程不必再去回收子线程，子进程自己回收自己



#### 线程取消机制

(1)pthread_cancel   一般都是主线程调用该函数去取消子线程（让它赶紧终止）

主线程要能够让子线程终止需要有相应的权限，所以需要下面两个函数：

    a.pthread_setcancelstate	子线程设置自己是否允许被取消
    b.pthread_setcanceltype     取消子进程时的类型
    有立即终止和等待能够终止的时候才终止（default）(比如要终止子进程的时候子进程手里握着锁这种情况就不能立马终止)
    注：这个函数要在pthread_setcancelstate设置子进程允许被取消时才有意义


#### 线程函数退出相关

(1)pthread_exit与return退出

pthread_exit子进程自己终止函数，并返回一值给主线程的pthread_join函数

    注：子线程不能调用exit返回，因为子线程也属于整个进程的一个函数，除了一些特殊场合

(2)pthread_cleanup_push/pthread_cleanup_pop

这两个函数与posix线程清理有关，push和pop的出现一般和栈有关（先进后出）

首先需要明白一点，这跟线程同步有一点关。线程同步有时需要用到一些锁，这些锁非常类似于之前讲过的信号量。比如当前信号量cnt本来是0，主线程对这个子线程进行操作的时候，要怎么样做呢？是这样子的，先要使cnt这个值赋值加1，然后去进行子线程的操作，完了之后要减1。所以子线程在做这个操作的时候要做一个操作，先要判断cnt是否等于0，才能去做这些操作。这时候这个cnt就相当于是一个锁，cnt等于0则说明这个锁是打开的，打开的就可以使用，使用时就把cnt加一，这样就把锁给锁上了，锁上了之后别人过来打开的时候别人就打不开了

进程之间要有这样的一种锁机制。但是这样的一种锁机制有这样的一种问题，假设一个线程函数执行了cnt++，正在执行的子进程操作的时候，有可能被主进程取消。那如果子进程在cnt++了之后还没来得及减减呢？子进程拿着锁死了，那其他人就用不了，也就是死锁

所以得想办法让子进程死了之后这个锁不会继续锁上。解决发案就是pthread_cleanup_push和pthread_cleanup_pop
```
#include <pthread.h>

void pthread_cleanup_push(void (*routine)(void *), void *arg);//pthread_cleanup_push就是把清理函数压栈保存起来
void pthread_cleanup_pop(int execute);
```

两个函数在子进程中使用：

![](https://raw.githubusercontent.com/TongxinV/oneBook/master/0.3.Programming%20in%20the%20UNIX/assets/002/%E7%BA%BF%E7%A8%8B%E6%B8%85%E7%90%86%E6%9C%BA%E5%88%B6.png)


#### 获取线程id

> pthread_self

```
...
```

### 线程同步

> * 信号量  (sem_t)
> * 互斥锁  (pthread_mutex_t)
> * 条件变量(pthread_cond_t)

以下只是初学时的一些记录，建议有一些基础可以直接阅读这一篇博客[《Linux 线程同步的三种方法》](http://blog.csdn.net/zsf8701/article/details/7844316)


#### 为什么需要线程同步

> 任务：用户从终端输入任意字符然后统计个数显示，输入end则结束

普通程序：

![普通程序](https://raw.githubusercontent.com/TongxinV/oneBook/master/0.3.Programming%20in%20the%20UNIX/assets/002/%E6%99%AE%E9%80%9A%E7%A8%8B%E5%BA%8F.png)


线程程序：(主线程获取用户输入并判断是否退出，子线程计数)

![线程程序](https://raw.githubusercontent.com/TongxinV/oneBook/master/0.3.Programming%20in%20the%20UNIX/assets/002/%E7%BA%BF%E7%A8%8B%E7%A8%8B%E5%BA%8F.png)

以上程序有明显的bug：

    问题一：子线程程序运行立马执行打印：本次输入了0个字符，然后线程就终止了
    问题二：如果在子线程中直接设置一个while(1)，那么子线程就会一直打印消息

这就是为什么需要**线程同步**，所谓同步就是子线程和主线程需要配合


#### 线程同步之信号量

![](https://raw.githubusercontent.com/TongxinV/oneBook/master/0.3.Programming%20in%20the%20UNIX/assets/002/%E7%BA%BF%E7%A8%8B%E5%90%8C%E6%AD%A5%E4%B9%8B%E4%BF%A1%E5%8F%B7%E9%87%8F.png)

![示例程序1](https://raw.githubusercontent.com/TongxinV/oneBook/master/0.3.Programming%20in%20the%20UNIX/assets/002/%E7%A4%BA%E4%BE%8B%E7%A8%8B%E5%BA%8F1.png)

现象：可以统计字符个数，但是不能回收子线程，原因是子线程在sem_wait卡住了，所以
在输入end的时候还要再调用sem_post，更改如上

最后没有完美解决一些小问题，但主要知识已经get


#### 线程同步之互斥锁

> 互斥锁主要用来实现关键段保护

![示例程序2](https://raw.githubusercontent.com/TongxinV/oneBook/master/0.3.Programming%20in%20the%20UNIX/assets/002/%E7%A4%BA%E4%BE%8B%E7%A8%8B%E5%BA%8F2.png)

程序只是一个示例，有些bug，忽略！互斥锁本来就不是来干这个的，程序效率很低，用了好多sleep，这个代码就是凑出来的。真正的解锁上锁只是为了保护某一段代码，并不是像这边的同步


#### 线程同步之条件变量

> 线程特有，专门用来满足线程同步

![示例程序3](https://raw.githubusercontent.com/TongxinV/oneBook/master/0.3.Programming%20in%20the%20UNIX/assets/002/%E7%A4%BA%E4%BE%8B%E7%A8%8B%E5%BA%8F3.png)



