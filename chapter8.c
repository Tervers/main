/*** CHAPTER                            8                           ARRAYS ***/

the only variables we have seen so far are "scalar", meaning they hold a single
    data item
C also supports "aggregate" variables, which can hold collections of values
there are two types of C aggregates: arrays and structures
arrays can be both one-dimensional and multi-dimensional
there are also variable-length arrays

/*** CHAPTER                   8.1                  ONE-DIMENSIONAL ARRAYS ***/

an array is a data structure that contains a number of data values
these values ("AKA elements") have the same type
elements can be individually selected by their position within the array
the simplest array has only one dimension
each element ('_' in the next example) in a one-dimensional array, named
    'a', might be visualized on a row like this:  a _ _ _ _ _ _ _ _ _ _
to declare an array, you must specify the type of the arrays elements and the
    number of elements

int a[10];

array 'a' has 10 elements of type int
the elements of an array may be of any type
the length can be any integer constant expression
array lengths may often need to be adjusted, so using a macro to define the
    length of an array is a suggested practice:

#define N 10
...
int a[N];

//                          ARRAY SUBSCRIPTING

to access a particular array, write the array name followed by the integer
    value in square brackets
this is known as "subscripting", or "indexing", the array
array elements are numbered starting from 0, so elements of an array length 'n'
    are indexed from 0 to 'n' - 1:

a[0], a[1], a[2], a[3]...

expressions calling elements in the form a[i] are lvalues, so they can be used
    like normal variables:

a[0] = 1;
printf("%d\n", a[5]);
++a[i];

if an array contains elements of type 'T', then each element of the array is
    treated as if it were type 'T'
the above elements a[0], a[5], and a[i] behave like int variables
many programs contain for loops whose job is to perform some operation on every
    element in an array:

for (i = 0; i < N; i++)
    a[i] = 0;               /* clears a */

for (i = 0; i < N; i++)
    scanf("%d", &a[i]);     /* reads data into a */

for (i = 0; i < N; i++)
    sum += a[i];            /* sums the elements of a */

//                          WARNING

C does not require subscript bounds to be checked
if a subscript goes out of bounds, it enters undefined behavior
this often happens from forgetting an array with 'n' elements stops at 'n' - 1:

int a[10], i;                   /*** BAD CODE ***/
                                /*** BAD CODE ***/
for (i = 0; i <= 10; i++)       /*** BAD CODE ***/
    a[i] = 0;                   /*** BAD CODE ***/

some compilers can create an infinite loop with the above code
when 'i' reaches 10, the program stores 0 into a[10]
a[10] does not exist, so 0 goes into memory immediately after a[9]
if the variable 'i' happens to follow a[9] in memory (as it might here) then i
    will be assigned 0 in place of a[10]
with i reset to 0, the loop will start over

//END WARNING

an array subscript may be any integer expression:

a[i+j*10] = 0;

the expression can even have side effects:

i = 0;
while (i < N)
    a[i++] = 0;

after i is set to 0, while checks if i is less than 'N'
if so, 0 is assigned to a[0], and i is incremented
the loop repeats
note that a[++i] would not be right, as 0 would be assigned to a[1] during the
    first loop iteration

//                          WARNING

be careful when an array subscript has a side effect:

i = 0;              /*** BAD CODE ***/
while (i < N)       /*** BAD CODE ***/
    a[i] = b[i++];  /*** BAD CODE ***/

a[i] = b[i++] accesses 'i' and also modifies 'i' elsewhere, which causes
    undefined behavior
this can be avoided by removing the increment from the subscript:

for (i = 0; i < N; i++)
    a[i] = b[i];

//END WARNING

//                          REVERSING A SERIES OF NUMBERS

our first array program, reverse.c, prompts the user to enter a series of
    numbers, then writes the numbers in reverse order:

Enter 10 numbers: _34_82_49_102_7_94_23_11_50_31_
In reverse order:  31 50 11 23 94 7 102 49 82 34

we will store the numbers in an array as they are read, then go through the
    array backwards, printing the elements one by one:

//                          reverse.c - REVERSES A SERIES OF NUMBERS

#include <stdio.h>

#define N 10

int main(void)
{
    int a[N], i;

    printf("Enter %d numbers: ", N);
    for (i = 0; i < N; i++)
        scanf("%d", &a[i]);

    printf("In reverse order:");
    for (i = N - 1; i >= 0; i--)
        printf(" %d", a[i]);
    printf("\n");

    return 0;
}
