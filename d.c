#include <stdio.h>
#include <ctype.h>

int main(void)
{
    int l = 1, i = 0;
    char m[l];  //message [l]ength

    printf("Enter message: \n");

    while (m[i] = getchar() != '\n') {
        l++;
        i++;
    }
    /*
    for (int i = 0;;i++) {
        m[i] = getchar();
        m[i] = toupper(m[i]);
        l++;
    }
    */

    l--;

    for (i = 0; i < l; i++)
        putchar(m[i]);

    printf("characters: %d\n", l);

    return 0;
}
