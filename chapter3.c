/******************************************************************************
*   CHAPTER                     3                    FORMATTED INPUT/OUTPUT   *
******************************************************************************/

/***   CHAPTER                  3.1                  THE printf FUNCTION   ***/

printf displays a format string

printf("string", expr1, expr2, ...)

/***                       CONVERSION SPECIFICATIONS                       ***/

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

/***      tprintf.c - prints int and float values in various formats       ***/

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

/***                           ESCAPE SEQUENCES                            ***/

Alert (bell)   \a
Backspace   \b
New line   \n
Horizontal tab   \t
Double quote   \"
Double backslash   \\

/***   CHAPTER                   3.2                  THE scanf FUNCTION   ***/

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

/***                 ORDINARY CHARACTERS IN FORMAT STRINGS                 ***/

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

/***                    addfrac.c - adds two fractions                     ***/

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

/***   CHAPTER                        3                        EXERCISES   ***/

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

/***   CHAPTER                   3                  PROGRAMMING PROJECTS   ***/

1.

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

2.

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

3.

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

4.

#include <stdio.h>

int main(void)
{

	int area = 0, pre = 0, suf = 0;

	printf("Enter phone number (xxx) xxx-xxxx: \n");

	scanf("(%d) %d-%d", &area, &pre, &suf);

	printf("You entered %d.%d.%d\n", area, pre, suf);

	return 0;
}

5.

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

6.

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
