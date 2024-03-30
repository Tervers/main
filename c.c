/******************************************************************************
*                                                                             *
*   CHAPTER                         2                        C FUNDAMENTALS   *
*                                                                             *
******************************************************************************/



/*   CHAPTER                  2.1                 WRITING A SIMPLE PROGRAM   */



//pun.c - DISPLAYS A MESSAGE WHEN RUN


/*

#include <stdio.h>

int main(void)

{

    printf("I love \n");
    printf("you Michelle.\n");

    return 0;

}

*/


//# = directive. include = preprocessor type.
//stdio.h = standard input/output library
//main = program's executable code which represents the main program
//int = variable type. implies main returns an integer / status code
//void = main has no argument
//return 0 = tells program to return the value 0 to OS when program terminates
//statements end with a ;
//printf = 'print formatted' statement. library function call from stdio.h



//COMPILING AND LINKING



//Preprocessing adds directives (usually handled by compiler)
//?preprocessing connects header files to source files?
//Compiles human code into machine (object) code
//Links code with library functions
//gcc -o c c.c   // -o = rename a.out to c



/*   CHAPTER            2.2           THE GENERAL FORM OF A SIMPLE PROGRAM   */



//#include <stdio.h>
//int main(void)
//{
//   statements
//}

//C programs rely on three key language features:
//directives - editing commands that modifty program prior to compilation
//functions - named blocks of executable code (main)
//statements - commands to be performed when the program runs


/*

#directives

int main(void)

{

   declarations;           // int a;
   initialization;         // int a = 1, b = 2;
   assignments;            // a = 1; b = 2;

   statements;             // printf("abc\n");

   return 0;

}

*/



//DIRECTIVES



//a preprocessor first edits a program before the program  is compiled
//directives are commands intended for the preprocessor
//#include <stdio.h> says that information inside stdio.h should be included
//   into the program before compilation
//headers (.h) contain information about some part of the standard library
//C has no built-in read and write commands, functions in the standard library
//   supply these (printf)
//directives always begin with a #
//directives are one line long and the line ends with no special marker



//FUNCTIONS



//in C, a function is a series of statements that have been given a name
//there are also functions provided by the C language called library functions
//some functions compute a value; some don't
//a function that computes a value uses the return statement to specify what
//   value it returns
//'main' function is mandatory, it gets called automatically when program
//   is executed

//int main(void)
//return 0;

//int indicates main function returns an integer value
//main returns a status code that is given to the OS when the program ends
//void indicates main has no arguments
//return 0 causes main to terminate (which ends the program) and indicates
//   main to return a value of 0



//STATEMENTS



//statements are commands to be executed when the program runs
//return is a statement
//printf is a statement and also a function call
//asking a function to perform its task is known as 'calling the function'

//printf("To C, or not to C: that is the question.\n");

//pun.c calls the printf function to display a string on the screen
//statements end with a ; (except compound statements)



/*   CHAPTER                  2.4                 VARIABLES AND ASSIGNMENT   */



//VARIABLES



//most programs need to perform calculations before producing output
//so they need to store data temporarily during program execution
//variables are storage locations for temporary data



//TYPES



//every variable must have a type
//type specifies what kind of data it will hold
//type affects how the variable is stored and what operations can be performed
//int can store whole numbers (0, 1,392, -2553)
//largest int value is typically 2,147,483,647 but can be as small as 32,767

//float can store much larger numbers
//float can store numbers with digits after the decimal point (379.125)
//float arithmetic may be slower than arithmetic on int numbers
//float values are often approximations



//DECLARATIONS



//variables must be declared
//to declare a variable, specify its type, then name it

//int height;         /* variable 'height' of type 'int' */
//float profit;       /* variable 'profit' of type 'float' */
//int height, length, width, volume;

//#include <stdio.h>
//int main(void)
//{
//   declarations
//   statements
//}

//in c99, declarations do not have to be placed before statements



//ASSIGNMENT



//assignment is giving a variable a value
//constants are values assigned to variables
//float constants should end with 'f' to avoid compiler warnings

//height = 8;       /* variable = constant */
//length = 10;      /* length   = 10       */
//pi = 3.14f;


//dweight.c - COMPUTES THE DIMENSIONAL WEIGHT OF A BOX


/*

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

*/



//INITIALIZATION



//a variable that doesn't have a default value is uninitialized
//initialization happens when you give a variable a value during declaration

//int height;       /* declaration */
//height = 10;      /* assignment */
//int height = 10;  /* initialization */
//type variable = initializer


//dweight2.c - COMPUTES THE DIMENSIONAL WEIGHT OF A BOX


/*

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

*/



/*   CHAPTER               2.6               DEFINING NAMES FOR CONSTANTS   */



//when a program contains constants, ideally they should be given names
//a macro definition is used to name constants

//#define INCHES_PER_POUND 166

//#define is a preprocessor like #include, no ; goes at the end of the line
//macro values can be expressions
//enclose the expression with parenthesis if it contains operators

//#define RECIPROCAL_OF_PI (1.0f / 3.14159f)


//celcius.c - CONVERTS A FAHRENHEIT TEMPERATURE TO CELSIUS


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



/*   CHAPTER                        2.7                       IDENTIFIERS   */



//identifiers are names for variables, functions, macros, and other entities
//may contain letters, digits, and underscores
//must begin with a letter or underscore
//case-sensitive

//times10  get_next_char  _done  currentPage  nameAndAddress  SymbolTable



//KEYWORDS



//some words have special significance in C and cannot be used as identifiers
//these keywords are also case-sensitive
//names of functions in the standard library contain only lower-case letters



/*   CHAPTER                     2.8                     LAYOUT OF A C PROGRAM



//tokens are groups of characters that can't be split up without changing their
//   meaning

//printf("Height: %d\n", height);   /* contains 7 'TOKENS' */

//1: printf  2: (  3: "Height: %d\n"  4: ,  5: height  6: )  7: ;

//amount of space between tokens isn't usually critical
//space between tokens can make it easier on the eyes to read
//preprocessing directives require a separate line each
//entire main() function can be on one line, but difficult to read this way
//indentation can make nesting easier to spot (declarations inside main)
//blank lines can divide a program into logical units


/*

#include <stdio.h>
#define FREEZING_PT 32.0f
#define SCALE_FACTOR (5.0f / 9.0f)
int main(void){float fahrenheit,celsius;printf("Enter Fahrenheit temperature: ");scanf("%f", &fahrenheit);celsius=(fahrenheit-FREEZING_PT)*SCALE_FACTOR;printf("Celsius equivalent: %.1f\n", celsius);return 0;}

*/


//statements can be divided over any number of lines


/*
    printf("Dimensional weight (pounds): %d\n",
           (volume + INCHES_PER_POUND - 1) / INCHES_PER_POUND);
*/



/*   CHAPTER                          2                          EXERCISES   */



//2a - Identify the directives and statements in this program:
//2b - What output does the program produce?

/*

#include <stdio.h>	// include directive

int main(void)

{
printf("Parkinson's Law:\nWork expands so as to "); // printf statement
printf("fill the time\n");	                        // printf statement
printf("available for its completion.\n");	        // printf statement

return 0;	                                        // return statement

}

*/

//Parkinson's Law:
//Work expands so as to fill the time
//available for its completion.


//3a - Condense 'dweight.c' by replacing assignments with initializers and by
//   removing the weight variable // with an inline printf expression.

//printf("Weight: %d\n", (volume + 165) / 166);

/*

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

*/

/*

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



/******************************************************************************
*                                                                             *
*   CHAPTER                     3                    FORMATTED INPUT/OUTPUT   *
*                                                                             *
******************************************************************************/



/*   CHAPTER                    3.1                    THE printf FUNCTION   */



//printf displays a format string

//printf("string", expr1, expr2, ...)



//CONVERSION SPECIFICATIONS



//% = conversion specifications (converts from binary to printed)
//%d converts binary int value to a string of digits
//%m.pX %-m.pX  = conversion specification formats

//m = minimum field width = number of characters to print
//fewer than m characters, the value is right-justified
//"%4d" user enters 123 = ' 123'
//-m causes left-justification
//"%-4d" user enters 123 = '123 '
//field width expands if more than m characters required:
//   ("%4d", 12345) would show 12345

//p = precision = depends on choice of X
//X = conversion specifier = indicates which conversion to apply
//common specifiers:
//d = decimal. p = minimum # of digits to display (extra zeros if necessary)
//f = fixed-decimal float. p = # of digits after decimal. 0 = no decimal
//e = exponential float. p = # of digits after decimal. 0 = no decimal
//g = displays float in either fixed or exponential format depending on number
//   size. p = maximum # of significant digits. Doesn't show trailing numbers


//tprintf.c - PRINTS INT AND FLOAT VALUES IN VARIOUS FORMATS


/*

#include <stdio.h>

int main(void)
{
    int i;
    float x;

    i = 40;
    x = 839.21f;

    printf("|%d|%5d|%-5d|%5.3d|\n", i, i, i, i);
          //|40|   40|40   |  040|
    printf("|%10.3f|%10.3e|%-10g|\n", x, x, x);
          //|   839.210| 8.392e+02|839.21    |

    return 0;

}

*/



//ESCAPE SEQUENCES



//Alert (bell)   \a
//Backspace   \b
//New line   \n
//Horizontal tab   \t
//Double quote   \"
//Double backslash   \\



/*   CHAPTER                     3.2                    THE scanf FUNCTION   */



//scanf handles Conversion Specifications, white-space characters, and
//   'ordinary' characters differently
//scanf attempts to match input characters with conversion specifications
//scanf conversions are essentially the same as printf
//scanf READs a character when it matches format
//scanf often only contains conversion specifications
//starting from the left, scanf tries to find each *conversion specification*
//   with an item of appropriate type from *input* data, *skipping blank space
//   when necessary*
//STOPs reading when encountering a character that can't possibly match
//PUTs BACK if the item was read successfully
//scanf RETURNs if item was not read successfully

//scanf("%d%d%f%f", &i, &j, &x, &y);

//  1           //
//-20   .3      //user input
//   -4.0e3     //

//is equivalent to 1-20.3-4.0e3
//scanf ignores 'white-space characters': space, horizontal and vertical tab,
//   form-feed, new-line
//scanf read integer order = digit, +, -, digits until nondigit
//scanf read float order = + or -, digits possibly with ., e, + or -, digits
//   until nondigit
//%e, %f, %g are interchangeable with scanf
//1|-20|0.3|-4.0e3
//scanf will process characters in a format string differently depending if
//   its a white-space character or other character
//with one or more consecutive white-spaces, scanf repeatedly reads until
//   non-white-space character encountered



//ORDINARY CHARACTERS IN FORMAT STRINGS



//white-space chars read from input until non-white-space character, which is
//   'put back'
//number of white-space chars in format string irrelevant; it will match ANY
//   number of white-space chars, including NONE
//if non-white-space chars match, scanf continues
//if no match, scanf aborts

//suppose a format string is "%d/%d"
//if user input is ' 5/ 96', scanf skips first space, matches %d with 5,
//   matches / with /, skips a space looking for integer, then matches %d with
//   96
//if user input is ' 5 / 96' instead, scanf skips one space, matches %d with 5,
//   attempts to match a space with /. There is no match, scanf puts the space
//   back; ' / 96' remain to be read by next scanf.
//allow spaces after first number by adding a space into string: "%d /%d"


//addfrac.c - ADDS TWO FRACTIONS


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



/*   CHAPTER                          3                          EXERCISES   */



//1. What output do the following calls of printf produce?
                                   //123456789012       123456789012
//printf("%6d, %4d\n", 86, 1040);   '    86', '1040'   '   86, 1040'
//printf("%12.5e\n", 30.253);       '   3.0253e-1'     '3.02530e+001'
//printf("%.4f\n", 83.162);         '83.1620'          '83.1620'
//printf("%-6.2g\n", .0000009979);  '9.9e10'           '1e-006'


//2. Write calls of printf that display a float variable x int the following
//     formats.

//printf("%-8.1e", 8.47);
//printf("%10.6e", 8.47);
//printf("%-8.3f", 8.47);
//printf("%6.0f", 8.47);


//3. Indicate whether the 2 strings are equivalent. If not, show how.

//3a - "%d" vs " %d" : equivalent
//3b - "%d-%d-%d" vs "%d -%d -%d" : equivalent
//3c - "%f" vs "%f " : unequal - "%f " won't finish until a non-white-space
//     character is entered
//3d - "%f,%f" vs "%f, %f" : equivalent


//4. Suppose scanf("%d%f%d", &i, &x, &j); User enters '10.3 5 6', what values
//     will show?

//10 5 6


//5. Suppose scanf("%f%d%f", &x, &i, &y); User enters '12.3 45.6 789', what
//     values will show?

//12.3 45 0.6


//6. Show how to modify addfrac.c so that user can enter fractions that contain
//     spaces before and after each / character.

//scanf("%d/%d") : scanf("%d /%d")



/*   CHAPTER                     3                    PROGRAMMING PROJECTS   */



//1.

/*

#include <stdio.h>

int main(void)
{
    int mm = 0, dd = 0, yyyy = 0;

    printf("Please enter a date in the format of mm/dd/yyyy.")
    printf(" For example, February 7, 2005 would be 02/07/2005\n");
    scanf("%d/%d/%d", &mm, &dd, &yyyy);
    printf("You have entered %2.2d/%2.2d/%4.4d", mm, dd, yyyy);

    return 0;
}

*/


//2.

/*

#include <stdio.h>

int main(void)

{
    int item = 0, mm = 0, dd = 0, yyyy = 0;
    float price = 0.0f;

    printf("Enter item number: ");
    scanf("%d", &item);
    printf("Enter unit price: ");
    scanf("%f", &price);
    printf("Enter purchase date (mm/dd/yyyy): ");
    scanf("%d/%d/%d", &mm, &dd, &yyyy);

    printf("Item\t\tUnit\t\tPurchase\n");
    printf("\t\tPrice\t\tDate\n");
    printf("%d\t\t$%6.2f\t%d/%d/%d\n", item, price, mm, dd, yyyy);

    return 0;

}

*/


//3.

/*

#include <stdio.h>

int main(void)

{
	int gs1 = 0, group = 0, pub =0, item = 0, check = 0;

	printf("Enter ISBN: ");

	scanf("%d-%d-%d-%d-%d", &gs1, &group, &pub, &item, &check);

	printf("GS1 prefix: %d\n", gs1);
    	printf("Group identifier: %d\n", group);
	printf("Publisher code: %d\n", pub);
	printf("Item number: %d\n", item);
	printf("Check digit: %d\n", check);

	return 0;


}

*/


//4.

/*

#include <stdio.h>

int main(void)

{

	int area = 0, pre = 0, suf = 0;

	printf("Enter phone number (xxx) xxx-xxxx: \n");

	scanf("(%d) %d-%d", &area, &pre, &suf);

	printf("You entered %d.%d.%d\n", area, pre, suf);

	return 0;

}

*/


//5.

/*

#include <stdio.h>

int main(void)

{
    int a1 = 0, a2 = 0, a3 = 0, a4 = 0;
    int b1 = 0, b2 = 0, b3 = 0, b4 = 0;
    int c1 = 0, c2 = 0, c3 = 0, c4 = 0;
    int d1 = 0, d2 = 0, d3 = 0, d4 = 0;

    int rowa = 0, rowb = 0, rowc = 0, rowd = 0;
    int col1 = 0, col2 = 0, col3 = 0, col4 = 0;
    int diag1 = 0, diag2 = 0;

    printf("Enter the numbers from 1 to 16 in any order: \n");

    scanf("%d %d %d %d", &a1, &a2, &a3, &a4);
    scanf(" %d %d %d %d", &b1, &b2, &b3, &b4);
    scanf(" %d %d %d %d", &c1, &c2, &c3, &c4);
    scanf(" %d %d %d %d", &d1, &d2, &d3, &d4);

    rowa = a1+a2+a3+a4, rowb = b1+b2+b3+b4, rowc = c1+c2+c3+c4,
    rowd = d1+d2+d3+d4, col1 = a1+b1+c1+d1, col2 = a2+b2+c2+d2,
    col3 = a3+b3+c3+d3, col4 = a4+b4+c4+d4, diag1 = a1+b2+c3+d4,
    diag2 = a4+b3+c2+d1;

    printf("Row sums: %d %d %d %d\n", rowa, rowb, rowc, rowd);
    printf("Column sums: %d %d %d %d\n", col1, col2, col3, col4);
    printf("Diagonal sums: %d %d\n", diag1, diag2);

    return 0;

}

*/


//6.

/*

#include <stdio.h>

int main(void)
{
    int num1, denom1, num2, denom2, result_num, result_denom;

    printf("Enter two fractions separated by a plus sign: ");
    scanf("%d/%d+%d/%d", &num1, &denom1, &num2, &denom2);

    result_num = num1 * denom2 + num2 * denom1;
    result_denom = denom1 * denom2;
    printf("The sum is %d/%d\n", result_num, result_denom);

    return 0;
}

*/



/******************************************************************************
*                                                                             *
*   CHAPTER                          4                          EXPRESSIONS   *
*                                                                             *
******************************************************************************/



//Expressions are formulas that show how to compute a value
//the simplest expressions are variables and constants
//variables represent values that are computed at runtime
//constants represent values that don't change
//complex expressions apply operators to operands
//operands are themselves expressions

//a + (b * c)

//a is an operand; + is an operator; (b * c) is an operand;
//arithmetic operators; +, -, *, /
//relational operators; <, >, <=
//logical operators; x < 0 && x > -10;     //&& possibly wrong



/*   CHAPTER                    4.1                   ARITHMETIC OPERATORS   */



//arithmetic operators come in two forms; unary and binary

//unary operators require one operand (u-nary)
//+ = unary plus; - = unary minus
//unary + / - used to emphasize positive / negative numbers

//binary operators require two operands (bi-nary)
//additive binary: + = binary addition; - = binary subtraction
//multiplicative binary: * = multiplication; / = division; % = remainder
//the value of i % j is the remainder of i / j
//10 % 3 = 1; 12 % 4 = 0

//+, -, *, / operators allow either integer or float, with mixing
//mixing int and float creates a float
//the / operator will truncate results if both operands are integers
//1 / 2 = 0, not 0.5
//% operator requires two int operands or program won't compile
//using 0 as right operand of / or % causes undefined behavior

//in C89, if either operand is negative, division results can be rounded up or
//   down, depending on implementation
//(-9 / 7) may yield -1 or -2 depending on cpu
//in C99, division is always truncated towards 0
//implementation-defined behavior arises from purposely unspecified C language
//   details (the idea is to match the way hardware behaves)


//OPRATOR PRECEDENCE AND ASSOCIATIVITY


//arithmetic operator precedence:

//Highest: + - (unary)
//         * / %
//Lowest:  + - (binary)

//   i + j * k   is equivalent to   i + (j * k)
//     -i * -j   is equivalent to   (-i) * (-j)
//  +i + j / k   is equivalent to   (+i) + (j / k)

//left associative operators group from left to right, binary arithmetic
//   operators are left associative:

//   i - j - k   is equivalent to   (i - j) - k
//   i * j / k   is equivalent to   (i * j) / k

//right associative operators group from right to left, unary arithmetic
//   operators are right associative:

//   - + i       is equivalent to   -(+i)


//upc.c - COMPUTES A UNIVERSAL PRODUCT CODE CHECK DIGIT


/*

#include <stdio.h>

int main(void)
{
    int d, i1, i2, i3, i4, i5, j1, j2, j3, j4, j5,
        first_sum, second_sum, total;

    printf("Enter the first (single) digit: ");
    scanf("%1d", &d);
    printf("Enter first group of five digits: ");
    scanf("%1d%1d%1d%1d%1d", &i1, &i2, &i3, &i4, &i5);
    printf("Enter second group of five digits: ");
    scanf("%1d%1d%1d%1d%1d", &j1, &j2, &j3, &j4, &j5);

    first_sum = d + i2 + i4 + j1 + j3 + j5;
    second_sum = i1 + i3 + i5 + j2 + j4;
    total = 3 * first_sum + second_sum;

    printf("Check digit: %d/n", 9 - ((total - 1) % 10));

    return 0;
}

*/

//%1d allows you to store a five-digit number as five one-digit numbers
//some older compilers limit maximum value of int variable to 32,767



/*   CHAPTER                    4.2                   ASSIGNMENT OPERATORS   */



//SIMPLE ASSIGNMENT



//= simple assignment operator
//= can be used to store a variable
//assignment v = e
//evaluate expression e and copy its value to v
//e can be a constant, variable, or a more complicated expression:

//i = 5;            i is now 5
//j = i;            j is now 5

//k = 10 * i + j;   k is now 55
//if v and e don't share the same type, then e is converted to the type of v
//   as the assignment takes place:

//int i;
//float f;
//i = 72.99f;   i is now 72
//f = 136;      f is now 136.0

//assignment is an operator, like +, *, >
//the value of assignment v = e is the value of v after assignment
//thus the value of i = 72.99f is 72
//most C operators don't modify their operands; = is one that does
//an operator modifying an operand is known as a side effect



//LVALUES



//Most C operators allow operands to be variables, constants, or expressions
//= requires its left operand to be an lvalue
//lvalues represent objects stored in memory
//variables are lvalues
//constants or computational results are not lvalues



//COMPOUND ASSIGNMENT



//assignments often use their old value to compute their new value

//i = i + 2;     /* add 2 to the value of i */

//compound assignment operators allow us to shorten these types of statements

//i += 2;     /* same as i = i + 2; */

//v += e   adds e to v, storing the result in v
//v -= e   subtracts e from v, storing the result in v
//v *= e   multiplies v by e, storing the result in v
//v /= e   divides v by e, storing the result in v
//v %= e   computes remainder of v divided by e, storing the result in v

//v += e is not exactly equivalent to v = v + e
//i *= j + k isn't the same as i = i * j + k due to operator precedence
//v may also have a side effect
//compound operators are right-associative

//i += j += k;   means   i += (j += k);



/*   CHAPTER             4.3            INCREMENT AND DECREMENT OPERATORS   */



//i = i + 1;
//j = j - 1;

//i += 1;
//j -= 1;

//++ increment adds 1 to operand; --decrement subtracts 1 from operand
//can be used as prefix (++i) or postfix (i--)
//++ and -- have side effects by modifying the values of their operands

//evaluating ++i (a pre-increment) yields i + 1 and increments i (side effect)

//i = 1;
//printf("i is %d\n", ++i);     /* prints "i is 2" */
//printf("i is %d\n), i);       /* prints "i is 2" */

//evaluating i++ (a post-increment) yields i, but causes i to increment later

//i = 1;
//printf("i is %d\n", i++);     /* prints "i is 1" */
//printf("i is %d\n), i);       /* prints "i is 2" */

//++i increment immediately, i++ increment later
//C standard doesn't specify how much later, but its safe to assume its before
//   the next statement is executed

//i = 1;
//j = 2;
//k = ++i + j++;     k = 4

//i = 1;
//j = 2;
//k = i++ + j++;     k = 3

//postfix ++ -- are higher precedence than unary + - and are left-associative
//prefix ++ -- are same precedence as unary + - and are right-associative



/*   CHAPTER                   4.4                  EXPRESSION EVALUATION   */



//a = b += c++ - d + --e / -f                     /* precedence */
//a = b += (c++) - d + --e / -f                   postfix increment
//a = b += (c++) - d + (--e) / (-f)               prefix increment, unary minus
//a = b += (c++) - d + ((--e) / (-f))             multiplicative (division)
//a = b += (((c++) - d) + ((--e) / (-f)))         additive
//(a = (b += (((c++) - d) + ((--e) / (-f)))))     assignment



//ORDER OF SUBEXPRESSION EVALUATION



//
