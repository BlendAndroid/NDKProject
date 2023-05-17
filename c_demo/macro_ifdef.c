#include <stdio.h>
#include <stdarg.h>

// 单行宏函数 最好用括号括起来，因为在编译期就会被替换掉，因为这个参数可能是一个表达式
#define MAX(a, b) (a) > (b) ? (a) : (b)

// 定义多行宏  最后的\ 代表换行
#define IS_HEX_CHARACTER(ch)            \
    ((ch) >= '0' && (ch) <= '9') ||     \
        ((ch) >= 'A' && (ch) <= 'F') || \
        ((ch) >= 'a' && (ch) <= 'f')

// 普通函数 在调用之前会计算值
int Max(int a, int b)
{
    return a > b ? a : b;
}

// 条件编译
/*
 * 1. #ifdef 如果定义了
 * 2. #ifndef 如果没定义
 * 3. #if 如果 ...
 *
 * #endif
 *
 *  //#if defined(MACRO) 等价于 #ifdef MACRO
 *  #if defined(MACRO) ==> #ifdef MACRO
 */

// 条件编译判断C和C++
#ifdef __cplusplus
extern "C"
{
#endif
    //.....
    int Add(int left, int right);
#ifdef __cplusplus
};
#endif

// 这里定义了宏DEBUG
#define DEBUG 1

// 条件编译判断宏DEBUG，如果成功输出message信息
void dump(char *message)
{
#ifdef DEBUG
    puts(message);
#endif
}

// 定义换行的print，分别定义函数和宏
// 函数变长参数定义
void Printlnf(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    printf("\n");
    va_end(args);
}

// 宏
//  在C语言中可以这样写： "Hello ""world" ==> "Hello world"，所以"format"\n" == format 后面直接加"\n"
// __VA_ARGS__：获取变长参数
// ##__VA_ARGS__，变长参数可为空
// __FILE__：所在的文件
// __LINE__：所在的代码行号
// __FUNCTION__：所在的函数
#define PRINTLNF(format, ...) printf("("__FILE__               \
                                     ":%d) %s : " format "\n", \
                                     __LINE__, __FUNCTION__, ##__VA_ARGS__)

// 在宏中，参数前面加#，可以直接把参数变成相应的字符串
#define PRINT_INT(value) PRINTLNF(#value ": %d", value)

int main(void)
{
    int max = MAX(1.0, 3);
    int max2 = MAX(1, MAX(3, 4));

    int max3 = Max(1, Max(3, 4));

    // 这里的宏是不行的，替换回来就是(max++) > (5) ? (max++) : (5)，max++被执行了两次，就会有问题
    int max4 = MAX(max++, 5);

    printf("max2: %d\n", max2);

    // true就是1
    printf("is A a hex character? %d\n", IS_HEX_CHARACTER('A'));

    dump("DEBUG output!");

    // 条件编译判断C的版本
#if __STDC_VERSION__ >= 201112
    puts("C11!!");
#elif __STDC_VERSION__ >= 199901
    puts("C99!!");
#else
    puts("maybe C90?");
#endif

    int value = 2;
    Printlnf("Hello World! %d", value);

    PRINT_INT(value);
    return 0;
}