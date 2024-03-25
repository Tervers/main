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

	loan = loan - payment;
	loan = (interest / 100.0f) / 12.0f * loan + loan;

	printf("Balance remaining after first payment: %.2f\n", loan);

	return 0;

}
