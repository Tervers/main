/*

(a) Write a program that reads a message, then checks whether it's a palindrome:

    Enter a message: __He_lived_as_a_devil,_eh?__
    Palindrome

    Enter a message: __Madam,_I_am_Adam.__
    Not a palindrome

Ignore all characters that aren't letters. Use integer variables to keep track
of positions in the array.

(b) Revise the program to use pointers instead of integers to keep track of pos-
itions in the array.

*/


//(a)

#include <stdio.h>
#include <stdbool.h>

#define MAX 100
int main(void)
{
    bool mismatch = false;
    int i = 0;
    char message[MAX], *p = message, *q = message;

    printf("Enter a message to see if it is a palindrome:\n");
    while ((*p = getchar()) != '\n') {
	    if (*p >= 'a' && *p <= 'z' || *p >= 'A' && *p <= 'Z') {
	        p++;
            i++;
        }
    }

    p--;

    for (; q < message + i - 1; p--, q++)
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


//(b)

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
