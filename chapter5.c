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

/***   CHAPTER                   5.1                 LOGICAL EXPRESSIONS   ***/

C statements often test the value of an expression to see if its true or false

/***                         RELATIONAL OPERATORS                          ***/
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

/***                          EQUALITY OPERATORS                           ***/

== equal to
!= not equal to
produce 0 or 1 as a result
left associative
lower precedence than relational operators
i < j == j < k means (i < j) == (j < k)
which is true if i < j and j < k are both true or both false
(i >= j) + (i == j) is either 0, 1, or 2 depending on whether i is less than,
    greater than, or equal to j

/***                           LOGICAL OPERATORS                           ***/

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

/***   CHAPTER                    5.2                   THE if STATEMENT   ***/

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

/***                          COMPOUND STATEMENTS                          ***/

if ( expression ) { statements }
braces around compound statements are required
{ line_num = 0; page_num++; }
each statements still ends with a ;
no ; after braces

if (line_num == MAX_LINES) {
  line_num = 0;
  page_num++;       //line_num = 0; page_num++;
  }

/***                            THE else CLAUSE                            ***/

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

/***                        CASCADED if STATEMENTS                         ***/

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

/***                   CALCULATING A BROKER'S COMMISSION                   ***/

the heart of the program is a cascaded if statement that determines which
    range the trade falls into.

/***              broker.c - calculates a broker's commission              ***/

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

/***                       THE DANGLING else PROBLEM                       ***/

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

/***                        CONDITIONAL EXPRESSIONS                        ***/

if statements allow a program to perform one of two actions depending on the
    value of a condition
C also provides an operator that allows an expression to produce one of two
    values depending on the value of a conditional
precedence is lower than other operators so far, except assignment operator
the conditional operator consists of ? and :, which must be used
    together in the following way:

expr1 ? expr2 :   /* if 1, do 2; otherwise 3 */

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

/***                         BOOLEAN VALUES IN C89                         ***/

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

/***                         BOOLEAN VALUES IN C99                         ***/

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

/***   CHAPTER                  5.3                 THE switch STATEMENT   ***/

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

/***                    THE ROLE OF THE break STATEMENT                    ***/

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

/***                      PRINT A DATE IN LEGAL FORM                       ***/

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

/***                           ADDITIONAL NOTES                            ***/

when int and float values are mixed in a conditional expression, the expr has
    type float
(i > 0 ? i : f)
if i > 0 is true, the value of the expr will be the value of i after conversion
    to float type

a switch statement can contain labels that are not preceded by the word case
suppose you accidentally misspell the word default as 'defualt', the compiler
    may not detect the error, since it assumes 'defualt' is a ordinary label

/***                               EXERCISES                               ***/

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

/***                         PROGRAMMING PROJECTS                          ***/

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
{
	int income;
	float tax;

	printf("Enter income: ");
	scanf("%d", &income);


	if (income <= 749)
	printf("Tax due: %.2f\n", tax = (income * 0.01));

	else if (income >= 750 && income <= 2249)
	printf("Tax due: %.2f\n", tax = (7.50f + ((income - 750) * 0.02)));

	else if (income >= 2250 && income <= 3749)
	printf("Tax due: %.2f\n", tax = (37.50f + ((income - 2250) * 0.02)));

	else if (income >= 3750 && income <= 5249)
	printf("Tax due: %.2f\n", tax = (82.50f + ((income - 3750) * 0.02)));

	else if (income >= 5250 && income <= 6999)
	printf("Tax due: %.2f\n", tax = (142.50f + ((income - 5250) * 0.02)));

	else if (income >= 7000)
	printf("Tax due: %.2f\n", tax = (230.00f + ((income - 7000) * 0.02)));

	else
		printf("Try again.\n");

	return 0;
}

6. Modify the upc.c program so that it checks whether a UPC is valid. The
     program should also display either VALID or NOT VALID.

#include <stdio.h>

int main(void)
{
    int a, b, c, d, e, f, g, h, i, j, k, l, first_sum;
    int second_sum, total;

    printf("Enter a 12-digit UPC: ");
    scanf("%1d%1d%1d%1d%1d%1d%1d%1d%1d%1d%1d%1d",
          &a, &b, &c, &d, &e, &f, &g, &h, &i, &j, &k, &l);

    first_sum = a + c + e + g + i + k;
    second_sum = b + d + f + h + j;
    total = (9 - ((3 * first_sum + second_sum) - 1 ) % 10);

    total == l ? printf("VALID\n") : printf("NOT VALID\n");

    return 0;
}

7. Write a program that finds the largest and smallest of four integers entered
     by the user.

#include <stdio.h>

int main(void)
{
	int i, j, k, l, max1, max2, min1, min2;

	printf("Enter four integers: ");
	scanf("%d%d%d%d", &i, &j, &k, &l);

    if (i >= j){
        max1 = i;
        min1 = j;}
    else{
        max1 = j;
        min1 = i;}

    if (k >= l){
        max2 = k;
        min2 = l;}
    else{
        max2 = l;
        min2 = k;}

    if (max1 >= max2)
        printf("Largest: %d\n", max1);
    else
        printf("Largest: %d\n", max2);

    if (min1 <= min2)
        printf("Smallest: %d\n", min1);
    else
        printf("Smallest: %d\n", min2);

    return 0;
}

8. Write a program that asks user to enter a 24-hour time. The program will
     display the departure and arrival times for the flight whose departure
     time is closest to the time entered by the user.

#include <stdio.h>

int main(void)
{

    clunky-ass project

}

9. Write a program that prompts the user to enter two dates and then
     indicates which date comes earlier on the calendar.

#include <stdio.h>

int main(void)
{
    int m1, m2, d1, d2, y1, y2;

    printf("Enter first date (mm/dd/yy): ");
    scanf("%d/%d/%d", &m1, &d1, &y1);

    printf("Enter second date (mm/dd/yy): ");
    scanf("%d/%d/%d", &m2, &d2, &y2);

    if (y1 < y2)
        printf("%2.2d/%2.2d/%2.2d is earlier than %2.2d/%2.2d/%2.2d\n",
                m1, d1, y1, m2, d2, y2);
    else
        printf("%2.2d/%2.2d/%2.2d is earlier than %2.2d/%2.2d/%2.2d\n",
                m2, d2, y2, m1, d1, y1);

    return 0;
}

10. Using the switch statement, write a program that converts a numerical grade
     into a letter grade.

#include <stdio.h>

int main(void)
{
    int d1;

    printf("Enter grade: ");
    scanf("%d", &d1);

    (d1 > 100 || 0 > d1) ?
    printf("ERROR: Enter a number between 0 and 100\n") :
    (d1 /= 10);

    switch (d1) {
        case 10: case 9:
                printf("Letter grade: A\n");   break;
        case 8:
                printf("Letter grade: B\n");   break;
        case 7:
                printf("Letter grade: C\n");   break;
        case 6:
                printf("Letter grade: D\n");   break;
        case 5: case 4: case 3: case 2: case 1: case 0:
                printf("Letter grade: F\n");   break;
        }

    return 0;
}

11. Write a program that asks the user for a two-digit number, then prints the
     English word for the number.

#include <stdio.h>

int main(void)
{
    int d1, d2;

    printf("Enter a two-digit number: ");
    scanf("%1d%1d", &d1, &d2);

    if (d1 == 1)
        if (d2 == 0)
            printf("ten\n");
        else if (d2 == 1)
            printf("eleven\n");
        else if (d2 == 2)
            printf("twelve\n");
        else switch (d2) {
            case 3: printf("thirteen\n");       break;
            case 4: printf("fourteen\n");       break;
            case 5: printf("fifteen\n");       break;
            case 6: printf("sixteen\n");       break;
            case 7: printf("seventeen\n");       break;
            case 8: printf("eightteen\n");       break;
            case 9: printf("nineteen\n");       break;
            }

    else if (d1 >= 2 && 9 >= d1)
        switch (d1) {
            case 2: printf("twenty");            break;
            case 3: printf("thirty");            break;
            case 4: printf("forty");            break;
            case 5: printf("fifty");            break;
            case 6: printf("sixty");            break;
            case 7: printf("seventy");            break;
            case 8: printf("eighty");            break;
            case 9: printf("ninety");            break;
            }

    if (d1 >= 2 && d2)
        printf("-");

    if (d1 != 1)
        switch (d2) {
            case 1: printf("one\n");            break;
            case 2: printf("two\n");            break;
            case 3: printf("three\n");            break;
            case 4: printf("four\n");            break;
            case 5: printf("five\n");            break;
            case 6: printf("six\n");            break;
            case 7: printf("seven\n");            break;
            case 8: printf("eight\n");            break;
            case 9: printf("nine\n");            break;
            }

    return 0;
}
