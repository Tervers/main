#include <stdio.h>
#include <ctype.h>

int main(void)
{
    int l = 1, i = 0;
    char m[l];  //message [l]ength

    printf("Enter message: ");

    for (int i = 0;;i++) {
        m[i] = getchar();
        if (m[i] == '\n')
            break;
        m[i] = toupper(m[i]);
        l++;
    }

    for (i = 0; i < l; i++){
        if (m[i] == 'A')
            m[i] = '4';
        if (m[i] == 'B')
            m[i] = '8';
        if (m[i] == 'E')
            m[i] = '3';
        if (m[i] == 'I')
            m[i] = '1';
        if (m[i] == 'O')
            m[i] = '0';
        if (m[i] == 'S')
            m[i] = '5';
        putchar(m[i]);
    }

    printf("!!!!!!!!!!\n");

    return 0;
}
