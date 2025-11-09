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

gcd(int m, int n)
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


6. 
