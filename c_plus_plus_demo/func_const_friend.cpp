#include <iostream>
#include <math.h>

using namespace std;

/**
 * C++类对象中的成员变量和成员函数是分开存储的
 * 成员变量：
 * 普通成员变量：存储于对象中，与struct变量有相同的内存布局和(字节对齐)方式
 * 静态成员变量：存储于全局数据区中
 * 成员函数：存储于代码段中。
 */

/**
 * 函数是指在函数声明中使用 `const` 限定符的成员函数，表示该函数不会修改类中的任何数据成员。常函数可以保证在调用过程中不会对数据成员进行修改，
 * 从而确保了安全性和可靠性。
 * 在常函数中，不能修改类中的任何数据成员，包括普通数据成员和常数据成员，否则会导致编译错误。因此，常函数通常适用于查询类函数，而不适用于修改类函数。
 *
 * 常函数只能调用常函数。
 * 常函数能被所有函数调用，包括非常函数。
 *
 * 1） 如果一个变量已被声明为常变量，只能用指向常变量的指针变量指向它，而不能用一般的（指向非const型变量的）指针变量指向它。
 * 2） 指向常变量的指针变量除了可以指向常变量外，还可以指向未被声明为const的变量。此时不能通过此指针变量改变该变量的值。
 * 3） 如果函数的形参是指向非const型变量的指针，实参只能用指向非const变量的指针，而不能用指向const变量的指针。
 */
class Example
{

public:
    // 这种方式的初始化，叫做初始化列表
    Example(int value, int const_value) : m_value(value), m_const_value(const_value) {}

    Example(int const_value) : m_const_value(const_value) {}

    // 拷贝构造函数
    Example(const Example &other) : m_value(other.m_value), m_const_value(other.m_const_value), friend_value(other.friend_value) {}

    int getValue()
    {
        return this->m_value;
    }

    int getConstValue() const
    {
        return this->m_const_value;
    }

    // const 函数重载
    int getOpe() const
    {
        return this->m_const_value + this->m_value;
    }

    int getOpe()
    {
        return this->m_const_value * this->m_value;
    }

private:
    int m_value;
    // 常成员变量只能通过初始化列表来进行初始化
    const int m_const_value;

    int friend_value;
};

// 友元类和友元函数

class MyClass
{

    // 将FriendClass设置为MyClass的好朋友，就能叫好朋友访问私有变量了
    friend class FriendClass;

private:
    int value = 0;
};

class FriendClass
{
private:
    MyClass myClass;

public:
    FriendClass(MyClass myClass)
    {
        this->myClass = myClass;
    }

    void visit()
    {
        cout << "friend_value " << this->myClass.value << endl;
    }
};

void visit(MyClass *myClass)
{
    // cout << "friend_value " << myClass->value << endl; // 私有的，访问不到
}

/*******************************友元函数*******************************************************/

class Point; // 生命Point类，但是先不实现

class Circle
{
public:
    float getArea(Point &p1, Point &p2); // 声明计算面积的成员函数
private:
    const float PI = 3.14;
};

class Point
{
    // 声明类Circle的成员函数getArea()为友元函数，这样circle就能访问Point的_x和_y
    friend float Circle::getArea(Point &p1, Point &p2);

public:
    Point(float x, float y);
    ~Point();

private:
    float _x;
    float _y;
};

Point::Point(float x = 0, float y = 0) : _x(x), _y(y) // 实现Point类的构造函数
{
    cout << "init Point" << endl;
}

Point::~Point() {}

float Circle::getArea(Point &p1, Point &p2)
{
    double x = std::abs(p1._x - p2._x); // 获取横轴坐标间的距离
    float y = std::abs(p1._y - p2._y);  // 获取纵轴坐标间的距离
    float len = sqrtf(x * x + y * y);   // 计算两个坐标点之间的距离
    cout << "Point1 and Point2 is: " << len << endl;
    return len * len * PI; // 友元函数访问私有成员变量PI
}

int main()
{
    Example e(2, 3);
    cout << "const_value: " << e.getConstValue() << endl;
    cout << "getOpe: " << e.getOpe() << endl;

    // 这里是const修饰的，所以会调用const函数
    const Example e_const(2, 3);
    cout << "getOpe: " << e_const.getOpe() << endl;

    // 在C++中，整型变量的初始值取决于它在哪里被定义。如果整型变量是全局变量或者是静态变量，则它的初始值默认为0。
    // 如果它是局部变量，则未初始化的整型变量的初始值是未定义的，也就是说，它的值是不确定的。
    const Example e_const1(7);
    cout << "const_value: " << e_const1.getConstValue() << endl;
    // cout << "getValue: " << e_const1.getValue() << endl; //只能调用const函数

    MyClass myClass;
    FriendClass friendClass(myClass);
    friendClass.visit();

    Point p1(5, 5);
    Point p2(10, 10);
    Circle circle;
    float area = circle.getArea(p1, p2);
    cout << "circle area is: " << area << endl;
    return 0;
}
