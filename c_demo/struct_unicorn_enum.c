#include <stdio.h>
#include "./include/io_utils.h"

#define ARRAY_SIZE 10
#define OP_PRINT_INT 0
#define OP_PRINT_DOUBLE 1
#define OP_PRINT_STRING 2

void struct_test();
struct Part build_part(int, int);
void union_test();
void enum_text();

/**
 * 结构是可能具有不同类型的值（成员）的集合。
 * 联合和结构很类似，不同之处在于联合的成员共享同一存储空间。这样的结果是，联合可以每次存储一个成员，但是无法同时存储全部成员。
 * 枚举是一种整数类型，它的值由程序员来命名。
 */
int main(void)
{
    struct_test();
    union_test();
    enum_text();
    return 0;
}

/********************************************************************************************/

// 声明了结构标记Part，而且还声明了变量part2
struct Part
{
    int number;
    int on_hand;
    char cc;
} part2, part4; // 这里的part2已经定义了变量，但是没有初始化，int默认值就是0，char就是空

// 结构体变量，要么在定义结构体的时候就初始化，要么在后面定义结构体变量的时候初始化
void struct_test()
{

    // 初始化式中的值必须按照结构成员的顺序进行显示
    struct Part part1 = {528, 10};

    // 也可以这样初始化，就不用跟随顺序了
    struct Part part3 = {.on_hand = 10, .number = 528};

    // 同一个类型的结构体，就能复制了，这里是真正的复制，包括数组
    part2 = part1; /* legal; both parts have the same type */

    // 这里重新改变part2的值，但是part1的值不变
    part2.number = 999;

    // 复合字面量赋值，这里赋值给part4，任何未初始化的成员默认值为0
    part4 = (struct Part){111, 222, 'A'};

    PRINT_INT(part1.number);
    PRINT_INT(part2.number);
    PRINT_CHAR(part2.cc);
    PRINT_INT(part4.number);

    // 用typedef来定义真实的类型名
    // 注意，类型Part的名字必须出现在定义的末尾
    // typedef struct也可以加上标记，比如typedef struct PartType，这里就是定义了结构标记Part
    typedef struct
    {
        int number;
        char name[ARRAY_SIZE];
        int on_hand;
    } PartType;

    PartType part_type = {20, "Blend", 10};
    PRINT_CHAR_ARRAY(part_type.name, 11);

    // 接收返回值是结构体
    struct Part build = build_part(1, 2);
}

// 返回一个结构体
struct Part build_part(int number, int on_hand)
{
    struct Part p;
    p.number = number;
    p.on_hand = on_hand;
    return p;
}

/********************************************************************************************/

// 联合体的使用说明
typedef union Operand
{
    int int_operand;       // 4
    double double_operand; // 8
    char *string_operand;  // 8
} Operand;

typedef struct Instruction
{
    int operator;
    Operand operand;
} Instruction;

void Process(Instruction *instruction)
{
    //->是指针取值的时候
    switch (instruction->operator)
    {
    case OP_PRINT_INT:
        PRINT_INT(instruction->operand.int_operand);
        break;
    case OP_PRINT_DOUBLE:
        PRINT_DOUBLE(instruction->operand.double_operand);
        break;
    case OP_PRINT_STRING:
        puts(instruction->operand.string_operand);
        puts("output");
        break;
    default:
        fprintf(stderr, "Unsupported operator: %d\n", instruction->operator);
    }
}

// 联合（union）也是由一个或多个成员构成的，而且这些成员可能具有不同的类型。
// 但是，编译器只为联合中最大的成员分配足够的内存空间。
// 联合的成员在这个空间内彼此覆盖。这样的结果是，给一个成员赋予新值也会改变其他成员的值。
void union_test()
{
    // 用联合来节省空间，book/mug/shirt每次只能存在一个
    struct catalog_item
    {
        int stock_number;
        double price;
        int item_type;
        union
        {
            struct
            {
                char title[10];
                char author[10];
                int num_pages;
            } book;
            struct
            {
                char design[10];
            } mug;
            struct
            {
                char design[10];
                int colors;
                int sizes;
            } shirt;
        } item;
    };

    // 用联合来构造混合的数据结构
    typedef union
    {
        int i;
        double d;
    } Number;

    Number number_array[10];
    number_array[0].i = 5;
    number_array[1].d = 3.14;

    // 具体的使用，用.操作符来赋值
    Instruction instruction = {
        .operator= OP_PRINT_STRING,
        .operand = {
            .string_operand = "Hello World!"}};

    Process(&instruction);
}

/********************************************************************************************/

// 在系统内部，C语言会把枚举变量和常量作为整数来处理
typedef enum FileFormatPart
{
    PNG,
    JPEG = 10,
    BMP = 20,
    UNKNOWN // 顺序赋值，就是21
} FileFormat;

void enum_text()
{
    // 枚举标记
    enum FileFormatPart file_format1;
    // typedef定义类型名
    FileFormat file_format2, file_format3;

    file_format1 = PNG;
    file_format2 = JPEG;
    file_format3 = UNKNOWN;

    PRINT_INT(file_format1);
    PRINT_INT(file_format2);
    PRINT_INT(file_format3);
}