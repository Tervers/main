/*

Simplify Programming Project 1(b) by taking advantage of the fact that an array
name can be used as a pointer.

*/

#include <stdio.h>

#define LIMIT 80

int main(void)
{
    char message[LIMIT], *p;

    printf("Enter a message to see it reversed:\n");

    for(p = message; p < message + LIMIT; p++) {
        *p = getchar();
        if (*p == '\n')
            break;
    }

    printf("In reverse:\n");

    for (; p >= message; p--) {
        if (*p == '\n')
            --p;
        putchar(*p);
    }

    printf("\n");

    return 0;
}
