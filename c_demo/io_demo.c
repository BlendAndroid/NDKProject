#include <stdio.h>
#include "./include/io_utils.h"
#include "./include/time_utils.h"
#include <errno.h>
#include <string.h>
#include <locale.h>

#define COPY_SUCCESS 0
#define COPY_ILLEGAL_ARGUMENTS -1
#define COPY_SRC_OPEN_ERROR -2
#define COPY_SRC_READ_ERROR -3
#define COPY_DEST_OPEN_ERROR -4
#define COPY_DEST_WRITE_ERROR -5
#define COPY_UNKNOWN_ERROR -100

#define BUFFER_SIZE 512

/**
 * C语言中，文本文件和二进制文件是两种不同的数据存储方式。
 * 文本文件是以字符为单位进行存储的，每个字符都有对应的ASCII码值。在读取或写入文本文件时，C语言会将这些ASCII码转换成相应的字符，并按照一定格式进行输出或输入。
 * 而二进制文件则是以字节为单位进行存储的，其中每个字节可以表示0到255之间任意一个整数。在读取或写入二进制文件时，C语言直接操作这些字节数据，并不会对其进行任何转换。
 * 因此，在处理文本内容较多、需要按照特定格式输出或输入时使用文本文件；而在处理图像、音频等非文本数据时使用二进制文件更加合适。
 */

void readFile()
{
    FILE *file = fopen("time.c", "r");
    if (file)
    {
        // C 库函数 int getc(FILE *stream) 从指定的流 stream 获取下一个字符（一个无符号字符），并把位置标识符往前移动。
        int next_char = getc(file);
        while (next_char != EOF)
        {
            // C 库函数 int putchar(int char) 把参数 char 指定的字符（一个无符号字符）写入到标准输出 stdout 中。
            putchar(next_char);
            next_char = getc(file);
        }
        fclose(file);
    }
    else
    {
        // C 标准库的 errno.h 头文件定义了整数变量 errno，它是通过系统调用设置的，在错误事件中的某些库函数表明了什么发生了错误。
        // 该宏扩展为类型为 int 的可更改的左值，因此它可以被一个程序读取和修改。
        PRINT_INT(errno);
        // C 库函数 char *strerror(int errnum) 从内部数组中搜索错误号 errnum，并返回一个指向错误消息字符串的指针。
        puts(strerror(errno));
        // C 库函数 void perror(const char *str) 把一个描述性错误消息输出到标准错误 stderr。首先输出字符串 str，后跟一个冒号，然后是一个空格。
        perror("fopen");
    }
}

void stdInOutErr()
{
    printf("Stdout Helo World!!\n");
    // printf其实就是向stdout中输出，和上面的等价
    fprintf(stdout, "Stdout Hello World!!\n");
    perror("Stderr Hello World!!"); // 这里会换行
    fprintf(stderr, "Stderr Hello World!!\n");
}

// 每次读取一个字符
int CopyFile(char const *src, char const *dest)
{
    if (!src || !dest)
    {
        return COPY_ILLEGAL_ARGUMENTS;
    }

    FILE *src_file = fopen(src, "rb");
    if (!src_file)
    {
        return COPY_SRC_OPEN_ERROR;
    }

    FILE *dest_file = fopen(dest, "wb");
    if (!dest_file)
    {
        fclose(src_file);
        return COPY_DEST_OPEN_ERROR;
    }

    int result;

    while (1)
    {
        int next = fgetc(src_file);
        // 在while循环中以EOF作为文件结束标志，这种以EOF作为文件结束标志的文件，必须是文本文件。在文本文件中，数据都是以字符的ASCII代码值的形式存放。
        // 我们知道，ASCII代码值的范围是0~127，不可能出现-1，因此可以用EOF作为文件结束标志。
        if (next == EOF)
        {
            // 若有错误，先判断错误
            if (ferror(src_file))
            {
                result = COPY_SRC_READ_ERROR;
            }
            // 判断是否是文件结束
            else if (feof(src_file))
            {
                result = COPY_SUCCESS;
            }
            else
            {
                result = COPY_UNKNOWN_ERROR;
            }
            break;
        }

        if (fputc(next, dest_file) == EOF)
        {
            result = COPY_DEST_WRITE_ERROR;
            break;
        }
    }

    fclose(src_file);
    fclose(dest_file);

    return result;
}

int CopyFile2(char const *src, char const *dest)
{
    if (!src || !dest)
    {
        // 参数至少有一个为 NULL
        return COPY_ILLEGAL_ARGUMENTS;
    }

    FILE *src_file = fopen(src, "r");
    if (!src_file)
    {
        // src 打开失败
        return COPY_SRC_OPEN_ERROR;
    }

    FILE *dest_file = fopen(dest, "w");
    if (!dest_file)
    {
        // dest 打开失败，记得关闭 src
        fclose(src_file);
        return COPY_DEST_OPEN_ERROR;
    }

    int result = COPY_SUCCESS;
    char buffer[BUFFER_SIZE];
    char *next;
    while (1)
    {
        // 从文件或标准输入读取一行字符串的函数
        // 它的原型为：char *fgets(char *str, int n, FILE *stream);其中，str是一个指向字符数组的指针，用于存储读入的字符串；
        // n表示最多读入n-1个字符（因为还要留一个位置放'\0'）；stream表示要读取数据的流。
        next = fgets(buffer, BUFFER_SIZE, src_file);
        if (!next)
        {
            if (ferror(src_file))
            {
                result = COPY_SRC_READ_ERROR;
            }
            else if (feof(src_file))
            {
                result = COPY_SUCCESS;
            }
            else
            {
                result = COPY_UNKNOWN_ERROR;
            }
            break;
        }

        if (fputs(next, dest_file) == EOF)
        {
            result = COPY_DEST_WRITE_ERROR;
            break;
        }
    }

    fclose(src_file);
    fclose(dest_file);
    return result;
}

// 读取二进制文件
int CopyFile3(char const *src, char const *dest)
{
    if (!src || !dest)
    {
        // 参数至少有一个为 NULL
        return COPY_ILLEGAL_ARGUMENTS;
    }

    FILE *src_file = fopen(src, "rb");
    if (!src_file)
    {
        // src 打开失败
        return COPY_SRC_OPEN_ERROR;
    }

    FILE *dest_file = fopen(dest, "wb");
    if (!dest_file)
    {
        // dest 打开失败，记得关闭 src
        fclose(src_file);
        return COPY_DEST_OPEN_ERROR;
    }

    int result = COPY_SUCCESS;
    char buffer[BUFFER_SIZE];

    while (1)
    {
        // C语言中的fread函数是用来从文件中读取数据的。它的原型如下：
        // size_t fread(void *ptr, size_t size, size_t count, FILE *stream);
        // 其中，ptr表示要读取数据存放的缓冲区地址；size表示每个元素所占字节数；count表示要读取元素的个数；stream表示文件指针。
        // fread函数返回实际读取到的元素个数，如果出现错误则返回0或者小于count。
        // void *ptr就是为提供了很多的便利性，既能是char*，也能是int *
        size_t bytes_read = fread(buffer, sizeof(buffer[0]), BUFFER_SIZE, src_file);
        if (fwrite(buffer, sizeof(buffer[0]), bytes_read, dest_file) < bytes_read)
        {
            result = COPY_DEST_WRITE_ERROR;
            break;
        }

        if (bytes_read < BUFFER_SIZE)
        {
            if (ferror(src_file))
            {
                result = COPY_SRC_READ_ERROR;
            }
            else if (feof(src_file))
            {
                result = COPY_SUCCESS;
            }
            else
            {
                result = COPY_UNKNOWN_ERROR;
            }
            break;
        }
    }

    fclose(src_file);
    fclose(dest_file);
    return result;
}

void Echo1()
{
    char buffer[4];
    while (1)
    {
        // 这个就是从标准输入流中读取，每次读取3个字节，最后一个放"\0"
        if (!fgets(buffer, 4, stdin))
        {
            break;
        }
        // puts(buffer);
        printf("aa -> %s", buffer);
    }
}

void Echo2()
{
#define BUFFER_SIZE 4
    // 这里定义的就是int数组，16个字节
    char buffer[BUFFER_SIZE];
    while (1)
    {
        size_t bytes_read = fread(buffer, sizeof(buffer[0]), BUFFER_SIZE, stdin);
        // 返回读了几个字节
        PRINT_INT(bytes_read);
        // 如果发生错误或者已经到达了文件末尾，则返回值可能小于count
        if (bytes_read < BUFFER_SIZE)
        {
            if (feof(stdin))
            {
                puts("EOF");
                fwrite(buffer, sizeof(char), bytes_read, stdout);
            }
            else if (ferror(stdin))
            {
                perror("Error read from stdin");
            }
            break;
        }
        fwrite(buffer, sizeof(buffer[0]), BUFFER_SIZE, stdout);
    }
}

int main(void)
{
    // 设置中文编码，但是还是有问题的
    setlocale(LC_ALL, "zh_CN.utf-8");

    stdInOutErr();

    printf("--------------------------------------\n");

    readFile();

    printf("--------------------------------------\n");

    int result = CopyFile("include/io_utils.h", "include/io_utils_copy.h");
    PRINT_INT(result);

    printf("--------------------------------------\n");

    TimeCost(NULL);
    CopyFile2("data/Romance of the Three Kingdoms.txt", "data/三国演义2.txt");
    PRINT_IF_ERROR("CopyFile: %s", "data/三国演义.txt");
    TimeCost("COPY");

    printf("--------------------------------------\n");

    Echo2();

    return 0;
}