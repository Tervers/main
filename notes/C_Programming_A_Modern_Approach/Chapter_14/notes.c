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
suppose that we invoke the two macros in the following way:
    i = MAX(j+k, m-n);
    if (IS_EVEN(i)) i++;
MAX behaves like a function that computes the larger of two values
IS_EVEN behaves like a function that returns 1 if its argument is an even number
    and 0 otherwise

