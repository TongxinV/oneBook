~~C++软件重用和封装的思想~~
======


~~C编程之结构体内使用函数指针进行封装。比如open函数指针，不同设备open的方式不同，所以在C编程的时候，~~

~~我可以定义几个不同的xxx_open函数然后再把地址给结构体内的open？那么在C++类中要实现这种用法具体怎么做呢？~~

~~当然，C++可以和C那样使用，是想问C++有没有对这种情况做特殊处理；如果没有，有没有合适的处理方法~~

~~自己捋了一下，可以这样使用：不同设备是子类，xxx_open、yyy_open、zzz_open中的相同部分open抽象出来做成父类~~


~~(似乎是实现了，但是这是两种完全不同的思维方式：如下代码表现，get到了你会觉得很奇妙)~~

--

**C version:**


```cc
struct A{
  (void* open)(void);
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
  void open();
};


class xxx{
public:
  void open(){...;a.open();...}
private:
  A a;
};


class yyy{
public:
  void open(){...;a.open();...}
private:
  A a;
};

class zzz{
public:
  void open(){...;a.open();...}
private:
  A a;
};

```



~~再考虑一个问题：谁的内存开销大：单一粗略的看，`c version` 的开销大，理由如下：`xxx_open`、`yyy_open`、`zzz_open`内部都使用了相同的open，即整个程序有三份open。但是`c plus version`使用不同类的open时内部调用的是同一份open（也就是类A的open）（函数是属于类的，成员变量才属于对象，定义多个对象不会有多个函数）~~
~~**从这个问题体会C++封装和软件重用的思想，前面考虑如何使用C++实现C一样的用法是体会抽象和封装，后面比较内存开销是体会软件重用**~~
