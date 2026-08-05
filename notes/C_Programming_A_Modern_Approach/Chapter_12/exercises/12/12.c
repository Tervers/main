/*

Write the following function:

void find_two_largest(const int *a, int n, int *largest, int *second_largest);

a points to an array of length n. The function searches the array for its
    largest and second largest elements, storing them in the variables pointed
    to by largest and second_largest, respectively. User pointer arithmetic -
    not subscripting - to visit array elements.

void find_two_largest(int a[], int n, int *largest, int *second_largest)
{
    *largest = a[0];
    *second_largest = a[1];

    for (int i = 0; i < n; i++) {
        if (a[i] > *largest) {
            *second_largest = *largest;
            *largest = a[i];
        }
        else if (a[i] > *second_largest)
            *second_largest = a[i];
    }
}

*/

void find_two_largest(const int *a, int n, int *largest, int *second_largest)
{
    const int *p = a;

    *largest = *p;
    *second_largest = *(p + 1);

    for (p = a; p < a + n; p++)
        if (*p > *largest) {
            *second_largest = *largest;
            *largest = *p;
        }
        else if (*p > *second_largest)
            *second_largest = *p;
    }
}
