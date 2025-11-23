/*

Rewrite the following function to use pointer arithmetic instead of array sub-
    scripting. (In other words, elimate the variable i and all uses of the []
    operator.) Make as few changes as possible.

void store_zeroes(int a[], int n)
{
    int i;

    for (i = 0; i < n; i++)
        a[i] = 0;
}

*/

void store_zeroes(int *a, int n)
{
    int *p;

    for (p = a; p < a + n; p++)
        *p = 0;
}
