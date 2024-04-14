#include <stdio.h>

int main(void)
{
    int i = 1, n = 1;
    float e = 0.0f, b = 0.0f, e1 = 0.0f, epsilon = 0.0f;

    printf("Enter a number: ");
    scanf("%f", &epsilon);

    e = (1.0f + (1.0f / n));    //stores calculated values
    b = e;                      //base equation

    for (;;i++){
        n = i;
        e1 = e;
        e *= b;
            if ((e - e1) < epsilon)
                break;
            else
                continue;
        }

    printf("%f\n", e1);

    return 0;
}
