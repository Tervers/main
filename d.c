#include <stdio.h>

int main(void)
{
    short i;
    char ch, term, sentence[len];    //terminating character, sentence [length]

    printf("Enter a sentence: ");

    for (;;len++) {
        ch = getchar();
        if (ch == '\n')
            break;
        else if (ch == '.' || ch == '!' || ch == '?')
            term = ch;
        sentence[len] = ch;
    }
}
