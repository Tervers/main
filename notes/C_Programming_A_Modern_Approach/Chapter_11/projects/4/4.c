/*
Modify Programming Project 3 from Chapter 6 so that it includes the following
	function:
	void reduce(int numerator, int denominator, int *reduced_numerator,
				int *reduced_denominator);

numerator and denominator are the numerator and denominator of a fraction.
	*reduced_numerator and *reduced_denominator are pointers to variables in
	which the function will store the numerator and denominator of the fraction
	once it has been reduced to lowest terms.
*/

#include <stdio.h>

void reduce(int numerator, int denominator, int *reduced_numerator,
			int *reduced_denominator)
{
	int remainder;

	for (; denominator;) {
       	remainder = numerator % denominator;
        numerator = denominator;
        denominator = remainder;
    }

    *reduced_numerator /= numerator;
    *reduced_denominator /= numerator;
}

int main(void)
{

    int num, denom;

    printf("Enter a fraction: ");
    scanf("%d/%d", &num, &denom);

    reduce(num, denom, &num, &denom);

    printf("In lowest terms: %d/%d\n", num, denom);

    return 0;
}

