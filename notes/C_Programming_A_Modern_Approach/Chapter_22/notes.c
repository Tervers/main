/*** CHAPTER                        22                         INPUT/OUTPUT ***/


In C89, all standard input/output functions belong to <stdio.h>, but such is not
    the case in C99, where some I/O functions are declared in the <wchar.h>
    header. The <wchar.h> functions deal with wide characters rather than ordi-
    nary characters; the good news is that most of these functions closely re-
    semble those of <stdio.h>. Functions in <stdio.h> that read or write data
    are known as "byte input/output functions;" similar functions in <wchar.h>
    are called "wide-character input/output functions."


//              22.1 STREAMS


In C, the term "stream" means any source of input or any destination for output.
	Many small programs, like the ones in previous chapters, obtain all their
	input from one stream (usually associated with the keyboard) and write all
	their output to another stream (usually associated with the screen).
Larger programs may need additional streams. These streams often represent files
	stored on various media (such as hard drives, CDs, DVDs, and flash memory),
	but they could just as easily be associated with devices that don't store
	files: network ports, printers, and the like. We'll concentrate on files,
	since they're common and easy to understand. (I may even occasionally use
	the term 'file' when I should say 'stream.') Keep in mind, however, that
	many of the functions in <stdio.h> work equally well with all streams, not
	just the ones that represent files.


// File Pointers


Accessing a stream in a C program is done through a "file pointer," which has
	type FILE * (the FILE type is declared in <stdio.h>). Certain streams are
	represented by file pointers with standard names; we can declare additional
	file pointers as needed. For example, if a program needs two streams in add-
	ition to the standard ones, it might contain the following declaration:

FILE *fp1, *fp2;

A program may declare any number of FILE * variables, although operating systems
	usually limit the number of streams that can be open at one time.


// Standard Streams and Redirection


<stdio.h> provides three standard streams. These streams are ready to use--we
    don't declare them, and we don't open or close them.

File Pointer        Stream          Default Meaning
> stdin         Standard Input          Keyboard
> stdout        Standard Output          Screen
> stderr        Standard Error           Screen

The functions that we've used in previous chapters--printf, scanf, putchar,
    getchar, puts, and gets--obtain input from stdin and sent output to stdout.
    By default, stdin represents the keyboard; stdout and stderr represent the
    screen. However, many operating systems allow these default meanings to be
    changed via a mechanism known as "redirection."
Typically, we can force a program to obtain its input from a file instead of
    from the keyboard by putting the name of the file on the command line, pre-
    ceded by the < character:

demo <in.dat

This technique, known as "input redirection," essentially makes the stdin stream
    represent a file (in.dat) instead of the keyboard. The beauty of redirection
    is that the demo program doesn't realize that it's reading from in.dat; as
    far as it knows, any data it obtains from stdin is being entered at the key-
    board.
"Output redirection" is similar. Redirecting the stdout stream is usually done
    by putting a file name on the command line, preceded by the > character:

demo >out.dat

All data written to stdout will now go into the out.dat file instead of appear-
    ing on the screen. Incidentally, we can combine output redirection with in-
    put redirection:

demo <in.dat >out.dat

The < and > characters don't have to be adjacent to file names, and the order in
    which the redirected files are listed doesn't matter, so the following exam-
    ples would work just as well:

demo < in.dat > out.dat
demo >out.dat <in.dat

One problem with output redirection is that everything! written to stdout is put
    into a file. If the program goes off the rails and begins writing error
    messages, we won't see them until we look at the file. This is where stderr
    comes in. By writing error messages to stderr instead of stdout, we can
    guarantee that those messages will appear on the screen even when stdout has
    been redirected. (Operating systems often allow stderr itself to be redi-
    rected, though.)


// Text Files versus Binary Files


<stdio.h> supports two kinds of files: text and binary. The bytes in a "text"
    "file" represent chracters, making it possible for a human to examine the
    file or edit it. The source code for a C program is stored in a text file,
    for example. In a "binary file," bytes don't necessarily represent charac-
    ters; groups of bytes might represent other types of data, such as integers
    and floating-point numbers. An executable C program is stored in a binary
    file, as you'll quickly realize if you try to look at the contents of one.
Text files have two characteristics that binary files don't possess:

> Text files are divided into lines. Each line in a text file normally ends with
    one or two special characters; the choice of characters depends on the OS.
    In Windows, the end-of-line marker is a carriage-return character ('\x0d')
    followed immediately by a line-feed character ('\x0a'). In UNIX and newer
    versions of the Macintosh OS, the end-of-line marker is a single line-feed
    character. Older versions of Mac OS use a single carriage-return character.
> Text files may contain a special 'end-of-file' marker. Some OSes allow a spe-
    cial byte to be used as a marker at the end of a text file. In Windows, the
    marker is '\x1a' (Ctrl-Z). There's no requirement that Ctrl-Z be present,
    but if it is, it marks the end of the file; any bytes after Ctrl-Z are to be
    ignored. The Ctrl-Z convention is a holdover from DOS, which in turn inher-
    ited it from CP/M, an early OS for personal computers. Most other OSes, in-
    cluding UNIX, have no special end-of-file character.

Binary files aren't divided into lines. In a binary file, there are no end-of-
    line or end-of-file markers; all bytes are treated equally.
When we write data to a file, we'll need to consider whether to store it in text
    form or in binary form. To see the difference, consider how we might store
    the number 32767 in a file. One option would be to write the number in text
    form as the characters 3, 2, 7, 6, and 7. If the character set is ASCII,
    we'd have the following five bytes:

00110011 00110010 00110111 00110110 00110111
  '3'      '2'      '7'      '6'      '7'

The other option is to store the number in binary, which would take as few as
    two bytes:

01111111 11111111

(The bytes will be reversed on systems that store data in little-endian order.)
    As this example shows, storing numbers in binary can often save quite a bit
    of space.
When we're writing a program that reads from a file or writes to a file, we need
    to take into account whether it's a text file or a binary file. A program
    that displays the contents of a file on the screen will probably assume it's
    a text file. A file copying program, on the other hand, can't assume that
    the file to be copied is a text file. If it does, binary files containing an
    end-of-file character won't be copied completely. When we can't say for sure
    whether a file is text or binary, it's safer to assume that it's binary.


//              22.2 FILE OPERATIONS


Simplicity is one of the attractions of input and output redirection; there's no
    need to open a file, close a file, or perform any other explicit file oper-
    ations. Unfortunately, redirection is too limited for many applications.
    When a program relies on redirection, it has no control over its files; it
    doesn't even know their names. Worse still, redirection doesn't help if the
    program needs to read from two files or write to two files at the same time.
When redirection isn't enough, we'll end up using the file operations that
    <stdio.h> provides.


// Opening a File


FILE *fopen(const char * restrict filename, const char * restrict mode);

Opening a file for use as a stream requires a call of the fopen function.
    fopen's first argument is a string containing the name of the file to be
    opened. (A 'file name' may include information about the file's location,
    such as a drive specifier or path.) The second argument is a 'mode string'
    that specifies what operations we intend to perform on the file. The string
    "r", for instance, indicates that data will be read from the file, but none
    will be written to it.
Note that restrict appears twice in the prototype for the fopen function. re-
    strict, which is a C99 keyword, indicates that filename and mode should
    point to strings that don't share memory locations. The C89 prototype for
    fopen doesn't contain restrict but is otherwise identical. restrict has no
    effect on the behavior of fopen, so it can usually just be ignored. In this
    and subsequent chapters, I'll italicize restrict as a reminder that it's a
    C99 feature.
! Windows programmers: Be careful when the file name in a call of fopen includes
    the \ character, since C treats \ as the beginning of an escape sequence.
    The call

fopen("c:\project\test1.dat", "r")

    will fail, because the compiler treats \t as a character escape. (\p isn't a    valid character escape, but it looks like one. The C standard states that
    its meaning is undefined.) There are two ways to avoid the problem. One is
    to use \\ instead of \:

fopen("c:\\project\\test1.dat", "r")

    The other technique is even easier--just use the / character instead of \:

fopen("c:/project/test1.dat", "r")

    Windows will happily accept / instead of \ as the directory separator. !

fopen returns a file pointer that the program can (and usually will) save in a 
    variable and use later whenever it needs to perform an operation on the
    file. Here's a typical call of fopen, where fp is a variable of type FILE *:

fp = fopen("in.dat", "r");  // opens in.dat for reading

When the program calls an input function to read from in.dat later, it will sup-
    ply fp as an argument.
When it can't open a file, fopen returns a null pointer. Perhaps the file
    doesn't exist, or it's in the wrong place, or we don't have permission to
    open it.
! Never assume that a file can be opened; always test the return value of fopen
    to make sure it's not a null pointer. !


// Modes


"r"     Open for reading
"w"     Open for writing (file need not exist)
"a"     Open for appending (file need not exist)
"r+"    Open for reading and writing, starting at beginning
"w+"    Open for reading and writing (truncate if file exists)
"a+"    Open for reading and writing (append if file exists)

When we use fopen to open a binary file, we'll need to include the letter b in
    the mode string. We see the <stdio.h> distinguishes between writing data and
    appending data. When data is written to a file, it normally overwrites what
    was previously there. When a file is opened for appending, however, data
    written to the file is added at the end, thus preserving the file's original
    contents.
Special rules apply when a file is opened for both reading and writing (+ mode).
    We can't switch from reading to writing without first calling a file-posi-
    tioning function unless the reading operation encountered the end of the
    file. Also, we can't switch from writing to reading without either calling
    fflush (covered later in this section) or calling a file-positioning func-
    tion.

"rb"            Open for reading
"wb"            Open for writing (file need not exist)
"ab"            Open for appending (file need not exist)
"r+b" "rb+"     Open for reading and writing, starting at beginning
"w+b" "wb+"     Open for reading and writing (truncate if file exists)
"a+b" "ab+"     Open for reading and writing (append if file exists)


// Closing a File


int fclose(FILE *stream);

The fclose function allows a program to close a file that it's no longer using.
    The argument to fclose must be a file pointer obtained from a call of fopen
    or freopen (discussed later in this section). fclose returns zero if the
    file was closed successfully; otherwise, it returns the error code EOF.
To show how fopen and fclose are used in practice, here's the outline of a pro-
    gram that opens the file example.dat for reading, checks that it was opened
    successfully, then closes it before terminating:

#include <stdio.h>
#include <stdlib.h>

#define FILE_NAME "example.dat"

int main(void)
{
    FILE *fp;

    fp = fopen(FILE_NAME, "r");
    if (fp == NULL) {
        printf("Can't open %s\n", FILE_NAME);
        exit(EXIT_FAILURE);
    }
    ...
    fclose(fp);
    return 0;
}

Of course, C programmers being the way they are, it's not unusual to see the
    call of fopen combined with the declaration of fp:

FILE *fp = fopen(FILE_NAME, "r");

or the test against NULL:

if ((fp = fopen(FILE_NAME, "r")) == NULL) ...


// Attaching a File to an Open Stream


FILE *freopen(const char * restrict filename, const char * restrict mode,
                    FILE * restrict stream);

freopen attaches a different file to a stream that's already open. The most com-
    mon use of freopen is to associate a file with one of the standard streams
    (stdin, stdout, or stderr). To cause a program to begin writing to the file
    foo, for instance, we could use the following call of freopen:

if (freopen("foo", "w", stdout) == NULL) {
    // error; foo can't be opened
}

After closing any file previously associated with stdout (by command-line redi-
    rection or a previous call of freopen), freopen will open foo and associate
    it with stdout.
freopen's normal return value is its third argument (a file pointer). If it
    can't open the new file, freopen returns a null pointer. (freopen ignores
    the error if the old file can't be closed.)
In C99, if filename is a null pointer, freopen attempts to change the stream's
    mode to that specified by the mode parameter. Implementations aren't requir-
    ed to support this feature, however; if they do, they may place restrictions
    on which mode changes are permitted.


// Obtaining File Names from the Command Line


When we're writing a program that will need to open a file, one problem soon be-
    comes apparent: how do we supply the file name to the program? Building file
    names into the program itself doesn't provide much flexibility, and prompt-
    ing the user to enter file names can be awkward. Often, the best solution is
    to have the program obtain file names from the command line. When we execute
    a program named demo, for example, we might supply it with file names by
    putting them on the command line:

demo names.dat dates.dat

We can access command-line arguments by defining main as a function with two
    parameters:

int main(int argc, char *argv[])
{
    ...
}

argc is the number of command-line arguments; argv is an array of pointers to
    the argument strings. argv[0] points to the program name, argv[1] through
    argv[argc-1] point to the remaining arguments, and argv[argc] is a null
    pointer. In the example above, argc is 3, argv[0] points to a string con-
    taining the program name, argv[1] points to the string "names.dat", and
    argv[2] points to the string "dates.dat".


// PROGRAM: Checking Whether a File Can Be Opened


The following program determines if a file exists and can be opened for reading.
    When the program is run, the user will give it a file name to check:

canopen file

The program will then print either file can be opened or file can't be opened.
    If the user enters the wrong number of arguments on the command line, the
    program will print the message use: canopen filename to remind the user that
    canopen requires a single file name.


//              canopen.c


#include <stdio.h>
#include <stdlib.>

int main(int argc, char *argv[])
{
    FILE *fp;

    if (argc != 2) {
        printf("usage: canopen filename\n");
        exit(EXIT_FAILURE);
    }

    if ((fp = fopen(argv[1], "r")) == NULL) {
        printf("%s can't be opened\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    printf("%s can be opened\n", argv[1]);
    fclose(fp);
    return 0;
}

-----------------------------------------------------------
Note that we can use redirection to discard the output of caopen and simply test
    the status value it returns.


// Temporary Files


FILE *tmpfile(void);
char *tmpnam(char *s);

Real-world programs often need to create temporary files--files that exist only
    as long as the program is running. C compilers, for instance, often create
    temporary files. A compiler might first translate a C program to some inter-
    mediate form, which it stores in a file. The compiler would then read the
    file later as it translates the program to object code. Once the program is
    completely compiled, there's no need to preserve the file containing the
    program's intermediate form.
tmpfile creates a temporary file (opened in "wb+" mode) that will exist until
    it's closed or the program ends. A call of tmpfile returns a file pointer
    that can be used to access the file later:

FILE *tempptr;
...
tempptr = tmpfile();    // creates a temporary file

If it fails to create a file, tmpfile returns a null pointer.
Although tmpfile is easy to use, it has a couple of drawbacks: (1) we don't know
    the name of the file that tmpfile creates, and (2) we can't decide later to
    make the file permanent. If these restrictions turn out to be a problem, the
    alternative is to create a temporary file using fopen. Of course, we don't
    want this file to have the same name as a previously existing file, so we
    need some way to generate new file names; that's where the tmpnam function
    comes in.
tmpnam generates a name for a temporary file. If its argument is a null pointer,
    tmpnam stores the file name in a static variable and returns a pointer to
    it:

char *filename;
...
filename = tmpnam(NULL);    // creates a temporary file name

Otherwise, tmpnam copies the file name into a character array provided by the
    programmer:

char filename[L_tmpnam];
...
tmpname(filename);      //creates a temporary file name

In the latter case, tmpnam also returns a pointer to the first character of this
    array. L_tmpnam is a macro in <stdio.h> that specifies how long to make a
    character array that will hold a temporary file name.
! Be sure that tmpnam's argument points to an array of at least L_tmpnam charac-
    ters. Also, be careful not to call tmpnam too often; the TMP_MAX macro spec-
    ifies the maximum number of temporary file names that can potentially be
    generated by tmpnam during the execution of a progra. If it fails to gener-
    ate a file name, tmpnam returns a null pointer. !


// File Buffering


Transferring data to or from a disk drive is a relatively slow operation. As a
    result, it isn't feasible for a program to access a disk file directly each
    time it wants to read or write a byte. The secret to achieving acceptable
    performance is "buffering:" daya written to a stream is actually stored in a
    buffer area in memory; when it's full (or the stream is closed), the buffer
    is 'flushed' (written to the actual output devices). Input streams can be
    buffered in a smilar way: the buffer contains data from the input device:
    input is read from this buffer instead of the device itself. Buffering can
    result in enormous gains in efficiency, since reading a byte from a buffer
    or storing a byte in a buffer takes hardly any time at all. Of course, it
    takes time to transfer the buffer contents to or from disk, but one large
    'block move' is much faster than many tiny byte moves.
The functions in <stdio.h> perform buffering automatically when it seems advan-
    tageous. The buffering takes place behind the scenes, and we usually don't
    worry about it. On rare occasions, though, we may need to take a more active
    role. If so, we can use the functions fflush, setbuf, and setvbuf.
When a program writes output to a file, the data normally goes into a buffer
    first. The buffer is flushed automatically when it's full or the file is
    closed. By calling fflush, however, a program can flush a file's buffer as
    often as it wishes. The call

fflush(fp);

flushes the buffer for the file associated with fp. The call

fflush(NULL);

flushes all! output streams. fflush returns zero if it's successful and EOF if
    an error occurs.
setvbuf allows us to change the way a stream is buffered and to control the size
    and location of the buffer. The function's third argument, which specifies
    the kind of buffering desired, should be one of the following macros:

> _IOFBF (full buffering). Data is read from the stream when the buffer is empty
    or written to the stream when it's full.
> _IOLBF (line buffering). Data is read from the stream or written to the stream
    one line at a time.
> _IONBF (no buffering). Data is read from the stream or written to the stream
    directly, without a buffer.

(All three macros are defined in <stdio.h>.) Full buffering is the default for
    streams that aren't connected to interactive devices.
setvbuf's second argument (if it's not a null pointer) is the address of the de-
    sired buffer. The buffer might have static storage duration, automatic stor-
    age duration, or even be allocated dynamically. Making the buffer automatic
    allows its space to be reclaimed automatically at block exit; allocating it
    dynamically enables us to free the buffer when it's no longer needed.
    setvbuf's last argument is the number of bytes in the buffer. A larger buf-
    fer may give better performance; a smaller buffer saves space.
For example, the following call of setvbuf changes the buffering of stream to
    full buffering, using the N bytes in the buffer array as the buffer:

char buffer[N];
...
setvbuf(stream, buffer, _IOFBF, N);

! setvbuf must be called after stream is opened but before any other operations
    are performed on it. !
It's also legal to call setvbuf with a null pointer as the second argument,
    which requests that setvbuf create a buffer with the specified size. setvbuf
    returns zero if it's successful. It returns a nonzero value if the mode
    argument is invalid or the request can't be honored.
setbuf is an older function that assumes default values for the buffering mode
    and buffer size. If buf is a null pointer, the call setbuf(stream, buf) is
    equivalent to

(void) setvbuf(stream, NULL, _IONBF, 0);

Otherwise, it's equivalent to

(void) setvbuf(strea, buf, _IOFBF, BUFSIZ);

where BUFSIZ is a macro defined in <stdio.h>. The setbuf function is considered
    obsolete; it's not recommended for use in new programs.
! When using setvbuf or setbuf, be sure to close the stream before its buffer is
    deallocated. In particular, if the buffer is local to a function and has
    automatic storage duration, be sure to close the stream before the function
    returns. !


// Miscellaneous File Operations


int remove(const char *filename);
int rename(const char *old, const char *new);

The functions remove and rename allow a program to perform basic file management
    operations. Unlike most other functions in theis section, remove and rename
    work with file names! instead of file pointers!. Both functions return zero
    if they succeed and a nonzero value if they fail.
remove deletes a file:

remove("foo");

If a program uses fopen (instead of tmpfile) to create a temporary file, it can
    use remove to delete the file before the program terminates. Be sure that
    the file to be removed has been closed; the effect of removing a file that's
    currently open is implementation-defined.
rename changes the name of a file:

rename("foo", "bar");   // renames foo to bar

rename is handy for renaming a temporary file created using fopen if a program
    should decide to make it permanent. If a file with the new name already ex-
    ists, the effect is implementation-defined.
! If the file to be renamed is open, be sure to close it before calling rename;
    the function may fail if asked to rename an open file. !


//              22.3 FORMATTED I/O


int fprintf(FILE * restrict stream, const char * restrict format, ...);
int printf(const char * restrict format, ...);

The fprintf and printf functions write a variable number of data items to an
    output stream, using a format string to control the appearance of the out-
    put. The prototypes for both functions end with the ... symbol (an
    "ellipsis"), which indicates a variable number of additional arguments. Both
    functions return the number of character written; a negative return value
    indicates that an error occurred.
The only difference between printf and fprintf is that printf always writes to
    stdout, whereas fprintf writes to the stream indicated by its first argu-
    ment:

printf("Total: %d\n", total);
fprintf(fp, "Total: %d\n", total);

A call of printf is equivalent to a call of fprintf with stdout as the first ar-
    gument.
Don't think of fprintf as merely a function that writes data to disk files,
    though. fprintf works fine with any output stream. In fact, one of the most
    common uses of fprintf--writing error messages to stderr--has nothing to do
    with disk files. Here's what such a call might look like:

fprintf(stderr, "Error: data file can't be opened.\n");

Writing the message to stderr guarantees that it will appear on the screen even
    if the user redirects stdout.
There are two other functions that are fairly obscure; vfprintf and vprintf.
    Both rely on the va_list type, which is declared in <stdarg.h>, so they're
    discussed with that header.


// ...printf Conversion Specifications


Both printf and fprintf require a format string containing ordinary characters
    and/or conversion specifications. Ordinary characters are printed as is;
    conversion specifications describe how the remaining arguments are to be
    converted to character form for display.
A ...printf conversion specification consists of the % character, followed by as
    many as five distinct items:

%#012.5Lg

%
#0 flags
12 minimum field width
.5 precision
L length modifier
g conversion specifier

A detailed description of these items, which must appear in the order shown:

> Flags: (optional, more than one permitted)
    - Left-justify within field. (The default is right justification.)
    + Numbers produced by signed conversions always begin with + or -. (Normal-
        ly, only negative numbers are preceded by a sign.)
    'space' Nonnegative numbers produced by signed conversions are preceded by a
        space. (The + flag overrides the space flag.)
    # Octal numbers begin with 0, nonzero hexadecimal numbers with 0x or 0X.
        Floating-point numbers always have a decimal point. Trailing zeros
        aren't removed from numbers printed with the g or G conversions.
    0 Numbers are padded with leading zeros up the field width. The 0 flag is
        ignored if the conversion is d, i, o, u, x, or X and a precision is spe-
        cified. (The - flag oversides the 0 flag.)

> Minimum field width (optional). An item that's too small to occupy this number
    of characters will be padded. (By default, spaces are added to the left of
    the item, thus right-justifying it within the field.) An item that's too
    large for the field width will still be displayed in its entirety. The field
    width is obtained from the next argument. If this argument is negative, it's
    treated as a positive number preceded by a - flag.

> Precision (optional). the meaning of the precision depends on the conversion:

    d, i, o, u, x, X: minimum number of digits
                      (leading zeros are added if the number has fewer digits)
    a, A, e, E, f, F: number of digits after the decimal point
    g, G: number of significant digits
    s: maximum number of bytes
    
    The precision is a period (.) followed by an integer or the character *. If
    * is present, the precision is obtained from the next argument. (If this ar-
    gument is negative, the effect is the same as not specifying a precision.)
    If only the period is present, the precision is zero.

> Length modifier (optional). The presence of a length modifier indicates that
    the item to be displayed has a type that's longer or shorter than is normal
    for a particular conversion specification. (For example, %d normally refers
    to an int value; %hd is used to display a short int and %ld is used to dis-
    play a long int.)

Length Modifier     Conversion Specifiers               Meaning
hh                d, i, o, u, x, X        signed char, unsigned char
                  n                       signed char *
h                 d, i, o, u, x, X        short int, unsigned short int
                  n                       short int *
l                 d, i, o, u, x, X        long int, unsigned long int
                  n                       long int *
                  c                       wint_t
                  s                       wchar_t *
                  a, A, e, E, f, F, g, G  no effect
ll                d, i, o, u, x, X        long long int, unsigned long long int
                  n                       long long int *
j                 d, i, o, u, x, X        intmax_t, uintmax_t 
                  n                       intmax_t *
z                 d, i, o, u, x, X        size_t
                  n                       size_t *
t                 d, i, o, u, x, X        ptrdiff_t
                  n                       ptrdiff_t *
L                 a, A, e, E, f, F, g, G  long double

> Conversion specifier. The conversion specifier must be one of the characters
    listed in the table below. Notice that f, F, e, E, g, G, a, and A are all
    designed to write double values. However, they work fine with float values
    as well; thanks to the default argument promotions, float arguments are con-
    verted automatically to double when passed to a function with a variable
    number of arguments. Similarly, a character pass to ...printf is converted
    automatically to int, so the c conversion works properly.
    ! Be careful to follow the rules described here; the effect of using an in-
    valid conversion specification is undefined. !

Conversion
Specifier                           Meaning
  d, i      Converts an int value to decimal form
o, u, x, X  Converts an unsigned int vale to base 8 (o), base 10 (u), or base 16
            (x, X). x displays the hexadecimal digits a-f in lower case; X dis-
            plays them in upper case.


//              22.4 CHARACTER I/O


You'll notice that the functions in this section treat characters as values of
    type int, not char. One reason is that input functions indicate an end-of-
    file (or error) condition by returning EOF, which is a negative integer con-
    stant.


// Output Functions


int fputc(int c, FILE *stream);
int putc(int c, FILE *stream);
int putchar(int c);

putchar writes one character to the stdout stream:

putchar(ch);

fputc and putc are more general versions of putchar that write a character to an
    arbitrary stream:

fputc(ch, fp);
putc(ch, fp);       // both write ch to fp

Although put and fputc do the same thing, putc is usually implemented as a macro
    (as well as a function), while fputc is implemented only as a function.
    putchar itself is usually a macro defined in the following way:

#define putchar(c) putc((c), stdout)

It may seem odd that the library provides both putc and fputc. But, as we saw in
    14.3, macros have several potential problems. The C standard allows the putc
    macro to evaluate the stream argument more than once, which fputc isn't per-
    mitted to do. Although programmers usually prefer putc, which gives a faster
    program, fputc is available as an alternative.
If a write error occurs, all three functions set the rror indicator for the
    stream and return EOF; otherwise, they return the character that was writ-
    ten.


// Input Functions


int fgetc(FILE *stream);
int getc(FILE *stream);
int getchar(void);
int ungetc(int c, FILE *stream);

getchar reads a character from the stdin stream:

ch = getchar();

fgetc and getc read a character from an arbitrary stream:

ch = fgetc(fp);
ch = getc(fp);      // both read a character from fp

All three functions treat the character as an unsigned char value (which is then
    converted to int type before it's returned). As a result, they never return
    a negative value other than EOF.
The relationship between getc and fgetc is similar to that between putc and
    fputc. getc is usually implemented as a macro (as well as a function), while
    fgetc is implemented only as a function. getchar is normally a macro as
    well:

#define getchar () getc(stdin)

For reading characters from a file, programmers usually prefer getc over fgetc.
    Since getc is normally available in macro form, it tends to be faster. fgetc
    can be used as a backup if getc isn't appropriate. (The standard allows the
    getc macro to evaluate its argument more than once, which may be a problem.)
One of the most common uses of fgetc, getc, and getchar is to read characters
    from a file, one by one, until end-of-file occurs. It's customary to use the
    following while loop for that purpose:

while ((ch = getc(fp)) != EOF) {
    ...
}

    After reading a character from the file associated with fp and storing it in
    the variable ch (which must be of type int), the while test compared ch with
    EOF. If ch isn't equal to EOF, we're not at the end of the file yet, so the
    body of the loop is executed. If ch is equal to EOF, the loop terminates.
! Always store the return value of fgetc, getc, or getchar in an int variable,
    not a char variable. Testing a char variable against EOF may give the wrong
    result. !
There's one other character input function, ungetc, which 'pushes back' a char-
    acter read from a stream and clears the stream's end-of-file indicator. This
    capability can be handy if we need a 'lookahead' character during input. For
    instance, to read a series of digits, stopping at the first nondigit, we
    could write

while (isdigit(ch = getc(fp))) {
    ...
}
ungetc(ch, fp);     // pushes back last chracter read

The number of characters that can be push back by consecutive calls of ungetc--
    with no intervening read operations-- depends on the implementation and the
    type of stream invlolved; only the first call is guaranteed to succeed.
    Calling a file-positioning function (fseek, fsetpos, or rewind) causes the
    pushed-back characters to be lost.
ungetc returns the character it was asked to push back. However, it returns EOF
    if an attempt is made to push back EOF or to push back more characters than
    the implementation allows.


// PROGRAM: Copying a File


The following programmakes a copy of a file. The names of the original file and
    the new file will be specified on the command line when the program is exe-
    cuted. For example, to copy the file f1.c to f2.c, we'd use the command

fcopy f1.c f2.c

fcopy will issue an error message if there aren't exactly two file names on the
    command line or if either file can't be opened.


//              fcopy.c


#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *source_fp, *dest_fp;
    int ch;

    if (argc != 3) {
        fprintf(stderr, "usage: fcopy source dest\n");
        exit(EXIT_FAILURE);
    }

    if ((source_fp = fopen(argv[1], "rb")) == NULL) {
        fprintf(stderr, "Can't open %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    if ((dest_fp = fopen(argv[2], "wb")) == NULL) {
        fprintf(stderr, "Can't open %s\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    while ((ch = getc(source_fp)) != EOF)
        putc(ch, dest_fp);

    fclose(source_fp);
    fclose(dest_fp);
    return 0;
}

-----------------------------------------------------------
Using "rb" and "wb" as the file modes enables fcopy to copy both text and binary
    files. If we used "r" and "w" instead, the program wouldn't necessarily be
    able to copy binary files.


//              22.5 LINE I/O


We'll now turn to library functions that read and write lines. These functions
    are used mostly with text streams, although it's legal to use them with bi-
    nary streams as well.


// Output Functions


int fputs(const char * restrict s, FILE * restrict stream);
int puts(const char *s);

We ecnountered the puts functions in 13.3; it writes a string of characters to
    stdout:

puts("Hi, There!");     // writes to stdout

After it writes the characters in the string, puts always adds a new-line char-
    acter.
fputs is a more general version of puts. Its second argument indicates the
    stream to which the output should be written:

fputs("Hi, there!", fp);    // writes to fp

Unlike puts, the fputs function doesn't write a new-line character unless one is
    present in the string.
Both functions return EOF if a write error occurs; otherwise, they return a non-
    negative number.


// Input Functions


char *fgets(char * restrict s, int n, FILE * restrict stream);
char *gets(char *s);

The gets function, which we first saw in 13.3, reads a line of input from stdin:

gets(str);  // reads a line from stdin

gets reads characters one by one, storing them in the array pointed to by str,
     until it reads a new-line character (which it discards).
fgets is a more general version of gets that can read from any stream. fgets is
    also safer than gets, since it limits the number of characters that it will
    store. Here's how we might use fgets, assuming that str is the name of a
    character array:

fgets(str, sizeof(str), fp);    // reads a line from fp

    This call will cause fgets to read characters until it reaches the first
    new-line character or sizeof(str) - 1 characters have been read, whichever
    happens first. If it reads the new-line character, fgets stores it along
    with the other characters. (Thus, gets never! stores the new-line character,
    but fgets sometimes! does.)
Both gets and fgets return a null pointer if a read error occurs or they reach
    the end of the input stream before storing any characters. (As usual, we can
    call feof or ferror to determine which situation occurred.) Otherwise, both
    return their first arrgument, which points to the array in which the input
    was store. As you'd expect, both functions store a null character at the end
    of the string.
Using fgets instead of gets is suggested in most situations. With gets, there's
    always the possibility of stepping outside the bounds of the receiving
    array, so it's safe to use only when the string being read is guaranteed! to
    fit into the array. When there's no guarantee (and there usually isn't),
    it's much safer to use fgets. Note that fgets will read from the standard
    input if passed stdin as its third argument:

fgets(str, sizeof(str), stdin);


//              22.6 BLOCK I/O


size_t fread(void * restrict ptr, size_t size,
             size_t nmemb, FILE * restrict stream);
size_t fwrite(const void * restrict ptr, size_t size,
              size_t nmemb, FILE * restrict stream);

The fread and fwrite functions allow a program to read and write large blocks of
    data in a single step. fread and fwrite are used primarily with binary
    streams, although--with care--it's possible to use them with text streams as
    well.
fwrite is designed to copy an array from memory to a stream. The first argument
    in a call of fwrite is the array's address, the second argument is the size
    of each array element (in bytes), and the third argument is the number of
    elements to write. The fourth argument is a file pointer, indicating where
    the data should be written. To write the entire contents of the array a, for
    instance, we could use the following call of fwrite:

fwrite(a, sizeof(a[0]), sizeof(a) / sizeof(a[0], fp);

    There's no rule that we have to write the entire array; we could just as
    easily write any portion of it. fwrite returns the number of elements (not!
    bytes) actually written. This number will be less than the third argument if
    a write error occurs.
fread will read the elements of an array from a stream. fread's arguments are
    similar to fwrite's: the array's address, the size of each element (in
    bytes), the number of elements to read, and a file pointer. To read the con-
    tents of a file into the array a, we might use the following call of fread:

n = fread(a, sizeof(a[0]), sizeof(a) / sizeof(a[0]), fp);

    It's important to check fread's return value, which indicates the actual
    number of elements (not! bytes) read. This number should equal the third
    argument unless the end of the input file was reached or a read error
    occurred. The feof and ferror functions can be used to determine the reason
    for any shortage.
! Be careful not to confuse fread's second and third arguments. Consider the
    following call of fread:

fread(a, 1, 100, fp)

We're asking fread to read 100 one-byte elements, so it will return a value be-
    tween 0 and 100. The following call asks fread to read one block of 100
    bytes:

fread(a, 100, 1, fp)

fread's return value in this case will be either 0 or 1. !
fwrite is convenient for a program that needs to store data in a file before
    terminating. Later, the program (or another program, for that matter) can
    use fread to read the data back into memory. Despite appearances, the data
    doesn't need to be in array form; fread and fwrite work just as well with
    variables of all kinds. Structures, in particular, can be read by fread or
    written by fwrite. To write a structure variable s to a file, for instance,
    we could use the following call of fwrite:

fwrite(&s, sizeof(s), 1, fp);

! Be careful when using fwrite to write out structures that contain pointer
    values; these values aren't guaranteed to be valid when read back in. !


//              22.7 FILE POSITIONING


int fgetpos(FILE * restrict stream, fpos_t * restrict pos);
int fseek(FILE *stream, long int offset, int whence);
int fsetpos(FILE *stream, const fpos_t *pos);
long int ftell(FILE *stream);
void rewind(FILE *stream);

Every stream has an associated "file position." When a file is opened, the file
    position is set at the beginning of the file. (If the file is opened in
    'append' mode, however, the initial file position may be at the beginning or
    end of the file, depending on implementation.) Then, when a read or write
    operation is performed, the file position advances automatically, allowing
    us to move through the file in a sequential manner.
Although sequential access is fine for many applications, some programs need the
    ability to jump around within a file, accessing some data here and other
    data there. If a file contains a series of records, for example, we might
    want to jump directly to a particular record and read it or update it.
    <stdio.h> supports this form of access by providing five functions that al-
    low a program to determine the current file position or to change it.
The fseek function changes the file position associated with the first argument
    (a file pointer). The third argument specifies whether the new position is
    to be calculated with respect to the beginning of the file, the current pos-
    ition, or the end of the file. <stdio.h> defines three macros from this pur-
    pose:

SEEK_SET    Beginning of file
SEEK_CUR    Current file position
SEEK_END    End of file

The second argument is a (possibly negative) byte count. To move to the beginn-
    ing of a file, for example, the seek direction would be SEEK_SET and the
    byute count would be zero:

fseek(fp, 0L, SEEK_SET);    // moves to the beginning of a file

    To move to the end of a file, the seek direction would be SEEK_END:

fseek(fp, 0L, SEEK_END);    // moves to end of file

    To move back 10 bytes, the seek direction would be SEEK_CUR and the byte
    count would be -10:

fseek(fp, -10L, SEEK_CUR);  // moves back 10 bytes

    Note that the byte count has type long int, so I've used 0L and -10L as arg-
    uments. (0 and -10 would also work, of course, since arguments are converted
    to the proper type automatically.)
Normally, fseek returns zero. If an error occurs (the requested position doesn't
    exist, for example), fseek returns a nonzero value.
The file-positioning functions are best used with binary streams, by the way. C
    doesn't prohibit programs from using them with text streams, but care is re-
    quired because of operating system differences. fseek in particular is sen-
    sitive to whether a stream is text or binary. For text streams, either (1)
    offset (fseek's second argument) must be zero or (2) whence (its third argu-
    ment) must be SEEK_SET and offset a value obtained by a previous call of
    ftell. (In other words, we can only use fseek to move to the beginning or
    end of a text stream or to return to a place that was visited previously.)
    For binary streams, fseek isn't required to support calls in which whence is
    SEEK_END.

