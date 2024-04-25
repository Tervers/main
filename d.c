#include <stdio.h>

int main(void)
{
    int i = 1, n = 1;
    float e = 0.0f, b = 0.0f, e1 = 0.0f, epsilon = 0.0f;

    printf("Enter a number: ");
    scanf("%d", &n);

    e = (1.0f + (1.0f / n));    //stores calculated values
    b = e;                      //base equation

    for (;i <= n;i++){
	e *= b;
    }
    printf("%f\n", e);

    return 0;
}
