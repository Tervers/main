#include <stdio.h>

int main(void)
{
    int n;

    printf("Enter a number: ");
    scanf("%d", &n);

    do {
        printf("%d", (n % 10));
        n /= 10;
    }
        while (n);

    printf("\n");

    return 0;
}
