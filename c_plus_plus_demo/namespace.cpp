#include <stdio.h>

// 为了解决合作开发时的命名冲突问题，C++ 引入了命名空间（Namespace）的概念。
// 将类定义在命名空间中
namespace Diy
{
    class Student
    {
    public:
        char *name;
        int age;
        float score;

    public:
        void say() { printf("%s age is: %d, score is %f\n", name, age, score); }
    };
}
int main()
{
    Diy::Student stu1; //:: 是一个新符号，称为域解析操作符，在C++中用来指明要使用的命名空间。
    stu1.name = "Blend";
    stu1.age = 15;
    stu1.score = 92.5f;
    stu1.say();
    return 0;
}