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
    A 'catchall' header for functions that don't fit into any of the other head-
        ers. The functions in this header can convert strings to numbers, gener-
        ate pseudo-random numbers, perform memory management tasks, communicate
        with the operating system, do searching and sorting, and perform conver-
        sions between multibyte characters and wide characters.

<string.h> String Handling (23.6)
    Provides functions that perform string operations, including coping, concat-
        enation, comparison, and searching, as well as functions that operate on
        arbitrary blocks of memory.

<time.h> Date and Time (26.3)
    Provides functions for determining the time (and date), manipulating times,
        and formatting times for display.


//              21.3 C99 LIBRARY CHANGES


<complex.h> Complex Arithmetic (27.4)
    Defines the complex and I macros, which are useful when working with complex
        numbers. Also provides functions for performing mathematical operations
        on complex numbers.

<fenv.h> Floating-Point Environment (27.6)
    Provides access to floating-point status flags and control modes. For exam-
        ple, a program might test a flag to see if overflow occurred during a
        floating-point operating or set a control mode to specify how rounding
        should be done.

<inttypes.h> Format Conversion of Integer Types (27.2)
    Defines macros that can be used in format strings for input/output of the
        integer types declared in <stdint.h>. Also provides functions for work-
        ing with greatest-width integers.

<iso646.h> Alternative Spellings (25.3)
    Defines macros that represent certain operators (the ones containing the
        characters &, |, ~, !, and ^). These macros are useful for writing pro-
        grams in an environment where these characters might not be part of the
        local character set.

<stdbool.h> Boolean Type and Values (21.5)
    Defines the bool, true, and false macros, as well as a macro that can be
        used to test whether these macros have been defined.

<stdint.h> Integer Types (27.1)
    Declares integer types with specified widths and defines related macros
        (such as macros that specify the maximum and minimum values of each
        type). Also defines parameterized macros that construct integer con-
        stants with specific types.

<tgmath.h> Type-generic Math (27.5)
    In C99, there are multiple versions of many math functions in the <math.h>
        and <complex.h> headers. The 'type-generic' macros in <tgmath.h> can de-
        tect the types of the arguments passed to them and substitute a call of
        the appropriate <math.h> or <complex.h> function.

<wchar.h> Extended Multibyte and Wide-Character Utilities (25.5)
    Providese functions for wide-character input/output and wide string manipu-
        lation.

<wctype.h> Wide-Character Classification and Mapping Utilities (25.6)
    The wide-character version of <ctype.h>. Provides functions for classifying
        and changing the case of wide characters.


//              21.4 THE <stddef.h> HEADER: COMMON DEFINITIONS


The <stddef.h> header provides definitions of frequently used types and macros;
    it doesn't declare any functions. The types are:

> ptrdiff_t: The type of the result when two pointers are subtracted.
> size_t: The type returned by the sizeof operator.
> wchar_t: A type large enough to represent all possible characters in all sup-
    ported locales.

All three are names for integer types; ptrdiff_t must be a signed type, while
    size_t must be an unsigned type. See 25.2 for more information about
    wchar_t.
The <stddef.h> header also defines two macros. One of them is NULL, which repre-
    sents the null pointer. The other macro, offsetof, requires two arguments:
    type (a structure type) and member-designator (a member of the structure).
    offsetof computes the number of bytes between the beginning of the struc-
    ture and the specified member:

struct s {
    char a;
    int b[2];
    float c;
};

The value of offsetof(struct s, a) must be 0; C guarantees that the first member
    of a structure has the same address as the structure itself. We can't say
    for sure what the offsets of b and c are. One possibility is that offsetof
    (struct s, b) is 1 (since a is one byte long), and offsetof(struct s, c) is
    9 (assuming 32-bit integers). However, some compilers leave 'holes' -- un-
    used bytes -- in structures, which can affect the value produced by
    offsetof. If a compiler should leave a three-byte hole after a, for example,
    then the offsets of b and c would be 4 and 12, respectively. But that's the
    beauty of offsetof: it produces the correct offsets for any compiler, ena-
    bling us to write portable programs.
Suppose that we want to save the first two members of an s structure in a file,
    ignoring the c member. Instead of having the fwrite function write sizeof
    (struct s) bytes, which would save the entire structure, we'll tell it to
    write only offsetof(struct s, c) bytes.
Some of the types and macros defined in <stddef.h> appear in other headers as
    well. (The NULL macro, for example, is also defined in <locale.h>,
    <stdio.h>, <stdlib.h>, <string.h>, and <time.h>, as well as in the C99 head-
    er <wchar.h>.) As a result, few programs need to include <stddef.h>.


//              21.5 <stdbool.h> HEADER (C99): BOOLEAN TYPE AND VALUES


The <stdbool.h> header defines four macros:

> bool (defined to be _Bool)
> true (defined to be 1)
> false (defined to be 0)
> __bool_true_false_are_defined(defined to be 1)

We've seen many examples of how bool, true, and false are used. Potential uses
    of the __bool_true_false_are_defined macro are more limited. A program could
    use a preprocessing directive (such as #if or #ifdef) to test this macro be-
    fore attempting to define its own version of bool, true, or false.


//              Q & A


Q: 14.3 described some disadvantages of using parameterized macros in place of
    functions. In light of these problems, isn't it dangerous to provide a macro
    substitute for a standard library function?

A: According to the C standard, a parameterized macro that substitutes for a
    library function must be 'fully protected' by parentheses and must evaluate
    its arguments exactly once. These rules avoid most of the problems mentioned
    in 14.3.
