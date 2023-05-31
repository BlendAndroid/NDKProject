#include <iostream>
using namespace std;

// 运算符重载
/**
 * 语法如下：
 *
 * 返回值类型 operator 运算符名称 (参数列表)
 * {
 *  ...//函数体
 * }
 */

class AA
{
public:
    AA();
    AA(double real, double imag);

public:
    // 声明运算符重载
    AA operator+(const AA &A) const;

    void display() const;

    // 运算符重载输出，声明为友元函数
    friend ostream &operator<<(ostream &os, const AA &a);

    // 重载==号码
    friend bool operator==(const AA &aa, const AA &bb);

private:
    double m_real; // 实部
    double m_imag; // 虚部
};

AA::AA() : m_real(0.0), m_imag(0.0) {}

AA::AA(double real, double imag) : m_real(real), m_imag(imag) {}

// 输出运算符重载
ostream &operator<<(ostream &os, const AA &a)
{
    os << "(" << a.m_imag << "," << a.m_real << ")";
    return os;
}

bool operator==(const AA &aa, const AA &bb)
{
    cout << "bool operator==" << endl;
    return aa.m_imag == bb.m_imag;
}

// 实现运算符重载
AA AA::operator+(const AA &A) const
{
    AA B;
    B.m_real = this->m_real + A.m_real;
    B.m_imag = this->m_imag + A.m_imag;
    return B;
}

void AA::display() const
{
    cout << m_real << " + " << m_imag << "i" << endl;
}

int main()
{
    AA c1(4.3, 5.8);
    AA c2(2.4, 3.7);
    AA c3;
    c3 = c1 + c2;
    c3.display();

    cout << c3 << endl;

    if (!(c1 == c2)) // 比较的是重载函数
    {
        cout << "aa" << endl;
    }

    return 0;
}