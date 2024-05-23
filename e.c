#include <stdio.h>

int main(void)
{
    char ch, fn = 0, ln = 0;    //character, first name, last name

    printf("Enter a first and last name: ");

    while ((ch = getchar()) != '\n') {
        if (!fn && ch >= 'A' && ch <= 'Z') {
            fn = ch;
            }

        else if (fn && !ln && ch >= 'A' && ch <= 'Z') {
            ln = ch;
            putchar(ch);
            }

        else if (fn && ln)
            putchar(ch);

        else
            ch = getchar();
    }

    printf(", %c.\n", fn);

    return 0;
}
