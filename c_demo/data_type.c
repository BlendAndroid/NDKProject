#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

// _Bool是整数类型（更准确地说是无符号整型），所以_Bool变量实际上就是整型变量；但是和一般的整型不同，
// _Bool只能赋值为0或1。一般来说，往_Bool变量中存储非零值会导致变量赋值为1
// <stdbool.h>头还提供了true和false两个宏，分别代表1和0

// 整数类型又分为两大类：有符号型和无符号型。

// 读写无符号整数时，使用字母u、o或x代替转换说明中的d。u表示将以十进制形式读写，o表示八进制形式，而x表示十六进制形式。
// 读写短整数时，在d、o、u或x前面加上字母h。
// 读写长整数时，在d、o、u或x前面加上字母l。

void LocalStaticVar(void)
{
    // 静态变量
    // 1. 作用域全局，内存不会因函数退出而销毁
    // 2. int 初值默认为 0
    static int static_var;

    // 自动变量
    // 1. 函数、块作用域，随着函数和块退出而销毁
    // 2. 没有默认初值
    int non_static_var;

    printf("static var: %d\n", static_var++);
    printf("non static var: %d\n", non_static_var++);
}

void HandleVarargs(int arg_count, ...)
{
    // 1. 定义 va_list 用于获取我们变长参数
    va_list args;

    // 2. 开始遍历
    va_start(args, arg_count);
    for (int i = 0; i < arg_count; ++i)
    {
        // 3. 取出对应参数，(va_list, type)
        int arg = va_arg(args, int);
        printf("%d: %d\n", i, arg);
    }

    // 4. 结束遍历
    va_end(args);
}

int main(void)
{
    _Bool flag = 1;

    bool flag_bool = 1;

    // 1）float数据类型表达的是一个近似的数，不是准确的，小数点后的n位有误差，浮点数的位数越大，误差越大，到8位的时候，误差了1，基本上不能用了。
    // 2）用“==”可以比较两个整数或字符是否相等，但是，看起来相等的两个浮点数，就是不会相等。
    float ff2 = 9.9; // 测试2位的浮点数
    printf("ff2=%f\n", ff2);
    if (ff2 == 9.9)
        printf("ff2==9.9\n");

    float ff5 = 99.999; // 测试5位的浮点数
    printf("ff5=%f\n", ff5);
    if (ff5 == 99.999)
        printf("ff5==99.999\n");

    float ff6 = 999.999; // 测试6位的浮点数
    printf("ff6=%f\n", ff6);
    if (ff6 == 999.999)
        printf("ff6==999.999\n");

    float ff7 = 9999.999; // 测试7位的浮点数
    printf("ff7=%f\n", ff7);
    if (ff7 == 9999.999)
        printf("ff7==9999.999\n");

    float ff8 = 99999.999; // 测试8位的浮点数
    printf("ff8=%f\n", ff8);
    if (ff8 == 99999.999)
        printf("ff8==99999.999\n");

    LocalStaticVar();

    //这里不进行类型校验，需要自己把握类型
    HandleVarargs(4, 1, 2, 3, 4);

    return 0;
}