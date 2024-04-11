/******************************************************************************
*   CHAPTER                      6                                    LOOPS   *
******************************************************************************/

a loop is a statement whose job is to repeatedly execute some other statement
    (the loop body)
every loop has a "controlling expression"
each time the loop body is executed ("iteration"), the controlling expression
    is evaluated
if true (not zero) the loop continues
there are three iteration statements: "while", "do", and "for"
"while" tests the controlling expressioon before the loop body is executed
"do" tests the expression after the loop body is executed
"for" is useful for loops that increment/decrement a counting variable
there are three other statements used in conjunction with loops
"break" jumps out of a loop and transfers control to the next statement after
    the loop
"continue" skips the rest of a loop iteration
"goto" jumps to any statement within a function
null statements can be used to create loops with empty bodies

/***   CHAPTER                  6.1                  THE while STATEMENT   ***/

while ( expression ) statement
the expression inside the parentheses is the "controlling expression"
the statement after the parentheses is the loop body

while (i < n)   /* controlling expression */
    i = i * 2;  /* loop body */

parentheses are mandatory and nothing goes between the right parenthesis and
    the loop body
when a "while" statement is executed, the controlling expression is evaluated
    first
if nonzero (true), the loop body is executed and the expression is tested again
the process contrinues until the controlling expression has the value zero

i = 1;
while (i < n)
    i = i * 2;
n = 10;

i = 1;      i is now 1
Is i < n?   yes; continue
i = i * 2;  i is now 2
Is i < n?   yes; continue
i = i * 2;  i is now 4
Is i < n?   yes; continue
i = i * 2;  i is now 8
Is i < n?   yes; continue
i = i * 2;  i is now 16
Is i < n?   no; exit loop

although the loop body must be a single statement, we can still use braces to
    create a single compound statement

while (i > 0) {
    printf("T minus %d and counting\n", i);
    i--;
}

first, i is assigned the value 10
since 10 > 0, loop body executed
message "T minus 10 and counting" printed
i decremented
i > 0 tested again
9 > 0, ...

if i has a negative or zero value when while first called, the loop wont
    execute even once

a more concise loop:

while (i > 0)
    printf("T minus %d and counting\n", i--);

/***                            INFINITE LOOPS                             ***/

a "while" statement wont terminate if the controlling expression always has a
    nonzero value

while (1)

this will execute forever unless its body contains a break, goto, return, or
    calls a function that causes the program to terminate

/***                      PRINTING A TABLE OF SQUARES                      ***/

//This program prints a table of squares.
//Enter number of entries in the table: _
//          1           1
//          2           4
//          3           9
//          4           16
//          5           25

/***          square.c - prints a table of squares using "while"           ***/

#include <stdio.h>

int main(void)
{
    int i, n;

    printf("This program prints a table of squares.\n");
    printf("Enter number of entries in table: ");
    scanf("%d", &n);

    i = 1;
    while (i <=n) {
        printf("%10d%10d\n", i, i * i);
        i++;
}

return 0;
}

/***                      SUMMING A SERIES OF NUMBERS                      ***/

//This program sums a series of integers.
//Enter integers (0 to terminate) : 8_23_71_5_0
//The sum is: 107

#include <stdio.h>

int main(void)
{
    int n, sum = 0;

    printf("This program sums a series of integers.\n");
    printf("Enter integers (0 to terminate) : ");

    scanf("%d", &n);
    while (n != 0) {
        sum += n;
        scanf("%d", &n);
    }
    printf("The sum is: %d\n", sum);

    return 0;
}

n != 0 is tested after a number is read, allowing the loop to terminate as soon
    as possible
note the two identical calls of scanf, which is hard to avoid when using while
    loops

/***   CHAPTER                    6.2                   THE do STATEMENT   ***/

the "do" statement is similar to while, except that "do" tests its controlling
    statement after each loop body execution

do statement while ( expression ) ;

the body of a do statement must be one statement (including compound)
the controlling expression must be enclosed within parentheses
when a "do" statement is executed, the loop body is executed first
then the controlling expression is evaluated
if nonzero, the loop body is executed again and the expr evaluated once more
do terminates when the controlling expression has the value 0 after the loop
    body has been executed

i = 10;
do {
    printf("T minus %d and counting\n", i);
    --i;
} while (i > 0);

its a good idea to use braces in all do statements
without braces, "do" statements can easily be mistaken for "while" statements

do
    printf("T minus %d and counting\n", i--);
while (i > 0);

/***            CALCULATING THE NUMBER OF DIGITS IN AN INTEGER             ***/

although "while" appears much more often than "do", the latter is useful for
    loops that must execute at least once

//Enter a nonnegative integer: 60_
//The number has 2 digit(s).

the strategy of this next program is to divide the users input by 10 repeatedly
    until it becomes 0
the number of divisions performed is the number of digits

#include <stdio.h>

int main(void)
{
    int digits = 0, n;

    printf("Enter a nonnegative integer: ");
    scanf("%d", &n);

    do {
        n /= 10;
        digits++;
    }   while (n > 0);

    printf("The number has %d digit(s).\n", digits);

    return 0;
}

/***   CHAPTER                   6.3                   THE for STATEMENT   ***/

the "for" statement is ideal for counting variables, although its versatility
    lends to other types of loops as well

for ( expr1 ; expr2 ; expr3 ) statement

for (i = 10; i > 0; i--)
    printf("T minus %d and counting\n", i);

first i is initialized to 10
then i is tested to see if its greater than 0
since it is, printf executes, printing "T minus 10 and counting"
i is decremented
condition i > 0 is tested again
the loop body will execute 10 times in all, with i varying from 10 down to 1
the "for" statement is closely related to "while"
except for some rare cases, a for loop can always be replaced by an equivalent
    while loop

expr1;
while ( expr2 ) {
    statement
    expr3;
}

expr1 is an initialization step that performs only once
expr2 controls loop termination
expr3 is an operation to be performed at the end of each loop iteration
applying this pattern to the previous for loop example:

i = 10;
while (i > 0) {
    printf("T minus %d and counting\n", i);
    i--;
}

studying the equivalent while statement can highlight the fine points of a for
    statement
suppose we replace i-- with --i

for (i = 10; i > 0; --i)
    printf("T minus %d and counting\n", i);

how does this change affect the loop? looking at the equivalent while loop
    shows there is no effect

i = 10;
while (i > 0) {
    printf("T minus %d and counting\n", i);
    --i;

since the first and third expressions in a for statement are executed as
    individual statements, their values are irrelevant (theyre only useful for
    their side-effects)

/***                         for STATEMENT IDIOMS                          ***/

the "for" statement is usually the best choice for loops that count-up or
    count-down

counting up from 0 to n-1:
for (i = 0; i < n; i++)

counting up from 1 to n:
for (i = 1; i <= n; i++)

counting down from n-1 to 0:
for (i = n - 1; i >= 0; i--)

counting down from n to 1:
for (i = n; i > 0; i--)

/***                OMITTING EXPRESSIONS IN A for STATEMENT                ***/

C allows us to omit any or all expressions in a "for" loop
if the first expression is omitted (expr1), no initialization is performed

i = 10;
for (; i > 0; --i)
    printf("T minus %d and counting\n", i);

the two semicolons must be present, even if all expressions have been omitted
in the above example, i is initialized by a separate assignment before "for"
if we omit expr3, the loop body is responsible for ensuring the value of expr2
    eventually becomes false

for (i = 10; i > 0;)
    printf("T minus %d and counting\n", i--);

when the first and the third expressions are both omitted, the resulting loop
    is just a "while" statement in disguise

for (; i > 0;)
    printf("T minus %d and counting\n", i--);

is the same as

while (i > 0)
    printf("T minus %d and counting\n", i--);

if expr2 is missing, it defaults to a true value, so "for" doesnt terminate
    (unless stopped in some other fashion)
for example, heres how you can establish an infinite loop:

for (;;) ...

/***                         for STATEMENTS IN C99                         ***/

in C99, expr1 in a "for" statement can be replaced by a declaration

for (int i = 0; i < n; i++) ...

i need not have been declared prior to this statement
but if a declaration of i already exists, this statement creates a new version
    of i that will be used solely within the loop
a variable declared by a for statement cant be accessed outside the body of the
    loop (we say that its not "visible" outside the loop)

for (int i = 0; i < n; i++) {
    ...
    printf("%d", i);    /* legal; i is visible inside loop */
    ...
}
printf("%d", i);        /*** WRONG ***/

having a for statement clare its own control variable is often a good idea
however, if the program needs access to the variable after loop termination,
    its necessary to use the older form of "for"
a "for" statement may declare more than one variable

for (int i = 0, j = 0; i < n; i++)

/***                          THE COMMA OPERATOR                           ***/

sometimes we might write a "for" statement with two or more initialization
    expressions or one that increments several variables each time through the
    loop
we can use a "comma expression" as the first or third expression in a "for"
    statement

expr1 , expr2

expr1 and expr2 are any two expressions
first expr1 is evaluated and its value discarded
then expr2 is evaulated; its value is the value of the entire expression
evaluating expr1 should always have a side effect, otherwise expr1 serves no
    purpose

i = 1, j = 5
++i, i + j          /* comma expression */

when evaluated, i is first incremented
then i + j is evaluated, so the value of the expression is 7 (and i is now 2)
comma operator precedence is less than that of all other operators, so theres
    no need to add parentheses around ++i and i + j
left associative

i = 1, j = 2, k = i + j
((i = 1), (j = 2), (k = i + j))

the comma operator is provided for situations where C requires a single
    expression, but we would like to have two or more expressions
essentially this allows us to fuse two expressions into a single expression,
    similar to compound statements
the "for" statement is the likely the only place where the comma operator will
    be used (certain macro definitions may benefit from it)
instead of writing:

sum = 0;
for (i = 1; i <= N; i++)
    sum += i;

we can write

for (sum = 0, i = 1; i <= N; i++)
    sum += i;

/***          square2.c - printing a table of squares (revisited)          ***/

square.c can be improved by converting its "while" loop to a "for" loop:

#include <stdio.h>

int main(void)
{
    int i, n;

    printf("This program prints a table of squares.\n");
    printf("Enter number of entries in table: ");
    scanf("%d", &n);

    for (i = 1; i <= n; i++)
        printf("%10d%10d\n", i, i * i);

    return 0;
}

although "for" statements usually initialize, test, and update the same
    variable, there is actually no requirement that they be related in any way

/***                               square3.c                               ***/

#include <stdio.h>

int main (void)
{
    int i, n, odd, square;

    printf("This program prints a table of squares.\n");
    printf("Enter number of entries in table: ");
    scanf("%d", &n);

    i = 1;
    odd = 3;
    for (square = 1; i <= n; odd += 2) {
        printf("%10d%10d\n", i, square);
        ++i;
        square += odd;
    }
    return 0;
}

the "for" statement initializes square, tests i, and increments odd
i is the number to be squared, square is the square of i, and odd is the odd
    number added to the current square to get the next square

/***   CHAPTER                  6.4                  EXITING FROM A LOOP   ***/

break allows us to leave a loop with an exit point in the middle of the loop
continue makes it possible to skip part of a loop without exiting the loop
goto allows a program to jump from one statement to another

/***                          THE break STATEMENT                          ***/

suppose we write a program that checks whether a number n is prime
this program will use a "for" statement that divides n by the numbers between
    2 and n-1 (n = 5; n / 2, n / 3, n / 4)
the loop should break as soon as any divisor is found (since that would mean
    the number is not prime)
after the loop has ended, we can use an if statement to determine whether
    termination was premature (hence n is not prime) or normal (n is prime)

for (d = 2; d < n; d++)
    if (n % d == 0)
        break;
    if (d < n)
        printf("%d is divisible by %d\n", n, d);
    else
        printf("%d is prime\n", n);

break is useful for writing loops in which the exit point is in the middle of
    the loop rather than the beginning or end
generic format:

for (;;) {
    printf("Enter a number (enter 0 to stop): ");
    scanf("%d", &n);
    if (n == 0)
        break;
    printf("%d cubed is %d\n", n, n * n * n);
}

a break statement can transfer control out of the *innermost* enclosing "while",
    "do", "for", or "switch" statement
when nested, "break" can only escape one level of nesting

while (...) {
    switch (...) {
        ...
        break;
        ...
    }
}

the break transfers control out of the switch, but not out of the while

/***                        THE continue STATEMENT                         ***/

"continue" doesnt really exit a loop
while "break" transfers control just past the end of a loop, "continue"
    transfers control to a point just before the end of the loop body
"continue" is limited to loops (it cannot be used in switch statements)

n = 0;
sum = 0;
while (n < 10) {
    scanf("%d", &i);
    if (i == 0)
        continue;
    sum += i;
    n++;
    /* continue jumps to here */
    }

this loop terminates when 10 nonzero numbers have been read
whenever the number 0 is read, the "continue" statement is executed, skipping
    the rest of the loop body, but still remaining in the loop
if "continue" were not available, the example could be written as:

n = 0;
sum = 0;
while (n < 10) {
    scanf("%d", &i);
    if (i != 0) {
        sum += i;
        n++;
        }
    }

/***                          THE goto STATEMENT                           ***/

the "goto" statement is capable of jumping to any statement in a function,
    provided that the statement has a label
C99 states goto cannot be used to bypass the declaration of a variable-length
    array
a label is just an identifier placed at the beginning of a statement

identifier : statement

a statement may have more than one label
"goto" statement format:

goto identifier ;

executing the statement goto L; transfers control to the statement that follows
    the label L, which must be in the same function as the goto statement

for (d = 2; d < n; d++)
    if (n % d == 0)
        goto done;
done:
if (d < n)
    printf("%d is divisible by %d\n", n, d);
else
    printf("%d is prime\n", n);

break, continue, and return are useful much more often than goto, although goto
     can still have its uses

while (...) {
    switch (...) {
        ...
        goto loop_done;   /* break wont work here */
        ...
    }
}
loop_done: ...

"goto" is also useful for exiting from nested loops

/***                         BALANCING A CHECKBOOK                         ***/

many simple interactive programs are menu-based, presenting the user with a
    list of commands
once the user selects a command, the program executes the desired action, then
    prompts the user for another command
this process continues until the user selects an exit or quit command
the heart of this program is a loop
inside the loop will be statements that prompt the user for a command, read the
    command, then decide what action to take:

for (;;) {
    prompt user to enter command;
    read command;
    execute command;
}

executing the command will require a switch statement, or cascaded if statement

for (;;) {
    prompt user to enter command;
    read command;
    switch (command) {
        case command~1 : perform operation~1; break;
        case command~2 : perform operation~2; break;
        .
        .
        .
        case command~n : perform operation~n; break
        default: print error message; break;
    }
}

this next program will offer the user a menu of choices:
clear the account balance, credit money to the account, debit money from the
    account, display the current balance, and exit the program
a session of the program will look like:

*** ACME checkbook-balancing program ***
Commands: 0=clear, 1=credit, 2=debit, 3=balance, 4=exit

Enter command: 1_
Enter amount of credit: 1042.56_
Enter command: 2_
Enter amount of debit: 133.79_
Enter command: 1_
Enter amount of credit: 1754.32_
.
.
Current balance: $1145.09
Enter command: 4_

when the user enter the command 4 (exit), the program needs to exit from the
    switch statement and the surrounding loop.
"break" wont help, and we would prefer to not use a "goto" statement
we will have the program execute a "return" statement, which will cause "main"
    to return to the operating system

/***                              checking.c                               ***/

#include <stdio.h>

int main(void)
{
    int cmd;
    float balance = 0.0f, credit, debit;

    printf("*** ACME checkbook-balancing program ***\n");
    printf("Commands: 0=clear, 1=credit, 2=debit, ");
    printf("3=balance, 4=exit\n\n");

    for (;;) {
        printf("Enter command: ");
        scanf("%d", &cmd);
        switch (cmd) {
            case 0:
                balance = 0.0f;
                break;
            case 1:
                printf("Enter amount of credit: ");
                scanf("%f", &credit);
                balance += credit;
                break;
            case 2:
                printf("Enter amount of debit: ");
                scanf("%f", &debit);
                balance -= debit;
                break;
            case 3:
                printf("Current balance: $%.2f\n", balance);
                break;
            case 4:
                return 0;
            default:
                printf("Commands: 0=clear, 1=credit, 2=debit, ");
                printf("3=balance, 4=exit\n\n");
                break;
        }
    }
}

note that return is not followed by a break statement, as it can never be
    executed, and many compilers will issue a warning message

/***   CHAPTER                  6.5                   THE NULL STATEMENT   ***/

a null statement is devoid of any symbols except for the semicolon at the end

i = 0; ; j = 1;

this line contains three statements: an assignment to i, a null statement, and
    an assignment to j
the null statement is good for writing loops whose bodies are empty

for (d = 2; d < n; d++)
    if (n % d == 0)         //prime-finding loop 1
        break;

for (d = 2; d < n && n % d != 0; d++)       //prime-finding loop 2
    ;               //empty loop body

first d is initialized, then d < n is tested
if false, the loop terminates
otherwise n % d != 0 is tested, and if thats false, the loop terminates
note that the null statement is placed on a line by itself, otherwise a program
    may get misread by a human reader:

for (d = 2; d < n && n % d != 0; d++);
if (d < n)
    printf("d is divisible by %d\n", n, d);

putting a semicolon after the parentheses in an if, while, or for statement
    creates a null statement, thus ending the if, while, or for prematurely
turning an ordinary loop into one with an empty body is often more concise but
    not usually more efficient
empty body loops do have their clear use cases, such as reading character data

/***                           ADDITIONAL NOTES                            ***/

while (1) and for (;;) are both forms of infinite loops
older compilers may force programs to test the 1 condition each time in a while
    loop, so for (;;) is usually preferred

/***   CHAPTER                        6                        EXERCISES   ***/

1. What output does the following program fragment produce?

"1 2 4 8 16 32 64 128 "

2. What output does the following program fragment produce?

"9384 938 93 9 "

3. What output does the following for statement produce?

"5 4 3 2 "

4. Which one of the following statements is not equivalent to the other two
     (assuming the loop bodies are the same)?

(c) will increment i before it reaches expr3, while (a) and (b) increment one
     statement later

5. Which one of the following statements is not equivalent to the other two
     (assuming the loop bodies are the same)?

(c) will execute its body at least once, while (a) and (b) will not execute
     their bodies if their conditions are false

6. Translate the program fragment of Exercise 1 into a single for statement

for (i = 1; i <= 128; printf("%d ", i), i *= 2) {}

7. Translate the program fragment of Exercise 2 into a single for statement

for (i = 9384; i > 0; printf("%d ", i), i /= 10) {}

8. What output does the following for statement produce?

i is equal to 10; i is equal to or greater than 1; printf prints "10 ", i
    increments to 6; i is divided by 2 and is now equal to 5; printf prints
    "5 ", i increments to 6; i is greater than or equal to 1; i is divided by 2
    and is now equal to 3; printf prints "3 ", i increments to 4; i is greater
    than or equal to 1; i is divided by 2 and is now equal to 2; printf prints
    "2 ", i increments to 3; i is greater than ore qual to 1; i is divided by 2
    and is now equal to 1; printf prints "1 ", i increments to 2; i is greater
    than or equal to 1; i is divided by 2 and is now equal to 1; printf prints
    "1 ", i increments to 2; ... ...

"10 5 3 2 1 1 1 "... with repeating ones

9. Translate the for statement of Exercise 8 into an equivalent while
     statement. You will need one statement in addition to the while loop
     itself.

i = 10;
while (i >= 1) {
    printf("%d ", i++);
    i /= 2;
}

10. Show how to replace a continue statement by an equivalent goto statement.

n = 0;                      |   n = 0;
sum = 0;                    |   sum = 0;
while (n < 10){             |   while (n < 10) {
    scanf("%d", &i);        |       scanf("%d", &i);
    if (i == 0)             |       if (i == 0)
        continue;           |           goto done;
    sum += i;               |       sum += i;
    n++;                    |       n++;
}                           |   }
                            |   done: return 0;

11. What output does the following program fragment produce?

1: sum is equal to 0; i is equal to 0; i is less than 10; if checks 0 % 2, with
    a remainer of 2; continue skips sum += i;
2: i increments to 1; i is less than 10; if checks 1 % 2, with a remainer of 2;
    continue skips sum += i;
3: i increments to 2; i is less than 10; if checks 2 % 2, with a remainer of 0;
    sum += i executes;
4: sum = 2; i increments to 3; i is less than 10; if checks 3 % 2, with a
    remainer of 1; continue skips sum += i;
5: i increments to 4; i is less than 10; if checks 4 % 2, with a remainer of 0;
    sum += i executes;
6: sum = 6; i increments to 5; i is less than 10; if checks 5 % 2, with a
    remainer of 1; continue skips sum += i;
7: i increments to 6; i is less than 10; if checks 6 % 2, with a remainer of 0;
    sum += i executes;
8: sum = 12; i increments to 7; i is less than 10; if checks 7 % 2, with a
    remainder of 1; continue skips sum += i;
9: i increments to 8; i is less than 10; if checks 8 % 2, with a remainder of
    0; sum += i executes;
10: sum = 20; i increments to 9; i is less than 10; if checks 9 % 2, with a
    remained of 1; continue skips sum += i;
11: i increments to 10; i is not less than 10; for exits loop;

printf prints "20" with a new line;

12. Modify the "prime-testing" loop to only check divisors up to the square
     root of n.

   for (d = 2; d < n; d++) {
        if (d * d == n)
            break;
        if (n % d == 0)
            break;
        }

13. Rewrite the following loop so that its body is empty:

for (n = 0; m > 0; n++, m /= 2) {}

14. Find the error in the following program fragment and fix it.

if (n % 2 == 0);            //extra semicolon, causing a null statement that
    printf("n is even\n");  //detaches printf from the loop body

/***   CHAPTER                   6                  PROGRAMMING PROJECTS   ***/

