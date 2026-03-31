/*** CHAPTER                  17                  ADVANCED USES OF POINTERS ***/


//              17.1 DYNAMIC STORAGE ALLOCATION


C's data structures are normally fixed in size. Fixed-size data structures can
    be a problem, since we're forced to chooose their sizes when writing a
    program; we can't change the sizes without modifying the program and com-
    piling it again.
The solution to this problem is dynamic storage allocation: the ability to allo-
    cate storage during program execution. Using dynamic storage allocation, we
    can design data structures that grow and shrink as needed.
Dynamic storage allocation is used most often for strings, arrays, and
    structures.


// Memory Allocation Functions


To allocate storage dynamically, we'll need to call one of the three memory
    allocation functions declared in <stdlib.h>:

> malloc: Allocates a block of memory but doesn't initialize it.
> calloc: Allocates a block of memory and clears it.
> realloc: Resizes a previously allocated block of memory.

Of the three, malloc is the most used.
When we call a memory allocation function to request a block of memory, the
    function has no idea what type of data we're planning to store in the block,
    so it can't return a pointer to an ordinary type such as int or char. In-
    stead, the function returns a value of type void *. a void * value is a
    'generic' pointer; essentially, just a memory address.


// Null Pointers


When a memory allocation function is called, there's always a possibility that
    it won't be able to locate a block of memory large enough to satisfy our
    request. If that should happen, the function will return a "null pointer."
    A null pointer is a "pointer to nothing"; a special value that can be dis-
    tinguished from all valid pointers. !After we've stored the function's
    return value in a pointer variable, we must test to see if it's a null
    pointer.!
The null pointer is represented by a macro named NULL, so we can test malloc's
    return value in the following way:

p = malloc(10000);
if (p == NULL) {
    /* allocation failed; take appropriate action */
}

You can combine the call of malloc with the NULL test:

if ((p = malloc(10000)) == NULL) {
    /* allocation failed; take appropriate action */
}

The NULL macro is defined in six headers: <locale.h>, <stddef.h>, <stdio.h>,
    <stdlib.h>, <string.h>, and <time.h>. In C99, <wchar.h> also defines NULL.
Pointers test true or false in the same way as numbers. All non-null pointers
    test true; only null pointers are false. Instead of writing

if (p == NULL) ...

we could write

if (!p) ..

and instead of writing

if (p != NULL) ...

we could write

if (p) ...


//              17.2 DYNAMICALLY ALLOCATED STRINGS


// Using malloc to Allocate Memory for a String


The malloc function has the following prototype:

void *malloc(size_t size);

malloc allocates a block of size bytes and returns a pointer to it. size has
    type size_t, which is an unsigned integer type defined in the C library.
Using malloc to allocate memory for a string is easy, because C guarantees that
    a char value requires exactly one byte of storage (sizeof(char) is 1). To
    allocate space for a string of n characters, we'd write

p = malloc(n + 1);

    where p is a char * variable. n + 1 allows room for the null character. The
    generic pointer that malloc returns will be converted to char * when the
    assignment is performed. In general, we can assign a void * value to a var-
    iable of any pointer type and vice versa. Nevertheless, some programmers
    prefer to cast malloc's return value:

p = (char *) malloc(n + 1);

Memory allocation using malloc isn't cleared or initialized in any way, so p
    will point to an uninitialized array of n + 1 characters.
Calling strcpy is one way to initialize this array:

strcpy(p, "abc");

The first four characters of the array will now be a, b, c, and \0.


// Using Dynamic Storage Allocation in String Functions


Dynamic storage allocation makes it possible to write functions that return a
    pointer to a 'new' string; a string that didn't exist before the function
    was called. We can use this to write a function that concatenates two
    strings without changing either one.
The function will measure the lengths of the two strings to be concatenated,
    then call malloc to allocate just the right amount of space for the result.
    The function then copies the first string into the new space and calls
    strcat to concatenate the second string:

char *concat(const char *s1, const char *s2)
{
    char *result;

    result = malloc(strlen(s1) + strlen(s2) + 1);
    if (result == NULL) {
        printf("Error: malloc failed in concat\n");
        exit(EXIT_FAILURE);
    }
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

Printing an error message and terminating a program isn't always the right
    action to take. Some programs need to recover from memory allocation
    failures and continue running.
Here's how the concat function might be called:

p = concat("abc", "def");

After the call, p will point to the string "abcdef", which is stored in a dynam-
    ically allocated array. The array is seven characters long, including the
    null character at the end.
! Functions that dynamically allocate storage must be used with care. When the
    string that concat returns is no longer needed, we'll cant to call the free
    function to release the space that the string occupies. If we don't, the
    program may eventually run out of memory.


// Arrays of Dynamically Allocated Strings


In 13.7, we found that storing strings as rows in a two-dimensional array of
    characters can waste space, so we tried setting up an array of pointers to
    string literals. The techniques of 13.7 work just as well if the elements of
    an array are pointers to dynamically allocated strings. To illustrate this
    point, we'll rewrite remind.c, which prints a one-month list of daily re-
    minders.


// PROGRAM: Printing a One-Month Reminder List (Revisited)


In this new program (remind2.c), the array will be one-dimensional; its elements
    will be pointers to dynamically allocated strings. Switching to dynamically
    allocated strings will use space more efficiently. We will no longer need to
    call strcpy as we'll merely move pointers to strings.


//              remind2.c


#include <stdio.h>
#include <stdlib.h>     //new
#include <string.h>

#define MAX_REMIND 50
#define MSG_LEN 60

int read_line(char str[], int n);

int main(void)
{
    char *reminders[MAX_REMIND];    //new
    char day_str[3], msg_str[MSG_LEN+1];
    int day, i, j, num_remind = 0;

    for (;;) {
        if (num_remind == MAX_REMIND) {
            printf("-- No space left --\n");
            break;
        }

        printf("Enter day and reminder: ");
        scanf("%2d", &day);
        if (day == 0)
            break;

        printf("Enter day and reminder: ");
        scanf("%2d", &day);
        if (day == 0)
            break;
        sprintf(day_str, "%2d", day);
        read_line(msg_str, MSG_LEN);

        for (i = 0; i < num_remind; i++)
            if (strcmp(day_str, reminders[i]) < 0)
                break;
        for (j = num_remind; j > i; j--)
            reminders[j] = reminders[j-1];      //new

        reminders[i] = malloc(2 + strlen(msg_str) + 1);     //new
        if (reminders[i] == NULL) {     //new
            printf("-- No space left --\n");    //new
            break;      //new
        }       //new

        strcpy(reminders[i], day_str);
        strcat(reminders[i], msg_str);

        num_remind++;
    }

    printf("\nDay Reminders\n");
    for (i = 0; i < num_remind; i++)
        printf(" %s\n", reminders[i]);

    return 0;
}

int read_line(char str[], int n)
{
    int ch, i = 0;

    while ((ch = getchar()) != '\n')
        if (i < n)
            str[i++] = ch;
    str[i] = '\0';
    return i;
}


//              17.3 DYNAMICALLY ALLOCATED ARRAYS



