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


