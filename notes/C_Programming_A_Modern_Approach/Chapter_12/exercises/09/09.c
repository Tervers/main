/*

Write the following function:

double inner_product(const double a*, const double *b, int n);

a and b both point to arrays of length n. The function should return
    a[0] * b[0] + a[1] * b[1] + ... + a[n - 1] * b[n - 1]. Use pointer arith-
    metic - not subscripting - to visit array elements.

*/

#include <stdio.h>

double inner_product(const double *a, const double *b, int n)
{
    double total;
    const double *p = a, *q = b;

    for (; p < n + a; p++, q++)
        total += *p * *q;

    return total;
}

int main(void)
{
    int n;

    printf("How many numbers in each set?");
    scanf("%d", &n);

    double a[n], b[n];

    printf("Enter the first set of numbers:");
    for (int i = 0; i < n; i++)
        scanf("%lf", &a[i]);

    printf("Enter the second set of numbers:");
    for (int i = 0; i < n; i++)
        scanf("%lf", &b[i]);

    printf("Total: %g", inner_product(a, b, n));

    return 0;
}
