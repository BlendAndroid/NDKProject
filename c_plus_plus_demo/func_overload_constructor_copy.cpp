#include <iostream>

using namespace std;

// 1. 函数的默认参数
// 2. 函数的重载

// 函数可以为形参分配默认参数，这样当在函数调用中遗漏了实际参数时，默认参数将传递给形参。
// 函数默认参数通常设置在函数原型中
void displayStars(int starsPerRow = 10, int numRows = 1);

void test(int a, int b = 10)
{
    cout << "int a: " << a << "  int b: " << b << endl;
}

void test(int a)
{
    cout << "int a: " << a << endl;
}
void test(int &a)
{ // int 和int &冲突的
    cout << "int&  a: " << a << endl;
}

// typedef 还可以用于定义复杂的类型别名
typedef void (*myFuncTest)(int a, int b);
typedef void (*myFuncTest1)(int a);
typedef void (*myFuncTest2)(int &a);

class Test
{
private:
    int x;

public:
    Test(int x)
    {
        this->x = x;
        cout << "Test(int x) is Created" << endl;
    }

    Test()
    {
        x = 0;
        cout << "Test() is Created" << endl;
    }

    // this，只有用对象调用时，才会调用this
    void init(int x)
    {
        this->x = x;
        cout << "init(int x) function " << endl;
    }

    // 拷贝构造函数，也是函数
    Test(const Test &a)
    {
        cout << "Test(const Test &a) function " << endl;
        this->x = a.x;
    }

    // 析构函数只有一个
    ~Test()
    {
        cout << "~Test()" << endl;
    }

    int GetX()
    {
        return x;
    }
};

// 全局函数
Test p()
{
    Test c(4);
    return c;
}

int main()
{

    displayStars(); // starsPerRow & numRows use defaults (10 & 1)
    cout << endl;
    displayStars(5); // starsPerRow 5. numRows uses default value 1
    cout << endl;
    displayStars(7, 3); // starsPerRow 7. numRows 3. No defaults used.

    cout << "****************************************************" << endl;

    // 直接调用是没有办法区分重载的，需要用函数指针来确定
    // test(666);

    // 区分重载
    myFuncTest func = test;
    func(100, 20);

    myFuncTest1 fun1 = test;
    fun1(100);

    myFuncTest2 fun2 = test;
    int a = 555;
    int &f = a;
    fun2(f);

    cout << "****************************************************" << endl;

    // 构造函数与析构函数

    Test test1(10); // 括号法

    Test test2 = 10; // 隐式法
    test2.init(20);

    Test person = Test(30); // 显示法

    cout << "****************************************************" << endl;

    // 拷贝构造函数的调用时机

    // 第一个场景: 用对象test1初始化对象testCopy1:
    Test testCopy1 = test1;

    // 第二个场景: 用对象a初始化对象b
    Test testCopy2(testCopy1);

    // 第一个场景和第二个场景是一样的,用一个对象初始化另一个对象

    cout << "**testCopy3**" << endl;

    // 第三个场景: 函数返回一个匿名对象
    // 在这里，是不会发生构造函数复制的，原因是gcc编译器做了优化
    Test testCopy3 = p();
    cout << testCopy3.GetX() << endl;

    return 0;
}

void displayStars(int starsPerRow, int numRows)
{
    for (int row = 1; row <= numRows; row++)
    {
        for (int star = 1; star <= starsPerRow; star++)
            cout << '*';
        cout << endl;
    }
}

/**
 * 函数重载几个特别的事列：
 * 1)
 *     void print();
 *     int print(); //不算重载，直接报错
 *
 * 2) void print(int x);
 *    void print(const int x); //不算重载，直接报错重定义
 *
 * 3) void print(int *x);
 *    void print(const int *x); //算重载，执行正确，实参为const int *时候调用这个，为int* 的时候调用上面一个
 *
 *    void print(int &x);
 *    void print(const int &x); //算重载，执行正确，实参为const int &时候调用这个，为int& 的时候调用上面一个
 *
 * 4) void print();
      void print() const; //算重载。const对象或const引用const指针调用时调用这个函数，普通对象或普通引用调用时调用上面一个。
 */