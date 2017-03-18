#include <iostream>

using namespace std;


class A
{
public:
    A(int i){ cout << "A"; }
    ~A(){}
};

class B {
public:
    B(int j){ cout << "B"; }
    ~B(){}
};

class C {
public:
    C(int k){ cout << "C"; }
    ~C(){ cout << "~C";  }
};

class D:public C
{
public:
    D(int i, int j,int k):a(i),b(j),C(k)
    {
        cout<<"D";
    }

    ~D(){ cout << "~D";}
private:
    B b;
    A a;
};



//int main(int argc, char** argv)
int main()
{
    C *pc = new D(1,2,3);
    delete pc;

    return 0;
}
