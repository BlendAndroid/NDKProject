#include <iostream>
using namespace std;

/**
 * 在 C++ 中，虚函数表（vtable）是用于支持多态性的一种机制，它是一组指针数组，存储了包含虚函数的类的虚函数地址。当一个对象被声明为指向基类的
 * 指针或引用类型时，通过虚函数表可以调用到对象所属的派生类中的虚函数。C++中实现多态性的方式是通过虚函数和虚函数表实现的。当一个类定义了虚函数
 * 时，编译器会在该类的虚函数表中添加一个指针，指向该类的虚函数地址。如果派生类重写了该虚函数，那么相应的虚函数地址也会被更新。当一个对象被声明
 * 为指向基类的指针或引用类型时，通过该对象的虚函数表可以找到该对象所属的派生类的虚函数地址，从而实现对派生类中虚函数的调用。需要注意的是，虚函
 * 数表是每个类单独维护的，它的大小与类中的虚函数数量和系统位数有关。在调用虚函数时，通过指向对象的指针或引用类型找到该对象的虚函数表，再通过虚
 * 函数表找到实际要调用的虚函数地址，最终进行函数调用。总之，虚函数表是用于支持多态性的一种机制，它存储了包含虚函数的类的虚函数地址，通过它可以
 * 实现对派生类中虚函数的调用。
 */

// 抽象类的定义： 称带有纯虚函数的类为抽象类。

/**
 * public继承：父类成员在子类中保持原有的访问级别（子类可以访问public和protected）。
 * private继承：父类成员在子类中变为private成员（虽然此时父类的成员在子类中体现为private修饰，但是父类的public和protected是允许访问的，因为
 * 是继承后改为private）。
 * protected继承：父类中的public成员会变为protected级别。父类中的protected成员依然为protected级别。父类中的private成员依然为private级别。
 *
 * 注意：父类中的private成员依然存在于子类中，但是却无法访问到。不论何种方式继承父类，子类都无法直接使用父类中的private成员。
 */

/**************************************************************************/
/**
 * 多继承中的二义性: C++为我们提供了虚继承这个概念，即B1和B2虚继承自A，则在构造A对象的时候，只创建一个A的对象。
 */
/* 类B */
class B
{
public:
    int a;
};

/* 虚继承自类B */
class B1 : virtual public B
{
    virtual void funtion1() = 0;
};

/* 虚继承自类B */
class B2 : virtual public B
{
};

/* 继承自B1,B2 */
class C : public B1, public B2
{
public:
    void funtion1()
    {
        cout << "funtion1" << endl;
    }
};

/**************************************************************************/

class VoidClass
{
    void BB()
    {
        cout << "VoidClass :: BB()" << endl;
    }
};

class CFather
{
public:
    virtual void AA() // 虚函数标识符
    {
        cout << "CFather :: AA()" << endl;
    }
    void BB()
    {
        cout << "CFather :: BB()" << endl;
    }
};

class CSon : public CFather
{
public:
    void AA()
    {
        cout << "CSon :: AA()" << endl;
    }
    void BB()
    {
        cout << "CSon :: BB()" << endl;
    }
};

int main()
{
    C c;
    c.a = 100;

    cout << c.B::a << endl;
    cout << c.B1::a << endl;
    cout << c.B2::a << endl;

    cout << "********************************" << endl;

    // 一个空类（没有成员变量和成员方法）的对象通常不会占用任何空间，但为了避免空对象的大小为零，编译器往往会在类的空对象上添加
    // 一个字节的大小，这样可以确保空对象的大小不为零，避免出现指针运算错误等问题。
    cout << sizeof(VoidClass) << endl; // 占用一个字节

    // 占用四个字节，空对象通常会占用一个指针（通常占用 4 到 8 个字节，具体取决于系统类型和指针位数），用于指向虚函数表（vtable），
    // 这个表存放了类的虚函数地址。
    cout << sizeof(CFather) << endl; // 测试加了虚函数的类

    // 让所有的类对象（主要是派生类对象）都可以执行纯虚函数的动作，但类无法为纯虚函数提供一个合理的默认实现
    c.funtion1();
    return 0;
}