#include <iostream>
#include <string.h>

using namespace std;

/**
 * - 构造函数：先调用父类的构造函数，再调用成员变量的构造函数，最后调用自己的构造函数。
 * - 析构函数：先调用自己的析构函数，再调用成员变量的析构函数，最后调用父类的析构函数。
 *
 *  当在继承中，如果父类的成员和子类的成员属性名称相同，我们可以通过作用域操作符来显式的使用父类的成员，如果我们不使用作用域操作符，默认使用的是子类的成员属性。
 */

class Parent
{
protected:
    char *str;
    int i;

public:
    Parent(char *str)
    {
        if (str != NULL)
        {
            this->str = new char[strlen(str) + 1];
            strcpy(this->str, str);
        }
        else
        {
            this->str = NULL;
        }
        cout << "Parent(char *str)..." << endl;
    }

    void print()
    {
        cout << "Parent print:" << i << endl;
    }

    ~Parent()
    {
        if (this->str != NULL)
        {
            delete[] this->str;
            this->str = NULL;
        }
        cout << "~Parent()..." << endl;
    }
};

class Child : public Parent
{
private:
    char *name;
    int age;
    int i = 0;

public:
    /* 在构造子类对象时，调用父类的构造函数 */
    Child() : Parent(NULL)
    {
        this->name = NULL;
        this->age = 0;
        cout << "Child()..." << endl;
    }
    /* 在构造子类对象时，调用父类的构造函数 */
    Child(char *name, int age) : Parent(name)
    {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        cout << "Child(char *name, int age)..." << endl;
    }
    ~Child()
    {
        if (this->name != NULL)
        {
            delete[] this->name;
            this->name = NULL;
        }
        cout << "~Child()..." << endl;
    }

    void test()
    {
        /* 使用父类的同名成员 */
        Parent::i = 10;
        /* 使用子类的同名成员 */
        i = 100;
    }
    void print()
    {
        cout << "Parent:" << Parent::i << ","
             << "Child:" << i << endl;
    }
};

int main()
{
    Child c1;
    Child c2((char *)"BlendAndroid", 22);

    c2.test();

    c2.print();

    /* 用子类对象初始化父类对象 */
    Parent p1 = c2;
    p1.print();
    /* 父类指针直接指向子类对象 */
    Parent *p2 = &c2;
    p2->print();
    /* 父类对象直接引用子类对象 */
    Parent &p3 = c2;

    return 0;
}