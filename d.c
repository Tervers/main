#include <stdio.h>

int main(void)
{
    char fi = 0, name[21] = {0};    //first initial, last name

    printf("Enter a first and last name: ");

    for (;;) {
        fi = getchar();

        if (!fi && ch >= 'A' && ch <= 'Z') {
            fn = ch;
            }

        else if (fn && !name[i] && ch >= 'A' && ch <= 'Z') {
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
