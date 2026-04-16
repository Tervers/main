/*** CHAPTER               26               MISCELLANEOUS LIBRARY FUNCTIONS ***/


<stdarg.h> makes it possible to write functions with a variable number of argu-
    ments. <stdlib.h> is an assortment of functions that don't fit into one of
    the other headers. <time.h> allows programs to work with dates and times.


//              26.1 THE <stdarg.h> HEADER: VARIABLE ARGUMENTS


'type' va_arg(va_list ap, 'type');
void va_copy(va_list dest, va_list src);
void va_end(va_list ap);
void va_start(va_list ap, 'parmN');

Functions such as printf and scanf have an unusual property: they allow any num-
    ber of arguments. The ability to handle a variable number of arguments isn't
    limited to library functions, as it turns out. The <stdarg.h> header pro-
    vides the tools we'll need to write our own functions with variable-length
    argument lists. <stdarg.h> declares one type (va_list) and defines several
    macros. In C89, there are three macros, named va_start, va_arg, and va_end,
    which can be thought of as functions with the prototypes shown above. C99
    adds a function-like macro named va_copy.
To see how these macros work, we'll use them to write a function named max_int
    that finds the maximum of any number of integer arguments. Here's how we
    might call the function:

max_int(3, 10, 30, 20)

    The first argument specifies how many additional arguments will follow. This
    call of max_int will return 30 (the largest of the numbers 10, 30, and 20).
Here's the definition of the max_int function:

int max_int(int n, ...)     // n must be at least 1
{
    va_list ap;
    int i, current, largest;

    va_start(ap, n);
    largest = va_arg(ap, int);

    for (i = 1; i < n; i++) {
        current = va_arg(ap, int);
        if (current > largest)
            largest = current;
    }

    va_end(ap);
    return largest;
}

The ... symbol in the parameter list (known as an "ellipsis") indicates that the
    parameter n is followed by a variable number of additional parameters.
The body of max_int begins with the declaration of a variable of type va_list:

va_list ap;

Declaring such a variable is mandatory for max_int to be able to access the
    arguments that follow n.
The statement

va_start(ap, n);

    indicates where the variable-length part of the argument list begins (in
    this case, after n). A function with a variable number of arguments must
    have at least one 'normal' parameter; the ellipsis always goes at the end of
    the parameter list, after the last normal paramter.
The statement

largest = va_arg(ap, int);

    fetches max_int's second argument (the one after n), assigns it to largest,
    and automatically advances to the next argument. The word int indicates that
    we expect max_int's second argument to have int type. The statement

current = va_arg(ap, int);

    fetches max_int's remaining arguments, one by one, as it is executed inside
    a loop.

! Don't forget that va_arg always advances to the next argument after fetching
    the current one. Because of this property, we couldn't have written max_
    int's loop in the following way:

for (i = 1; i < n; i++)
    if (va_arg(ap, int) > largest)      // WRONG
        largest = va_arg(ap, int);  !

The statement

va_end(ap);

    is required to 'clean up' before the function returns. (Or, instead of re-
    turning, the function might call va_start and traverse the argument list
    again.)
The va_copy macro copies src (a va_list value) into dest (also a va_list). The
    usefulness of va_copy lies in the fact that multiple calls of va_arg may
    have been made using src before it's copied into dest, thus processing some
    of the arguments. Calling va_copy allows a function to remember where it is
    in the argument list so that it can later return to the same point to reexa-
    mine an argument (and possibly the arguments that follow it).
Each call of va_start or va_copy must be paired with a call of va_end, and the
    calls must appear in the same function. All calls of va_arg must appear be-
    tween the call of va_start (or va_copy) and the matching call of va_end.
! When a function with a variable argument list is called, the compiler performs
    the default argument promotions on all arguments that match the ellipsis. In
    particular, char and short arrguments are promoted to int, and float values
    are promoted to double. Consequently, it doesn't make sense to pass types
    such as char, short, or float to va_arg, since arguments--after promotion--
    will never have one of those types. !


// Calling a Function with a Variable Argument List


Calling a function with a variable argument list is an inherently risky proposi-
    tion. The primary difficulty is that a function with a variable argument
    list has no way to determine the number of arguments or their types. This
    information must be passed into the function and/or assumed by the function.
    max_int relies on the first argument to specify how many additional argu-
    ments follow; it assumes that the arguments are of type int. Functions such
    as printf and scanf rely on the format string, which describes the number of
    additional arguments and the type of each.
Another problem has to do with passing NULL as an argument. NULL is usually de-
    fined to represent 0. When 0 is plassed to a function with a variable argu-
    ment list, the compiler assumes that it represents an integer--there is no
    way it can tell that we want it to represent the null pointer. The solution
    is to add a cast, writing (void*) NULL or (void *) 0 instead of NULL.


// The v...printf Functions


int vfprintf(FILE * restrict stream, const char * restrict format, va_list arg);
int vprintf(const char * restrict format, va_list arg);
int vsnprintf(char * restrict s, size_t n, const char * restrict format,
              va_list arg);
int vsprintf(char * restrict s, const char * restrict format, va_list arg);

The vfprintf, vprintf, and vsprintf functions belong to <stdio.h>. We're dis-
    cussing them here because they're invariably used in conjunction with the
    macros in <stdarg.h>. C99 adds the vsnprintf function.
The v...printf functions are closely related to fprintf, printf, and sprintf.
    Unlike these functions, however, the v...printf functions have a fixed num-
    ber of arguments. Each function's last argument is a va_list value, which
    implies that it will be called by a function with a variable argument list.
    In practice, the v...printf functions are used primarily for writing 'wrap-
    per' functions that accept a variable number of arguments, which are then
    passed to a v...printf function.
As an example. let's say that we're working on a program that needs to display
    error messages from time to time. We'd like each message to begin with a
    prefix of the form

** Error 'n':

where n is 1 for the first error message and increases by one for each subse-
    quent error. To make it easier to produce error messages, we'll write a
    function named errorf that's similar to printf, but adds ** Error n: to the
    beginning of its output and always writes to stderr instead of stdout. We'll
    have errorf call vfprintf to do most of the actual output. Here's what
    errorf might look like:

int errorf(const char *format, ...)
{
    static int num_errors = 0;
    int n;
    val_list ap;

    num_errors++;
    fprintf(stderr, "** Error %d: ", num_errors);
    va_start(ap, format);
    n = vfprintf(stderr, format, ap);
    va_end(ap);
    fprintf(stderr, "\n");
    return n;
}

The wrapper function--errorf--is responsible for calling va_start prior to call-
    ing the v...printf function and for calling va_end after the v...printf
    function returns. The wrapper function is allowed to call va_arg one or more
    times before calling the v...printf function.
The vsnprintf function was added to the C99 version of <stdio.h>. It corresponds
    to snprintf (22.8), which is also a C99 function.


// The v...scanf Functions


int vfscanf(FILE * restrict stream, const char * restrict format, va_list arg);
int vscanf(const char * restrict format, va_list arg);
int vsscanf(const char * restrict s, const char * restrict format, va_list arg);

C99 adds a set of v...scanf functions to the <stdio.h> header. vfscanf, vscanf,
    and vsscanf are equivalent to fscanf, scanf, and sscanf, respectively, ex-
    cept that they have a va_list parameter through which a variable argument
    list can be passed. Like the v...printf functions, each v...scanf function
    is designed to be called by a wrapper function that accepts a variable num-
    ber of arguments, which it then passes to the v...scanf function. The wrap-
    per function is responsible for calling va_start prior to calling the
    v...scanf function and for calling va_end after the v...scanf function re-
    turns.


//              26.2 THE <stdlib.h> HEADER: GENERAL UTILITIES


<stdlib.h> serves as a catch-all for functions that don't fit into any of the
    other headers. The functions in <stdlib.h> fall into eight groups:
> Numeric conversion functions
> Pseudo-random sequence generation functions
> Memory-management functions (Chapter 17)
> Communication with the environment
> Searching and sorting utilities
> Integer arithmetic functions
> Multibyte/wide-character conversion functions (25.2)
> Multibyte/wide-string conversion functions (25.2)


// Numeric Conversion Functions



