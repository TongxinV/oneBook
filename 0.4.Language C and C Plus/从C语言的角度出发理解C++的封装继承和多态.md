从C语言的角度出发理解C++的封装继承和多态
---
[TOC] 

> 在学习C++面对对象程序设计的时候，会把C++类的使用和C结构体的使用作比较。以下内容是学习过程中思考的问题，从而总结出为什么要设计出C++的封装继承和多态。因为自己写C程序的时候也是以面对对象的思想来写(看过内核源码你就知道我在说什么)，我们都知道C++是C语言的继承，而C++最明显的特征就是面对对象，那么C++是如何继承的，这是我思考的出发点

> 以下内容只是个人观点，不一定对，或者说只是想说只是想说服自己更好的理解C++


### 封装

> 显然封装没有区别，为了完整性，把封装给贴出来了

首先明白什么是对象Object

    Objects = Attributes + Services
程序里的封装就是对象Services的设计。封装的意义在于不直接操作数据。程序员很容易犯这样的错误，写着写着就伸到那个对象的里面去，直接去操数据

### 继承Inheritance

问题：C编程使用结构体嵌套，那么C++类的嵌套是什么？：一种就是——**继承**。在学习Linux设备驱动模型时，kobject就相当于是一个父类！！另外一种重要的方式是——**组合**。两种都可以使用，并没有谁是最好的，谁更合适应根据上下文决定或者混合使用。比如造车，继承应该是拿一个最基本的车来做父类，组合则是拿轮子拿引擎来拼装。再比如串口设备，应该是继承类device，然后组合串口。

```cc
例子较简单就不写了
```

可以尝试一个类引用另一个类，即C编程中的结构体里面使用一个结构体类型的指针，真正需要用到时再malloc。参考博客：http://blog.csdn.net/kelvin_yan/article/details/44653145





### 多态Polymorphism

问题：C编程结构体内使用函数指针进行封装。比如open函数指针，不同设备open的方式不同，所以在C编程的时候，我可以定义几个不同的xxx_open函数然后再把地址给结构体里面的open？那么在C++类中要实现这种用法具体怎么做呢？：多态

**C version:**
```cc
struct A{
  void (*open)(void);
  ...
};

struct A xxx;xxx.open = xxx_open;
struct A yyy;yyy.open = yyy_open;
struct A zzz;zzz.open = zzz_open;
```

**C plus version:**
```cc
class A{
public:
  virtual void open();
};

class XXX：public A{
public:
  virtual void open();
};

class YYY{
public:
  virtual void open();
};

class ZZZ{
public:
  virtual void open();
};
```
