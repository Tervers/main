#include <stdio.h>

int main(void)
{
    int a1, b1, a2, b2, r;

    printf("Enter a fraction: ");
    scanf("%d/%d", &a1, &b1);

    a2 = a1;
    b2 = b1;

    for (; b2;) {
        r = a2 % b2;
        a2 = b2;
        b2 = r;
        }

    a1 /= a2;
    b1 /= a2;

    printf("In lowest terms: %d/%d", a1, b1);

    return 0;
}

