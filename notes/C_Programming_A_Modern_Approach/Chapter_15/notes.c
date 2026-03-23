/*** CHAPTER                   15                    WRITING LARGE PROGRAMS ***/



//              15.1 SOURCE FILES


source files have the extension .c
each source file constains part of the program, primarily definitions of
    functions and variables
one source file must contain a function named main, which serves as the starting
    point for the program


//              15.2 HEADER FILES


#include tells the preprocessor to open a specified file and insert its contents
    into the current file
files included in this fashion are called "header files" (sometimes include
    files)
header files have the extension .h
!the C standard uses the term fource file to refer to all files written by the
    programmer, including both .c and .h files. source file, in the context of
    these notes, refer to .c files only


// The #include Directive


#include <filename> //for header files belonging to C's own library
#include "filename" //for all other headers, including any that we write

the compiler will locate the header files as follows:
    -#include <filename>: Search the directory (or directories) in which system
        header files reside (UNIX: usually /usr/include)
    -#include "filename": Search the current directory, then search the direc-
        tory (or directories) in which system header files reside.
the places to be searched for header files can usually be altered, often by a
    command-line option such as -Ipath

#include "c:\cprogs\utils.h" /* Windows path */
#include "/cprogs/utils.h"   /* UNIX path */

you should avoid using path or drive information, like shown above. Compiling on
    another machine or operating system may fail
these following directives are better; they don;t mention specific drives, and
    paths are relative rather than absolute:

#include "utils.h"
#include "../include/utils.h"

a third form of #include:

#include tokens

where "tokens" is any sequence of preprocessing tokens. the preprocessor will
    scan the tokens and replace any macros that it finds. after macro replace-
    ment, the resulting directive must match one of the other forms of #include:

#if defined(IA32)
    #define CPU_FILE "ia32.h"
#elif defined(IA64)
    #define CPU_FILE "ia64.h"
#elif defined(AMD64)
    #define CPU_FILE "amd64.h"
#endif

#include CPU_FILE


// Sharing Macro Definitions and Type Definitions


most large programs contain macro definitions and type definitions that need to
    be shared by several source files (or sometimes all source files). These
    definitions should go into header files.

//boolean.h
#define BOOL int
#define TRUE 1
#define FALSE 0

//prog.c
#include "boolean.h"


// Sharing Function Prototypes


function prototypes should be placed in a header file, and then the header file 
    included in all the places the functions are called.


// Sharing Variable Declarations


int i; /* declares i and defines it as well */

the above line declares i to be a variable of type int, and also defines i by
    causing the compiler to set aside space for i
to declare i without defining it:

extern int i; /* declares i without defining it */

extern informs the compiler that i is defined elsewhere in the program, so it
    shouldn't allocate space for it


// Protecting Header Files


if a source file includes the same header file twice, compilation errors may
    result. This problem is common when header files include other header files.    To protect a header file, we can enclose the contents of the file in an
    #ifndef-#endif pair:

#ifndef BOOLEAN_H
#define BOOLEAN_H

#define TRUE 1
#define FALSE 0
typedef int Bool;

#endif

when this file is included the first time, the BOOLEAN_H macro won't be defined.
    If the file should be included a second time, the preprocessor will remove
    the lines between #ifndef and #endif, protecting from duplicate definitions


// #error Directives in Header Files


to prevent a header file from being used with older, nonstandard compilers, you
    can use an #ifndef directive that tests for the existence of the __STDC__
    macro:

#ifndef __STDC__
#error This header requires a Standard C compiler
#endif


//              15.3 DIVIDING A PROGRAM INTO FILES



