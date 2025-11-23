/*

Section 8.2 had a program fragment in which two nested for loops initialized
    the array ident for use as an identity matrix. Rewrite this code, using a
    single pointer to step through the array one element at a time. Hint: Since
    we won't be using row and col index variables, it won't be easy to tell
    where to store 1. Instead, we can use the fact that the first element of
    the array should be 1, the next N elements should be 0, the next element
    should be 1, and so forth. Use a variable to keep track of how many consec-
    utive 0s have been stored; when the count reaches N, it's time to store 1.

#define N 10

double ident[N][N];
int row, col;

for (row = 0; row < N; row++)
    for (col = 0; col < N; col++)
    if (row == col)
        ident[row][col] = 1.0;
    else
        ident[row][col] = 0.0;

*/

#define N 10

int zeroes = N - 1;
double ident[N][N], *p;

for (p = &ident[0][0]; p <= &ident[N - 1][N - 1]; p++) {
    zeroes++;
    if (zeroes == N) {
        *p = 1.0;
        zeroes = 0;
    }
    else
        *p = 0.0;
}
