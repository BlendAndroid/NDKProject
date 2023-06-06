#include <iostream>
using namespace std;
/**
 * 在 C++ 中，模板分为函数模板和类模板两种, 其中的 typename 关键字也可以用class 关键字替换。
 */

template <class T>
void Swap(T &x, T &y)
{
    T tmp = x;
    x = y;
    y = tmp;
}

template <class T>
T Inc(int n)
{
    return 1 + n;
}

/***********************************************************************************/

template <typename T>
class A
{
public:
    A(T t)
    {
        this->t = t;
    }

    T &getT()
    {
        return t;
    }

protected:
public:
    T t;
    static T m_t; // 这样是不能进行初始化的
};

// 静态成员初始化只能放在外面
template <class T>
T A<T>::m_t = 0;

// 继承中的类模板的写法
class B : public A<int>
{
public:
    B(int i) : A<int>(i)
    {
    }

    void printB()
    {
        cout << "A:" << t << endl;
    }

protected:
private:
};

// 从模板类派生模板类
template <typename T>
class C : public A<T>
{

public:
    C(T c, T a) : A<T>(a)
    {
        this->c = c;
    }
    void printC()
    {
        cout << "c:" << c << endl;
    }

protected:
    T c;

private:
};

// 模板与上继承
// 怎么样从基类继承
// 若基类只有一个带参数的构造函数,子类是如何启动父类的构造函数
void pintBB(B &b)
{
    b.printB();
}
void printAA(A<int> &a) // 类模板做函数参数
{
    a.getT();
}

int main()
{
    int a = 1, b = 2;
    Swap(a, b);
    cout << "a: " << a << ", b:" << b << endl;

    // Inc(4)指明了此处实例化的模板函数原型应为：double Inc(double);
    // 编译器不会因为实参 4 是 int 类型，就生成原型为 int Inc(int) 的函数。因此，上面程序输出的结果是2.5 而非 2。
    cout << Inc<double>(4) / 2 << endl;

    B B_b(55);
    B_b.m_t++;

    B_b.printB();

    C<int> C_c(66, 77);
    C_c.printC();
    C_c.m_t++;

    // 类模板的实现机制是通过二次编译原理实现的。c++编译器并不是在第一个编译类模板的时候就把所有可能出
    // 现的类型都分别编译出对应的类（太多组合了），而是在第一个编译的时候编译一部分，遇到泛型不会
    // 替换成具体的类型（这个时候编译器还不知道具体的类型），而是在第二次编译的时候再将泛型替换成
    // 具体的类型（这个时候编译器知道了具体的类型了）。由于类模板的二次编译原理再加上static关键字修
    // 饰的成员，当它们在一起的时候实际上一个类模板会被编译成多个具体类型的类，所以，不同类型的类
    // 模板对应的static成员也是不同的（不同的类），但相同类型的类模板的static成员是共享的（同一个类）。
    cout << "A<int>::m_t: " << A<int>::m_t << endl;
    cout << "A<float>::m_t: " << A<float>::m_t << endl;

    return 0;
}