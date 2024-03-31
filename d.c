#include <stdio.h>

int main(void)
{
    int n = 0, d1 = 0, d2 = 0, d3 = 0;

    printf("Enter a three-digit number: ");
    scanf("%d", &n);

    d1 = (n / 100);
    d2 = ((n / 10) % 10);
    d3 = (n % 10);

    printf("The reversal is: %d%d%d\n", d3, d2, d1);

    return 0;
}
