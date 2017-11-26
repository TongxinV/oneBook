<h1 align="center">
    oneBook
</h1>

<p align="center">
  <a href="https://github.com/TongxinV">
    <img alt="tongxinv github" src="https://img.shields.io/badge/author-TongxinV-green.svg">
  </a>
  
  <a href="http://blog.csdn.net/tongxinv">
    <img alt="CSDN" src="https://img.shields.io/badge/CSDN-%E5%8D%9A%E5%AE%A2-ff69b4.svg">
  </a>
  
  <a href="https://github.com/TongxinV/oneBook/issues">
    <img src="https://img.shields.io/github/issues/TongxinV/oneBook.svg" alt="GitHub issues">
  </a>
  
  <a href="mailto:liyanbin0027@163.com">
    <img src="https://img.shields.io/badge/%20liyanbin0027%40163.com-Chat-blue.svg" alt="YouXiang">
  </a>
  
  <a href="">
    <img src="https://img.shields.io/twitter/url/http/shields.io.svg?style=social" alt="Twitter URL">
  </a>
</p>


> DoING... 工作了，还有很多内容没整理，但时间有限，可能仓库更新不会那么频繁；主要是整理以前学的linux驱动知识

## SIP／SDP／RTP/UDP

* [`sip协议基础`][0-1-001]
* [`sip业务基础`][0-1-002]

## 程序设计


## 嵌入式应用开发与底层开发     


**1.Basic external equipment**


**2.BootLoader and Kernel**

* [`随笔--uboot 源码简要分析`][2-1]
* [`随笔--kernel源码简要分析`]()


**3.Programming in the UNIX**

* [`UNIX环境高级编程·简单分类`][3-0]
* [`并发式io解决方案`][3-1]
* [`linux进程控制`][3-2]
* [`linux线程控制`][3-3]


**4.Linux-Driver Development**

 * [`随笔--Linux字符设备驱动开发基础`][5-0]
 * [`随笔--Linux驱动框架入门之LED`][5-1]
 * [`随笔--Linux内核的gpiolib学习`][5-2]
 * [`随笔--Linux设备驱动模型`][5-3]
 * [`随笔--platform平台总线`][5-4]    
 * [`随笔--misc类设备驱动`][5-5]



## 博客/零散问题/心情

* [`Ubuntu1604下使用virtualenv工具搭建python2，3开发环境 `](https://github.com/TongxinV/oneBook/issues/28)
* [`ubuntu 16.04 samba安装与设置访问权限`](https://github.com/TongxinV/oneBook/issues/24)
* [`uboot主Makefile`](https://github.com/TongxinV/oneBook/issues/22)
* [`uboot配置过程(mkconfig脚本+其他)`](https://github.com/TongxinV/oneBook/issues/21)
* [`uboot根目录下的config.mk`](https://github.com/TongxinV/oneBook/issues/20)
* [`uboot链接脚本（为什么需要链接脚本）`](https://github.com/TongxinV/oneBook/issues/19)
* [`内核链表实现分析与使用（双向环形链表）`](https://github.com/TongxinV/oneBook/issues/18)
* [`从C语言的角度出发理解C++的封装继承和多态`](https://github.com/TongxinV/oneBook/issues/16)
* [`谈论attribute驱动实现方式(及device_create与设备节点的关系)`](https://github.com/TongxinV/oneBook/issues/15)
* [`移植库需要注意事项(与移植库生成的文件如何使用)`](https://github.com/TongxinV/oneBook/issues/14)
* [`正确使用指针(指针作为输出型参数)与结构体指针作为函数参数`](https://github.com/TongxinV/oneBook/issues/13)
* [`系统启动时在bus系统中注册platform总线`](https://github.com/TongxinV/oneBook/issues/11)
* [`将写好的驱动添加到内核中`](https://github.com/TongxinV/oneBook/issues/10)
* [`linux内核段属性机制(以subsys_initcall和module_init为例)`](https://github.com/TongxinV/oneBook/issues/9)
* [`内核提供读写寄存器接口实现可移植性`](https://github.com/TongxinV/oneBook/issues/8)
* [`__register_chrdev_region分析(简单字符设备驱动在内核的工作原理)`](https://github.com/TongxinV/oneBook/issues/7)
* [`动态映射之结构体方式操作寄存器`](https://github.com/TongxinV/oneBook/issues/6)
* [`Linux内核静态映射表建立过程分析`](https://github.com/TongxinV/oneBook/issues/5)





> **备忘录**

- [ ] `linux源码是一个很棒的教学素材，不单要学习如何开发，还要融会贯通它的一些设计方式设计理念，举一反三`

- [ ] `完成文章``《Kconfig Makefile .config三者之间的关系（在内核中添加或去除某个驱动）》`

> **备忘录（新）**
- [ ] 大型工程的makefile/子模块的Makefile(driver、device)的编写记录
- [ ] 编译时的链接路径的运行时的链接路径的区别
- [ ] libxml2、xpath的学习记录
- [ ] GNU  Readline 的学习记录
- [ ] getline、getdelim函数（getline 第一次读取到的是空行）
- [ ] msgget、msgsend、msgrcv、magctl
- [ ] 定时器的使用
- [ ] fopen、freopen的区别
- [ ] C语言函数返回数组的问题 
- [ ] C语言二维指针数组的使用记录（解析csv行数据的时候）
- [ ] 函数指针数组的妙用
- [ ] __attribute((constructor)) 加编译的时候链接.o文件可以实现类似内核的模块加载动作
- [ ] 使用全局变量去赋值给另一个全局变量 error：initializer element is not constant  
- [ ] 使用libxml2的时候，明明包含了头文件的路径，路径下也有相应的.h文件，但是编译的时候还是报错，原因时#defien  __XML_PARSER_H__
- [ ] 链表的链表的使用记录
- [ ] 维护两份数据+下发更新 来替代 多线程的维护成本，当然具体场景具体分析
- [ ] 【实体数组+成员中使用指针】与【指针数组+成员中使用实体】 的权衡
- [ ] 透过现象看本质，不单了解How，还要理解why。比如BMU下发配置，只说了说了如何下发，但自己又另外提问了为什么要下发，下发什么内容等；追求一个问题的本质的作用是有助于你更好的解决问题
- [ ] 现在的学习不能单单的只意识到正确的一面，尝试思考，这一过程是否一直都是正确的理所当然的正确执行，如果不是，什么时候会出错，什么情况下会出错，导致出错的因素都有哪些；出错后是否有处理，怎么处理等等；再抠一点，退出的时候是正常退出还是非正常退出等
- [ ] 今天有一个错误，问ZZJ太多问题了，可能最近松懈散漫了，“不仅仅要会学习，还要会怎么学习，而不是等谁给你讲这个东西要怎么学习，要先学这个再学那个这样，当然有人指导是好事，可以少走弯路，节约时间，但是实际开发过程中，更多的是谁都不了解这项技术，然后要你去调研，所以要懂得怎么去学习”
- [ ] 尝试从最底层开始思考，比如别人问你一个问题，在某些场景下你从问题的表面开始思考可能会遗漏一些这个问题依赖的一些底层的前提条件，比如HTTP+JSON是否需要维护状态？-->思考dot：HTTP底层使用的TCP连接
- [ ] 软件工程设计总结：大的流程-->分层+每一层的模块粗细分-->层与层之间的模块数据交互（之前做CNS自动化测试工具的时候这一部分没考虑清楚，在实际编程的时候这块的工作量是有的，以至于导致开发效率低下）-->模块内部细细分（也是对大的流程的细分）
- [ ] 如何通过源代码去找到源码中某一组件的的使用方式？比如源码中的底层模块A的使用方式，相信一份好代码都是层次清晰的，假设有一个模块B使用了A，那么在B文件中找到A的相关接口，思考联系一下就会有收获；（个人见解，小小感悟，当然还有其他的方式，比如通过某一贯穿全局的参数）
- [ ] 编译的时候加上-g，否则调试的时候没有行号（比如使用valgrind）
- [ ] 是设计文档拖延一周被骂好，还是想后面因为设计文档没考虑到位项目出现重大事故而被骂？
- [ ] printf `"%.*s"` http://www.cnblogs.com/yuaqua/archive/2011/10/21/2219856.html 
- [ ] 有没有必要对MCU的定时器和线程的实现一探究竟呢？
- [ ] MCU主makefile中 %-build 的写法
- [ ] 把自己看成一个合格的开发者，不要什么事都征询他人意见或者要别人定夺，要自己会判别。从某一种角度来说，这是一种不敢承担后果的行为
- [ ] 个人见解：一般来说，程序中功能划分或者模块划分耦合性越小越多好。比如最近在编写数据库订阅的相关功能中，一种是取数据库的消息然后紧接着去做消息发送到Http client的动作；而另外一种是取数据库的消息，保存到一个全局链表，当全部都保存好了之后；然后发送消息动作另外，从全局链表中去取数据；另外程序中模块与模块间使用【消息队列+MsgQId+两者都能解析的格式（如JSON格式）】取代一些全部用全局变量的做法也是一种解耦的方式
- [ ] MCU数据库支持Map方式的代码分析

---- **路虽远，不行不至**






[0-1-001]:https://github.com/TongxinV/oneBook/blob/master/0.0.Document%20update%20catalog/class/1.0.0.SIP%E5%8D%8F%E8%AE%AE%E7%9B%B8%E5%85%B3/sip%E5%8D%8F%E8%AE%AE%E5%9F%BA%E7%A1%80.md
[0-1-002]:https://github.com/TongxinV/oneBook/blob/master/0.0.Document%20update%20catalog/class/1.0.0.SIP%E5%8D%8F%E8%AE%AE%E7%9B%B8%E5%85%B3/sip%E4%B8%9A%E5%8A%A1%E5%9F%BA%E7%A1%80.md

[2-1]: https://github.com/TongxinV/oneBook/blob/master/0.2.BootLoader%20and%20Kernel/uboot%E6%BA%90%E7%A0%81%E5%88%86%E6%9E%90.md

[3-0]:https://github.com/TongxinV/oneBook/tree/master/0.3.Programming%20in%20the%20UNIX
[3-1]:https://github.com/TongxinV/oneBook/blob/master/0.3.Programming%20in%20the%20UNIX/%E5%B9%B6%E5%8F%91%E5%BC%8FIO%E8%A7%A3%E5%86%B3%E6%96%B9%E6%A1%88.md#并发式io解决方案
[3-2]:https://github.com/TongxinV/oneBook/blob/master/0.3.Programming%20in%20the%20UNIX/linux%E8%BF%9B%E7%A8%8B%E6%A6%82%E8%BF%B0.md
[3-3]:https://github.com/TongxinV/oneBook/blob/master/0.3.Programming%20in%20the%20UNIX/linux%E7%BA%BF%E7%A8%8B%E6%8E%A7%E5%88%B6.md






[5-0]:https://github.com/TongxinV/oneBook/blob/master/0.5.Linux-Driver%20Development/0.0.%E5%AD%97%E7%AC%A6%E8%AE%BE%E5%A4%87%E5%9F%BA%E7%A1%80.md#随笔--linux字符设备驱动开发基础
[5-1]:https://github.com/TongxinV/oneBook/blob/master/0.5.Linux-Driver%20Development/5.1.%E9%A9%B1%E5%8A%A8%E6%A1%86%E6%9E%B6%E5%85%A5%E9%97%A8.md#随笔--linux驱动框架入门之led
[5-2]:https://github.com/TongxinV/oneBook/blob/master/0.5.Linux-Driver%20Development/5.2.%E5%86%85%E6%A0%B8%E7%9A%84gpiolib.md#随笔--linux内核的gpiolib学习
[5-3]:https://github.com/TongxinV/oneBook/blob/master/0.5.Linux-Driver%20Development/5.3.%E8%AE%BE%E5%A4%87%E9%A9%B1%E5%8A%A8%E6%A8%A1%E5%9E%8B.md#随笔--linux设备驱动模型
[5-4]:https://github.com/TongxinV/oneBook/blob/master/0.5.Linux-Driver%20Development/5.4.platform_bus.md#随笔--platform平台总线
[5-5]:https://github.com/TongxinV/oneBook/blob/master/0.5.Linux-Driver%20Development/5.5.misc%E7%B1%BB%E8%AE%BE%E5%A4%87%E9%A9%B1.md#随笔--misc类设备驱动
