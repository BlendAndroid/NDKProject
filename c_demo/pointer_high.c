#include <stdio.h>
#include <stdlib.h>
#include "./include/io_utils.h"

#define PLAYER_COUNT 10

// C语言的数据结构通常是固定大小的。例如，一旦程序完成编译，数组元素的数量就固定了。
// 变长数组的长度在运行时确定，但在数组的生命周期内仍然是固定长度的。

/**
 * ·malloc函数——分配内存块，但是不对内存块进行初始化。
 * ·calloc函数——分配内存块，并且对内存块进行清零。
 * ·realloc函数——调整先前分配的内存块大小。
 */

// 定义链表
// 成员next具有struct node *类型，这就意味着它能存储一个指向node结构的指针。顺便说一下，关于名字node没有任何特殊含义，只是一个普通的结构标记
// 在结构有一个指向相同结构类型的指针成员时（就像node中那样），要求使用结构标记。没有node标记，就没有办法声明next的类型。
struct node
{
    int value;
    struct node *next;
};

// 为什么最后一行不能把 return new_node; 改成 list = new_node
// 因为：在调用点，会把first复制给list。（像所有其他参数一样，指针也是按值传递的）函数内的最后一行改变了list的值，使它指向了新的结点。但是，此赋值操作对first没有影响。
struct node *add_to_list(struct node *list, int n)
{
    struct node *new_node;
    new_node = malloc(sizeof(struct node));
    if (new_node == NULL)
    {
        printf("Error: malloc failed in add_to list\n");
        exit(EXIT_FAILURE);
    }
    new_node->value = n;
    new_node->next = list;
    return new_node;
}

// 指向指针的指针（指针是一种特殊的数据类型，它用于存储另一个变量的地址。）
// 指针的指针就是存储这个变量地址的指针，应当于一个变量能使用两个指针来表示
// 当函数的实际参数是指针变量时，有时候会希望函数能通过指针指向别处的方式改变此变量，也就是改变实际参数的指向
// 因为参数的传递，总是做一个临时的副本，如果想改变指针的指向，就需要指针的指针

// 让函数add_to_list修改first是可能的，但是这就要求给函数add_to_list传递一个指向first的指针
// 在这个例子中，定义的是struct node **list就是指针的指针，*list就是这个指针的指针的内容，改变了*list，其实就是改变了first（注意：first是一个指针）
// 而*list就是first，就是改变了first，其实就是把new_node的地址给传出来，传给了first，而*first就是拿到了这个地址的内容
// 一级指针只能操作first指向的变量的值，其本身在函数结束后，变量就会被销毁，不会影响first的值
void void_add_to_list(struct node **list, int n)
{
    struct node *new_node;
    new_node = malloc(sizeof(struct node));
    if (new_node == NULL)
    {
        printf("Error: malloc failed in add_to_list\n");
        exit(EXIT_FAILURE);
    }
    new_node->value = n;
    new_node->next = *list;
    *list = new_node;
}

struct node *read_numbers(void)
{
    struct node *first = malloc(sizeof(struct node));
    first->value = 0;
    first->next = NULL;
    int n;
    printf("Enter a series of integers (0 to terminate): ");
    for (;;)
    {
        scanf("%d", &n);
        if (n == 0)
            return first;
        // first = add_to_list(first, n);

        void_add_to_list(&first, n);

        PRINT_HEX(first);
        PRINT_INT(*first);
    }
    return first;
}

/****************************************************************************************************/

// 指向函数的指针（函数指针），毕竟函数占用内存单元，所以每个函数都有地址，就像每个变量都有地址一样。
// 函数的名字也是一个地址，就和数组的名字一样，数组名就是一个地址，所以函数名字也是一个地址。

// 这个是返回指针的函数，就是一个普通函数
int *(f1(int, double));

// 这个是函数指针
int (*f2)(int, double);

// 这个是函数指针，并且返回值也是一个指针
int *(*f3)(int, double);

int max(int x, int y)
{
    return x > y ? x : y;
}

// 生成随机数
int getNextRandomValue(void)
{
    return rand();
}

// size_t: unsigned int类型，无符号数
void rand_array(int *array, size_t arraySize, int (*getNextValue)(void))
{
    for (size_t i = 0; i < arraySize; i++)
    {
        array[i] = getNextValue();
    }
}

int main(void)
{
    // 动态分配数组内存大小
    int *players = calloc(PLAYER_COUNT, sizeof(int));
    // 判断是不是空指针，是player != NULL的缩写
    if (players)
    {
        for (int i = 0; i < PLAYER_COUNT; ++i)
        {
            players[i] = i;
        }
        PRINT_INT_ARRAY(players, PLAYER_COUNT);
    }

    players = realloc(players, PLAYER_COUNT * 2 * sizeof(int));
    PRINT_INT_ARRAY(players, PLAYER_COUNT * 2);

    // 内存释放
    if (players != NULL)
    {
        free(players);
    }

    // 定义链表
    struct node *first = read_numbers();

    while (first != NULL)
    {
        PRINT_INT(first->value);
        first = first->next;
    }

    // p是函数指针
    int (*p)(int, int) = &max; //&可以不用

    int d = p(4, 5);
    PRINT_INT(d);

    // 函数回调
    int array[10];
    rand_array(array, 10, getNextRandomValue);
    for (size_t i = 0; i < 10; i++)
    {
        PRINT_INT(array[i]);
    }

    return 0;
}