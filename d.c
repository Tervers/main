#include <stdio.h>

int main()
{
    int sum = 0;
    for (int i = 0; i < 10; i++) {
        if (i % 2)
            continue;
        printf("%d\n", sum += i);
    }
    printf("%d\n", sum);

return 0;
}
