#include <stdio.h>

int main (void)
{
    int month_days, day_start, i, j;

    printf("Enter number of days in month: ");
    scanf("%2d", &month_days);
    printf("Enter starting day of the week (1=Sun, 7=Sat): ");
    scanf("%1d", &day_start);

    if (j < day_start){
        printf("\t");
        j++;
    }

    for (; i <= month_days; i++) {
        printf("%d\t", i);
        if (!(i % 7))
            printf("\n");
    }

    return 0;
}
