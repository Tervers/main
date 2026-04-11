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



