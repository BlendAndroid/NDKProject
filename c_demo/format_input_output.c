/* Prints int and float values in various formats */
#include <stdio.h>
int main(void)
{
    int i, j;
    float x;
    i = 40;
    x = 839.21f;
    printf("|%d|%5d|%-5d|%5.3d|\n", i, i, i, i);
    printf("|%10.3f|%10.3e|%-10g|\n", x, x, x);

    // scanf函数本质上是一种“模式匹配”函数，试图把输入的字符组与转换说明相匹配
    // scanf函数“忽略”了最后的换行符，实际上没有读取它。这个换行符将是下一次scanf函数调用的第一个字符。
    // 在寻找数据项时，scanf函数通常会跳过空白字。

    // scanf函数首先寻找输入中的整数，把这个整数存入变量i中；然后，scanf函数将试图把逗号与下一个输入字符相匹配。
    // 如果下一个输入的字符是空格而不是逗号，那么scanf函数将终止操作，而不再读取变量j的值
    scanf("%d, %d", &i, &j);
    printf("out put: %d, %d", i, j);

    return 0;
}
/**
 * ·%d ——以十进制形式显示变量i，且占用最少的空间。
 * ·%5d ——以十进制形式显示变量i，且至少占用5个字符的空间。因为变量i只占两个字符，所以添加了3个空格。
 * ·%-5d ——以十进制形式显示变量i，且至少占用5个字符的空间。因为表示变量i的值不需要用满5个字符，所以在后续位置上添加空格（更确切地说，变量i在长度为5的字段内是左对齐的）
 * ·%5.3d ——以十进制形式显示变量i，且至少占用5个字符的空间并至少有3位数字。因为变量i只有2个字符长度，所以要添加一个额外的零来保证有3位数字。现在只有3个字符长度，为了保证占有5个字符，还要添加2个空格（变量i是右对齐的）。
 *
 * ·%10.3f ——以定点十进制形式显示变量x，且总共用10个字符，其中小数点后保留3位数字。因为变量x只需要7个字符（即小数点前3位，小数点后3位，再加上小数点本身1位），所以在变量x前面有3个空格。
 * ·%10.3e ——以指数形式显示变量x，且总共用10个字符，其中小数点后保留3位数字。因为变量x总共需要9个字符（包括指数），所以在变量x前面有1个空格。
 * ·%-10g ——既可以以定点十进制形式显示变量x，也可以以指数形式显示变量x，且总共用10个字符。在这种情况下，printf函数选择用定点十进制形式显示变量x。负号的出现强制进行左对齐，所以有4个空格跟在变量x后面。
 */