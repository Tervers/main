/*

Modify the find_largest function so that it uses pointer arithmetic - not sub-
    scripting - to visit array elements.

int find_largest(int a[], int n)
{
    int i, max;

    max = a[0];
    for (i = 1; i < n; i++)
        if (a[i] > max)
            max = a[i];
    return max;
}

*/

int find_largest(int *a, int n)
{
    int *p = a, max;

    max = *p;
    for (;p < a + n; p++)
        if (*p > max)
            max = *p;
    return max;
}
