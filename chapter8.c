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

//                          ARRAY INITIALIZATION

an array can be given an initial value at declaration
the most common form of "array initializer" is a list of constant expressions
    enclosed in braces and separated by commas:

int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

if the initializer list is shorter than the array, the remaining elements are
    given the value 0:

int a[10] = {1, 2, 3, 4, 5, 6};
    /* initial value of a is {1, 2, 3, 4, 5, 6, 0, 0, 0, 0} */

initializing an array to all zeros:

int a[10] = {0};
    /* initial value of a is {0, 0, 0, 0, 0, 0, 0, 0, 0, 0} */

an initializer cannot be completely empty ( {} wrong : {0} okay )
an initializer cannot be longer than the array it initializes
if an initializer is present, the length of the array can be omitted:

int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

the array in the above example still has a fixed number of elements

//                          C99 - DESIGNATED INITIALIZERS

often only a few elements of an array need to be initialized, while the other
    elements can be given default values:

int a[15] = {0, 0, 29, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 48};

for a large array, writing an initializer this way is tedious and error-prone
    (what if there were 200 zeros between two of the non-zero values?)
"designated initializers" solve this problem:

int a[15] = {[2] = 29, [9] = 7, [14] = 48};

each number within brackets is said to be a "designator"
the order in which elements are listed no longer matter when using designators:

int a[15] = {[14] = 48, [9] = 7, [2] = 29};

designators must be integer constant expressions
if an array is given length 'n', each designator must be between 0 and 'n' - 1
if the length of the array is omitted, then a designator can be any nonnegative
    integer (the compiler will deduce the length of the array):

int b[] = {[5] = 10, [23] = 13, [11] = 36, [15] = 29};//array length will be 24

an initializer can use both the element-by-element technique, or the designator
    technique
since the next element to be initialized is the one following the element that
    was initialized last, take care when placing designators in a list using
    the element-by-element technique:

int c[10] = {5, 1, 9, [4] = 3, 7, 2, [8] = 6};

elements 0, 1, and 2 will have the values 5, 1, and 9
element 4 will have the value 3
elements 5 and 6 will have values 7 and 2
element 8 will have value 6
all other values will be 0

int a[] = {4, 9, 1, 8, [0] = 5, 7};

element 0 is value 4
element 1 is value 9
element 2 is value 1
element 3 is value 8
element 0 is now 5
element 1 is now 7  //next element to be initialized follows the last one

//                          CHECKING A NUMBER FOR REPEATED DIGITS

this program checks whether any of the digits in a number appear more than once
the program will print either "Repeated digit" or "No repeated digit"

Enter a number: _28212_
Repeated digit

the program uses an array of Boolean values to keep track of which digits
    appear in a number

//                          repdigit.c - CHECKS NUMBERS FOR REPEATED DIGITS

#include <stdbool.h>    /* C99 only */
#include <stdio.h>

int main(void)
{
    bool digit_seen[10] = {false};
    int digit;
    long n;

    printf("Enter a number: ");
    scanf("%ld", &n);

    while (n > 0) {
        digit = n % 10;
        if (digit_seen[digit])
            break;
        digit_seen[digit] = true;
        n /= 10;
    }

    if (n > 0)
        printf("Repeated digit\n");
    else
        printf("No repeated digit\n");

    return 0;
}

//                          USING THE sizeof OPERATOR WITH ARRAYS

sizeof can be used to determine the size of an array
if 'a' is an array of 10 integers, then sizeof(a) is typically 40 (assuming
    each integer requires four bytes)
sizeof can also measure the size of an array element, such as a[0]
dividing the array size by the element size gives the length of the array:

sizeof(a) / sizeof(a[0])

this expression is useful for when the length of the array is needed
to clear the array 'a', we could write:

for (i = 0; i < sizeof(a) / sizeof(a[0]); i++)
    a[i] = 0;//loop sets a[0] to 0, then sets a[1] to 0, then sets a[2] to 0...

this technique allows the loop to stay unmodified should the length of the
    array change later
you can also use a macro to represent the array length, but sizeof is slightly
    better to use since there is no macro name to remember
some compilers produce a warning message for the expression
    i < sizeof(a) / sizeof(a[0])
this is because 'i' is probably type int, whereas sizeof produces a value of
    type size_t (an unsigned type)
this is not an issue here since both ('i') and (sizeof(a) / sizeof(a[0])) have
    nonnegative values
to avoid a warning, convert (sizeof(a) / sizeof(a[0])) to a signed integer
    using cast:

for (i = 0; i < (int) (sizeof(a) / sizeof(a[0])); i++)
    a[i] = 0;

writing (int) (sizeof(a) / sizeof(a[0]) is a bit cumbersome, so defining a
    macro for it is helpful:

#define SIZE ((int) (sizeof(a) / sizeof(a[0])))

for (i = 0; i < SIZE; i++)
    a[i] = 0;

//                          COMPUTING INTEREST

this next program shows the value of $100 invested at different rates of
    interest over a period of years
a session with the program will look like this:

Enter interest rate: _6_
Enter number of years: _5_

Years     6%     7%     8%     9%    10%
  1     106.00 107.00 108.00 109.00 110.00
  2     112.36 114.49 116.64 118.81 121.00
  3     119.10 122.50 125.97 129.50 133.10
  4     126.25 131.08 126.05 141.16 146.41
  5     133.82 140.26 146.93 153.86 161.05

//              `           interest.c - PRINTS A TABLE OF COMPOUND INTEREST

#include <stdio.h>

#define NUM_RATES ((int) (sizeof(value) / sizeof(value[0])))
#define INITIAL_BALANCE 100.00

int main(void)
{
    int i, low_rate, num_years, year;
    double value[5];

    printf("Enter interest rate: ");
    scanf("%d", &low_rate);
    printf("Enter number of years: ");
    scanf("%d", &num_years);

    printf("\nYears");
    for (i = 0; i < NUM_RATES; i++) {
        printf("%6d%%", low_rate + i); //prints interest rate to right of Years
        value[i] = INITIAL_BALANCE; //sets the value of each element to 100.00
    }
    printf("\n");

    for (year = 1; year <= num_years; year++) {
        printf("%3d    ", year); //first prints year
        for (i = 0; i < NUM_RATES; i++) {
            value[i] += (low_rate + i) / 100.0 * value[i];//calculates interest
            printf("%7.2f", value[i]);
        }
        printf("\n");
    }

    return 0;
}

the idea is to store the first row as an array as it is computed, then use the
    values in the array to compute the second row
this process can be repeated for the third and later rows
one for statement will be nested inside another
the outer loop will count from 1 to the number of years requested by the user
the inner loop will increment the interest rate from its lowest value to its
    highest value

/*** CHAPTER                  8.2                  MULTIDIMENSIONAL ARRAYS ***/

an array may have any number of dimensions
this following declaration creates a two-dimensional array (matrix):

int m[5][9];

array 'm' will have 5 rows and 9 columns
both rows and columns are indexed from 0
array 'm' visualized:

  0 1 2 3 4 5 6 7 8
0 _ _ _ _ _ _ _ _ _
1 _ _ _ _ _ _ _ _ _
2 _ _ _ _ _ _ _ _ _
3 _ _ _ _ _ _ _ _ _
4 _ _ _ _ _ _ _ _ _

to access the element of m in row i, column j, we must write m[i][j]
even though we visualize two-dimensional array as tables, they are stored in
    memory in "row-major order":

    row  0            row  1            row  2            row  3
  /        \        /        \        /        \        /        \
m[0,0]_..._m[0,8]_m[1,0]_..._m[1,8]_m[2,0]_..._m[2,8]_m[3,0]_..._m[3,8]_...

nested for loops are ideal for processing multi-dimensional arrays
this next example shows how to initialize an array as an "identity matrix":

#define N 10

double ident [N][N];
int row, col;

for (row = 0; row < N; row++)
    for (col = 0; col < N; col++)
    if (row == col)
        ident[row][col] = 1.0;
    else
        ident[row][col] = 0.0;

//                          INITIALIZING A MULTIDIMENSIONAL ARRAY

you can initialize a two-dimensional array by nesting one-dimensional
    initializers:

int m[5][9] = {{1, 1, 1, 1, 1, 0, 1, 1, 1},
               {0, 1, 0, 1, 0, 1, 0, 1, 0},
               {0, 1, 0, 1, 1, 0, 0, 1, 0},
               {1, 1, 0, 1, 0, 0, 0, 1, 0},
               {1, 1, 0, 1, 0, 0, 1, 1, 1}};

initializers for higher-dimensional arrays are constructed the same way
if an initializer is not large enough to fill a multi-dimensional array, the
    remaining elements are given the value 0
if an inner list is not long enough to fill a row, the remaining elements in
    the row are initialized to 0
the inner braces may be omitted (some compilers may produce a warning)
designated initializers work with multi-dimensional arrays:

double ident[2][2] = {[0][0] = 1.0, [1][1] = 1.0};	//2x2 identity matrix

//			                CONSTANT ARRAYS

arrays can be made "constant" by starting its declaration with const:

const char hex_char[] =
    {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
     'A', 'B', 'C', 'D', 'E', 'F'};

const declarations should not be modified by the program; the compiler will
    detect direct attempts to modify an element
const works with any variable

//                          DEALING A HAND OF CARDS

this next program deals a random hand from a standard deck of cards
to pick cards randomly, we will use several C library functions
time (<time.h>) returns the current time, encoded in a single number
srand (<stdlib.h>) initializes the C random number generator
passing the return value of time to srand prevents the program from dealing the
    same cards every time we run it
rand (<stdlib.h>) produces an apparently random number each time it is called
by using the modulo (%) operator, we can scale the return value from rand so
    that it falls between 0 and 3 (for suits) or between 0 and 12 (for ranks)
array in_hand will keep track of which cards have already been chosen

//                          deal.c - DEALS A RANDOM HAND OF CARDS

#include <stdbool.h>    /* C99 only */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_SUITS 4
#define NUM_RANKS 13

int main(void)
{
    bool in_hand[NUM_SUITS][NUM_RANKS] = {false};
    int num_cards, rank, suit;
    const char rank_code[] = {'2', '3', '4', '5', '6', '7', '8',
                              '9', 't', 'j', 'q', 'k', 'a'};
    const char suit_code[] = {'c', 'd', 'h', 's'};

    srand((unsigned) time(NULL));

    printf("Enter number of cards in hand: ");
    scanf("%d", &num_cards);

    printf("Your hand:");
    while (num_cards > 0) {
            suit = rand() % NUM_SUITS;
            rank = rand() % NUM_RANKS;
            if (!in_hand[suit][rank]) {
                in_hand[suit][rank] = true;
                num_cards--;
                printf(" %c%c", rank_code[rank], suit_code[suit]);
            }
        }
        printf("\n");

        return 0;
}

/*** CHAPTER                8.3               VARIABLE-LENGTH ARRAYS (C99) ***/

in C89, an array variable must be specified by a constant expression
in C99, it is sometimes possible to use an expression that is not constant:

//                          reverse2.c - REVERSES A SERIES OF NUMBERS USING VLA

#include <stdio.h>

int main(void)
{
    int i, n;

    printf("How many numbers do you want to reverse? ");
    scanf("%d", &n);

    int a[n];   /* C99 only */

    printf("Enter %d numbers: ", n);
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("In reverse order:");
    for (i = n - 1; i >= 0; i--)
        printf(" %d", a[i]);
    printf("\n");

    return 0;
}

the length of a VLA can be a single variable or even arbitrary expressions:

int a[3*i+5];
int b[j+k];

VLAs can also be multidimensional:

int c[m][n];

VLAs cannot have static storage duration (not yet discussed)
VLAs may not have an initializer

/*** CHAPTER                          8                          EXERCISES ***/

/*** CHAPTER                     8                    PROGRAMMING PROJECTS ***/

1. Modify the repdigit.c program (Section 8.1) so that it shows which digits
     (if any) were repeated.

#include <stdbool.h>    /* C99 only */
#include <stdio.h>

int main(void)
{
    bool repcheck = false, digit_seen[10] = {false}, repdigit[10] = {false};
    int digit;
    long n;

    printf("Enter a number: ");
    scanf("%ld", &n);

    while (n > 0) {
        digit = n % 10;
        if (digit_seen[digit]) {
            repdigit[digit] = true;
            repcheck = true;
	    }
        digit_seen[digit] = true;
        n /= 10;
    }

    if (repcheck)
	    printf("Repeated digits:");
    else {
	    printf("No repeated digits\n");
	    return 0;
    }

    for (int i = 0; i < (sizeof(repdigit) / sizeof(repdigit[0])); i++)
            if (repdigit[i])
                printf(" %d", i);

    printf("\n");

    return 0;
}

2. Modify the repdigit.c program so that it prints a table showing how many
     times each digit appears in the number.

#include <stdio.h>

int main(void)
{
    int digit, digit_seen[10] = {0};
    long n;

    printf("Enter a number: ");
    scanf("%ld", &n);

    while (n > 0) {
        digit = n % 10;
        digit_seen[digit] += 1;
        n /= 10;
    }

    printf("Digit:        0  1  2  3  4  5  6  7  8  9\n");
    printf("Occurrences:");

    for (int i = 0; i < (sizeof(digit_seen) / sizeof(digit_seen[0])); i++)
            printf("%3d", digit_seen[i]);

    printf("\n");

    return 0;
}

3. Modify repdigit.c so that the user can enter more than one number to be
     tested for repeated digits. The program should terminate when the user
     enters a number that is less than or equal to 0.

#include <stdio.h>

#define SIZE (int) (sizeof(digit_seen) / sizeof(digit_seen[0]))

int main(void)
{
    int digit, digit_seen[10] = {0};
    long n;

    printf("Enter a number: ");

    for (;;) {
        scanf("%ld", &n);
        if (n <= 0)
            break;
        while (n > 0) {
            digit = n % 10;
            digit_seen[digit] += 1;
            n /= 10;
        }
    }

    printf("Digit:        0  1  2  3  4  5  6  7  8  9\n");
    printf("Occurrences:");

    for (int i = 0; i < SIZE; i++)
            printf("%3d", digit_seen[i]);

    printf("\n");

    return 0;
}

4. Modify the reverse.c program (Section 8.1) to use the expression
     (int) (sizeof(a) / sizeof(a[0])) (or a macro with this value) for the
     array length.

#include <stdio.h>

#define N 10
#define SIZE (int) (sizeof(a) / sizeof(a[0]))

int main(void)
{
    int a[N], i;

    printf("Enter %d numbers: ", N);
    for (i = 0; i < SIZE; i++)
        scanf("%d", &a[i]);

    printf("In reverse order:");
    for (i = SIZE - 1; i >= 0; i--)
        printf(" %d", a[i]);
    printf("\n");

    return 0;
}

5. Modify the interest.c program (Section 8.1) so that it compounds interest
     monthly instead of annually. The form of the output should not change, the
     balance should still be shown at annual intervals.

#include <stdio.h>

#define NUM_RATES ((int) (sizeof(value) / sizeof(value[0])))
#define INITIAL_BALANCE 100.00

int main(void)
{
    int m, i, low_rate, num_years, year;
    double value[5];

    printf("Enter interest rate: ");
    scanf("%d", &low_rate);
    printf("Enter number of years: ");
    scanf("%d", &num_years);

    printf("\nYears");
    for (i = 0; i < NUM_RATES; i++) {
        printf("%6d%%", low_rate + i); //prints interest rate to right of Years
        value[i] = INITIAL_BALANCE; //sets the value of each element to 100.00
    }
    printf("\n");

    for (year = 1; year <= num_years; year++) {
        printf("%3d    ", year); //first prints year
        for (i = 0; i < NUM_RATES; i++) {
            for (m = 1; m <= 12; m++) {
                value[i] += (((low_rate + i) / 100.0) / 12) * value[i];
                }
            printf("%7.2f", value[i]);
        }
        printf("\n");
    }

    return 0;
}

6. Write a "B1FF filter" that reads a message entered by the user and
     translates it into B1FF-speak. Your program should convert the message to
     upper-case, substitute letters for certain letters (A -> 4, B -> 8, E -> 3
     I -> 1, O -> 0, S -> 5), and then append 10 or so exclamation marks.

#include <stdio.h>     /*** CODE BREAKS AFTER ~15 CHARACTERS ***/
#include <ctype.h>

int main(void)
{
    int l = 1, i = 0;
    char m[l];  //message [l]ength

    printf("Enter message: ");

    for (i = 0;;i++) {
        l++;
        m[i] = getchar();
        if (m[i] == '\n')
            break;
    }

    printf("In B1FF speak: ");

    for (i = 0; i < l; i++){
        m[i] = toupper(m[i]);
        if (m[i] == 'A')
            m[i] = '4';
        if (m[i] == 'B')
            m[i] = '8';
        if (m[i] == 'E')
            m[i] = '3';
        if (m[i] == 'I')
            m[i] = '1';
        if (m[i] == 'O')
            m[i] = '0';
        if (m[i] == 'S')
            m[i] = '5';
        putchar(m[i]);
    }

    l--;

    printf("!!!!!!!!!!\n");
    return 0;
}

7. Write a program that reads a 5 x 5 array of integers and then prints the row
     sums and the column sums.

#include <stdio.h>

int main(void)
{
    int i, j, n;
    long a[5][5] = {0}, row[5] = {0}, col[5] = {0};

    for (i = 0, n = 1; i <= 4; n++, i++) {
        printf("Enter row %d: ", n);
        for (j = 0; j <= 4; j++) {
            scanf(" %ld", &a[i][j]);
        }
    }

    for (i = 0; i <= 4; i++) {
        for (j = 0; j <= 4; j++) {
            row[i] += a[i][j];
            col[i] += a[j][i];
        }
    }

    printf("Row totals:");
    for (i = 0; i <= 4; i++)
        printf(" %ld", row[i]);

    printf("\nColumn totals:");
    for (i = 0; i <= 4; i++)
        printf(" %ld", col[i]);

    return 0;
}

8. Modify Project 7 so that it prompts for five quiz grades for each of five
     students, then computes the total score and average score for each
     student, and the average score, high score, and low score for each quiz.

#include <stdio.h>

int main(void)
{
    int s, q, n;
    int sq[5][5] = {0}, stot[5] = {0}, savg[5] = {0};
    int qavg[5] = {0}, qtot[5] = {0};
    int qh[5] = {0}, ql[5] = {100, 100, 100, 100, 100};

    for (s = 0, n = 1; s <= 4; n++, s++) {
        printf("Enter student %d quiz grades: ", n);
        for (q = 0; q <= 4; q++) {
            scanf("%d", &sq[s][q]);
        }
    }

    for (s = 0; s <= 4; s++) {
        for (q = 0; q <= 4; q++) {
            stot[s] += sq[s][q];
            qtot[s] += sq[q][s];
            if (sq[q][s] > qh[s])
                qh[s] = sq[q][s];
            if (sq[q][s] < ql[s])
                ql[s] = sq[q][s];
        }
        savg[s] = (stot[s] / 5);
        qavg[s] = (qtot[s] / 5);
    }

    printf("Student totals:");
    for (s = 0; s <= 4; s++)
        printf(" %d", stot[s]);

    printf("\nStudent averages:");
    for (s = 0; s <= 4; s++)
        printf(" %d", savg[s]);

    printf("\nQuiz averages:");
    for (q = 0; q <= 4; q++)
        printf(" %d", qavg[q]);

    printf("\nQuiz high scores:");
    for (q = 0; q <= 4; q++)
        printf(" %d", qh[q]);

    printf("\nQuiz low scores:");
    for (q = 0; q <= 4; q++)
        printf(" %d", ql[q]);

    printf("\n");

    return 0;
}

9. Write a program that generates a "random walk" across a 10x10 array. The
     array will contain characters (all '.' initially). The program must
     randomly "walk" from element to element, always going up, down, left, or
     right by one element. The elements visited by the program will be labeled
     A through Z, in the order visited.

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define X 10
#define Y 10
#define NoD 4   //Number of Directions

int main(void)
{
    bool u = 0, r = 0, d = 0, l = 0;
    short y, x, dir;
    char grid[Y][X], walk = 'A';

    srand((unsigned) time(NULL));

    for (y = 0; y < Y; y++) {
        for (x = 0; x < X; x++) {
            grid[y][x] = '.';
        }
    }

    for (y = 0, x = 0;;walk++) {
        grid[y][x] = walk;
        if (walk == 'Z') {
            break;
        }

        retry:

        if (u && r && d && l) {
            printf("The walk was unable to finish it's course...\n\n");
            break;
        }

        dir = rand() % NoD;

        switch (dir) {
            case 0:
                if ((y - 1) < 0 || grid[y - 1][x] != '.') {
                    u = 1;
                    goto retry;
                }
                y--;
                u = 0; r = 0; d = 1; l = 0;
                break;

            case 1:
                if ((x + 1) > 9 || grid[y][x + 1] != '.') {
                    r = 1;
                    goto retry;
                }
                x++;
                u = 0; r = 0; d = 0; l = 1;
                break;

            case 2:
                if ((y + 1) > 9 || grid[y + 1][x] != '.') {
                    d = 1;
                    goto retry;
                }
                y++;
                u = 1; r = 0; d = 0; l = 0;
                break;

            case 3:
                if ((x - 1) < 0 || grid[y][x - 1] != '.') {
                    l = 1;
                    goto retry;
                }
                x--;
                u = 0; r = 1; d = 0; l = 0;
                break;
            }
        }

    for (y = 0; y < Y; y++) {
        for (x = 0; x < X; x++) {
            printf("%c ", grid[y][x]);
        }
        printf("\n");
    }
    return 0;
}

10. Modify Chapter 5, Project 8 so that the departure times are stored in an
     array and the arrival times are stored in a second array. The program will
     use a loop to search the array of departure times for the one closest to
     the time entered by the user.

#include <stdio.h>
#include <ctype.h>

#define AVG (((dep[i + 1] - dep[i]) / 2) + dep[i])//the average between two departure times

int main(void)
{
    short uh, um, cm, i;//user hour, user minute, converted min
    short dep[8] = {480, 583, 679, 767, 840, 945, 1140, 1305};
    short arr[8] = {616, 712, 811, 900, 968, 1075, 1280, 1438};
    char mer;

    printf("Enter a 12-hour time: ");
    scanf("%2hd:%2hd %c", &uh, &um, &mer);

    mer = toupper(mer);

    if (mer == 'P' && uh != 12)
        cm = (((uh * 60) + um) + 720);
    else if (mer == 'A' || mer == 'P' && uh == 12)
        cm = ((uh * 60) + um);
    else
        printf("Invalid time.\n");

    printf("%hd\n", cm);

    for (i = 0; i < 8; i++)
        if (cm < AVG)
            break;

        //dep before noon, arr before noon
    if (dep[i] < 720 && arr[i] < 720) {
        printf("Closest departure time is %2.2hd:%2.2hda.m.,", dep[i] / 60, dep[i] % 60);
        printf("arriving at %2.2hd:%2.2hda.m.\n", arr[i] / 60, arr[i] % 60);
    }
        //dep before noon, arr during noon
    else if (dep[i] < 720 && arr[i] >= 720 && arr[i] < 780) {
        printf("Closest departure time is %2.2hd:%2.2hda.m.,", dep[i] / 60, dep[i] % 60);
        printf("arriving at %2.2hd:%2.2hdp.m.\n", arr[i] / 60, arr[i] % 60);
    }
        //dep before noon, arr after noon
    else if (dep[i] < 720 && arr[i] > 780) {
        arr[i] -= 720;
        printf("Closest departure time is %2.2hd:%2.2hda.m.,", dep[i] / 60, dep[i] % 60);
        printf("arriving at %2.2hd:%2.2hdp.m.\n", arr[i] / 60, arr[i] % 60);
    }
        //dep during noon, arr during noon
    else if (dep[i] >= 720 && dep[i] < 780 && arr[i] >= 720 && arr[i] < 780) {
        printf("Closest departure time is %2.2hd:%2.2hdp.m.,", dep[i] / 60, dep[i] % 60);
        printf("arriving at %2.2hd:%2.2hdp.m.\n", arr[i] / 60, arr[i] % 60);
    }
        //dep during noon, arr after noon
    else if (dep[i] >= 720 && dep[i] < 780 && arr[i] > 780) {
            arr[i] -= 720;
        printf("Closest departure time is %2.2hd:%2.2hdp.m.,", dep[i] / 60, dep[i] % 60);
        printf("arriving at %2.2hd:%2.2hdp.m.\n", arr[i] / 60, arr[i] % 60);
    }
        //dep after noon, arr after noon
    else {
        dep[i] -= 720;
        arr[i] -= 720;
        printf("Closest departure time is %2.2hd:%2.2hdp.m.,", dep[i] / 60, dep[i] % 60);
        printf("arriving at %2.2hd:%2.2hdp.m.\n", arr[i] / 60, arr[i] % 60);
    }
    return 0;
}

11. Modify Chapter 7, Project 4 so that the program labels its output. The
     program will need to store the phone number in an array of characters
     until it can be printed. You may assume the phone number is no more than
     15 characters long.

#include <stdio.h>
#include <ctype.h>

int main(void)
{
    short i;
	char phone[15] = {0};

	printf("Enter phone number: ");

	for (i = 0; i < 15;i++) {
        scanf("%c", &phone[i]);
        phone[i] = toupper(phone[i]);
        if (phone [i] >= 'A' && phone [i] <= 'Z')
            switch (phone[i]) {
                case 'A': case 'B': case 'C':
                        phone [i] = '2';
                        break;
                case 'D': case 'E': case 'F':
                        phone [i] = '3';
                        break;
                case 'G': case 'H': case 'I':
                        phone [i] = '4';
                        break;
                case 'J': case 'K': case 'L':
                        phone [i] = '5';
                        break;
                case 'M': case 'N': case 'O':
                        phone [i] = '6';
                        break;
                case 'P': case 'Q': case 'R': case 'S':
                        phone [i] = '7';
                        break;
                case 'T': case 'U': case 'V':
                        phone [i] = '8';
                        break;
                case 'W': case 'X': case 'Y': case 'Z':
                        phone [i] = '9';
                        break;
            }
        else if (phone[i] == '\n')
            break;
        else
            continue;
	}
	printf("In numeric form: ");

	for (i = 0; i < 15; i++) {
        printf("%c", phone[i]);
    }
	return 0;
}

12. Modify Chapter 7, Project 5 so that the SCRABBLE values of the letters are
     stored in an array. The array will have 26 elements for each letter of the
     alphabet, and each element will contain the SCRABBLE value for that letter
     (element 25 ('Z') is 10). Use an array initializer to set up the array.

#include <stdio.h>
#include <ctype.h>

int main(void)
{
	char l;
	short w = 0;    //word total
    short svalue[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3,
                       1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

	printf("Enter a word: ");

    for (;;) {
        l = getchar();
        if (l == '\n')
            break;
        l = toupper(l);
        l -= 'A';
        w += svalue[l];
    }

    printf("Scrabble value: %hd", w);

	return 0;
}

13. Modify Chapter 7, Project 11 so that the program labels its output. The
     program will need to store the last name (but not the first name) in an
     array of characters until it can be printed. You may assume that the last
     name is no more than 20 characters long.

#include <stdio.h>

int main(void)
{
    short i;
    char ch, fi = 0, name[21] = {0};    //first initial, last name

    printf("Enter a first and last name: ");

    for (;;) {
        ch = getchar();

        if (!fi) {
            fi = ch;
            }
        else if (ch == ' ') {
            for (i = 0; i < 22; i++) {
                name[i] = getchar();
                if (name[i] == '\n') {
                    name[i] = 0;
                    for (i = 0;; i++) {
                        putchar(name[i]);
                        if (!name[i]) {
                            printf("\b, %c.\n", fi);
                            return 0;
                        }
                    }
                }
            }
		}
    }
}

14. Write a program that reverses the words in a sentence. Have the loop stop
     at a period, question mark, or exclamation point, which is saved in a
     separate char variable. Then use a second loop to search backwards through
     the array for the beginning of the last word. Print the last word, then
     search backward for the next to last word, then the next... Then print the
     terminating character.

