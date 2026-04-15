/*** CHAPTER                       24                        ERROR HANDLING ***/


//              24.1 THE <assert.h> Header: Diagnostics


void assert(scalar expression);

assert, which is defined in the <assert.h> header, allows a program to monitor
    its own behavior and detect possible problems at an early stage.
Although assert is actually a macro, it's designed to be used like a function.
    It has one argument, which must be an 'assertion'--an expression that we ex-
    pect to be true under normal circumstances. Each time assert is executed, it
    tests the value of its argument. If the argument has a nonzero value, assert
    does nothing. If the argument's value is zero, assert writes a message to
    stderr and calls the abort function to terminate program execution.
For example, let's say that the file demo.c declares an array a of length 10.
    We're concerned that the statement

a[i] = 0;

    in demo.c might cause the program to fail because i isn't between 0 and 9.
    We can use assert to check this condition before we perform the assignment
    to a[i]:

assert(0 <= i && i < 10);
a[i] = 0;

    If i's value is less than 0 or greater than or equal to 10, the program will
    terminate after displaying a message like the following one:

Assertion failed: 0 <= i && i < 10, file demo.c, line 109

C99 chages assert in a couple of minor ways. The C89 standard states that the
    argument to assert must have int type. The C99 standard relaxes this re-
    quirement, allowing the argument to have any scalar type (hence the word
    scalar in the prototype for assert). This change allows the argument to be a
    floating-point number or a pointer, for example. Also, C99 requires that a
    failed assert display the name of the function in which it appears. (C89
    requires only that assert display the argument--in text form--along with the
    name of the source file and the source line number). The suggested form of
    the message is

Assertion failed: expression, function abc, file xyz, line nnn.

The exact form of the message produced by assert may vary from one compiler to
    another, although it should always contain the information required by the
    standard. For example, the GCC compiler produces the following message in
    the situation described earlier:

a.out: demo.c:109: main: Assertion '0 <= i && i < 10' failed.

assert has one disadvantage: it slightly increases the running time of a program
    because of the extra check it performs. Using assert once in a while proba-
    bly won't have any great effect on a program's speed, but even this small
    time penalty may be unacceptable in critical applications. As a result, many
    programmers use assert during testing, then disable it when the program is
    finished. Disabling assert is easy: we need only define the macro NDEBUG
    prior to including the <assert.h> header:

#define NDEBUG
#include <assert.h>

    The value of NDEBUG doesn't matter, just the fact that it's defined. If the
    program should fail later, we can reactivate assert by removing NDEBUG's
    definition.
! Avoid putting an expression that has a side effect--including a function call
    --inside an assert; if assert is disabled at a later date, the expression
    won't be evaluated. Consider the following example:

assert((p = malloc(n)) != NULL);

    If NDEBUG is defined, assert will be ignored and malloc won't be called. !
