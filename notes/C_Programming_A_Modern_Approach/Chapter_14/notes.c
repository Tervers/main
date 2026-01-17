/*** CHAPTER                        14                        THE PROCESSOR ***/



//              14.1 HOW THE PREPROCESSOR WORKS


#: Commands that begin with this are "preprocessing directives."
#define defines a macro.
#include tells the processor to open a particular file and 'include' its con-
	tents as part of the file being compiled.
The compilation process:
	C program > Preprocessor > Modified C program > Compiler > Object code

The input to the preprocessor is a C program, possibly containing directives.
	The preprocessor executes these directives and then removes them (it techni-
	cally keeps the lines, but leaves them empty). The output of the pre-
	processor is another C program: the original program edited to contain no
	directives. This code goes to the compiler, which then checks for errors and	translates it to object code (machine instructions).
The preprocessor has only a limited knowledge of C, which makes it capable of
	creating illegal programs as it executes directives.


//				14.2 PREPROCESSING DIRECTIVES


Most preprocessing directives will fall into one of these three categories:
-Macro definition (like #define and #undef)
-File inclusion (like #include)
-Conditional compilation (like #if, #ifdef, #ifndef, #elif, #else, and #endif)

Some other, lesser used directives include #error, #line, and #pragma
Rules for all directives:
-Directives always begin with # (it doesn't need to be at the beginning of the
	line, as long as only white space proceeds it).
-Any number of spaces and horizontal tab characters may separate the tokens in a
	directive (e.g. #	define		N		100)
-Directives always end at the first new-line character, unless explicitly con-
	tinued using splices:
	#define DISK_CAPACITY (SIDES *				\
						   TRACKS_PER_SIDE *	\
						   SECTORS_PER_TRACK *	\
						   BYTES_PER_SECTOR)
-Directives can appear anywhere in a program.
-Comments may appear on the same line as a directive


//				14.3 MACRO DEFINITIONS


//	Simple Macros (object-like macros)
