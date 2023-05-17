#include <stdio.h>
#include "./include/io_utils.h"

#define ARRAY_SIZE 10

// 文件作用域的初始化，默认是0
int global_array[ARRAY_SIZE];

int main(void)
{

    // 默认值是0
    for (int i = 0; i < ARRAY_SIZE; ++i)
    {
        // array[i] = i;
        PRINT_HEX(global_array[i]);
    }

    // 从第三个是2，第四个是l，第五个是l，第一个和第二个的值是0
    char array_char[5] = {[2] = 'o', 'l', 'l'};
    for (int i = 0; i < 5; ++i)
    {
        PRINT_CHAR(array_char[i]);
    }

    // 函数作用域，如果没有初始化，只是开辟了内容，则里面的值是不确定的
    int array[ARRAY_SIZE];
    int array_with_expression[3 + 2];
    PRINT_INT(array[0]);
    PRINT_INT(array[5]);

    // 打印字符串
    char string[] = "Hello World";

    for (int i = 0; i < 11; ++i)
    {
        PRINT_CHAR(string[i]);
    }
    // short %hd
    // NULL \0
    PRINTLNF("%s", string);

    char string_zh[] = "你好，中国";

    //打印中国会乱码
    PRINTLNF("%s", string_zh);

    // 宽字符
    wchar_t ws[] = L"你好，中国";

    PRINTLNF("%s", ws);

    return 0;
}