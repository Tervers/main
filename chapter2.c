/******************************************************************************
*   CHAPTER                         2                        C FUNDAMENTALS   *
******************************************************************************/

/***   CHAPTER                2.1                 WRITING A SIMPLE PROGRAM ***/

/***                  pun.c - displays a message when run                  ***/

#include <stdio.h>

int main(void)
{

    printf("I love ");
    printf("you Michelle.\n");

    return 0;
}

# = directive. include = preprocessor type.
stdio.h = standard input/output library
main = programs executable code which represents the main program
int = variable type. implies main returns an integer / status code
void = main has no argument
return 0 = tells program to return the value 0 to OS when program terminates
statements end with a ;
printf = 'print formatted' statement. library function call from stdio.h

/***                         COMPILING AND LINKING                         ***/

preprocessing adds directives (usually handled by compiler)
?preprocessing connects header files to source files?
compiles human code into machine (object) code
links code with library functions
gcc -o c c.c        // -o = rename a.out to c

/***   CHAPTER          2.2         THE GENERAL FORM OF A SIMPLE PROGRAM   ***/

#include <stdio.h>
int main(void)
{
   statements
}

C programs rely on three key language features:
directives - editing commands that modifty program prior to compilation
functions - named blocks of executable code (main)
statements - commands to be performed when the program runs

#directives

int main(void)
{
   declarations;           // int a;
   initialization;         // int a = 1, b = 2;
   assignments;            // a = 1; b = 2;

   statements;             // printf("abc\n");

   return 0;
}

/***                              DIRECTIVES                               ***/

a preprocessor first edits a program before the program  is compiled
directives are commands intended for the preprocessor
#include <stdio.h> says that information inside stdio.h should be included into
    the program before compilation
headers (.h) contain information about some part of the standard library
C has no built-in read and write commands, functions in the standard library
    supply these (printf)
directives always begin with a #
directives are one line long and the line ends with no special marker

/***                               FUNCTIONS                               ***/

in C, a function is a series of statements that have been given a name
there are also functions provided by the C language called library functions
some functions compute a value; some dont
a function that computes a value uses the return statement to specify what
    value it returns
"main" function is mandatory, it gets called automatically when program is
    executed

int main(void)
return 0;

int indicates main function returns an integer value
main returns a status code that is given to the OS when the program ends
void indicates main has no arguments
return 0 causes main to terminate (which ends the program) and indicates main
    to return a value of 0

 /***                              STATEMENTS                              ***/

statements are commands to be executed when the program runs
return is a statement
printf is a statement and also a function call
asking a function to perform its task is known as 'calling the function'

printf("To C, or not to C: that is the question.\n");

pun.c calls the printf function to display a string on the screen
statements end with a ; (except compound statements)

/***   CHAPTER                2.4               VARIABLES AND ASSIGNMENT   ***/

/***                               VARIABLES                               ***/

most programs need to perform calculations before producing output
so they need to store data temporarily during program execution
variables are storage locations for temporary data

/***                                 TYPES                                 ***/

every variable must have a type
type specifies what kind of data it will hold
type affects how the variable is stored and what operations can be performed
int can store whole numbers (0, 1,392, -2553)
largest int value is typically 2,147,483,647 but can be as small as 32,767

float can store much larger numbers
float can store numbers with digits after the decimal point (379.125)
float arithmetic may be slower than arithmetic on int numbers
float values are often approximations

/***                             DECLARATIONS                              ***/

variables must be declared
to declare a variable, specify its type, then name it

int height;         /* variable 'height' of type 'int' */
float profit;       /* variable 'profit' of type 'float' */
int height, length, width, volume;

#include <stdio.h>
int main(void)
{
   declarations
   statements
}

in c99, declarations do not have to be placed before statements

/***                              ASSIGNMENT                               ***/

assignment is giving a variable a value
constants are values assigned to variables
float constants should end with 'f' to avoid compiler warnings

height = 8;       /* variable = constant */
length = 10;      /* length   = 10       */
pi = 3.14f;

/***         dweight.c - computes the dimensional weight of a box          ***/

#include <stdio.h>

int main(void)
{
int height, length, width, volume, weight;

height = 8;
length = 12;
width = 10;
volume = height * length * width;
weight = (volume + 165) / 166;

printf("Dimensions: %dx%dx%d\n", length, width, height);
printf("Volume (cubic inches): %d\n", volume);
printf("Dimensional weight (pounds): %d\n", weight);

return 0;
}

/***                            INITIALIZATION                             ***/

a variable that doesn't have a default value is uninitialized
initialization happens when you give a variable a value during declaration

int height;       /* declaration */
height = 10;      /* assignment */
int height = 10;  /* initialization */
type variable = initializer

/***         dweight2.c - computes the dimensional weight of a box         ***/

#include <stdio.h>

int main(void)
{
   int height, length, width, volume, weight;

   printf("Enter height of box: ");
   scanf("%d", &height);   //'scan formatted' function
   printf("Enter length of box: ");
   scanf("%d", &length);   //scanf receives user input
   printf("Enter width of box: ");
   scanf("%d", &width);

   volume = height * length * width;
   weight = (volume + 165) / 166;

   printf("Volume (cubic inches): %d\n", volume);
   printf("Dimensional weight (pounds): %d\n", weight);

   return 0;
}

/***   CHAPTER              2.6             DEFINING NAMES FOR CONSTANTS   ***/

when a program contains constants, ideally they should be given names
a macro definition is used to name constants

#define INCHES_PER_POUND 166

#define is a preprocessor like #include, no ; goes at the end of the line
macro values can be expressions
enclose the expression with parenthesis if it contains operators

#define RECIPROCAL_OF_PI (1.0f / 3.14159f)

/***       celcius.c - converts a fahrenheit temperature to celsius        ***/

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

/***   CHAPTER                      2.7                      IDENTIFIERS   ***/

identifiers are names for variables, functions, macros, and other entities
may contain letters, digits, and underscores
must begin with a letter or underscore
case-sensitive

times10  get_next_char  _done  currentPage  nameAndAddress  SymbolTable

/***                               KEYWORDS                                ***/

some words have special significance in C and cannot be used as identifiers
these keywords are also case-sensitive
names of functions in the standard library contain only lower-case letters

/***   CHAPTER                 2.8                 LAYOUT OF A C PROGRAM   ***/

tokens are groups of characters that can't be split up without changing their
    meaning

printf("Height: %d\n", height);   /* contains 7 'TOKENS' */

1: printf  2: (  3: "Height: %d\n"  4: ,  5: height  6: )  7: ;

amount of space between tokens isn't usually critical
space between tokens can make it easier on the eyes to read
preprocessing directives require a separate line each
entire main() function can be on one line, but difficult to read this way
indentation can make nesting easier to spot (declarations inside main)
blank lines can divide a program into logical units

#include <stdio.h>
#define FREEZING_PT 32.0f
#define SCALE_FACTOR (5.0f / 9.0f)
int main(void){float fahrenheit,celsius;printf("Enter Fahrenheit temperature: ");scanf("%f", &fahrenheit);celsius=(fahrenheit-FREEZING_PT)*SCALE_FACTOR;printf("Celsius equivalent: %.1f\n", celsius);return 0;}

statements can be divided over any number of lines

printf("Dimensional weight (pounds): %d\n",
        (volume + INCHES_PER_POUND - 1) / INCHES_PER_POUND);

/***   CHAPTER                        2                        EXERCISES   ***/

2(a) - Identify the directives and statements in this program:
2(b) - What output does the program produce?

(a)
#include <stdio.h>	// include directive

int main(void)
{
printf("Parkinson's Law:\nWork expands so as to "); // printf statement
printf("fill the time\n");	                    // printf statement
printf("available for its completion.\n");          // printf statement

return 0;	                                    // return statement
}

(b)
Parkinson's Law:
Work expands so as to fill the time
available for its completion.

3. Condense dweight.c by replacing assignments with initializers and by
     removing the weight variable // with an inline printf expression.

printf("Weight: %d\n", (volume + 165) / 166);

/***   CHAPTER                   2                  PROGRAMMING PROJECTS   ***/

2/3. Write a program that computes the volume of a sphere with a 10-meter
     radius, then modify it so that it prompts the user to enter the radius of
     the sphere.

#include <stdio.h>

int main()
{
	int radius;
	float equation = (4.0f / 3.0f);
	float pi = 3.1415f;

	printf("Enter radius (meters): \n");
	scanf("%d", &radius);

	printf("The volume of a sphere with radius of %d meters is ");
	printf("%f.", radius, (pi * equation * (radius * radius * radius)));
	printf("\n");

	return 0;
}

5. Write a program that asks the user to enter a value for x and then displays
     the value of the following polynomial:

#include <stdio.h>

int main(void)
{
	int x = 0;

	printf("((((3x + 2)x - 5)x - 1)x + 7)x - 6\n");
	printf("Enter value for 'x' to solve:\n");
	scanf("%d", &x);

	printf("The answer is: ");
	printf("%d", ((((3 * x + 2) * x - 5 ) * x - 1 ) * x + 7 ) * x - 6);
    	printf("\n");

	return 0;
}

7. Write a program that asks the user to enter a dollar amount and then shows
     how to pay that amount using the smallest number of $20, $10, $5, and $1
     bills.

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

8. Write a program that calculates the remaining balance on a loan after the
     first, second, and third monthly payments:

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
