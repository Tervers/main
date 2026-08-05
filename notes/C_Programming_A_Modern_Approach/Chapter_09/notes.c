/*** CHAPTER                          9                          EXERCISES ***/


1. The following function, which computes the area of a triangle, contains two
    errors. Locate the errors and show how to fix them. (There are no errors in
    the formula.)

double triangle_area(double base, height)
double product;
{
    product = base * height;
    return product / 2;
}

//my answer
double triangle_area(double base, double height)
{
    double product = base * height;
    return product / 2;
}


2. Write a function check(x, y, n) that returns 1 if both x and y fall between
    0 and n - 1, inclusive. The function should return 0 otherwise. Assume that
    x, y, and n are all of type int.

int check(int x, int y, int n)
{
    if (x <= (n - 1) && y <= (n - 1) && n >= 0 && y >= 0)
        return 1;
    else
	return 0;
}


3. Write a function gcd(m, n) that calculates the greatest common divisor of
    the integers m and n. (Programming Project 2 in Chapter 6 describes
    Euclid's algorithm for computing the GCD.)

int gcd(int m, int n)
{
    int remainder = 0;

	while (n != 0) {
        remainder = m % n;
        m = n;
        n = remainder;
    }
    
    return m;
}


4. Write a function day_of_year(month, day, year) that returns the day of the
    year (an integer between 1 and 366) specified by the three arguments.

int day_of_year(int month, int day, int year)
{
    int total_days = 0;

    switch (month) {
        case 2: total_days += 31;
                break;
        case 3: total_days += 59;
                break;
        case 4: total_days += 90;
                break;
        case 5: total_days += 120;
                break;
        case 6: total_days += 151;
                break;
        case 7: total_days += 181;
                break;
        case 8: total_days += 212;
                break;
        case 9: total_days += 243;
                break;
        case 10: total_days += 273;
                break;
        case 11: total_days += 304;
                break;
        case 12: total_days += 334;
                break;
    }

    total_days += day;

    if ( year % 4 == 0 && month >= 3 )
        total_days += 1;

    return total_days;
}


5. Write a function num_digits(n) that returns the number of digits in n (a
    positive integer). To determine the number of digits in a number n, divide
    it by 10 repeatedly. When n reaches 0, the number of divisions indicates
    how many digits n originally had.

int num_digits(double positive_integer)
{
    int digits = 0;

    for (;;) {
        digits++;
        positive_integer /= 10l;
        if (positive_integer < 1l)
            break;
    }

    return digits;
}


6. Write a function digit(n, k) that returns the kth digit (from the right) in
    n (a positive integer). For example, digit(829, 1) returns 9, digit(829, 2)
    returns 2, and digit(829, 3) returns 8. If k is greater than the number of
    digits in n, have the function return 0.

uint32_t digit(uint32_t n, uint32_t k)
{
    while(k >= 2) {
        n /= 10;
        k--;
    }

    return n % 10;
}


7. Suppose that the function f has the following definition:
        int f(int a, int b) {...}

    Which of the following statements are legal? (Assume that i has type int
    and x has type double.)

    (a) i = f(83, 12);
    (b) x = f(83, 12);
    (c) i = f(3.15, 9.28);
    (d) x = f(3.15, 9.28);
    (e) f(83, 12);

a, b, d, e (e won't do anything, but is still legal)
c will have it's first argument truncated.


8. Which of the following would be valid prototypes for a function that returns
    nothing and has one double parameter?

    (a) void f(double x);
    (b) void f(double);
    (c) void f(x);
    (d) f(double x);

a, b are valid
c has no parameter type
d has no prototype type


9. What will be the output of the following program?

#include <stdio.h>

void swap(int a, int b);

int main(void)
{
    int i = 1, j = 2;

    swap(i, j);
    printf("i = %d, j = %d\n", i, j);
    return 0;
}

void swap(int a, int b)
{
    int temp = a;
    a = b;
    b = temp;
}

the program will print to the terminal "i = 1, j = 2". This is because
    arguments are passed by value, leaving the variables i and j unchanged.


10. Write functions that return the following values. (Assume that a and n are parameters, where a is an array of int values and n is the length of the array)

    (a) The largest element in a.
    (b) The average of all elements in a.
    (c) The number of positive elements in a.

(a) The largest element in a.

int largest(int a[], int n)
{
    int largest = 0;

    for (i = 0; i < n; i++)
        if (a[i] > largest)
            largest = a[i];

    return largest;
}

(b) The average of all elements in a.

int average(int a[], int n)
{
    total = 0;

    for (i = 0; i < n; i++)
        total += a[i];

    return total / n;
}

(c) The number of positive elements in a.

int positive(int a[], int n)
{
    count = 0;

    for (i = 0; i < n; i++)
        if (a[i] >= 0)
            count++;

    return count;
}


11. Write the following function:
        float compute_GPA(char grades[], int n);

    The grades array will contain letter grades (A, B, C, D, or F, either
    upper-case or lower-case); n is the length of the array. The function
    should return the average of the grades (assume that A=4, B=3, C=2, D=1,
    and F=0).

float compute_GPA(char grades[], int n)
{
    int total = 0;

    for (int i = 0; i < n; i++){
        if (grades[i] == 'A' || 'a')
            total += 4;
        if (grades[i] == 'B' || 'b')
            total += 3;
        if (grades[i] == 'C' || 'c')
            total += 2;
        if (grades[i] == 'D' || 'd')
            total += 1;
        if (grades[i] == 'F' || 'f')
            total += 0;
    }

    return total / n;
}


12. Write the following function:
        double inner_product(double a[], double b[], int n);

   The function should return a[0] * b[0] + a[1] * b[1] + ... + a[n-1] * b[n-1]

double inner_product(double a[], double b[], int n);
{
    double total = 0.0;

    for (int i = 0; i < n; i++){
        total += a[i] * b[i];

    return total;
}


13. Write the following function, which evaluates a chess position:
        int evaluate_position(char board[8][8]);

    board represents a configuration of pieces on a chessboard, where the
    letters K, Q, R, B, N, P represent White pieces, and the letters k, q, r,
    b, n, and p represent Black pieces. evaluate_position should sum the values
    of the White pieces (Q = 9, R = 5, B = 3, N = 3, P = 1). It should also sum
    the values of the Black pieces (done in a similar way). The function will
    return the difference between the two numbers. This value will be positive
    if White has an advantage in material and negative if Black has an
    advantage.

int evaluate_position(char board[8][8])
{
    int white = 0, black = 0;

    for (int i = 1; i <= 8; i++)
        for (int j = 1; j <= 8; j++){
            if (board[i][j] == 'Q')
                white += 9;
            if (board[i][j] == 'q')
                black += 9;
            if (board[i][j] == 'R')
                white += 5;
            if (board[i][j] == 'r')
                black += 5;
            if (board[i][j] == 'B')
                white += 3;
            if (board[i][j] == 'b')
                black += 3;
            if (board[i][j] == 'N')
                white += 3;
            if (board[i][j] == 'n')
                black += 3;
            if (board[i][j] == 'P')
                white += 1;
            if (board[i][j] == 'p')
                black += 1;
        }

    return white - black;
}


14. The following function is supposed to return true if any element of the
    array a has the value 0 and false if all elements are nonzero. Sadly, it
    contains an error. Find the error and show how to fix it:

    bool has_zero(int a[], int n)
    {
        int i;
    
        for (i = 0; i < n; i++)
            if (a[i] == 0)
                return true;
            else
                return false;
    }

The function, in its current form, will return instantly after reading the
    first element. Remove the else clause entirely and place return false;
    outside of the for loop.

    bool has_zero(int a[], int n)
    {
        int i;

        for (i = 0; i < n; i++)
            if (a[i] == 0)
                return true;

        return false;
    }


15. The following (rather confusing) function finds the median of three
    numbers. Rewrite the function so that it has just one return statement.

    double median(double x, double y, double z)
    {
        if (x <= y)
            if (y <= z) return y;
            else if (x <= z) return z;
            else return x;
        if (z <= y) return y;
        if (x <= z) return x;
        return z;
    }

double median(double x, double y, double z)
{
    double median = 0.0;

    if (x <= y)
        if (y <= z) median = y;
        else if (x <= z) median = z;
        else median = x;
    if (z <= y) median = y;
    if (x <= z) median = x;
    median = z;

    return median;
}


16. Condense the fact function in the same way we condensed power.

int fact(int n)
{
    return n <= 1 ? 1 : n * fact(n - 1);


17. Rewrite the fact function so that it's no longer recursive.

int fact(int n)
{
    int factorial = 1;

    for (i = 2; i <= n; i++)
        factorial *= i;

    return factorial;
}


18. Write a recursive version of the gcd function (see Exercise 3). Here's the
    strategy to use for computing gcd(m, n): if n is 0, return m. Otherwise, 
    call gcd recursively, passing n as the first argument and m % n as the
    second.

int gcd(m, n)
{
    if (n == 0)
        return m;
    else
        return gcd(n, m % n);


19. Consider the following "mystery" function:
    void pb(int n)
    {
        if (n != 0) {
            pb(n / 2);
            putchar('0' + n % 2);
        }
    }

    Trace the execution of the function by hand. Then write a program that
    calls the function, passing it a number entered by the user. What does the
    function do?

The program produces a binary representation of the entered number.
