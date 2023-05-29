#include <stdio.h>
#include "./include/io_utils.h"
#include "./include/time_utils.h"
#include <time.h>

int main()
{
    time_t current_time;
    // 传入current_time的地址
    time(&current_time);
    PRINT_LONG(current_time);

    // 或者这样写
    current_time = time(NULL);
    PRINT_LONG(current_time);

    // 获取时间戳
    PRINT_LLONG(TimeInMillisecond());

    return 0;
}