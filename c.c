/*************************************************
*                                                *
*                   Chapter 2                    *
*                                                *
*************************************************/

// Wherever a value is needed, any expression of the same type will do.

/*
*
* #include <stdio.h>        // # = Directive. Include = preprocessor type.
*
* int main(void)            // int = variable type. implies main returns an integer / status code.
*                           // void = main has no argument.
* {
* printf("I love \n");      // printf = 'print formatted' statement. library function call.
* printf("you Michelle.\n");// statements end with a ;.
* return 0;                 // return = statement. value.
* }
*
*/

// gcc -o c c.c             // -o = rename a.out to c

// Preprocessing adds directives (usually handled by compiler) ?preprocessing connects header files to source files?
// Compiles human code into machine (object) code ?human code into binary / assembly?
// Links code with library functions ?links functions from headers to object code?

/*
*
* #directives
*
* int main(void)
*
* {
*
*   declarations;           // int a;
*   initialization;         // int a = 1, b = 2;
*   assignments;            // a = 1; b = 2;
*
*   statements;             // printf("abc\n");
*
* }
*
*/

/*

#include <stdio.h>

int main(void)


{
*
*int height, length, width, volume, weight;
*
*height = 8;
*length = 12;
*width = 10;
*volume = height * length * width;
*weight = (volume + 165) / 166;
*
*printf("Dimensions: %dx%dx%d\n", length, width, height);
*printf("Volume (cubic inches): %d\n", volume);
*printf("Dimensional weight (pounds): %d\n", weight);
*
*return 0;
*
*}
*
*/

// volume = height * length * width;
// printf("%d\n", volume);

// can also be written as:

// printf("%d\n", height * length * width);

/*

 #include <stdio.h>

 int main(void)

{

   int height, length, width, volume, weight;

   printf("Enter height of box: ");
   scanf("%d", &height);   // 'scan formatted' function to accept user input.
   printf("Enter length of box: ");
   scanf("%d", &length);
   printf("Enter width of box: ");
   scanf("%d", &width);
   volume = height * length * width;
   weight = (volume + 165) / 166;

   printf("Volume (cubic inches): %d\n", volume);
   printf("Dimensional weight (pounds): %d\n", weight);

   return 0;

}

*/

/*

#include <stdio.h>

#define FREEZING_PT 32.0f
#define SCALE_FACTOR (5.0f / 9.0f)

int main(void)

{
	float fahrenheit, celsius;

		printf("Enter Fahrenheit temperature: \n");

		scanf("%f", &fahrenheit);

	celsius = (fahrenheit - FREEZING_PT) * SCALE_FACTOR;

		printf("Celcius equivalent: %.1f\n", celsius);

	return 0;

}

*/

// printf("Height: %d\n", height); // contains 7 'TOKENS'
// 1: printf  2: (  3: "Height: %d\n"  4: ,  5: height  6: )  7: ;
// preprocessing directives require a separate line each.
// entire main() function can be on one line.

/*

#include <stdio.h>
#define FREEZING_PT 32.0f
#define SCALE_FACTOR (5.0f / 9.0f)
int main(void){float fahrenheit,celsius;printf("Enter Fahrenheit temperature: ");scanf("%f", &fahrenheit);celsius=(fahrenheit-FREEZING_PT)*SCALE_FACTOR;printf("Celcius equivalent: %.1f\n", celsius);return 0;}

*/


// SECTION 2 EXERCISES


// 2a - Identify the directives and statements in this program:
// 2b - What output does the program produce?

/*

#include <stdio.h>	// include directive

int main(void)

{
        printf("Parkinson's Law:\nWork expands so as to ");	// printf statement
        printf("fill the time\n");	// printf statement
	printf("available for its completion.\n");	// printf statement

      	return 0;	// return statement

}

*/

// Parkinson's Law:
// Work expands so as to fill the time
// available for its completion.


// 3a - Condense 'dweight.c' by replacing assignments with initializers and by removing the weight variable // with an inline printf expression.
// printf("Weight: %d\n", (volume + 165) / 166);

/*

#include <stdio.h>

int main()
{
	int radius;
	float equation = (4.0f / 3.0f);
	float pi = 3.1415;

	printf("Enter radius (meters): \n");
	scanf("%d", &radius);

	printf("The volume of a sphere with radius of %d meters is %f.\n", radius, (pi * equation * (radius * radius * radius)));

	return 0;

}

*/

/*

#include <stdio.h>

int main(void)
{
	int x = 0;

	printf("((((3x + 2)x - 5)x - 1)x + 7)x - 6\n");
	printf("Enter value for 'x' to solve:\n");
	scanf("%d", &x);

	printf("The answer is: %d\n",
			((((3 * x + 2) * x - 5 ) * x - 1 ) * x + 7 ) * x - 6);


	return 0;

}

*/

/*

#include <stdio.h>

int main(void)

{
	int price = 0;

	printf("Enter dollar amount to pay: \n");
	scanf("%d", &price);

	printf("$20 bills: %d\n", price / 20);
	price = price - (20 * (price / 20));
	printf("$10 bills: %d\n", price / 10);
	price = price - (10 * (price / 10));
	printf("$5 bills: %d\n", price / 5);
	price = price - (5 * (price / 5));
	printf("$1 bills: %d\n", price / 1);


	return 0;
}

*/

/*

#include <stdio.h>

int main(void)

{
	float loan = 0.0, interest = 0.0, payment= 0.0;

	printf("Enter amount of loan: \n");
	scanf("%f", &loan);

	printf("Enter interest rate: \n");
	scanf("%f", &interest);

	printf("Enter monthly payment: \n");
	scanf("%f", &payment);

	loan = ((((interest / 100.0f) / 12.0f) * loan) + loan);
	loan = loan - payment;              // loan =- payment;

	printf("Balance remaining after first payment: %.2f\n", loan);

    loan = ((((interest / 100.0f) / 12.0f) * loan) + loan);
	loan = loan - payment;

	printf("Balance remaining after second payment: %.2f\n", loan);

    loan = ((((interest / 100.0f) / 12.0f) * loan) + loan);
	loan = loan - payment;

	printf("Balance remaining after third payment: %.2f\n", loan);

	return 0;

}

*/

/*************************************************
*                                                *
*                   Chapter 3                    *
*                                                *
*************************************************/


/*   3.1 The printf Function   */


//printf displays 'format string.' printf(string, expr1, expr2, ...)
//% = conversion specifications (converts from binary to printed)
//%m.pX %-m.pX  = conversion specification formats
//m = minimum field width = number of characters to print
//fewer than m characters, the value is right-justified
//-m causes left-justification
//p = precision = depends on choice of X
//X = conversion specifier = indicates which conversion to apply
//common specifiers:
//d = decimal. p = minimum # of digits to display
//f = fixed-decimal float. p = # of digits after decimal. 0 = no decimal
//e = exponential float. p = # of digits after decimal. 0 = no decimal
//g = displays float in either fixed or exponential format depending
//   on number size. p = maximum # of significant digits. Doesn't
//   show trailing numbers

/*

#include <stdio.h>

int main(void)
{
    int i;
    float x;

    i = 40;
    x = 839.21f;

    printf("|%d|%5d|%-5d|%5.3d|\n", i, i, i, i);    //|40|   40|40   |  040|
    printf("|%10.3f|%10.3e|%-10g|\n", x, x, x);     //|   839.210| 8.392e+02|839.21   |

    return 0;

}

*/

//Alert (bell)   \a
//Backspace   \b
//New line   \n
//Horizontal tab   \t
//Double quote   \"
//Double backslash   \\


/*   3.2 The scanf Function   */


//scanf conversions are essentially the same as printf
//scanf often only contains conversion specifications
//scanf("%d%d%f%f", &i, &j, &x, &y);
//scanf ignores 'white-space characters': space, horizontal and vertical tab,
//   form-feed, new-line
//scanf read integer order = digit, +, -, digits until nondigit
//scanf read float order = + or -, digits possibly with ., e, + or -, digits
//   until nondigit
//%e, %f, %g are interchangeable with scanf
//1-20.3-4.0e3
//1|-20|0.3|-4.0e3
//scanf will process characters in a format string depending if its a
//   white-space character or other character
//with one or more consecutive white-spaces, scanf repeatedly reads until
//   non-space character
//one space in the 'format string' will match any number of spaces from user
//   input
//a space in scanf doesn't actually make a space
//suppose a format string is "%d/%d"
//if user input is ' 5/ 96', scanf skips first space, matches %d with 5,
//   matches / with /, skips a space looking for integer, then matches %d
//   with 96
//if user input is ' 5 / 96' instead, scanf skips one space, matches %d with 5,//   attempts to match a space with /. There is no match, scanf puts space
//   back; ' / 96' remain to be read by next scanf.
//allow spaces after first number by adding a space into format string:
//   "%d /%d"

/*

#include <stdio.h>

int main(void)
{
    int num1, denom1, num2, denom2, result_num, result_denom;

    printf("Enter first fraction: ");
    scanf("%d/%d", &num1, &denom1);

    printf("Enter second fraction: ");
    scanf("%d/%d", &num2, &denom2);

    result_num = num1 * denom2 + num2 * denom1;
    result_denom = denom1 * denom2;
    printf("The sum is %d/%d\n", result_num, result_denom);

    return 0;
}

*/

9.97e10
