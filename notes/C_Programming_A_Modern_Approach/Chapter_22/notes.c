/*** CHAPTER                        22                         INPUT/OUTPUT ***/


In C89, all standard input/output functions belong to <stdio.h>, but such is not
    the case in C99, where some I/O functions are declared in the <wchar.h>
    header. The <wchar.h> functions deal with wide characters rather than ordi-
    nary characters; the good news is that most of these functions closely re-
    semble those of <stdio.h>. Functions in <stdio.h> that read or write data
    are known as "byte input/output functions;" similar functions in <wchar.h>
    are called "wide-character input/output functions."


//              22.1 STREAMS



