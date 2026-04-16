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


//              24.2 THE <errno.h> HEADER: ERRORS


Some functions in the standard library indicate failure by storing an error code
    (a positive integer) in errno, an int variable declared in <errno.h>. (errno
    may actually be a macro. If so, the C standard requires that it represent an
    lvalue, allowing us to use it like a variable.) Most of the functions that
    rely on errno belong to <math.h>, but there are a few in other parts of the
    library.
Let's say that we need to use a library function that signals an error by stor-
    ing a value in errno. After calling the function, we can check whether the
    value of errno is nonzero; if so, an error occurred during the function
    call. For example, suppose that we want to check whether a call of the sqrt     function has failed. Here's what the code would look like:

errno = 0;
y = sqrt(x);
if (errno != 0) {
    fprintf(stderr, "sqrt error; program terminated.\n");
    exit(EXIT_FAILURE);
}

    When errno is used to detect an error in a call of a library function, it's
    important to store zero in errno before calling the function. Although errno
    is zero at the beginning of program execution, it could have been altered by
    a later function call. Library functions never clear errno; that's the pro-
    gram's responsibility.
The value stored in errno when an error occurs is often either EDOM or ERANGE.
    (Both are macros defined in <errno.h>.) These macros represent the two kinds
    of errors that can occur when a math function is called:
> Domain errors (EDOM): An argument passed to a function is outside the func-
    tion's domain, For example, passing a negative number to sqrt causes a do-
    main error.
> Range errors (ERANGE): A function's return value is too large to be represent-
    ed in the function's return type. For example, passing 1000 to the exp func-
    tion usually causes a range error, because e^1000 is too large to represent
    as a double on most computers.
Some functions can experience both kinds of errors; by comparing errno to EDOM
    or ERANGE, we can determine which error occurred.
C99 adds the EILSEQ macro to <errno.h>. Library functions in certain headers--
    especially the <wchar.h> header--store the value of EILSEQ in errno when an
    encoding error occurs.


// The perror and strerror Functions


void perror(const char *s);     // <stdio.h>
char *strerror(int errnum);     // <string.h>

When a library function stores a nonzero value in errno, we may want to display
    a message that indicates the nature of the error. One way to do this is to
    call the perror function, which prints the following items, in the order
    shown: (1) its argument, (2) a colo, (3) a space, (4) an error message de-
    termined by the value of errno, and (5) a new-line character. perror writes
    to the stderr stream, not to standard output.

errno = 0;
y = sqrt(x);
if (errno != 0) {
    perror("sqrt error");
    exit(EXIT_FAILURE);
}

    If the call of sqrt fails because of a domain error, perror will generate
    the following output:

sqrt error: Numerical argument out of domain

    The error message that perror displays after sqrt error is implementation-
    defined. In this example, 'Numerical argument out of domain' is the message
    that corresponds to the EDOM error. An ERANGE error usually produces a dif-
    ferent message, such as 'Numerical result out of range.'
The strerror function belongs to <string.h>. When passed an error code, strerror
    returns a pointer to a string describing the error. For example, the call

puts(strerror(EDOM));

might print

Numerical argument out of domain

    The argument to strerror is usually one of the values of errno, but strerror
    will return a string for any integer passed to it.
strerror is closely related to the perror function. The error message that
    perror displays is the same message that strerror would return if passed
    errno as its argument.


//              24.3 THE <signal.h> HEADER: SIGNAL HANDLING


<signal.h> provides facilities for handling exceptional conditions, known as
    "signals." Signals fall into two categories: run-time errors (such as divi-
    sion by zero) and events caused outside the program. Many OSes, for example,
    allow users to interrupt or kill running programs; these events are treated
    as signals in C. When an error or external event occurs, we say that a sig-
    nal has been "raised." Many signals are asynchronous: they can happen at any
    time during program execution, not just at certain points that are known to
    the programmer. Since signals may occur at unexpected times, they have to be
    dealt with in a unique way.


// Signal Macros


The value of each signal macro is a positive integer constant. C implementations
    are allowed to provide other signal macros, as long as their names begin
    with SIG followed by an upper-case letter. (UNIX implementations, in parti-
    cular, provide a large number of additional signal macros.)
The C standard doesn't require that these next signals be raised automatically,
    since not all of them may be meaningful for a particular computer and OS.
    Most implementations support at least some of these signals:

SIGABRT     Abnormal termination (possibly caused by a call of abort)
SIGFPE      Error during an arithmetic operation (possibly division by zero)
SIGILL      Invalid instruction
SIGINT      Interrupt
SIGSEGV     Invalid storage access
SIGTERM     Termination request


// The signal Function


void (*signal(int sig, void (*func)(int)))(int);

<signal.h> provides two functions: raise and signal. signal installs a signal-
    handling function for use later if a given signal should occur. signal is
    much easier to use than you might expect from its rather intimidating proto-
    type. Its first argument is the code for a particular signal; the second ar-
    gument is a pointer to a function that will handle the signal if it's raised
    later in the program. For example, the following call of signal installs a 
    handler for the SIGINT signal:

signal(SIGINT, handler);

    handler is the name of a signal-handling function. If the SIGINT signal oc-
    curs later during program execution, handler will be called automatically.
Every signal-handling function must have an int parameter and a return type of
    void. When a particular signal is raised and its handler is called, the han-
    dler will be passed the code for the signal. Knowing which signal caused it
    to be called can be useful for a signal handler; in particular, it allows us
    to use the same handler for several different signals.
A signal-handling function can do a variety of things. Possibilities include ig-
    noring the signal, performing some sort of error recovery, or terminating
    the program. Unless it's invoked by abort or raise, however, a signal han-
    dler shouldn't call a library function or attempt to use a variable with
    static storage duration. (There are a few exceptions to these rules, how-
    ever.)
If a signal-handling function returns, the program resumes executing for the
    point at which the signal occurred, except in two cases: (1) If the signal
    was SIGABRT, the program will terminate (abnormally) when the handler re-
    turns. (2) The effect of returning from a function that has handler SIGFPE
    is undefined. (In other words, don't do it.)
Although signal has a return value, it's often discarded. The return value, a
    pointer to the previous handler for the specified signal, can be saved in a
    variable if desired. In particular, if we plan to restore the original sig-
    nal handler later, we need to save signal's return value:

void (*orig_handler)(int);
...
orig_handler = signal(SIGINT, handler);

    This statement installs handler as the handler for SIGINT and then saves a
    pointer to the original handler in the orig_handler variable. To restore the
    original handler later, we'd write

signal(SIGINT, orig_handler);


// Predefined Signal Handlers


Instead of writing our own signal handlers, we have the option of using one of
    the predefined handlers that <signal.h> provides.
> SIG_DFL handles signals in a 'default' way. To install SIG_DFL, we'd use a
    call such as

signal(SIGINT, SIG_DFL);

    The effect of calling SIG_DFL is implementation-defined, but in most cases
    it causes program termination.
> SIG_IGN specifies that SIGINT is to be ignored if it should be raised later.

signal(SIGINT, SIG_IGN);

    In addition to SIG_DFL and SIG_IGN, the <signal.h> header may provide other
    signal handlers; their names must begin with SIG_ followed by an upper-case
    letter. At the beginning of program execution, the handler for each signal
    is initialized to either SIG_DFL or SIG_IGN, depending on the implementa-
    tion.
<signal.h> defines another macro, SIG_ERR, that looks like it should be a signal
    handler. SIG_ERR is actually used to test for an error when installing a
    signal handler. If a call of signal is unsuccessful--it can't install a han-
    dler for the specified singal--it returns SIG_ERR and stores a positive val-
    ue in errno. Thus, to test whether signal has failed, we could write

if (signal(SIGINT, handler) == SIG_ERR) {
    perror("signal(SIGINT, handler) failed");
    ...
}

There's one tricky aspect to the entire signal-handling mechanism: what happens
    if a signal is raised by the function that handles that signal? To prevent
    infinite recursion, the C89 standard prescribes a two-step process when a
    signal is raised for which a signal-handling function has been installed by
    the programmer. First, either the handler for that signal is reset to
    SIG_DFL or else the signal is blocked from occurring while the handler is
    executing. (SIGILL is a special case; neither action is required when SIGILL
    is raised.) Only then is the handler provided by the programmer called.
! After a signal has been handled, whether or not the handler needs to be rein-
    stalled is implementation-defined. UNIX implementations typically leave the
    signal handler installed after it's been used, but other implementations may
    reset the handler to SIG_DFL. In the latter case, the handler can reinstall
    itself by calling signal rebfore it returns. !
C99 changes the signal-handling process in a few minor ways. When a signal is
    raised, an implementation may choose to disable not just that signal but
    others as well. If a signal-handling function returns from handling a SIGILL
    or SIGSEGV signal (as well as a SIGFPE signal), the effect is undefined. C99
    also adds the restriction that if signal occurs as a result of calling the
    abort function or the raise function, the signal handler itself must not
    call raise.


// The raise Function


int raise(int sig);
