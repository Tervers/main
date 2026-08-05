/*

(a) Write a program that reads a message, then prints the reversal of the
message:

    Enter a message: __Don't_get_mad,_get_even.__
    Reversal is: .neve teg ,dam teg t'noD

Hint: Read the message one character at a time (using getchar) and store the
characters in an array. Stop reading when the array is full or the character is
'\n'.

(b) Revise the program to use a pointer instead of an integer to keep track of
the current position in the array.

*/


(a)

#include <stdio.h>

#define LIMIT 80

void reversed(char message[], int length)
{
    for(length -= 1; length >= 0; length--)
        printf("%c", message[length]);

    printf("\n");
}

int main(void)
{
    char message[LIMIT];
    int length = 0;

    printf("Enter a message to see it reversed:\n");

    for(; length < LIMIT && message[length - 1] != '\n'; length++)
        message[length] = getchar();

    reversed(message, --length);
}



(b)

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
