#include <iostream>

// 使用命名空间
using namespace std;

// 定义结构体 Student
struct Student
{
    // 结构体包含的成员变量
    char *name;
    int age;
    float score;
};
// 显示结构体的成员变量
void display(struct Student stu)
{
    printf("%s age is: %d,score is: %f\n", stu.name, stu.age, stu.score);
}

class StudentClass
{
public:
    // 类包含的变量
    char *name;
    int age;
    float score;
    // 类包含的函数
    void say()
    {
        printf("%s age is: %d,score is: %f\n", name, age, score);
    }
};

// 通过结构体定义出来的变量还是叫变量，
// 而通过类定义出来的变量有了新的名称，叫做对象（Object）
int main()
{
    cout << "Hello, World!" << endl;

    struct Student stu1;
    // 为结构体的成员变量赋值
    stu1.name = "xiaoming";
    stu1.age = 15;
    stu1.score = 92.5;
    // 调用函数
    display(stu1);

    /**********************************************/

    // 通过类来定义变量，即创建对象
    class StudentClass stuClass; // 也可以省略关键字class
    // 为类的成员变量赋值
    stuClass.name = "xiaohai";
    stuClass.age = 15;
    stuClass.score = 92.5f;
    // 调用类的成员函数
    stuClass.say();
    return 0;
}