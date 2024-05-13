#include <stdbool.h>    /* C99 only */
#include <stdio.h>

int main(void)
{
    bool digit_seen[10] = {false}, repdigit[10] = {false};
    int digit;
    long n;

    printf("Enter a number: ");
    scanf("%ld", &n);

    while (n > 0) {
        digit = n % 10;
        if (digit_seen[digit])
            repdigit[digit] = true;
        digit_seen[digit] = true;
        n /= 10;
    }


    for (int i = 0; i < (sizeof(repdigit) / sizeof(repdigit[0])); i++)
            if (repdigit[i])
                printf("%d ", i);

    return 0;
}
