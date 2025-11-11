#include <stdio.h>

void selection_sort(int a[], int n)
{
    int largest = 0, hold = 0;

    if (n == 1)
        return;

    for (int i = 0; i < n - 1; i++)
        if (a[i] > largest){
            largest = a[i];
            hold = a[n - 1];
            a[n - 1] = largest;
            a[i] = hold;
        }
    
    return selection_sort(a, n - 1);
}

int main(void)
{
    int n = 0;

    printf("How many numbers do you need to sort?\n");
    scanf("%d", &n);

    int a[n];

    printf("Enter the numbers:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    selection_sort(a, n);

    printf("The numbers in sorted order: ");
    for (int i = 0; i < n - 1; i++)
        printf("%d, ", a[i]);

    printf("%d\n", a[n - 1]);

    return 0;
}
