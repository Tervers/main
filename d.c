#include <stdio.h>

int main(void)
{
    char ch, fi = 0, name[21] = {0};    //first initial, last name

    printf("Enter a first and last name: ");

    for (i = 0;; i++) {
        ch = getchar();

        if (!fi) {
            fi = ch;
            }

        else if (ch == ' ') {
		for (i = 0; i < 22; i++) {
        		name[i] = getchar();
		}


        else
            continue;
    }

    printf(", %c.\n", fi);

    return 0;
}
