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


each set of functions will go into a separate source file (let's say foo.c)
foo.h will contain the prototypes for the functions defined in foo.c (functions
    designed for use only within foo.c shouldn't be declared in foo.h)
include foo.h in each source file that needs to call a function defined in foo.c
include foo.h in foo.c so that the compiler can check that the function proto-
    types in foo.h are consistent with the definitions in foo.c
the main function will go in a file whose name matches the name of the program
    (so if we want the program to be known as bar, then main should be in the
    file bar.c)
it's possible that there are other functions in the same file as main, so long
    as they're not called from other files in the program.


// Text Formatting


we'll write a small text-formatting program named justify. As sample input to
    justify, we'll use a file named 'quote' that contains a (poorly formatted)
    quotation.
to run the program from a UNIX or Windows prompt:

justify <quote

the < symbol informs the OS that justify will read from the file quote
using < is known as input redirection
this normally just prints the file on the screen, but you can save it to a file
    by using output redirection:

justify <quote >newquote

justify will delete extra spaces and blank lines, and lines will be filled and
    justified. Filling a line means adding words until one more word would cause
    the line to overflow. Justifying a line means adding extra spaces between
    words so that each line has exactly the same length (60 characters). The
    last line won't be justified. We'll assume that no word is longer than 20
    characters. After the first 20 characters, the rest will be replaced with a
    single asterisk.
now to think about program design. We observe that the program can't write the
    words one by one as they're read. Instead, the program will have to store
    them in a 'line buffer' until there are enough to fill a line. The program
    will be a loop that goes something like this:

for (;;) {
    read word;
    if (can't read word) {
        write contents of line buffer without justification;
        terminate program;
    }

    if (word doesn't fit in line buffer) {
        write contents of line buffer with justification;
        clear line buffer;
    }
    add word to line buffer;
}

since we'll need functions that deal with words and functions that deal with
    the line buffer, let's split the prograinto three source files, putting all
    functions related to words in one file(word.c) and all functions related to
    the line buffer in another file (line.c). A third file (justify.c) will con-
    tain the main function. We'll also need word.h and line.h. word.h will con-
    tain prototypes for the functions in word.c; line.h will play a similar role
    for line.c.


//              word.h


#ifndef WORD_H
#define WORD_H

void read_word(char *word, int len);

#endif


the WORD_H macro protects word.h from being included more than once (although
    word.h doesn't really need, it's good practice to protect all header files)


//              line.h


the outline for our main loop reveals the need for functions that perform the
    following operations:
-write contents of line buffer without justification
-determine how many characters are left in line buffer
-write contents of line buffer with justification
-clear line buffer
-add word to line buffer


#ifndef LINE_H
#define LINE_H

void clear_line(void);
void add_word(const char *word);
int space_remaining(void);
void write_line(void);
void flush_line(void);

#endif


//              justify.c


#include <string.h>
#include "line.h"
#include "word.h"

#define MAX_WORD_LEN 20

int main(void)
{
    char word[MAX_WORD_LEN+2];
    int word_len;

    clear_line();
    for (;;) {
        read_word(word, MAX_WORD_LEN+1);
        word_len = strlen(word);
        if (word_len == 0) {
            flush_line();
            return 0;
        }
        if (word_len > MAX_WORD_LEN)
            word[MAX_WORD_LEN] = '*';
        if (word_len +1 > space_remaining()) {
            write_line();
            clear_line();
        }
        add_word(word);
    }
}


//              readword.c


#include <stdio.h>
#include "word.h"

int read_char(void)
{
    int ch = getchar();

    if (ch == '\n' || ch == '\t')
        return ' ';
    return ch;
}

void read_word(char *word, int len)
{
    int ch, pos = 0;

    while ((ch = read_char()) == ' ')
        ;
    while (ch != ' ' && ch != EOF) {
        if (pos < len)
            word[pos++] = ch;
        ch = read_char();
        }
    word[pos] = '\0';
}


//              line.c


#include <stdio.h>
#include <string.h>
#include "line.h"

#define MAX_LINE_LEN 60

char line[MAX_LINE_LEN+1];
int line_len = 0;
int num_words = 0;

void clear_line(void)
{
    line[0] = '\0';
    line_len = 0;
    num_words = 0;
}

void add_word(const char *word)
{
    if (num_words > 0) {
        line[line_len] = ' ';
        line[line_len+1] = '\0';
        line_len++;
    }
    strcat(line, word);
    num_words++;
}

int space_remaining(void)
{
    return MAX_LINE_LEN - line_len;
}

void write_line(void)
{
    int extra_spaces, spaces_to_insert, i, j;

    extra_spaces = MAX_LINE_LEN - line_len;
    for (i = 0; i < line_len; i++) {
        if (line[i] != ' ')
            putchar(line[i]);
        else {
            spaces_to_insert = extra_spaces / (num_words - 1);
            for (j = 1; j <= spaces_to_insert + 1; j++)
                putchar(' ');
            extra_spaces -= spaces_to_insert;
            num_words--;
        }
    }
    putchar('\n');
}

void flush_line(void)
{
    if (line_len > 0)
        puts(line);
}


//              15.3 BUILDING A MULTIPLE-FILE PROGRAM


building a large program requires the same basic steps as building a small one:
-Compiling: Each source file must be compiled separately. For each source file,
    the compiler generates a file containing object code (.o in UNIX, .obj in
    Windows)
-Linking: The linker combines the object files (along with code for library
    functions) to produce an executable file. The linker is also responsible for
    resolving external references left behind by the compiler (an external
    reference occurs when a function in one file calls a function defined in
    another file or accesses a variable defined in another file).
using GCC, we can build the justify program as so:

gcc -o justify justify.c line.c word.c


// Makefiles


instead of putting the names of all the source files on the command line, we can
    save time by writing a makefile
makefiles not only lists the files that are part of the program, but also de-
    scribes dependencies among the files. Suppose foo.c includes bar.h. We say
    that foo.c depends on bar.h, because a change to bar.h will require is to
    recompile foo.c.
UNIX makefile example:

justify: justify.o word.o line.o
    gcc -o justify justify.o word.o line.o

justify.o: justify.c word.h line.h
    gcc -c justify.c

word.o: word.c word.h
    gcc -c word.c

line.o: line.c line.h
    gcc -c line.c

the above example has four 'rules'. The first line in each rule gives a 'target'
    file, followed by the files on which it depends. On the first rule, justify
    is the target file, which is an executable file that is to be created. The
    second line is a 'command' to be executed if the target should need to be
    rebuilt because of a change to one of its dependent files. The -o option
    allows us to name the file it creates.
in the second rule, justify.o is the target that needs to be rebuilt if there is
    a change to justify.c, word.h, or line.h. The -c option tells the compiler
    to compile justify.c into an object file but not attempt to link it.
you can use the make utility to build or rebuild the program. make can determine
    which files are out of date by checking the time and date associated with
    each file.
each command in a makefile must be preceded by a tab character, not a series of
    spaces
a makefile is normally stored in a file named Makefile (or makefile). when make
    is used, it automatically checks the current directory for a file with one
    of these names.
to invoke make, use the command:

make target

where target is one of the targets listed in the makefile
to build the justify executable:

make justify

if no target is specified, it will build the target of the first rule:

make

this will build the justify executable, since it is the first rule in our make-
    file


// Errors During Linking


Common causes:
-misspellings: if a variable or function is misspelled, the linker will report
    it as missing
-missing files: if the linker can't find functions that are in file foo.c, it
    may not know about the file. Check the makefile or project file to make sure
    that foo.c is listed there.
-missing libraries: the linker may not be able to find all library functions
    used in the program. An example that occurs in UNIX programs that use the
    <math.h> header. Simply using the header in a program may not be enough;
    many versions of UNIX require the the -lm option be specified when the pro-
    gram is linked, causing the linker to search a system file that contains
    compiled versions of the <math.h> functions. Failing to use this option may
    cause "undefined reference" messages during linking.

 
// Rebuilding a Program


// Defining Macros Outside a Program


C compilers usually provide some method of specifying the value of a macro at
	the time a program is compiled. This ability makes it easy to change the
	value of a macro without editing any of the program's files. It's especially
	valuable when programs are built automatically using makefiles.
most compilers support the -D option, which allows the value of a macro to be
	specified on the command line:

gcc -DDEBUG=1 foo.c

in this example, the DEBUG macro is defined to have the value 1 in the program
	foo.c, just as if the line:

#define DEBUG 1

appeared at the beginning of foo.c
if the -D option names a macro without specifyin its value, the value is taken
	to be 1
the -U option undefines a macro as if by using #undef
we can use -U to undefine a predefined macro or one that was defined earlier in
	the command line using -D


//				NOTES


!! avoid using source (.c) files in #include directives. If you have foo.c, with
	function f, and you #include foo.c in two or more additional source files
	(like bar.c and baz.c), the linker will discover two copies of object code
	for f. !!
!! Q: I needed to call a function in the file foo.c, so I included the matching
	header file, foo.h. My program compiled, but it won't link. Why?
A: Compilation and linking are completely separate in C. Header files exist to
	provide information to the compiler, not the linker. If you want to call a
	function in foo.c, then you have to make sure that foo.c is compiled and
	that the linker is aware that it must search the object file for foo.c.
	Usually this means naming foo.c in the program's makefile or project file.

