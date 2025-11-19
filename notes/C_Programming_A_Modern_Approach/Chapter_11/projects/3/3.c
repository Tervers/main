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

	for (; *reduced_denominator;) {
       	remainder = *reduced_numerator % *reduced_denominator;
        *reduced_numerator = *reduced_denominator;
        *reduced_denominator = remainder;
    }

    num /= *reduced_numerator;
    denom /= *reduced_numerator;
}

int main(void)
{

    int num, num_copy, *reduced_numerator = &num_copy;
	int denom, denom_copy, *reduced_denominator = &denom_copy;

    printf("Enter a fraction: ");
    scanf("%d/%d", &num, &denom);

    reduce(num, denom, &reduced_numerator, &reduced_denomintor);


    printf("In lowest terms: %d/%d", num_copy, denom_copy);

    return 0;
}

