#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{

    srand(time(NULL));

    int magic_number = rand();

    while (1)
    {
        int user_input;
        puts("Please intput a number: ");
        scanf("%d", &user_input);
        if (user_input > magic_number)
        {
            puts("your number is bigger!");
        }
        else if (user_input < magic_number)
        {
            puts("your number is smaller!");
        }
        else
        {
            puts("Yes! You get it");
            break;
        }
    }
    return 0;
}