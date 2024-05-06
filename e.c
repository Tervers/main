#include <stdio.h>
#include <ctype.h>

int main(void)
{
    char ch;           //character
    int vc = 0;        //vowel count

    printf("Enter a message: ");
    while (getchar() != '\n') {
        ch = toupper(ch);
        if (ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U')
            vc++;
    }

    printf("Your sentence contains %d vowels.\n", vc);

    return 0;
}
