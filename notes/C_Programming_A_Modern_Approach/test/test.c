#include <stdio.h>

int num_digits(double positive_integer)
{
    int digits = 0;

    for (;;) {
        digits++;
        positive_integer /= 10l;
        if (positive_integer <= 1l)
            break;
    }

    return digits;
}

int main(void)
{
    double positive_integer = 0;

    printf("Enter a positive integer: \n");
    scanf("%lf", &positive_integer);
    printf("Your number has %d digits.\n", num_digits(positive_integer));

    return 0;
}
