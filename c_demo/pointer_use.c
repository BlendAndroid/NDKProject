#include <stdio.h>
#include "./include/io_utils.h"

int IsBigEndian()
{
    // 使用union，使用同一块存储内存
    union
    {
        char c[2]; // char是一个字节
        short s;   // 占用两个字节，十六进制0x100转换为二进制1 00000000
    } value = {.s = 0x100};

    PRINT_INT(value.c[0]);
    PRINT_INT(value.c[1]);
    return value.c[0] == 1;
}

// 同样是利用char,占用一个字节
int IsBigEndian2()
{
    short s = 0x100;
    PRINT_HEX(&s);
    char *p = (char *)&s; // 将s强制转换成char指针,我的理解是,p本身的地址和s是一样的,从打印的日志就能看出,但是p的内容,*p就要符合char的一个字节
    PRINT_HEX(p);
    PRINT_INT(*p);
    return *p == 1;
}

// 大端序一般用于网络传输，和网络协议有关系
// 小端序一般用于CPU计算
int main(void)
{
    PRINT_INT(IsBigEndian());
    PRINT_INT(IsBigEndian2());
    return 0;
}