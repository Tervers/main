/*

Simplify Promgramming Project 2(b) by taking advantage of the fact that an array
name can be used as a pointer.

*/

#include <stdio.h>
#include <stdbool.h>

#define MAX 100
int main(void)
{
    bool mismatch = false;
    char message[MAX], *p = message, *q = message, *last;

    printf("Enter a message to see if it is a palindrome:\n");
    while ((*p = getchar()) != '\n') {
        if (*p >= 'a' && *p <= 'z' || *p >= 'A' && *p <= 'Z') {
            p++;
        }
    }

    p--;
    last = p;

    for (; q < last; p--, q++)
        if (*p != *q) {
            mismatch = true;
            break;
        }

    if (mismatch)
        printf("Not a palindrome\n");
    else if (!mismatch)
        printf("Palindrome\n");

    return 0;
}
