/*** CHAPTER                          9                          FUNCTIONS ***/

functions are the building blocks of C programs
each function is like a small program with its own declarations and statements
using functions, we can divide a program into small pieces that are easier for
    us, and others, to understand and modify
functions are reusable, allowing us to take a function that was part of one
    program and us it in others

/*** CHAPTERS              9.1              DEFINING AND CALLING FUNCTIONS ***/

//type function_name(function parameters)
double average(double a, double b) //function definition | identifiers a and b
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

return-type function-name ( parameters ) ;

#include <stdio.h>

double average(double a, double b);   /* DECLARATION */ //function prototype

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

double average(double a, double b)   /* DEFINITION */
{
    return (a + b) / 2;
}

a function prototype does not have to specify the names of the functions
    parameters as long as their types are present: //not best practice

double average(double, double);

in C99, you must have either a declaration or a definition of a function prior
    to any call of the function; calling a function for which the compiler has
    not yet seen a declaration or definition is an error

/*** CHAPTER                         9.3                         ARGUMENTS ***/

parameters appear in function "definitions"
arguments appear in function "calls"
arguments are "passed by value": when a function is called, each _argument_ is
    evaluated and _its value_ assigned to the corresponding _parameter_
since the _parameter_ contains a _copy_ of the arguments _value_, any changes
    made to the _parameter_ during the execution of the function do not affect
    the _argument_

int power(int x, int n)
{
    int i, result = 1;

    for (i = 1; i <= n; i++)
        result = result * x;

    return result;
}

since 'n' is a copy of the original exponent, we can modify it inside the
    function, removing the need for 'i';

int power(int x, int n)
{
    int result = 1;

    while (n-- > 0)
        result = result * x;

    return result;
}

//			                ARRAY ARGUMENTS

int f(int a[])		/* no length specified */
{
	...
}

int sum_array(int a[], int n) //array must have specified length, hence 'n'
{
	int i, sum = 0;

	for (i = 0; i < n; i++)
		sum += a[i];

	return sum;
}

int sum_array(int a[], int n);  //prototype
int sum_array(int [], int);  //prototype without parameter names

#define LEN 100

int main(void)
{
    int b[LEN], total;
    ...
    total = sum_array(b, LEN);
    ...
}

when calling a function with an array argument, you can tell the function that
    the array is smaller than it is and it will only calculate the first x
    elements

total = sum_array(b, 50);

functions are allowed to change the elements of an array parameter, and the
    change is reflected in the corresponding argument

void store_zeros(int a[], int n)
{
    int i;

    for (i = 0; i < n; i++)
        a[i] = 0;
}

the call

store_zeros(b, 100);

this will store zeros into the first 100 elements of array b
this may seem like a contradiction to the fact that C passes argument by value;
    though it is not a contradiction, it cannot be explained until Section 12.3
only the length of the first element of a multi-dimensional array may be
    omitted when the parameter is declared

#define LEN 10

int sum_two_dimensional_array(int a[][LEN], int n)
{
    int i, j, sum = 0;

    for (i = 0; i < n; i++)
        for (j = 0; j < LEN; j++)
            sum += a[i][j];

    return sum;
}

//                          C99 - VARIABLE-LENGTH ARRAY PARAMETERS

int sum_array(int n, int a[n])
{
    ...
}

putting the parameters in the correct order is important with variable-length
    array parameters; if a[n] was listed first, the compiler would give an
    error because it has not yet seen 'n'.

int sum_array(int n, int a[n]); //prototype
int sum_array(int n, int a[*]); //prototype

since parameter names may be omitted in function declarations, if the first
    parameter is omitted, you would not be able to specify the length of the
    array, but '*' provides a clue that the length of the array is related to
    parameters earlier in the list

int sum_array(int, int [*]); //prototype
int sum_array(int n, int a[]); //prototype
int sum_array(int, int []); //prototype (not a good choice)

the length of a variable-length array parameter can be any expression

int concatenate(int m, int n, int a[m], int b[n], int c[m+n])
{
    ...
}

int sum_two_dimensional_array(int n, int m, int a[n][m])
{
    int i, j, sum = 0;

    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            sum += a[i][j];

    return sum;
}

prototypes for the above function:

int sum_two_dimensional_array(int n, int m, int a[n][m]);
int sum_two_dimensional_array(int n, int m, int a[*][*]);
int sum_two_dimensional_array(int n, int m, int a[][m]);
int sum_two_dimensional_array(int n, int m, int a[][*]);

//                          C99 - USING static IN ARRAY PARAMETER DECLARATIONS

int sum_array(int a[static 3], int n)
{
    ...
}

this guarantees that array 'a' will have a length of at least 3
if the compiler knows that an array will always have a certain minimum length,
   it can arrange to prefetch these elements from memory when the function is
   called, before the elements are needed by statements within the function
static can only be used in the first dimension of a multi-dimensional array

//                          C99 - COMPOUND LITERALS

total = sum_array((int) []{3, 0, 3, 4, 1}, 5);

in the above code,  (int) []{3, 0, 3, 4, 1}  is the compound literal
a compound literal is an unnamed array that is created on the fly by simply
    specifying which elements it contains
you do not have to specify the length of the array, although it is allowed

(int [10]){8, 6}

this literal has 10 elements; the first two values are 8 and 6, and the
    remaining elements will have the value 0
compound literals may contain arbitrary expressions:

total = sum_array((int []){2 * i, i + j, j * k}, 3);

a compound literal is an lvalue, so the values of its elements can be changed
if desired, a compound literal can be made read-only using const:

(const int []){5, 4}

/*** CHAPTER                    9.4                   THE return STATEMENT ***/


