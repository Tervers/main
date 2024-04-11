#include <stdio.h>

int main()
{
    int d, n;

    printf("Enter a number to test if it is prime: ");
    scanf("%d", &n);

    for (d = 2; d < n; d++) {
        if (d * d == n)
            break;
        if (n % d == 0)
            break;
        }

    if (d < n)
        printf("%d is divisible by %d\n", n, d);
    else
        printf("%d is prime\n", n);

return 0;
}
