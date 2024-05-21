/*** CHAPTER                          9                          FUNCTIONS ***/

functions are the building blocks of C programs
each function is like a small program with its own declarations and statements
using functions, we can divide a program into small pieces that are easier for
    us, and others, to understand and modify
functions are reusable, allowing us to take a function that was part of one
    program and us it in others

/*** CHAPTERS              9.1              DEFINING AND CALLING FUNCTIONS ***/

//type function_name(function parameters)
double average(double a, double b) //identifiers a and b
{
    return (a + b) / 2; //body
}

//function call average()
printf("Average: %g\n", average(x, y)); //(x, y) function arguments

function arguments can be a variable or any expression of a compatible type

/***             average.c - COMPUTES AVERAGES OF THREE NUMBERS            ***/

#include <stdio.h>

double average(double a, double b)
{
	return (a + b) / 2;
}

int main(void)
{
	double x, y, z;

	printf("Enter three numbers: ");
	scanf("%lf%lf%lf", &x, &y, &z);
	printf("Average of %g and %g: %g\n", x, y, average(x, y));
	printf("Average of %g and %g: %g\n", y, z, average(y, z));
	printf("Average of %g and %g: %g\n", x, z, average(x, z));

	return 0;
}

/***                    countdown.c - PRINTS A COUNTDOWN                   ***/

#include <stdio.h>

void print_count(int n)
{
    printf("T minus %d and counting\n", n);
}

int main(void)
{
    int i;

    for (i = 10; i > 0; --i)
        print_count(i);   //i gets copied to n in print_count()

    return 0;
}

/***                       pun2.c - PRINTS A BAD PUN                       ***/

#include <stdio.h>

void print_pun(void)
{
	printf("To C or not to C: that is the question.\n");
}

int main(void)
{
	print_pun();
	return 0;
}

//                          FUNCTION DEFINITIONS

return-type function-name ( parameters )
{
    declarations
    statements
}

in C89, if the return type is omitted, the function is presumed to return a
    value of type int
in C99, it is illegal to omit the return type of a function

double//legal placement of return-type
average(double a, double b)
{
    return (a + b) / 2;
}

if a function has no parameters, it must contain void between the parentheses

double average(double a, double b)
{
    double sum;     /* declaration */

    sum = a + b;    /* statement */
    return sum / 2; /* statement */
}

variables declared in the body of a function belong exclusively to that
    function; they cannot be examined or modified by other functions
in C89, variable declaration must come first, before all statements in the body
    of a function
in C99, variable declarations and statements can be mixed, as long as each
    variable is declared prior to the first statement that uses the variable

void print_pun(void)
{
}

//                          FUNCTION CALLS

average(x, y)       //*
print_count(i)      //individual function calls
print_pun()         //*

a call of a void function is always follwed by a semicolon to turn it into a
    statement:

print_count(i);
print_pun();

a call of a non-void function produces a value that can be stored in a
    variable, tested, printed, or used in some other way:

avg = average(x, y);
if (average(x, y) > 0)
    printf("Average is positive\n");
printf("The average is %g\n", average(x, y));

/* discarding a return value ("expression statement")
average(x, y);  //computes a value, but is not stored in a variable */

num_chars = printf("Hi, Mom!\n");   //num_chars will have the value 9

printf("Hi, Mom!\n");   //discards return value (9)

(void) printf("Hi, Mom!\n");//shows we are deliberately discarding return value

/***               prime.c - TESTS WHETHER A NUMBER IS PRIME               ***/

#include <stdbool.h>
#include <stdio.h>

bool is_prime(int n)
{
    int divisor;

    if (n <= 1)
        return false;
    for (divisor = 2; divisor * divisor <= n; divisor++)
        if (n % divisor == 0)
            return false;
    return true;
}

int main(void)
{
    int n;

    printf("Enter a number: ");
    scanf("%d", &n);
    if (is_prime(n))
        printf("Prime\n");
    else
        printf("Not prime\n");

    return 0;
}

/*** CHAPTER                   9.2 FUNCTION DECLARATIONS                   ***/
