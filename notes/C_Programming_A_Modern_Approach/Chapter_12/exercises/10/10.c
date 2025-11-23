/*

Modify the find_middle function of Section 11.5 so that it uses pointer arith-
    metic to calculate the return value.

int *find_middle(int a[], int n) {
    return &a[n / 2];
}

*/

int *find_middle(int *a, int n) {
    return a + (n / 2);
}
