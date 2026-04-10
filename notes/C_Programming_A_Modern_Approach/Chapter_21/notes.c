/*** CHAPTER                    21                     THE STANDARD LIBRARY ***/


//              21.1 USING THE LIBRARY


    Standard Library Headers
C89                 C99
------------        ------------
<assert.h>          <complex.h>
<ctype.h>           <fenv.h>
<errno.h>           <inttypes.h>
<float.h>           <iso646.h>
<limits.h>          <stdbool.h>
<locale.h>          <stdint.h>
<math.h>            <tgmath.h>
<setjmp.h>          <wchar.h>
<signal.h>          <wctype.h>
<stdarg.h>
<stddef.h>
<stdio.h>
<stdlib.h>
<string.h>
<time.h>

Most compilers come with a more extensive library that invariably has many head-
    ers that don't appear in the above table. The extra headers aren't standard,
    of course, so we can't count on them to be available with other compilers.
    These headers often provide functions that are specific on a particular com-
    puter or operating system (which explains why they're not standard). They
    may provide functions that allow more control over the screen and keyboard.
    Headers that support graphics or a window-based user interface are also
    common.
The standard headers consist primarily of function prototypes, type definitions,
    and macro definitions. If one of our files contains a call of a function de-
    clared in a header or uses one of the types or macros defined there, we'll
    need to include the header at the beginning of the file. When a file in-
    cludes several standard headers, the order of #include directives doesn't
    matter. It's also legal to include a standard header more than once.


// Restrictions on Names Used in the Library


Any file that includes a standard header must obey a couple of rules. First, it
    can't use the names of macros defines in that header for any other purpose.
    If a file includes <stdio.h>, for example, it can't reuse NULL, since a
    macro by that name is already defined in <stdio.h>. Second, library names
    with file scope (typedef names, in particular) can't be redefined at the
    file level. Thus, if a file includes <stdio.h>, it can't define size_t as a
    identifier with file scope, since <stdio.h> defines size_t to be a typedef
    name.
Although these restrictions are pretty obvious, C has other restrictions that
    you might not expect:

> Identifiers that begin with an underscore followed by an upper-case letter or
    a second underscore are reserved for use within the library; programs should
    never use names of this form for any purpose.
> Identifiers that begin with an underscore are reserved for use as identifiers
    and tags with file scope. You should never use such a name for your own pur-
    poses unless it's declared inside a function.
> Every identifier with external linkage in the standard library is reserved for
    use as an identifier with external linkage. In particular, the names of all
    standard library functions are reserved. Thus, even if a file doesn't! in-
    clude <stdio.h>, it shouldn't define an external function named printf,
    since there's already a function with this name in the library.

These rules apply to every file in a program, regardless of which headers the
    file includes. Although these rules aren't always enforced, failing to obey
    them can lead to a program that's not portable.
The rules also apply to names that are set aside for future use. The complete
    description of which names are reserved is rather lengthy; you'll find it in
    the C standard under 'future library directions.' As an example, C reserves
    identifiers that begin with str followed by a lower-case letter, so that
    functions with such names can be added to the <string.h> header.


// Functions Hidden by Macros


It's common for C programmers to replace small functions by parameterized mac-
    ros. This practice occurs even in the standard library. The C standard al-
    lows headers to define macros that have the same names as library functions,
    but protects the programmer by requiring that a true function be available
    as well. As a result, it's not unusual for a library header to declare a
    function and define a macro with the same name.
We've already seen an example of a macro duplicating a library function. getchar
    is a library function declared in the <stdio.h> header. It has the following
    prototype:

int getchar(void);

<stdio.h> usually defines getchar as a macro as well:

#define getchar() getc(stdin)

By default, a call of getchar will be treated as a macro invocation (since macro
    names are replaced during preprocessing).
Most of the time, we're happy using a macro instead of a true function, because
    it will probably make our program run faster. Occasionally, though, we want
    a genuine function, perhaps to minimize the size of the executable code.
If the need arises, we can remove a macro definition (thus gaining access to the
    true function) by using the #undef directive. For example, we could undefine
    the getchar macro after including <stdio.h>:

#include <stdio.h>
#undef getchar

If getchar isn't! a macro, no harm has been done; #undef has no effect when giv-
    en a name that's not defined as a macro.
As an alternative, we can disable individual uses of a macro by putting paren-
    theses around its name:

ch = (getchar)();   // instead of ch = getchar();

The preprocessor can't spot a parameterized macro unless its name is followed by
    a left parenthesis. The compiler isn't so easily fooled, however; it can
    still recognize getchar as a function.


//              21.2 C89 LIBRARY OVERVIEW


<assert.h> Diagnostics (24.1)
    Contains only the assert macro, which allows us to insert self-checks into a
        program. If any check fails, the program terminates.

<ctype.h> Character Handling (23.5)
    Provides functions for classifying characters and for converting letters
        from lower case to upper case and vice versa.

<errno.h> Errors (24.2)
    Provides errno ('error number'), an lvalue that can be tested after a call
        of certain library functions to see if an error occurred during the
        call.

<float.h> Characteristics of Floating Types (23.1)
    Providese macros that describe the characteristics of floating types, in-
        cluding range and accuracy.

<limits.h> Sizes of Integer Types (23.2)
    Provides macros that describe the characteristics of integer types (includ-
        ing character types), including their maximum and minimum values.

<locale.h> Localization (25.1)
    Provides functions to help a program adapt its behavior to a country or oth-
        er geographic region. Locale-specific behavior includes the way numbers
        are printed, the format of monetary values, the character set, and the
        appearance of the date and time.

<math.h> Mathematics (23.3)
    Provides common mathematical functions, including trigonometric, hyperbolic,
        exponential, logarithmic, power, nearest integer, absolute value, and
        remainder functions.

<setjmp.h> Nonlocal Jumps (24.4)
    Provides the setjmp and longjmp functions. setjmp 'marks' a place in a pro-
        gram; longjmp can then be used to return to that place later. These
        functions make it possible to jump from one function into another,
        still-active function, bypassing the normal function-return mechanism.
        setjmp and longjmp are used primarily for handling serious problems that
        arise during program execution.

<signal.h> Signal Handling (24.3)
    Provides functions that deal with exceptional conditions (signals), includ-
        ing interrupts and run-time errors. The signal function installs a func-
        tion to be called if a given signal should occur later. The raise func-
        tion causes a signal to occur.

<stdarg.h> Variable Arguments (26.1)
    Provides tools for writing functions that, like printf and scanf, can have a
        variable number of arguments.

<stddef.h> Common Definitions (21.4)
    Provides definitions of frequently used types and macros.

<stdio.h> Input/Output (22.1-22.8)
    Provides a large assortment of input/output functions, including operations
        on both sequential and random-access files.

<stdlib.h> General Utilities (26.2)

