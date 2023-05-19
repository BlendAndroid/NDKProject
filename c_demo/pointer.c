#include <stdio.h>
#include "./include/io_utils.h"

void point_const();
void point_array();
void max_min(int[], int, int *, int *); // 声明
int *max_func(int *, int *);

// 如果变量需要大量的存储空间，那么传递变量的值会浪费时间和空间
int main(void)
{
    int a = 10;
    // 定义int类型的指针p，并把它指向a的地址
    int *p = &a;

    // 打印出地址
    PRINT_HEX(p);
    PRINT_HEX(&a);

    PRINT_INT(sizeof(int *));

    point_const();

    point_array();

    int array[] = {0, 1, 2, 3, 4, 5, 6};
    int max;
    int min;
    // 取地址，定义
    max_min(array, 7, &max, &min);
    PRINT_INT(max);
    PRINT_INT(min);

    // 接受的类型也是一个指针
    int *maxFunc = max_func(&max, &min);
    PRINT_INT(*maxFunc);

    return 0;
}

/**
 * const 是C语言的一个关键字，需要注意的是，const 关键字是把变量变为一个只读的变量（也就是不可以作为左值），
 * 绝对不是将这个变量变为常量。也就是说经过const 修饰的变量成为只读的变量之后，那么这个变量就只能作为右值（只能赋值给别人），
 * 绝对不能成为左值（不能接收别人的赋值）。
 * 经过const 修饰的变量，在定义的时候，就要进行初始化。
 *
 *
 * 其实就看 const 的位置。const，在指针的星号之前，那么就是指向const 的指针，也就是 *p 的内容是常量，不能被改变。
 * const 在星号之后的话，那么 ，就是指向 const 的指针，也就是这个指针指向的地址，不能被改变的，所以，const 指针就必须进行初始化，
 * 然后这个地址就是一直被固定住了，不能内改变的。
 *
 * const 是由编译器进行处理，执行类型检查和作用域的检查；
 * define 是由预处理器进行处理，只做简单的文本替换工作而已。
 */
void point_const()
{

    int a = 10;
    int c = 20;

    // 指向const的指针

    // b是一个指针，b指向的内容（*b）所指向的内容是const int类型的
    // b这个指针可以随便值，但是b的内容不能改变
    const int *b = &a;
    // 或者下面的这种也行
    int const *b1 = &a;

    // 指针可以指向c
    b = &c;

    // 但是内容是不能改变的，这个编译会报错
    // *b = 40;

    // const 指针
    // d是一个指针，只不过这个指针是const类型的，也就是这个指针的地址，在初始化之后就不能改变，但是指针的地址是可以改变的
    int *const d = &a;

    // 指针的内容可以改变
    *d = 40;

    // d指向的位置不能改变，错误提示是：表达式必须是可修改的左值，但是const指针是不可修改的值
    // d = &c;

    // 指针和内容都是不可变的
    // p是一个指针，但是这个p是一个指针常量，地址不能改变，但是对于*p而言，又有一个const修饰，又不能改变值
    const int *const p = &a;
    int const *const p1 = &a;

    PRINT_INT(*b);
    PRINT_INT(*d);
}

void point_array()
{
    // 这里的函数名字就是指针
    int array[] = {0, 1, 2, 3, 4, 5, 6};
    int *p = array;
    PRINT_INT(*p);
    PRINT_INT(*(p + 3));
    PRINT_INT(*(array + 3));
    PRINT_INT(array[3]);
    PRINT_INT(p[3]);

    // 输入反向，P指向数组的最后一位
    for (p = array + 7 - 1; p >= array; p--)
        PRINT_INT(*p);

    int array1[4] = {0};
    int *pa = array1;
    *pa = 1;
    *(pa++) = 3; // 因为这里pa++了，是献给*pa赋值为3，在++，所以pa就指向了数组中1的位置
    *pa = 2;
    *(pa + 2) = 4;
    PRINT_INT_ARRAY(array1, 4);
}

// 指针参数
void max_min(int a[], int n, int *max, int *min)
{
    int i;
    *max = *min = a[0];
    for (i = 1; i < n; i++)
    {
        if (a[i] > *max)
            *max = a[i];
        else if (a[i] < *min)
            *min = a[i];
    }
}

// 指针作为返回值，返回一个int类型的指针
int *max_func(int *a, int *b)
{
    if (*a > *b) // 比较内容，返回指针
    {
        return a;
    }
    else
    {
        return b;
    }
}

// 这样写是不对的，因为f一旦返回后，变量i就不存在了
// int *f(void)
// {
//  int i;
//  return &i;
// }
