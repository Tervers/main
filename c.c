

/******************************************************************************
*   CHAPTER                         2                        C FUNDAMENTALS   *
******************************************************************************/

/*   CHAPTER                  2.1                 WRITING A SIMPLE PROGRAM   */

                    pun.c - DISPLAYS A MESSAGE WHEN RUN

/*
#include <stdio.h>

int main(void)
{

    printf("I love \n");
    printf("you Michelle.\n");

    return 0;
}
*/

# = directive. include = preprocessor type.
stdio.h = standard input/output library
main = program's executable code which represents the main program
int = variable type. implies main returns an integer / status code
void = main has no argument
return 0 = tells program to return the value 0 to OS when program terminates
statements end with a ;
printf = 'print formatted' statement. library function call from stdio.h

                    COMPILING AND LINKING

Preprocessing adds directives (usually handled by compiler)
?preprocessing connects header files to source files?
Compiles human code into machine (object) code
Links code with library functions
gcc -o c c.c        // -o = rename a.out to c

/*   CHAPTER            2.2           THE GENERAL FORM OF A SIMPLE PROGRAM   */

#include <stdio.h>
int main(void)
{
   statements
}

C programs rely on three key language features:
directives - editing commands that modifty program prior to compilation
functions - named blocks of executable code (main)
statements - commands to be performed when the program runs

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

                    DIRECTIVES

a preprocessor first edits a program before the program  is compiled
directives are commands intended for the preprocessor
#include <stdio.h> says that information inside stdio.h should be included into
    the program before compilation
headers (.h) contain information about some part of the standard library
C has no built-in read and write commands, functions in the standard library
    supply these (printf)
directives always begin with a #
directives are one line long and the line ends with no special marker

                    FUNCTIONS

in C, a function is a series of statements that have been given a name
there are also functions provided by the C language called library functions
some functions compute a value; some don't
a function that computes a value uses the return statement to specify what
    value it returns
'main' function is mandatory, it gets called automatically when program is
    executed

int main(void)
return 0;

int indicates main function returns an integer value
main returns a status code that is given to the OS when the program ends
void indicates main has no arguments
return 0 causes main to terminate (which ends the program) and indicates main
    to return a value of 0

                    STATEMENTS

statements are commands to be executed when the program runs
return is a statement
printf is a statement and also a function call
asking a function to perform its task is known as 'calling the function'

printf("To C, or not to C: that is the question.\n");

pun.c calls the printf function to display a string on the screen
statements end with a ; (except compound statements)

/*   CHAPTER                  2.4                 VARIABLES AND ASSIGNMENT   */

                    VARIABLES

most programs need to perform calculations before producing output
so they need to store data temporarily during program execution
variables are storage locations for temporary data

                    TYPES

every variable must have a type
type specifies what kind of data it will hold
type affects how the variable is stored and what operations can be performed
int can store whole numbers (0, 1,392, -2553)
largest int value is typically 2,147,483,647 but can be as small as 32,767

float can store much larger numbers
float can store numbers with digits after the decimal point (379.125)
float arithmetic may be slower than arithmetic on int numbers
float values are often approximations

                    DECLARATIONS

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

                    ASSIGNMENT

assignment is giving a variable a value
constants are values assigned to variables
float constants should end with 'f' to avoid compiler warnings

height = 8;       /* variable = constant */
length = 10;      /* length   = 10       */
pi = 3.14f;

                    dweight.c - COMPUTES THE DIMENSIONAL WEIGHT OF A BOX

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

                    INITIALIZATION

a variable that doesn't have a default value is uninitialized
initialization happens when you give a variable a value during declaration

int height;       /* declaration */
height = 10;      /* assignment */
int height = 10;  /* initialization */
type variable = initializer

                    dweight2.c - COMPUTES THE DIMENSIONAL WEIGHT OF A BOX

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

/*   CHAPTER                2.6               DEFINING NAMES FOR CONSTANTS   */

when a program contains constants, ideally they should be given names
a macro definition is used to name constants

#define INCHES_PER_POUND 166

#define is a preprocessor like #include, no ; goes at the end of the line
macro values can be expressions
enclose the expression with parenthesis if it contains operators

#define RECIPROCAL_OF_PI (1.0f / 3.14159f)

                    celcius.c - CONVERTS A FAHRENHEIT TEMPERATURE TO CELSIUS

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

/*   CHAPTER                        2.7                        IDENTIFIERS   */

identifiers are names for variables, functions, macros, and other entities
may contain letters, digits, and underscores
must begin with a letter or underscore
case-sensitive

times10  get_next_char  _done  currentPage  nameAndAddress  SymbolTable

                    KEYWORDS

some words have special significance in C and cannot be used as identifiers
these keywords are also case-sensitive
names of functions in the standard library contain only lower-case letters

/*   CHAPTER                   2.8                   LAYOUT OF A C PROGRAM   */

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

/*
#include <stdio.h>
#define FREEZING_PT 32.0f
#define SCALE_FACTOR (5.0f / 9.0f)
int main(void){float fahrenheit,celsius;printf("Enter Fahrenheit temperature: ");scanf("%f", &fahrenheit);celsius=(fahrenheit-FREEZING_PT)*SCALE_FACTOR;printf("Celsius equivalent: %.1f\n", celsius);return 0;}
*/

statements can be divided over any number of lines

/*
    printf("Dimensional weight (pounds): %d\n",
           (volume + INCHES_PER_POUND - 1) / INCHES_PER_POUND);
*/

/*   CHAPTER                          2                          EXERCISES   */

2a - Identify the directives and statements in this program:
2b - What output does the program produce?

/*
#include <stdio.h>	// include directive

int main(void)
{
printf("Parkinson's Law:\nWork expands so as to "); // printf statement
printf("fill the time\n");	                    // printf statement
printf("available for its completion.\n");          // printf statement

return 0;	                                    // return statement
}
*/

Parkinson's Law:
Work expands so as to fill the time
available for its completion.

3a - Condense 'dweight.c' by replacing assignments with initializers and by
    removing the weight variable // with an inline printf expression.

printf("Weight: %d\n", (volume + 165) / 166);

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
*   CHAPTER                     3                    FORMATTED INPUT/OUTPUT   *
******************************************************************************/

/*   CHAPTER                    3.1                    THE printf FUNCTION   */

printf displays a format string

printf("string", expr1, expr2, ...)

                    CONVERSION SPECIFICATIONS

% = conversion specifications (converts from binary to printed)
%d converts binary int value to a string of digits
%m.pX %-m.pX  = conversion specification formats

m = minimum field width = number of characters to print
fewer than m characters, the value is right-justified
"%4d" user enters 123 = ' 123'
-m causes left-justification
"%-4d" user enters 123 = '123 '
field width expands if more than m characters required:
   ("%4d", 12345) would show 12345

p = precision = depends on choice of X
X = conversion specifier = indicates which conversion to apply
common specifiers:
d = decimal. p = minimum # of digits to display (extra zeros if necessary)
f = fixed-decimal float. p = # of digits after decimal. 0 = no decimal
e = exponential float. p = # of digits after decimal. 0 = no decimal
g = displays float in either fixed or exponential format depending on number
    size. p = maximum # of significant digits. Doesn't show trailing numbers

                   tprintf.c - PRINTS INT AND FLOAT VALUES IN VARIOUS FORMATS

/*
#include <stdio.h>

int main(void)
{
    int i;
    float x;

    i = 40;
    x = 839.21f;

    printf("|%d|%5d|%-5d|%5.3d|\n", i, i, i, i);
            |40|   40|40   |  040|
    printf("|%10.3f|%10.3e|%-10g|\n", x, x, x);
            |   839.210| 8.392e+02|839.21    |

    return 0;
}
*/

                    ESCAPE SEQUENCES

Alert (bell)   \a
Backspace   \b
New line   \n
Horizontal tab   \t
Double quote   \"
Double backslash   \\

/*   CHAPTER                     3.2                    THE scanf FUNCTION   */

scanf handles Conversion Specifications, white-space characters, and
    'ordinary' characters differently
scanf attempts to match input characters with conversion specifications
scanf conversions are essentially the same as printf
scanf READs a character when it matches format
scanf often only contains conversion specifications
starting from the left, scanf tries to find each conversion specification with
    an item of appropriate type from input data, skipping blank space when
    necessary
STOPs reading when encountering a character that can't possibly match
PUTs BACK if the item was read successfully
scanf RETURNs if item was not read successfully

scanf("%d%d%f%f", &i, &j, &x, &y);

  1           //
-20   .3      //user input
   -4.0e3     //

is equivalent to 1-20.3-4.0e3
scanf ignores 'white-space characters': space, horizontal and vertical tab,
    form-feed, new-line
scanf read integer order = digit, +, -, digits until nondigit
scanf read float order = + or -, digits possibly with ., e, + or -, digits
    until nondigit
%e, %f, %g are interchangeable with scanf
1|-20|0.3|-4.0e3
scanf will process characters in a format string differently depending if its a
    white-space character or other character
with one or more consecutive white-spaces, scanf repeatedly reads until non-
    white-space character encountered

                    ORDINARY CHARACTERS IN FORMAT STRINGS

white-space chars read from input until non-white-space char, which is put back
number of white-space chars in format string irrelevant; it will match ANY
    number of white-space chars, including NONE
if non-white-space chars match, scanf continues
if no match, scanf aborts

suppose a format string is "%d/%d"
if user input is ' 5/ 96', scanf skips first space, matches %d with 5, matches
    / with /, skips a space looking for integer, then matches %d with 96
if user input is ' 5 / 96' instead, scanf skips one space, matches %d with 5,
    attempts to match a space with /. There is no match, scanf puts the space
    back; ' / 96' remain to be read by next scanf.
allow spaces after first number by adding a space into string: "%d /%d"

                    addfrac.c - ADDS TWO FRACTIONS

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

1. What output do the following calls of printf produce?
                                   //123456789012       123456789012
printf("%6d, %4d\n", 86, 1040);   '    86', '1040'   '   86, 1040'
printf("%12.5e\n", 30.253);       '   3.0253e-1'     '3.02530e+001'
printf("%.4f\n", 83.162);         '83.1620'          '83.1620'
printf("%-6.2g\n", .0000009979);  '9.9e10'           '1e-006'

2. Write calls of printf that display a float variable x int the following
     formats.

printf("%-8.1e", 8.47);
printf("%10.6e", 8.47);
printf("%-8.3f", 8.47);
printf("%6.0f", 8.47);

3. Indicate whether the 2 strings are equivalent. If not, show how.

3a - "%d" vs " %d" : equivalent
3b - "%d-%d-%d" vs "%d -%d -%d" : equivalent
3c - "%f" vs "%f " : unequal - "%f " won't finish until a non-white-space
     character is entered
3d - "%f,%f" vs "%f, %f" : equivalent

4. Suppose scanf("%d%f%d", &i, &x, &j); User enters '10.3 5 6', what values
     will show?

10 5 6

5. Suppose scanf("%f%d%f", &x, &i, &y); User enters '12.3 45.6 789', what
     values will show?

12.3 45 0.6

6. Show how to modify addfrac.c so that user can enter fractions that contain
     spaces before and after each / character.

scanf("%d/%d") : scanf("%d /%d")

/*   CHAPTER                     3                    PROGRAMMING PROJECTS   */

1.

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

2.

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

3.

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

4.

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

5.

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

6.

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
*   CHAPTER                          4                          EXPRESSIONS   *
******************************************************************************/

Expressions are formulas that show how to compute a value
the simplest expressions are variables and constants
variables represent values that are computed at runtime
constants represent values that don't change
complex expressions apply operators to operands
operands are themselves expressions

a + (b * c)

a is an operand; + is an operator; (b * c) is an operand;
arithmetic operators; +, -, *, /
relational operators; <, >, <=
logical operators; x < 0 && x > -10;     //&& possibly wrong

/*   CHAPTER                    4.1                   ARITHMETIC OPERATORS   */

arithmetic operators come in two forms; unary and binary

unary operators require one operand (u-nary)
+ unary plus
- unary minus
unary + / - used to emphasize positive / negative numbers

binary operators require two operands (bi-nary)
additive binary: + = binary addition; - = binary subtraction
multiplicative binary: * = multiplication; / = division; % = remainder
the value of i % j is the remainder of i / j
10 % 3 = 1; 12 % 4 = 0

+, -, *, / operators allow either integer or float, with mixing
mixing int and float creates a float
the / operator will truncate results if both operands are integers
1 / 2 = 0, not 0.5
% (modulus / mod) operator requires two int operands or program won't compile
using 0 as right operand of / or % causes undefined behavior

in C89, if either operand is negative, division results can be rounded up or
    down, depending on implementation
(-9 / 7) may yield -1 or -2 depending on cpu
in C99, division is always truncated towards 0
the value of i % j has the same unary operator as i
(-9 % 7) is -2; (9 % -7) is 2
implementation-defined behavior arises from purposely unspecified C language
    details (the idea is to match the way hardware behaves)

                    OPRATOR PRECEDENCE AND ASSOCIATIVITY

arithmetic operator precedence:

Highest: + - (unary)
         * / %
Lowest:  + - (binary)

   i + j * k   is equivalent to   i + (j * k)
     -i * -j   is equivalent to   (-i) * (-j)
  +i + j / k   is equivalent to   (+i) + (j / k)

left associative operators group left to right
binary arithmetic operators are left associative:

   i - j - k   is equivalent to   (i - j) - k
   i * j / k   is equivalent to   (i * j) / k

right associative operators group from right to left
unary arithmetic operators are right associative:

   - + i       is equivalent to   -(+i)

                    upc.c - COMPUTES A UNIVERSAL PRODUCT CODE CHECK DIGIT

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

%1d allows you to store a five-digit number as five one-digit numbers
some older compilers limit maximum value of int variable to 32,767

/*   CHAPTER                    4.2                   ASSIGNMENT OPERATORS   */

                    SIMPLE ASSIGNMENT

= simple assignment operator
= can be used to store a variable
assignment v = e
evaluate expression e and copy its value to v
e can be a constant, variable, or a more complicated expression:

i = 5;            i is now 5
j = i;            j is now 5

k = 10 * i + j;   k is now 55
if v and e don't share the same type, then e is converted to the type of v
    as the assignment takes place:

int i;
float f;
i = 72.99f;   i is now 72
f = 136;      f is now 136.0

assignment is an operator, like +, *, >
the value of assignment v = e is the value of v after assignment
thus the value of i = 72.99f is 72
most C operators don't modify their operands; = is one that does
an operator modifying an operand is known as a side effect

                    LVALUES

Most C operators allow operands to be variables, constants, or expressions
= requires its left operand to be an lvalue
lvalues represent objects stored in memory
variables are lvalues
constants or computational results are not lvalues

                    COMPOUND ASSIGNMENT

assignments often use their old value to compute their new value

i = i + 2;     /* add 2 to the value of i */

compound assignment operators allow us to shorten these types of statements

i += 2;     /* same as i = i + 2; */

v += e   adds e to v, storing the result in v
v -= e   subtracts e from v, storing the result in v
v *= e   multiplies v by e, storing the result in v
v /= e   divides v by e, storing the result in v
v %= e   computes remainder of v divided by e, storing the result in v

v += e isnt exactly equivalent to v = v + e
v += e evaluates v once; v = v + e evaluates v twice
thus any evaluation of v is multiplied

a[i++] += 2;     i is incremented once
a[i++] = a[i++] + 2;     i is modified as well as used elsewhere in the
    statement, so the effect of executing the statement is undefined

i *= j + k isn't the same as i = i * j + k due to operator precedence
v may also have a side effect
compound operators are right-associative

i += j += k;   means   i += (j += k);

/*   CHAPTER             4.3             INCREMENT AND DECREMENT OPERATORS   */

i = i + 1;
j = j - 1;

i += 1;
j -= 1;

++ increment adds 1 to operand; --decrement subtracts 1 from operand
can be used as prefix (++i) or postfix (i--)
++ and -- have side effects by modifying the values of their operands

evaluating ++i (a pre-increment) yields i + 1 and increments i (side effect)

i = 1;
printf("i is %d\n", ++i);     /* prints "i is 2" */
printf("i is %d\n", i);       /* prints "i is 2" */

evaluating i++ (a post-increment) yields i, but causes i to increment later

i = 1;
printf("i is %d\n", i++);     /* prints "i is 1" */
printf("i is %d\n", i);       /* prints "i is 2" */

++i increment immediately, i++ increment later
C standard doesn't specify how much later, but its safe to assume its before
    the next statement is executed

i = 1;
j = 2;
k = ++i + j++;     k = 4

i = 1;
j = 2;
k = i++ + j++;     k = 3

postfix ++ -- are higher precedence than unary + - and are left-associative
prefix ++ -- are same precedence as unary + - and are right-associative

/*   CHAPTER                   4.4                   EXPRESSION EVALUATION   */

a = b += c++ - d + --e / -f                     /* precedence */
a = b += (c++) - d + --e / -f                   postfix increment
a = b += (c++) - d + (--e) / (-f)               prefix increment, unary minus
a = b += (c++) - d + ((--e) / (-f))             multiplicative (division)
a = b += (((c++) - d) + ((--e) / (-f)))         additive
(a = (b += (((c++) - d) + ((--e) / (-f)))))     assignment

                    ORDER OF SUBEXPRESSION EVALUATION

C does not define the order in which subexpressions are evaluated (the
    exceptions being 'logical and', 'logical or', conditional, and comma
    operators)

(a + b) * (c - d)

we do not know whether (a + b) or (c - d) will evaluate first
most expressions will have the same value regardless of subexpression order
this will not be true if a subexpression modifies an operand

a = 5;
c = (b = a + 2) - (a = 1);

the answer can be either 6 or 2 depending on compiler
tobprevent problems, use a series of separate assignments

a = 5;
b = a + 2;
a = 1;
c = b - a;

the value of c is now always 6

= (assignment), ++ (increment) and -- (decrement) are the only operators that
    modify their operands

i = 2;
j = i * i++;

j could be 4 or 6
this unknown behavior should be avoided at all costs

/*   CHAPTER                   4.5                   EXPRESSION STATEMENTS   */

C has the rule that ANY expression can be used as a statement
any expression can be turned into a statement by appending a ;

++i      expression
++i;     statement

when ++i; is executed, i is first incremented, then the new i value is fetched
    (as though to be used in an enclosing expression)
++i; isnt part of a larger expression here, so it becomes discarded (the
    change to i is permanent)
since its value is discarded, there is little use in using an expression as a
    statement unless the expression has a side effect

i = 1;        1 is stored in i, then new value of i is fetched but not used
i--;          value of i is fetched but not used, though i is decremented after
i * j - 1;    value of expression is computed then discarded
i and j are not changed, so previous statement has no effect and no purpose

                    ADDITIONAL NOTES

an lvalue is an expression on the left side of an assignment
therefore an rvalue is an expression that can appear on the right side
rvalues can be variables, constants, or more complex expressions
rvalues are essentially expressions

++ -- work with float variables

"discarding a value"
by definition, expressions represent a value; if the expression is i = 5, then
    evaluating the expression i + 1 produces the value 6
turn the expression i + 1 into a statement
i + 1; when this statement is executed, the value of i + 1 is computed
since this computed value was not saved or used in some way, it is lost
even when i = 1; i is assigned the value of 1
?lvalue has been modified, and the rvalue has been discarded?

/*   CHAPTER                          4                          EXERCISES   */

1. Show the output produced by each of the following program fragments. Assume
     that i, j, and k are int variables.

(a) 1 2
(b) 12 0
(c) 1
(d) 0

2. if i and j are positive integers, does (-i) / j always have the same value
     as -(i/j)? Justify your answer.

yes, they have the same value

/*
#include <stdio.h>

int main(void)
{
    printf("Does (-i) / j always have the same value as -(i/j) when you use");
    printf("two positive integers?\nEnter two positive integers to find out.");

    int n1 = 0, n2 = 0;

    scanf("%d %d", &n1, &n2);

    printf("(-i) / j = %d\n", ((-n1) / n2));
    printf("-(i / j) = %d\n", (-(n1 / n2)));

    return 0;
}
*/

3. What is the value of each of the following expressions in C89? (give all
     possible values if an expression may have more than one value)

*(a) 1 or 2         /* answer is only 1. C89 implementation only results */
(b) -1 or -2         /* when an operand is negative */
(c) -1 or -2
(d) 1 or 2

4. Repeat exercise 3 for C99.

(a) 1
(b) -1
(c) -1
(d) 1

5. What is the value of each of the following expression in C89? (give all
     possible values if an expression may have more than one value)

(a) 3
(b) -3 or -2
(c) -3 or -2
*(d) 3 or 2

6. Repeat exercise 3 for C99.

(a) 3
(b) -3
(c) 3
(d) -3

7. Why doesn't changing the algorithm for computing the UPC check digit work?

changing the algorithm affects the answer you get while dividing, which also
   changes the final check digit after subtracting from 9

8. Would the upc.c program still work if the expression
     9 - ((total - 1) % 10) were replaced by (10 - (total % 10)) % 10?

yes, the program would still work, and would produce identical values

9. Show the output produced by each of the following program fragments. Assume
     that i, j, and k are int variables.

(a) 63, 8
(b) 3, 2, 1
(c) 2, -1, 3
(d) 0, 0, 0

10. Show the output produced by each of the following program fragments. Assume
     that i, j, and k are int variables.

(a) 12, 12
(b) 3, 4
(c) 2, 8
(d) 6, 9

11. Show the output produced by each of the following program fragments. Assume
     that i, j, and k are int variables.

(a) 0
    2
(b) 4
    11, 6
(c) 0
    8, 7
(d) 3
    4, 5, 4

12. Show the output produced by each of the following program fragments. Assume
     that i and j are int variables.

(a) 6, 16
(b) 6, -7
(c) 6, 23
(d) 6, 15

13. Only one of the expression ++i and i++ is exactly the same as (i += 1);
     which is it? Justify your answer.

++i will change the value of i immediately, while i++ keeps the original value
   of i until the statement is fully parsed. therefore ++i is exactly the same
   as (i += 1)

14. Supply parentheses to show how a C compiler would interpret each of the
     following expressions.

(a) (((a * b) - (c * d)) + e)
(b) (((a / b) % c) / d)
(c) ((((- a) - b) + c) - (+ d))
(d) (((a * (- b)) / c) - d)

15. Give the values of i and j after each of the following expression
     statements have been executed. (Assume that i has the value 1 initially
     and j has the value 2.)

(a) 3, 2
(b) 0, 2
(c) 1, 2       /* i and j value was never modified */
(d) 1, 3       /* i value was never modified */

/*   CHAPTER                     4                    PROGRAMMING PROJECTS   */

1. Write a program that asks the user to enter a two-digit number, then prints
     the number with its digits reversed.

/*
#include <stdio.h>

int main(void)
{
    int n = 0, d1 = 0, d2 = 0;

    printf("Enter a two-digit number: ");
    scanf("%d", &n);

    d1 = (n / 10);
    d2 = (n % 10);

    printf("The reversal is: %d%d\n", d2, d1);

    return 0;
}
*/

2. Extend the program in project 1 to handle three-digit numbers.

/*
#include <stdio.h>

int main(void)
{
    int n = 0, d1 = 0, d2 = 0, d3 = 0;

    printf("Enter a three-digit number: ");
    scanf("%d", &n);

    d1 = (n / 100);
    d2 = ((n / 10) % 10);
    d3 = (n % 10);

    printf("The reversal is: %d%d%d\n", d3, d2, d1);

    return 0;
}
*/

3. Rewrite the program in project 2 so that it prints the reversal of a three-
     digit number without using arithmetic to split the number into digits.

/*
#include <stdio.h>

int main(void)
{
    int n1 = 0, n2 = 0, n3 = 0;

    printf("Enter a three-digit number: ");
    scanf("%1d%1d%1d", &n1, &n2, &n3);

    printf("The reversal is: %d%d%d\n", n3, n2, n1);

    return 0;
}
*/

4. Write a program that reads an integer entered by the user and displays it in
     octal (base 8):

/*
#include <stdio.h>

int main(void)
{
    int n = 0, r1 = 0, r2 = 0, r3 = 0, r4 = 0, r5 = 0;

    printf("Enter a  number between 0 and 32767: ");
    scanf("%d", &n);

    r1 = n % 8;
    r2 = ((n / 8) % 8);
    r3 = (((n / 8) / 8) % 8);
    r4 = ((((n / 8) / 8) / 8) % 8);
    r5 = (((((n / 8) / 8) / 8) / 8) % 8);

    printf("In Octal, your number is: %d%d%d%d%d\n", r5, r4, r3, r2, r1);

    return 0;
}
*/

5. Rewrite the upc.c program so that the user enters 11 digits at one time.

/*
#include <stdio.h>

int main(void)
{
    int a, b, c, d, e, f, g, h, i, j, k, first_sum, second_sum, total;

    printf("Enter the first 11 digits of a UPC: ");
    scanf("%1d%1d%1d%1d%1d%1d%1d%1d%1d%1d%1d",
          &a, &b, &c, &d, &e, &f, &g, &h, &i, &j, &k);

    first_sum = a + c + e + g + i + k;
    second_sum = b + d + f + h + j;
    total = 3 * first_sum + second_sum;

    printf("Check digit: %d\n", 9 - ((total - 1) % 10));

    return 0;
}
*/

6. Modify upc.c so that it calculates the check digit for an EAN.

/*
#include <stdio.h>

int main(void)
{
    int a, b, c, d, e, f, g, h, i, j, k, l, first_sum, second_sum, total;

    printf("Enter the first 12 digits of a UPC: ");
    scanf("%1d%1d%1d%1d%1d%1d%1d%1d%1d%1d%1d%1d",
          &a, &b, &c, &d, &e, &f, &g, &h, &i, &j, &k, &l);

    first_sum = b + d + f + h + j + l;
    second_sum = a + c + e + g + i + k;
    total = 3 * first_sum + second_sum;

    printf("Check digit: %d\n", 9 - ((total - 1) % 10));

    return 0;
}
*/

/******************************************************************************
*   CHAPTER                      5                     SELECTION STATEMENTS   *
******************************************************************************/

so far, we have used the return statement and expression statements
most other statements fall into three categories:
selection statements 'if' and 'switch' allow programs to select a particular
    execution path from a set of alternatives
iteration statements 'while' 'do' and 'for' support iteration (looping)
jump statements 'break' 'continue' and 'goto' cause an unconditional jump to
    some other place in the program
the only other statements are compound statements and null statements

/*   CHAPTER                     5.1                   LOGICAL EXPRESSIONS   */

C statements often test the value of an expression to see if its true or false

                    RELATIONAL OPERATORS
<, >, <=, => are relational operators
a comparison such as i < j will yield an integer: 0 (false) or 1 (true)
10 < 11 is 1
11 < 10 is 0
relational operators can compare numbers of mixed type
1 < 2.5 is 1
5.6 < 4 is 0
left associative
lower precedence than arithmetic operators
i + j < k - 1 means ((i + j) < (k - 1))
i < j < k means ((i < j) < k), but i < j will produce a 0 or 1, which leads to
    (0 < k) or (1 < k)
the proper expression would be i < j && j < k

                    EQUALITY OPERATORS

== equal to
!= not equal to
produce 0 or 1 as a result
left associative
lower precedence than relational operators
i < j == j < k means (i < j) == (j < k)
which is true if i < j and j < k are both true or both false
(i >= j) + (i == j) is either 0, 1, or 2 depending on whether i is less than,
    greater than, or equal to j

                    LOGICAL OPERATORS

! logical negation (unary)
&& logical AND (binary)
|| logical OR (binary)
! same precedence as unary + -
! right associative
&& || lower precedence than relational and equality operators
&& || left associative
i < j && k == m means (i < j) && (k == m)
produce 0 or 1 as a result
logical operators treat any non-zero operand as true and any zero as false
!expr has the value 1 if expr has the value 0
expr1 && expr2 has the value 1 only when expr1 AND expr2 are both non-zero
expr1 || expr2 has the value 1 if expr1 OR expr2 OR both are non-zero
in all other cases, these operators produce 0
&& and || short-circuit evaluation of their operands
first left operand is evaluated, then right operand
if the value of the expression can be deduced from the left operand alone, then
    the right operand isn't evaluated
(i != 0) && (j / i > 0)
(i != 0) is evaluated first. if i isnt equal to 0, then we move on to
    (j / i > 0). if i is equal to 0, then the entire expression must be false
side effects from operands will not occur if short-circuiting discards an expr

/*   CHAPTER                      5.2                     THE if STATEMENT   */

the if statement can choose between two alternatives by testing the value of an
    expression
if ( expression ) statement
parentheses required around expression
when if is executed, the expression is evaluated; if non-zero, then the
    statement will be executed

if (line_num == MAX_LINES)
  line_num = 0;

to test whether a variable falls within range, for example 0 <= i < n...
if (0 <= i && i < n)
to test whether a variable falls outside range
if (i < 0 || i >= n)

                    COMPOUND STATEMENTS

if ( expression ) { statements }
braces around compound statements are required
{ line_num = 0; page_num++; }
each statements still ends with a ;
no ; after braces

if (line_num == MAX_LINES) {
  line_num = 0;
  page_num++;       //line_num = 0; page_num++;
  }

                    THE else CLAUSE

if ( expression ) statement else statement
the statement that follows else is executed if the ( expression ) is 0

if (i > j)			//if (i > j) max = i;
  max = i;			//else max = j
else
  max = j;

there are no restrictions on what statements can appear in an if statement
extra braces, like parentheses, can increase readability and modability, while
    possibly avoiding the compiler not understanding the program
these if statements find the largest of the numbers in i, j, k and store that
    value in max

if (i > j)		  |  	if (i > j) {	  | 	if (i > j) {
  if (i > k)	  | 	  if (i > k)	  | 	  if (i > k) {
    max = i;	  | 	    max = i;	  | 	    max = i;
  else		      |       else		      |       } else {
    max = k;	  | 	    max = k;	  | 	    max = k;
else			  |     } else {	      | 	  }
  if (j > k)	  | 	  if (j > k)	  | 	} else {
    max = j;	  | 	    max = j;	  | 	  if (j > k) {
  else			  |       else		      |         max = j;
    max = k;	  | 	    max = k;	  | 	  } else {
                  |     }			      |         max = k;
                              			  |       }
                                          |     }

                    CASCADED if STATEMENTS

we will often need to test a series of conditions, stopping as soon as one of
    them is true
the following cascaded if statements tests whether n is less than, equal to, or
    greater than 0:

if (n < 0)
  printf("n is less than 0\n");
else
  if (n == 0)
    printf("n is equal to 0\n");
  else
    printf("n is greater than 0\n");

if (n < 0)
  printf("n is less than 0\n");
else if (n == 0)
  printf("n is equal to 0\n");
else
  printf("n is greater than 0\n");

if ( expression )
  statement
else if ( expression )
  statement
...
else if ( expression )
  statement
else
  statement

the above way of indenting cascaded if statements avoids the problem of
    excessive indentation when the number of tests is large
cascaded if statements are not specifically a new kind of statement; they are
    just ordinary if statements that happen to have another if statement as its
    else clause; if...else if...else if...else if...else if...

                    CALCULATING A BROKER'S COMMISSION

the heart of the program is a cascaded if statement that determines which
    range the trade falls into.

                    broker.c - CALCULATES A BROKER'S COMMISSION

#include <stdio.h>

int main(void)
{
    float commission, value;

    printf("Enter value of trade: ");
    scanf("%f", &value);

    if (value < 2500.00f)
        commission = 30.00f + .017f * value;
    else if (value < 6250.00f)
        commission = 56.00f + .0066f * value;
    else if (value < 20000.00f)
        commission = 76.00f + .0034f * value;
    else if (value < 50000.00f)
        commission = 100.00f + .0022f * value;
    else if (value < 500000.00f)
        commission = 155.00f + .0011f * value;
    else
        commission = 255.00f + .0009f * value;

    if (commission < 39.00f)
        commission = 39.00f;

    printf("Commission: $%.2f\n", commission);

    return 0;
}

                    THE DANGLING else PROBLEM

if (y != 0)
  if (x != 0)
    result = x / y;
else        /* MISLEADING INDENTATION */
  prinf("Error: y is equal to 0\n");

the indentation suggests the else belongs to the outer if statement, but C
    follows the rule that an else clause belongs to the nearest if statement
to make the else clause part of the outer if statement, enclose the inner if
    statement in braces

if (y != 0) {
  if (x != 0)       /* if and if */
    result = x / y;
} else
    printf("Error: y is equal to 0\n");

                    CONDITIONAL EXPRESSIONS

if statements allow a program to perform one of two actions depending on the
    value of a condition
C also provides an operator that allows an expression to produce one of two
    values depending on the value of a conditional
precedence is lower than other operators so far, except assignment operator
the conditional operator consists of ? and :, which must be used
    together in the following way:

expr1 ? expr2 : expr3  /* if 1, do 2; otherwise 3 */

essentially, if expr1, then expr2, else expr3
expr1, expr2, and expr3 can be expressions of any type
since conditional expressions requires three operands, it can be referred to as
    a ternary operator
expr1 evaluated first; if its value isnt 0, then expr2 is evaluated, and its
    value is the value of the entire conditional expression
if expr1 is zero, then the value of expr3 is the value of the conditional

int i, j ,k;
i = 1; j = 2;
k = i > j ? i : j;            /* k is now 2 */
k = (i >= 0 ? i : 0) + j;     /* k is now 3 */

i > j ? i : j returns the value of either i or j, whichever is larger
since i > j (1 > 2) fails, the value of the conditional, 2, is added to k

i >= 0 succeeds in the second assignment to k
(i >= 0 ? i : 0) has the value 1, which is added to j to produce 3
the parentheses are necessary due to precedence
conditional expressions can make programs shorter but harder to understand

if (i > j)
  return i;
else
  return j;               //return i > j ? i : j;

if (i > j)
  printf("%d\n", i);
else
  printf("%d\n", j);      //printf("%d\n", i > j ? i : j);

                    BOOLEAN VALUES IN C89

C89 lacks a boolean type, although there are some workarounds

int flag;

flag = 0;
...
flag = 1;

its not obvious that flag should only be assigned boolean values, or that 0 and
    1 represent false and true

#define TRUE 1
#define FALSE 0

flag = FALSE
...
flag = TRUE

if (flag == TRUE) ...
or just
if (flag) ...

if (flag != FALSE) ...
if (!flag) ...

define a macro that can be used as a type
#define BOOL int

BOOL flag;

                    BOOLEAN VALUES IN C99

C99 provides the _Bool type

_Bool flag;

_Bool is an unsigned integer type
a _Bool variable can only be assigned 0 or 1
in general, a non-zero value stored into a _Bool variable will cause the
    variable to be assigned 1:

flag = 5;     /* flag is assigned 1 */

its legal (but not advisable) to perform arithmetic on _Bool variables; also
    legal to print a _Bool variable, and they can be tested in if statements

if (flag)     /* tests if flag is 1 */

C99 also provides the stdbool.h header, which provides a macro, bool, that
    stands for _Bool

#include stdbool.h

bool flag;        /* same as _Bool flag; */

stdbool.h also supplies macros named true and false, which stand for 1 and 0

flag = false;
...
flag = true;

/*   CHAPTER                    5.3                   THE switch STATEMENT   */

we will often need to compare an expression against a series of values to see
    which one it currently matches
for example, this cascaded if statement:

if (grade == 4)
  printf("Excellent");
else if (grade == 3)
  printf("Good");
else if (grade == 2)
  printf("Average");
else if (grade == 1)
  printf("Poor");
else if (grade == 0)
  printf("Failing");
else
  printf("Illegal grade");

the following switch statement is equivalent to our cascaded if:

switch (grade) {
   case 4:  printf("Excellent");
	    break;
   case 3:  printf("Good");
	    break;
   case 2:  printf("Average");
	    break;
   case 1:  printf("Poor");
	    break;
   case 0;  printf("Failing");
	    break;
   default: printf("Illegal Grade");
	    break;
}

when executed, the value of grade is tested against 4, 3, 2, 1, and 0. if it
    matches 4, the message Excellent is printed, then the break statement
    transfers control to the statement following the switch statement
if the value of grade does not match any choice, then the default case applies

switch statements are often easier to read than cascaded if statements
switch statements are often faster than if statements, especially when there
    are more than a few cases
common switch format:

switch ( expression ) {
   case constant-expression :  statements
   ...
   case constant-expression :  statements
   default : statements
}

the word switch must be followed by an integer expression in parentheses
characters are treated as integers in C, so they can be tested in switch
    statements; floating-point numbers and strings do not qualify

each case begins with a label of the form:
    case constant-expression :
constant expressions are similar to ordinary expressions, except it cannot
    contain variables or function calls
5 is a constant expr. 5 + 10 is a constant expr. n + 10 isnt a constant expr,
    unless n is a macro that represents a constant
the constant expr in a case label must evaluate to an integer or character

after each case label comes any number of statements
no braces are required around the statements
the last statement in each group is normally break

duplicate case labels are not allowed
case order does not matter, even for default
only one constant expression may follow the word case
several case labels may precede the same group of statements:

switch (grade) {
   case 4:
   case 3:
   case 2:
   case 1:  printf("Passing");
            break;
   case 0:  printf("Failing");
            break;
   default: printf("Illegal grade");
            break;
}

to save space, you can put several case labels on the same line:

switch (grade) {
   case 4: case 3: case 2: case 1:
            printf("Passing");
            break;
   case 0:  printf("Failing");
            break;
   default: printf("Illegal grade");
            break;
}

a switch statements isnt required to have a default case
if default is missing and the value of the controlling expression does not
    match any case label, control simply passes to the next statement after the
    switch

                    THE ROLE OF THE break STATEMENT

the break statement allows the program to exit the switch statement and pass
    control onto the next statement after the switch
we need a break statement because the switch statement is a form of computed
    jump
when the controlling expr is evaluated, control jumps to the case label
    matching the value of the switch expr
case labels are just markers indicating a position within switches
when the last statement in the case has been executed, control "falls through"
    to the first statement of the next case, ignoring the case label
to prevent control flowing from one case into the next, a break (or some other
    jump statement) is necessary as the last statement in a case

switch (grade) {
   case 4:  printf("Excellent");
   case 3:  printf("Good");
   case 2:  printf("Average");
   case 1:  printf("Poor");
   case 0:  printf("Failing");
   default: printf("Illegal grade");
}

if the value of grade is 3, the message printed is:

GoodAveragePoorFailingIllegal grade

deliberately falling through one case into the next is rare, so it is a good
    idea to point out any purposeful omission of break

switch (grade) {
    case 4: case 3: case 2: case 1:
            num_passing++;
            /* FALL THROUGH */
    case 0: total_grades++;
            break;
}

without the comment, someone might try to "fix the error" later by adding an
    unwanted break statement
although the last case in a switch statement never needs a break statement, it
    is common practice to put one anyways to prevent a "missing break" problem

                    PRINT A DATE IN LEGAL FORM

#include <stdio.h>

int main(void)
{
    int month, day, year;

    printf("Enter date (mm/dd/yy): ");
    scanf("%d /%d /%d", &month, &day, &year);

    printf("Dated this %d", day);
    switch (day) {
	    case 1: case 21: case 31:
            printf("st"); break;
        case 2: case 22:
            printf("nd"); break;
        case 3: case 23:
            printf("rd"); break;
        default: printf("th"); break;
    }
    printf(" day of ");

    switch (month) {
        case 1: printf("January");     break;
        case 2: printf("February");    break;
        case 3: printf("March");       break;
        case 4: printf("April");       break;
        case 5: printf("May");         break;
        case 6: printf("June");        break;
        case 7: printf("July");        break;
        case 8: printf("August");      break;
        case 9: printf("September");   break;
        case 10: printf("October");    break;
        case 11: printf("November");   break;
        case 12: printf("December");   break;
    }

    printf(", 20%.2d.\n", year);
    return 0;
}

                    ADDITIONAL NOTES

when int and float values are mixed in a conditional expression, the expr has
    type float
(i > 0 ? i : f)
if i > 0 is true, the value of the expr will be the value of i after conversion
    to float type

a switch statement can contain labels that are not preceded by the word case
suppose you accidentally misspell the word default as 'defualt', the compiler
    may not detect the error, since it assumes 'defualt' is a ordinary label

                    EXERCISES

1. The following program fragments illustrate the relational and equality
     operators. Show the output produced by each, assuming that i, j, and k are
     int variables.

(a) 1
(b) 1
(c) 1
(d) 0

2. The following program fragments illustrate the logical operators. Show the
     output produced by each, assuming that i, j, and k are int variables.

(a) 1
(b) 1
(c) 1
(d) 1

3. The following program fragments illustrate the short-circuit behavior of
     logical expressions. Show the output produced by each, assuming that i, j,
     and k are int variables.

(a) 1
    3, 5*, 5	/* undefined behavior for increments */
(b) 0
    7, 8, 9
(c) 1
    9, 9, 9
(d) 1
    2*, 2*, 2*	/* undefined behavior for increments */

4. Write a single expression whose value is either -1, 0, or +1, depending on
     whether i is less than, equal to, or greather than j, respectively.

((i >= j) + (i == j) - 1)

5. Is the following if statement legal? If so, what does it do when n is equal
     to 0?

its legal, but it wont work as intended
"1 is between 1 and 10"

6. Is the following if statement legal? If so, what does it do when n is equal
     to 5?

n == -9
wont run unless n is -9, in which it will then print "-9 is between 1 and 10"

7. What does the next statement print if i has the value 17? What about -17?

17
17

8. The following if statement is unnecessarily complicated. Simplify it as much
     as possible. (Hint: The entire statement can be replaced by a single
     assignment.)

teenager = age >= 13 && age <= 19;

9. Are the following if statements equivalent? If not, why not?

functionally equivalent

10. What output does the following program fragment produce? (Assume that i is
     an integer variable.)

onetwo, since there are no break statements

11. Write a switch statement whose controlling expression is the variable
     area_code. If the value of area_code is in the table, the switch
     statement will print the corresponding city name. Otherwise, the switch
     statement will display the message "Area code not recognized".

switch (area_code) {
    case 229: printf("Albany\n");
        break;
    case 404: case 470: case 678: case 770: printf("Atlanta\n");
        break;
    case 478: printf("Macon\n");
        break;
    case 706: case 762: printf("Columbus\n");
        break;
    case 912: printf("Savannah\n");
        break;
    default:   printf("Area code not recognized\n");  break;
}

                    PROGRAMMING PROJECTS

1. Write a program that calculates how many digits a number contains:

#include <stdio.h>

int main(void)
{
    int n;  //n represents number input by user

    printf("Enter a number: ");
    scanf("%d", &n);

    if (n < 0)
    {
        n = -n;
        printf("Removing the negative...\n");
    }

    if (n >= 0 && n <= 9)
        printf("The number %d has 1 digit", n);
    else if (n >= 10 && n <= 99)
        printf("The number %d has 2 digit", n);
    else if (n >= 100 && n <= 999)
        printf("The number %d has 3 digit", n);
    else if (n >= 1000 && n <= 9999)
        printf("The number %d has 4 digit", n);
    else
        printf("Number out of range!");

return 0;

}


2. Write a program that asks the user for a 24-hour time, then displays the
     time in 12-hour form:

#include <stdio.h>

int main(void)

{

	int hh, mm;

	printf("Enter a 24-hour time (hh:mm): ");
	scanf("%d:%d", &hh, &mm);

    if (hh >= 0 && hh <= 11)
        printf("Equivalent 12-hour time: %2.2d:%2.2d AM\n", hh, mm);

    else if (hh == 12)
        printf("Equivalent 12-hour time: %2.2d:%2.2d PM\n", hh, mm);

    else if (hh >= 13 && hh <= 24)
        printf("Equivalent 12-hour time: %2.2d:%2.2d PM\n", (hh - 12), mm);

    else printf("Invalid time.\n");

return 0;

}

3. Modify the broker.c program by making both of the following changes:
    (a) Ask the user to enter the number of shares and the price per share
    (b) Add statements that compute the commission charged by a rival broker
        ($33 plus 3 cents per share for fewer than 2000 shares; $33 plus 2
        cents per share for 2000 shares or more).

#include <stdio.h>

int main(void)
{
    int shares;
    float commission, rcommission, price, value;

    printf("Enter the number of shares: ");
    scanf("%d", &shares);

    printf("Enter the price per share: ");
    scanf("%f", &price);

    value = (shares * price);

    if (value < 2500.00f)
        commission = 30.00f + .017f * value;
    else if (value < 6250.00f)
        commission = 56.00f + .0066f * value;
    else if (value < 20000.00f)
        commission = 76.00f + .0034f * value;
    else if (value < 50000.00f)
        commission = 100.00f + .0022f * value;
    else if (value < 500000.00f)
        commission = 155.00f + .0011f * value;
    else
        commission = 255.00f + .0009f * value;

    if (commission < 39.00f)
        commission = 39.00f;

    printf("Commission: $%.2f\n", commission);

    if (shares < 2000)
        rcommission = ((shares * 0.03f) + 33.00f);

    else if (shares >= 2000)
        rcommission = ((shares * 0.02f) + 33.00f);

        printf("Rival broker's commission: $%.2f", rcommission);


    return 0;
}

4. @rite a program that asks a user to enter a wind speed (in knots) and
	 displays the corresponding Beaufort scale description

#include <stdio.h>

int main(void)
{
	int speed;

	printf("Enter a wind speed (in knots): ");
	scanf("%d", &speed);

	if (speed < 1)
		printf("Wind force is calm\n");
	else if (speed == 1 || speed == 2 || speed == 3)
		printf("Wind force is a light air\n");
	else if (speed >= 4 && speed <= 27)
		printf("Wind force is a breeze\n");
	else if (speed >= 28 && speed <= 47)
		printf("Wind force is a gale\n");
	else if (speed >= 48 && speed <= 63)
		printf("Wind force is a storm\n");
	else (speed > 63)
		printf("Wind force is a hurricane\n");

	return 0;

}

5. 

#include <stdio.h>

int main(void)

	int income;
	float tax;

	printf("Enter income: ");
	scanf("%d", &income);

	switch (income)
		case (0 <= 750):
		printf("Tax due: %.2f\n", tax = (income * 0.01); break;

		case (750 <= 2250):
