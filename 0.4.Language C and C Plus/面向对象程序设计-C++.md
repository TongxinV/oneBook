面向对象程序设计-C++ 
=============

> 怎么面对C++ 呢？把C++是用C语言实现的；把C++类的使用和c的结构体使用比较起来


自己的一些思考：

1. C结构体内使用函数指针。比如open函数指针，不同设备open的方式不同，所以在C编程的时候，我可以定义几个不同的xxx_open函数然后再把地址给结构体内的open。那么在C++类中要实现这种用法具体怎么做呢？(当然，C++完全可以像C一样的做法)：**多态**

2. C结构体的嵌套，那么C++类的嵌套是什么？：**继承**。在学习设备驱动模型时，kobject就相当于是一个父类！！还有另外一种重要的方式——**组合**，两种都可以使用没有谁更好，而是不同场景谁更合适
3. C结构体内使用结构体指针。2的问题进一步说，C结构体嵌套更多使用的是去引用一个结构体，真正需要用到时再malloc。那么C++怎么去引用另一个类呢？：百度到的一篇文章http://blog.csdn.net/kelvin_yan/article/details/44653145


[TOC]


###1-1 一个C++程序

....(略)

###2-1 面对对象编程

> 高度抽象的层面上的交互

####什么是对象

> Objects = Attributes + Services

很重要的一点，面对对象编程(OOP)的原则：不直接操作数据

**从程序的表现形式理解**：

C version

    C doesn't support relationship btw data and functions.
    typedef struct point3d{
        float x;
        float y;
        float z;
    }Point3d;
    
    void Point3d_print(const Point3d* pd);
    Point3d a;
    a.x = 1; a.y = 2; a.z = 3;
    Point3d_print(&a);
    
C++ version

    class Point3d {
    pubilc:
        Point3d(float x, float y, float z);
        print();
    private:
        float x;
        float y;
        float z;
    };
    
    Point3d a(1,2,3);
    a.print();

####对象和消息

两个对象之间通过信息交流。对象A发消息给对象B，但A不直接操作B，B的动作由B自己决定。

程序员很容易犯这样的错误，写着写着就伸到那个对象的里面去，直接去操作蛋黄了。


####对象和类

class defines object, object is a class

类是抽象，对象是实体

####面对对象编程（OOP）

**OOP Characteristics**:

1.everything is an object 
2.A program is bunch of objects telling each other what to do by sending messages
    很重要的一点：告诉它what to do要干嘛而不是how to do要怎么做，要怎么做由B对象自己决定
    比如你去餐厅叫服务员倒一杯水，你不可能还教她要去厨房拿水壶，走过来弯腰倒水倒到杯子等等
3.Each object has its own memory made up of other objects
4.Every object has a type.
    隐含意思是对于OOP来说，任何对象都是由类型定义出来的；虽然实际自然是先有对象后有类型
5.All objects of particular type can receive the same message
    接口的设计，灯泡虽然不同，像白炽灯、LED灯等原理是不一样的，当然也可以一样，但是只要有做出可以旋的接口就都
    可以插到灯座，就可以亮。为什么要这样的设计自己慢慢体会（这就是三大特性中的封装）


**OOP 三大特性**：

封装继承多态


###3-1 自动售票机的例子

两个冒号`::`，叫做域的解析符，没有`::`则变量或函数为全局

注意点0：声明 定义

注意点1：类const变量的初始化，参考博客：http://www.cnblogs.com/wxxweb/archive/2011/04/28/2031674.html

注意点2：`extern int a`是一个声明不是定义

###3-2 头文件

(略)

###3-3 时钟的例子

抽象：在某一层面上去看待一些问题，有意识的去屏蔽一些内部的东西。比如我看到一辆车我只关注它的外貌，什么颜色什么牌子，造型什么的。但我不会去考虑它用几号的轮胎用几号的汽油等


###3-4 成员变量

* 成员变量的概念
* 成员变量和本地变量的关系
* 成员变量到底在那里。

Fields parameters local variables 

**成员函数属于类class**，函数不属于对象（试想定义多个对象时，函数只有一份）

**成员变量属于对象**，成员变量不属于类class（试想定义多个对象，变量有多份）


###4-1 构造和析构

> 经常需要有init函数，以便保证使用的内存干净

    int main()
    {
        ...
        {
            ...
            A a;
            ...
        }
        ...
    }

进入到大括号里面后，空间是分配了，但构造要到那一行才运行<br>
没有执行构造不能执行析构<br>
带参数的构造函数<br>


###5-1 new & delete

> 相当于c的malloc和free

* new
    * new int;//只要分配空间就OK
    * new Stash;//除了分配空间还要调用类的构造函数
    * new int[10];

* delete
    * delete p;//如果是类还要调用类的析构函数再收回空间
    * delete[] p;//delete的是一`类的对象的数组`，保证每一个对象的析构都会被调用

![cc002][1]<br>
new返回的是这块内存的第一个元素的地址<br>
delete带上方括号[]就告诉delete它要去释放的地方是`类的对象的数组`，那么那么多`类的对象`的析构函数都会被调用。如果不带方括号，空间都会被回收但是只有第一个的析构会被执行。(方括号的作用不是告诉它要delete的地方是一个数组)

**总结**：new的时候带方括号，delete也带上方括号

###5-2 访问限制

> public和private，指明哪些可以成员能被别人访问，哪些只能被自己访问。这件事对OOP来说是非常重要的，我们在讲OOP理论的时候，一直在强调这件事情，你的对象应该是被封装起来的，对象应该是受保护的，对象里面的数据是不会被别人直接访问的，别人能够触碰的只是**你的函数**，别人可以通过**你的函数**要求你做事情，但是这个函数具体怎么做具体怎么会对你里面的数据产生影响这是你的代码所决定的。

> 所以我们需要有这么一种机制能够使programmers(使用你的类的程序员)不能随心所欲的访问你里面的东西，而且使library designer(写类的那些人)能够去修改内部的那些东西而不影响其他人

####public\private\protected

public：可以被任何人访问

private：完全私有的,只有当前类中的成员函数能访问。private属性的成员可以是变量也可以是函数，那么private属性的函数就只能被类的成员函数调用（类似于用static修饰的函数）（千万注意一点，**函数属于类**！！！！如果你看到对象A1访问了对象A2的私有成员变量，你可别以为他是错误的）

protected：受保护的,只有当前类的成员与继承该类的类才能访问


####friends

C++还有一个破环OOP原则的叫friends，你可以声明别人是你的朋友（别人说是你的朋友是不可信的），一旦声明了之后别人就可以访问你private的东西了。别人可以是别的类也可以是别的函数，可以是别的类的某个函数。(常见的用法就是把一个不属于类的全局函数声明为类的友元，以访问类的成员变量)

百度到的一段话： 

采用类的机制后实现了数据的隐藏与封装，类的数据成员一般定义为私有成员，成员函数一般定义为公有的，依此提供类与外界间的通信接口。但是，有时需要定义一些函数，这些函数不是类的一部分（**注意友元函数不是类的一部分**），但又需要频繁地访问类的数据成员，这时可以将这些函数定义为该函数的友元函数。除了友元函数外，还有友元类，两者统称为友元。友元的作用是提高了程序的运行效率（即减少了类型检查和安全性检查等都需要时间开销），但它破坏了类的封装性和隐藏性，使得非成员函数可以访问类的私有成员。

####class vs struct

class和struct在C++都是一样的，他们都是用来表达类的，只有一点点细微的差别：

* class defaults to private
* struct defaults to public

首选class，除非确实很简单只有几个变量的组合才考虑struct

####类的嵌套(后面讲的composition组合)

> **问题：C语言结构体嵌套，那么对应C++ 的类的嵌套如何使用**

C++嵌套类
1.嵌套类的名字只在外围类可见<br>
2.类的私有成员只有类的成员和友元可以访问，因此外围类不可以访问嵌套类的私有成员。嵌套类可以访问外围类的成员（通过对象、指针或者引用）<br>
3.一个好的嵌套类设计：嵌套类应该设成私有。嵌套类的成员和方法可以设为 public <br>
4.嵌套类可以直接访问外围类的静态成员、类型名（ typedef ）、枚举值<br>

博客地址：http://blog.csdn.net/firstit/article/details/6154320





###5-3 初始化列表initializer list


    class A
    {
    public:
        A(int a);
        virtual ~A();
        ...
    private:
        const int P;
    };

初始化列表：

    A::A(int a):P(a){
    }

    
**总结**：都用initializer list


###6-1 对象组合composition

> Reusing the implementation 

OOP的三大特性——封装继承多态性。但是从另外一种角度来说，继承是OOP对一件事情的回答——software reusing 软件重用，或者说你的代码重用。当然软件重用不是仅仅靠继承这一件事就能够解决的，但是继承是对软件重用的回答，或者说继承是可以用来实现软件重用的的一种方式。

软件重用是一个梦想，从软件开始人们就梦想能够有各种程度上的重用。到了OOP，我们找到可以实现的手段，当然这不是唯一的也不是最好的手段。软件重用有很多不同的方式，在继承之前，在C++里面还有另外一种方式——**组合**。

组合的意思是我们利用已有的对象来制造出新的对象出来。例如一辆车，如果我们已经有了引擎的对象，有了轮胎的对象，我们就可以利用起来。反应C++代码上就是我们设计一个类的时候成员可以是一个类的对象，这就叫做Composition：construct new object with existing objects

composition这种方式是一种软件重用方式，而且是一种非常重要的软件重用方式，你不能一讲软件重用一讲C++一讲OOP你就只想到只有继承

**Example**:

    class Person {...};
    class Currency {...};
    class SavingsAccount {
    public:
        SavingsAccount( const char* name,
                const char* address, int cents );
        ~SavingsAccount();
        void print();
    private:
        Person m_saver;
        Currency m_balance;
    };

**问题1**：当我们要去创建SavingsAccount的对象时候，实际上SavingsAccount的构造函数就会被调用。但是实际上Person对象和Currency对象有自己的构造函数。那么这两个对象的内存该怎么初始化，是应该由SavingsAccount来做呢？还是由Person和Currency来做呢？让他们自己去初始化自己，自己去管理自己，代码形式如下：

    SavingsAccount::SavingsAccount(const char* name,
                    const char* address, int cents):m_saver(name, address),
                    m_balance(0, cents){}
    
    void SavingsAccount::print(){
        m_saver.print();
        m_balance.print();
    }
这样做，而不是把它放在构造函数里面来构造它。之前讲`initializer list初始化队列`的时候遇到过，要放在构造函数里面处理那么就会要求的Person和Currency这两个类必须要有`default contraction默认构造函数`。那么实际上他就要多做一遍构造在做一遍赋值的事情，实际上是一件很浪费的事情。

然后在做print的时候我们就很简单，我们只要 `m_saver.print()`和`m_balance.print()`就可以了。

我composition组合进来的对象仍然具有独立的人格，它的边界仍然是清晰的。所以我不能去破坏对象的边界，我不能直接拿`m_saver`里面或`m_balance`里面的成员变量然后cout去输出。Person和Currency都提供了print的方法，我应该拿他们的print去做SavingsAccount的print，而不是直接去拿它的成员变量，尽管它们包含在我里头。

**问题2**：把Person对象和Currency对象放到public是否合适？做成public那么就意味着任何人可以从外面访问它，当然这是一种解决方案，但是这显然不是OOP所喜欢的，因为它突破了边界，它把你里面的数据开放给外面了，这不是我们那个鸡蛋模型了。就像你的心脏是在体外的，别人可以上来按两下。语言是很灵活的，但是它提供的这些手段不见得都是你适合去用的



###6-2 继承Inheritance

继承和组合都是软件重用的方式，组合是拿**已有的对象**拼装出新的类。继承是说我拿**已有的类**来，在已有的类上做一些改造，然后得到一个新的类。


![cc004][2]<br>
Inheritance是C++语言非常重要的一种技术，也是非常重要的一种OO设计方法，我们可以共享设计当中的`Member data` `Member functions` `interface`。<br>
什么是interface，interface和function有什么区别？为什么要在这里强调interface？我们提到public，提到private，我们说除了data可以是private，function也可以是private，所以member function可以是private也可以是public。它们的public构成了interface。（同样的member data也可能是public虽然我们并不想这么做某些情况下还确实需要这么做，这些public的member data也是interface的一部分）<br>
`interface`就是指一个类对外公开的那一些部分，别人可以通过interface观察到操纵到类的对象。

![cc005][3]<br>
superset：Person<br>
another class：Student<br>


![cc006][4]<br>
几个名词：基类，超类、父类<br>
几个名词：派生类、次类、子类<br>

![cc007][5]<br>
子类类B直接使用了父类类A中的private member data，这是非法的；解决办法在父类中把子类确实需要访问的内容由private转变成protected。但是，我们做成private是因为我们希望保持原有的设计，将来无论别人怎么继承都无法改变我对private member data的定义，所以大部分情况应该是封装出合理的接口。合理使用public、protected、private是一门艺术。

###6-3 子类父类关系


父类的所有东西都必须在你的体内，子类的初始化也必须初始化父类。另外注意构造顺序和析构顺序

![cc009][6]

初始化列表initializer list第一条规则：你所有的成员变量都必须放在这里<br>
初始化列表initializer list第二条规则：父类的初始化

###7-1 函数重载

> Same functions with different arguments list

###7-2 内联函数

####内联函数

减少函数调用开销，比如把参数push到函数自己的栈里面去，push保存函数的返回地址，准备返回值，pop函数自己栈内存得到返回地址等

![cc010][10]

![cc011][11]

####如何使用

inline函数存在于头文件，而不在.cpp里面，只要.h有inline就够了。头文件的inline函数一是告诉编译器这个函数是一个inline函数，所以编译器你不能生成调用的代码，应该把函数的代码插到相应地方。二是把inline函数插入到相应位置，那么问题就来了，插入不同于调用，调用时函数实体可以不在头文件中，插入就要求编译器当前在处理的文件中要有函数实体（编译器一次只能处理一个文件，include就是原地展开）。

如下编译器会报错：
```
a.h
inline void f(void);

a.cc
inline void f(void)
{
    cout << "inline function" << endl;
}

main.cc
#include "a.h"

int main(void)
{
    f();
    return 0;
}

```

####类中使用inline函数

函数的body直接放在类中，就是inline

![cc012][12]

![cc013][13]

除了上面那一种，还可以放到类外，这样保持了类比较干净

![cc014][14]

###8-1 const


####编译时的const

> 编译时用const修饰的变量仍然是一个变量而不是常量，常量需要被初始化

![cc015][15]

编译时用const修饰的变量仍然是一个变量而不是常量。使用const修饰时：编译器只是保证它的值不会被改变，跟这个变量是不是真正的const无关。`extern const int bufsize` 是说我说外部的那个bufsize在我这里是const，在外面是不是真的const是不一样的。


####const修饰对象（const成员函数）

![cc019][19]

一个对象前面加const，意思是整个对象是一个const，这个意思是说这个对象里面的**member data**是不能被修改的(成员变量是属于对象的)。一旦这么做了之后，对象里的函数就有问题了，调用Currency的某个函数，也许会修改里面的成员变量，也许不会，怎么知道它会不会成员变量呢？当然我们看源码是可以知道的。但是编译器就没办法做了，编译器只能看到.h里面的函数原型，函数的body是在.cpp里面的。the_raise现在一个const对象，我要对这个对象执行某些函数，我就必须要知道这些函数会不会去修改里面的值，有可能修改也有可能不修改。不可能什么函数都不能执行，不然这个对象就废掉了。一定要有些函数能执行的，但是哪些函数能执行哪些函数不能执行它（编译器）又要通过.cpp才能看到。你可以在一个函数的后面加上const（类和）。

![cc020][20]

这个意思是说我保证这个函数不会去修改任何成员变量。作为一种良好的编程风格，在声明一个成员函数时，若该成员函数并不对数据成员进行修改操作，应尽可能将该成员函数声明为const成员函数

关于C++ const成员函数更具体的介绍可以参考这篇博客：http://blog.csdn.net/lihao21/article/details/8634876


####const修饰指针

![cc017][17]

...(略)

###9-1 引用Reference

> Reference 就是const指针（int *const p; 指针的地址不能被改变，指针指向的内容可以改变）。引用的发明还有一个原因是为了好看

####引用Reference

Reference中文叫做引用，C++复杂就在于提供了太多的内存模型，或者说它提供了太多两种东西，第一种复杂是太多的可以放东西的地方，对像可以放在堆里面，栈里面和全局数据区里面；第二种复杂是提供了太多的可以访问对象的方式，你可以直接掌握这个对象，可以通过指针还可以使用现在要讲的**引用**。他还有另外一个称呼--别名。

![cc021][21]

如果在函数参数表里面，或者作为成员变量它才能够没有后面那个初始话的东西（因为函数参数调用的时候会给它，成员变量在构造对象的时候会初始化它）。但如果是本地变量或者全局变量你就必须给他一个初始值以绑定。

####引用和指针

![cc022][22]

![cc023][23]

...(略)

###10-1 向上造型Upcast

> 在C++中，把子类的对象当做父类对象看待，就称为向上造型。即学生可以不当成学生(子类)，而把它当成人(父类)来看

> cast翻译成造型而不是类型转换，造型和类型转换的区别就是double转成int，那就是int了。但是子类变成父类来看待，但他实质还是子类

![cc024][24]

![cc025][25]

###11-1 多态Polymorphism


####多态性

![cc026][26]

![cc027][27]

...(略)

####多态的实现

任何一个类如果有虚函数，那么它的对象就会比正常的大一点。子类和父类都有自己的vatable，用来记录函数地址。



####...

你的类里面有一个virtual函数，那么他的**析构函数**就一定virtual的。


###12-1 引用再研究

* 和多使用指针进行传参一样，多使用引用进行传参
* 使用`const int& a;` 的意义(和使用`const int* a;`意义一样)
* 对象作为函数参数，没有const的情况讨论。按照C的思维，你立马就想到输出型参数那个知识点。但是在C++数据总是设计成私有的，外部函数随意不能去修改对象私有数据（OOP原则），即在C++里面可以说是没有输出型参数这一说的（当然，实际上是有的）。访问对象私有数据只能通过类封装好的函数。**另外**当一个对象被const修饰后，能够使用的函数就只剩类里面的const函数。


* 临时变量是const的

![cc028][28]

```cc
void f1(const int & i){
    cout << i << endl;
}
void f1(int & i){
    cout << i << endl;
}
int main()
{
    int i = 3;
    f1(i*3);//可以运行
    f2(i*3);//ERROR
    return 0; 
}
```

###26 拷贝构造函数

> 初始化initialization和赋值assignment在C++是完全不同的两个东西（在C可以当成是相同的）

    Currency p = bucks;//initialization,这里的对象初始化要调用拷贝构造函数，而非赋值
    p = bucks;//assignment

####什么是拷贝构造函数(什么情况会拷贝构造函数)

> 如果你没有给拷贝构造函数,编译器会默认给你一个拷贝构造函数。

![cc030][30]
![cc029][29]

**分析打印信息的缘由**：

    HowMany h：调用构造函数HowMany() { objectCount++; ...; }
    
    HowMany h2 = f(h)：执行步骤如下：

    1. 由于f()函数是址传递，x为f()函数内部的对象：
        HowMany x = h;  //即HowMany x(h);调用编译器默认的temp构造函数HowMany(const HowMany&);
                        //注意不是调用h的构造函数，所以此时的objectCount还是等于1，没有加1
                        //如果类HowMany有这么一个函数：
                            HowMany(const HowMany& xxx){ objectCount++; }
                            那么这时候，就会调用这个函数而不是编译器给的那个，打印信息如下图显示
                            这个函数就是拷贝构造函数
    2. f()函数执行完了之后，对象x的内容被保存到栈上，调用x析构函数执行了objectCount--使得objectCount=0
    3. 到了HowMany h2 = f(h);//即HowMany h2(f(h));调用编译器默认的h2构造函数HowMany(const HowMany& xxx);
                          //注意不是调用h的构造函数，所以此时的objectCount等于上一次的值0，没有加1
    4. 到了程序终止是，调用了h1和h2的析构函数，即执行了两次objectCount--使得objectCount=-2
    
![cc032][32]
![cc031][31]

附：拷贝构造函数HowMany(const HowMany& xxx){...不能写成HowMany(const HowMany xxx){...不然就递归了，而且编译器也不让你过


**总结**：如果你没有给拷贝构造函数,编译器会默认生成一个拷贝构造函数。如果你给了，你可以用你给的那个来控制怎么来做拷贝，也许你有些东西不需要拷贝，有些东西你想做特别的处理。如果你没有什么特别想做的，你可以让系统使用编译器给你的那个。编译器给你的那个拷贝构造函数它会做的事情就是它拷贝每一个成员变量，他会做成员变量对成员变量的拷贝(不是字节对字节的拷贝bitwise，只不过如果你的成员全部都不是对象，那时才等同于Bitwise)，如果这个变量是int，它会把int拷贝给int，float给float，有其他类的对象就调用那个类的拷贝构造函数，有指针时是发生**指针的拷贝**(**重要**)，两个指针会指向同一片内存，造成的结果就是**析构**的时候会发生错误。

![cc033][33]

举个例子：

![cc034][34]
![cc035][35]
![cc036][36]

另外还有一个问题要说：

对于纯字符串处理到了C++尽量的使用`string&`，代替使用`char *`，具体原因网上搜索

更详细的内容网上再找些资料加深理解：比如[百度百科--拷贝构造函数](http://baike.baidu.com/link?url=tba0-T6ASk-7D7Cmj5IWKAri-YsGGtNB5TjORstfg9_CxUgUzWyCbuYSJdi1s2CSyS9RZsKi6h0faFWUKHPmneGqHomODTv3cQHr_8iYpsmfjGE2gzgPhvMSM-mTJ6UuW9l_yw86HM2zUkvxSoMM0a)

####总结（编程时应该怎么做）

![cc037][37]

学到目前(这张列表会逐渐增加的)，我给大家的建议是：你一旦写了一个类，你给它三个函数**default constructor**\ **virtual destructor**\ **copy construct**，不管你有没有用。
（自己再加一个，子类继承父类一定要记得在初始化列表添加父类以便父类的构造函数能被执行）


###28 static与静态对象

> static在C有两种不同的用法...，在C++会更复杂，因为我们有成员变量和成员函数（吐血中。。。。）

static在C++的用法：

![cc038][38]

static free functions：~~限制在本文件~~(过时了)
static global variables：~~限制在本文件~~(过时了)
static local variables：Persistent storage 持久存储
static member variables：Shared by all instances(在所有的对象间共享)
static member functions：Shared by all instances，can only access static member variables(静态函数在所有的对象之间共享(没有意义，函数本来就不属于对象)，只能访问静态的成员变量)


####一个类的对象是static


static意味着持久存储：C：全局变量和malloc出来的东西；C++除了函数，还有对象，对象和对象之间还能够存在的东西是persistent，第二种persistent的东西是对一个类来说，不管它有多少个对象，在不同的对象之间它都存在都不变，或者说都一样的去变。


类里面的static成员变量是一个声明(和extern一样)，那么你还有让他有body，所以还要：int A::i;而且初始化列表不能去初始化静态成员变量。内部的实现机制就是把这个变量做成全局变量，然后你在类的对象都有指向这个变量的指针


###30 运算符重载--基本规则

> Overloaded operators

![cc039][39]
只能对一个类或一个枚举类型做重载运算符，也就是是说你不能凭空去重载一个运算符，你可以自己定义一个类，然后定义它们之间加法要怎么做，这是可以的。

保持原有的操作数的个数和优先级，比如原来加法是两个

运算符重载实际上就是把运算符的运算用你写的函数表达出来：operator receive 
![cc040][40]
![cc041][41]

![cc043][43]
![cc042][42]

![cc044][44]
![cc045][45]
![cc046][46]

运算符重载时到底选择成员还是非成员呢？我们的Tips是：

![cc047][47]

* 单目的应该做成成员的
* = () [] -> ->* 必须做成成员的
* 赋值操作应该做成成员的
* **所有其他二元操作都做成非成员的**(二元运算是由两个元素形成第三个元素的一种规则)



###31 运算符重载--原型

...(再看一遍)

Operator [] 

###32 运算符重载--赋值

> 类之间的相等是由系统默认的类的赋值运算Assignment Operator（Memberwise）来执行

将拷贝构造函数的时候我们一直在讲，初始化和赋值在C++是不一样的：

    MyType b;
    MyType a = b;
    a = b;
第一行叫拷贝构造；第二行叫赋值，对象之间进行成员层面上的Copy(Memberwise assignment)，如果成员变量存在指针，就会导致两个指针指向同一个地址，析构时会发生错误。如果确实需要用到`a = b`，那么需要如何处理？那么这时候就需要对`=`运算符进行重载：

![cc048][48]

`if( this != &rhs )`为什么一定要有这句？先考虑下面这个问题你就知道了：

一般的指针的拷贝操作是这样的：

![cc049][49]

`delete p`：为什么要有这句，有人会说直接strcpy不就可以了吗？不可以的，想得太简单了，如果that.p的空间非常大，p指向的空间非常小，那就放不下了，如果that.p的空间非常小，又会造成资源的浪费，所以需要先`delete p`重新申请空间。

知道了`delete p`必须做之后，我们考虑如果是`两个指针指向同一块内存，如a =a `会这么样？显然到了`p = new [strlen(that.p)+1]`会出错。所以标准写法一定要`if( this != &rhs )`。

**总结--Assignment Operator**

![cc050][50]

如果类里面涉及到**动态分配内存**你需要自己写赋值运算符的重载函数，如果里面没有指针的，你可以用系统默认的Assignment Operator(memberwise)


###33 运算符重载--类型转换

运算符重载当中的**又**一个特殊的例子，有时候我们希望我们做的类是用来表达一些值的，value class。这个类的作用是表达一些值的，比如说基本元素类型复数字符串等

关于类型转换有以下几种情况：



* 当你有一个类A有一个构造函数，这个函数的参数是一个类B的类型；那么你可以用类A来获取一个类B的对象
* 当一个类的构造函数只有一个参数的时候编译器自动做类型转换
* 用来做类型转换的运算符

###34 模板Template1

函数模板

类模板

template模板函数

template模板类

声明和定义：Declarations and Definitions

什么时候定义：编译器来定义，模板的作用就是告诉编译器你要替我做出什么样的函数出来



###35 模板Template2


###36 异常Exceptions基本概念

你去调任何函数都应该去判断返回值，如下，这是一个好的代码。但是它有一个大问题，它把异常值和正常值放在了一起。

![cc054][54]

我们希望这两件事分开--异常处理机制

![cc055][55]

###37 异常的抛出和捕捉

异常情况出现的时候抛出一个异常**给更上层的人**，让他出面解决这个问题。keyword：**throw** **catch**，而且应该扔出有用的东西。扔出去的东西放哪里？

###38 异常语句

###39 流的概念

###40 流的运算符

###41 STL简介

容器Containers(做成**类模板**)、算法Algorithms(做成**函数模板**)、枚举器Iterators

![cc057][57]

最主要会用到的三个是map\vector\list

如何使用

![cc058][58]

![cc059][59]

![cc060][60]








--------------


[1]: https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc002.jpg
[2]: https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc004.jpg
[3]: https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc005.jpg
[4]: https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc006.jpg
[5]: https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc007.jpg
[6]: https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc009.jpg
[10]:https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc010.jpg
[11]:https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc011.jpg
[12]:https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc012.jpg
[13]:https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc013.jpg
[14]:https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc014.jpg
[15]:https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc015.jpg
[16]:https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc016.jpg
[17]:https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc017.jpg
[18]:https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc018.jpg
[19]:https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc019.jpg
[20]:https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc020.jpg
[21]:https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc021.jpg
[22]:https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc022.jpg
[23]:https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc023.jpg
[24]:https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc024.jpg
[25]:https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc025.jpg
[26]:https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc026.jpg
[27]:https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc027.jpg
[28]:https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc028.jpg
[29]:https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc029.jpg
[30]:https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc030.jpg
[31]:https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc031.jpg
[32]:https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc032.jpg
[33]:https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc033.jpg
[34]:https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc034.jpg
[35]:https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc035.jpg
[36]:https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc036.jpg
[37]:https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc037.jpg
[38]:https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc038.jpg
[39]:https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc039.jpg
[40]:https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc040.jpg
[41]:https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc041.jpg
[42]:https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc042.jpg
[43]:https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc043.jpg
[44]:https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc044.jpg
[45]:https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc045.jpg
[46]:https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc046.jpg
[47]:https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc047.jpg
[48]:https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc048.jpg
[49]:https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc049.jpg
[50]:https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc050.jpg
[51]:https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc051.jpg
[52]:https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc052.jpg
[53]:https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc053.jpg
[54]:https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc054.jpg
[55]:https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc055.jpg
[56]:https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc056.jpg
[57]:https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc057.jpg
[58]:https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc058.jpg
[59]:https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc059.jpg
[60]:https://raw.githubusercontent.com/TongxinV/GFM-i-GitUse/master/1.0/cc060.jpg


