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

/***   CHAPTER                  4.1                 ARITHMETIC OPERATORS   ***/

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

/***                 OPRATOR PRECEDENCE AND ASSOCIATIVITY                  ***/

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

/***         upc.c - computes a universal product code check digit         ***/

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

%1d allows you to store a five-digit number as five one-digit numbers
some older compilers limit maximum value of int variable to 32,767

/***   CHAPTER                  4.2                 ASSIGNMENT OPERATORS   ***/

/***                           SIMPLE ASSIGNMENT                           ***/

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

/***                                LVALUES                                ***/

Most C operators allow operands to be variables, constants, or expressions
= requires its left operand to be an lvalue
lvalues represent objects stored in memory
variables are lvalues
constants or computational results are not lvalues

/***                          COMPOUND ASSIGNMENT                          ***/

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

/***   CHAPTER           4.3           INCREMENT AND DECREMENT OPERATORS   ***/

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

/***   CHAPTER                 4.4                 EXPRESSION EVALUATION   ***/

a = b += c++ - d + --e / -f                     /* precedence */
a = b += (c++) - d + --e / -f                   postfix increment
a = b += (c++) - d + (--e) / (-f)               prefix increment, unary minus
a = b += (c++) - d + ((--e) / (-f))             multiplicative (division)
a = b += (((c++) - d) + ((--e) / (-f)))         additive
(a = (b += (((c++) - d) + ((--e) / (-f)))))     assignment

/***                   ORDER OF SUBEXPRESSION EVALUATION                   ***/

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

/***   CHAPTER                 4.5                 EXPRESSION STATEMENTS   ***/

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

/***                           ADDITIONAL NOTES                            ***/

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

/***   CHAPTER                        4                        EXERCISES   ***/

1. Show the output produced by each of the following program fragments. Assume
     that i, j, and k are int variables.

(a) 1 2
(b) 12 0
(c) 1
(d) 0

2. if i and j are positive integers, does (-i) / j always have the same value
     as -(i/j)? Justify your answer.

yes, they have the same value

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

/***   CHAPTER                   4                  PROGRAMMING PROJECTS   ***/

1. Write a program that asks the user to enter a two-digit number, then prints
     the number with its digits reversed.

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

2. Extend the program in project 1 to handle three-digit numbers.

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

3. Rewrite the program in project 2 so that it prints the reversal of a three-
     digit number without using arithmetic to split the number into digits.

#include <stdio.h>

int main(void)
{
    int n1 = 0, n2 = 0, n3 = 0;

    printf("Enter a three-digit number: ");
    scanf("%1d%1d%1d", &n1, &n2, &n3);

    printf("The reversal is: %d%d%d\n", n3, n2, n1);

    return 0;
}

4. Write a program that reads an integer entered by the user and displays it in
     octal (base 8):

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

5. Rewrite the upc.c program so that the user enters 11 digits at one time.

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

6. Modify upc.c so that it calculates the check digit for an EAN.

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
