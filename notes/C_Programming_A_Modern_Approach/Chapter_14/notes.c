/*** CHAPTER                        14                        THE PROCESSOR ***/



//              14.1 HOW THE PREPROCESSOR WORKS


#: Commands that begin with this are "preprocessing directives."
#define defines a macro.
#include tells the processor to open a particular file and 'include' its con-
	tents as part of the file being compiled
The compilation process:
	C program > Preprocessor > Modified C program > Compiler > Object code

The input to the preprocessor is a C program, possibly containing directives.
	The preprocessor executes these directives and then removes them (it techni-
	cally keeps the lines, but leaves them empty). The output of the pre-
	processor is another C program: the original program edited to contain no
	directives. This code goes to the compiler, which then checks for errors and	translates it to object code (machine instructions)
The preprocessor has only a limited knowledge of C, which makes it capable of
	creating illegal programs as it executes directives


//				14.2 PREPROCESSING DIRECTIVES


Most preprocessing directives will fall into one of these three categories:
-Macro definition (like #define and #undef)
-File inclusion (like #include)
-Conditional compilation (like #if, #ifdef, #ifndef, #elif, #else, and #endif)

Some other, lesser used directives include #error, #line, and #pragma
Rules for all directives:
-Directives always begin with # (it doesn't need to be at the beginning of the
	line, as long as only white space proceeds it)
-Any number of spaces and horizontal tab characters may separate the tokens in a
	directive (e.g. #	define		N		100)
-Directives always end at the first new-line character, unless explicitly con-
	tinued using splices:
	#define DISK_CAPACITY (SIDES *				\
						   TRACKS_PER_SIDE *	\
						   SECTORS_PER_TRACK *	\
						   BYTES_PER_SECTOR)
-Directives can appear anywhere in a program
-Comments may appear on the same line as a directive


//				14.3 MACRO DEFINITIONS


//	Simple Macros (object-like macros)


#define identifier replacement-list
replacement-list is any sequence of "preprocessing tokens"
the replacement list may include identifiers, keywords, numeric constants,
    string liters, operators, and punctuation
!!
#define N = 100     /*** WRONG ***/
...
int a[N];           /* becomes int a[= 100] */

#define N 100;      /*** WRONG ***/
...
int a[N];           /* becomes int a[100;]; */

the compiler will detect these errors, but will flag each use of the macro as
    incorrect, instead of the macro definition itself. This is due to the pre-
    processor removing the definition.
!!
K&R refered to simple macros as "manifest constants"
we can give names to numeric, character, and string values:
#define STR_LEN 80
#define TRUE    1
#define FALSE   0
#define PI      3.14159
#define CR      '/r'
#define EOS     '/0'
#define MEM_ERR "Error: not enough memory"
defines can:
    make programs easier to read and modify
    help avoid inconsistencies and typographical errors
    make minor changes to the syntax of C:
        #define BEGIN {
        #define END }
        #define LOOP for (;;)
    rename types (although type definitions are a better way)
    control conditional compilation:
        #define DEBUG
            //a macro's replacement list may be empty
when macros are used as constants, programmers customarily capitalize all let-
    ters in their names. However, there's no consensus as to how to capitalize
    macros used for other purposes


//  Parameterized Macros (a.k.a. function-like macros)


#define identifier( x1 , x2 , ... , xn ) replacement-list
where x1, x2, ..., xn are identifiers (the macro's "parameters")
the parameters may appear as many times as desired in the replacement list
!! there must be NO space between the macro name and the left parenthesis !!
when the preprocessor encounters the definition of a parameterized macro, it
    stores the definition away for later use
whenever a macro "invocation" of the form identifier(y1, y2, ..., yn) appears
    later in the program (where y1, y2, ..., yn are sequences of tokens), the
    preprocessor replaces it with replacement-list, substituting y1 for x1, y2
    for x2, and so forth:
        #define MAX(x,y)    ((x)>(y)?(x):(y))
        #define IS_EVEN(n)  ((n) %2==0)
the two above macros can be invoked in the following way:
    i = MAX(j+k, m-n);
    if (IS_EVEN(i)) i++;
MAX behaves like a function that computes the larger of two values
IS_EVEN behaves like a function that returns 1 if its argument is an even number
    and 0 otherwise
a more complicated macro:
#define TOUPPER(c) ('a'<=(c)&&(c)<='z'?(c)-'a'+'A':(c))
a parameterized macro may have an empty parameter list:
#define getchar() getc(stdin)
!* this is the same getchar that belongs to <stdio.h> *!
parameterized macros have a couple of advantages:
-the program *may* be slightly faster. function calls usually require some over-    head during program execution; context information must be saved, arguments
    copied, etc. (although inline functions provide a way to avoid this overhead
    without the use of macros)
-macros are "generic," meaning they have no particular type. This means a macro
    can accept arguments of any type, provided the resulting program, after pre-
    processing, is valid
-parameterized macros are useful for segments of code that we find ourselves
    often repeating
parameterized macros also have some disadvantages:
-the compiled code can often be larger, especially with nested macros:
    n = MAX(i, MAX(j, k));
    becomes
    n = ((i)>(((j)>(k)?(j):(k)))?(i):(((j)>(k)?(j):(k))));
-arguments aren't type-checked, which means the compiler will not check if the
    argument is converted to the proper type, nor will the compiler produce an
    error message
-it is not possible to have a pointer to a macro.
-a macro may evaluate its arguments more than once, which can cause unexpected
    behavior if the argument has side effects


//  The # Operator


macros may contain the # and ## operators
neither # or ## are recognized by the compiler; both are executed during pre-
    processing
# converts a macro argument into a string literal ("stringization"). it can only
    appear in the replacement list of a parameterized macro:
#define PRINT_INT(n) printf(#n " = %d\n", n)
if the above #define is invocated in the following way:
    PRINT_INT(i/j);
the result will be:
    printf("i/j" " = %d\n", i/j);
which then becomes:
    printf("i/j = %d\n", i/j);   // C combines adjacent strings


//  The ## Operator


The ## operator can 'paste' two tokens together to form a single token:
#define MK_ID(n) i##n
Suppose you invoke:
    int MK_ID(1), MK_ID(2), MK_ID(3);
After preprocessing, the above declaration becomes
    int i1, i2, i3;
Suppose we want to make a MAX function, but the MAX function may need to compare
    int values, float values, and other types. Instead of writing a MAX function
    for each type, we can create a macro that will create a MAX function of each
    type while also giving each MAX function it's own name:
#define GENERIC_MAX(type)       \
type type##_max(type x, type y) \
{                               \
    return x > y ? x : y;       \
}
If we invoke GENERIC_MAX(float), the preprocessor will expand it into:
float float_max(float x, float y) { return x > y ? x : y; }


//  General Properties of Macros



