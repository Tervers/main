/*** CHAPTER                          9                           PROJECTS ***/


1. Write a program that asks the user to enter a series of integers (which it
    stores in an array), then sorts the integers by calling the function
    selection_sort. When given an array with n elements, selection_sort must do
    the following:

    1. Search the array to find the largest element, then move it to the last
        position in the array.
    2. Call itself recursively to sort the first n - 1 elements of the array.

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

2. Modify Programming Project 5 from Chapter 5 so that it uses a function to
    compute the amount of income tax. When passed an amount of taxable income,
    the function will return the tax due.

//original code
#include <stdio.h>

int main(void)
{
    int income;
    float tax;

    printf("Enter income:\n");
    scanf("%d", &income);

    if (income <= 749)
    printf("Tax due: %.2f\n", tax = (income * 0.01));

    else if (income >= 750 && income <= 2249)
    printf("Tax due: %.2f\n", tax = (7.50f + ((income - 750) * 0.02)));

    else if (income >= 2250 && income <= 3749)
    printf("Tax due: %.2f\n", tax = (37.50f + ((income - 2250) * 0.02)));

    else if (income >= 3750 && income <= 5249)
    printf("Tax due: %.2f\n", tax = (82.50f + ((income - 3750) * 0.02)));

    else if (income >= 5250 && income <= 6999)
    printf("Tax due: %.2f\n", tax = (142.50f + ((income - 5250) * 0.02)));

    else if (income >= 7000)
    printf("Tax due: %.2f\n", tax = (230.00f + ((income - 7000) * 0.02)));

    else
        printf("Try again.\n");

    return 0;
}
