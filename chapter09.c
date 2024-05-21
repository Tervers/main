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

//			    average.c - COMPUTES AVERAGES OF THREE NUMBERS

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

//			    pun2.c - PRINTS A BAD PUN

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


