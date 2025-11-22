/*** CHAPTER                     12                    POINTERS AND ARRAYS ***/



//  12.1                    POINTER ARITHMETIC


Section 11.5 showed us how pointers can point to array elements:

int a[10], *p;

We can make p point to a[0] by writing:

p = &a[0];

We can store the value 5 in a[0] now:

*p = 5;

We can access the other elements of a by performing "pointer arithmetic" on p
C supports three forms of pointer arithmetic:

    Adding an integer to a pointer
    Subtracting an integer from a pointer
    Subtracting one pointer from another

We'll use these declarations to explain how to perform the above operations:

int a[10], *p, *q, i;


//  ADDING AN INTEGER TO A POINTER


Adding an integer j to a pointer p yields a pointer to the element j places
    after the one that p points to.
In other words, if p points to the array element a[i], then p + j points to
    a[i + j].

p = &a[2];

      p
      v
a|_ _ _ _ _ _ _ _ _ _
  0 1 2 3 4 5 6 7 8 9


q = p + 3;

      p     q
      v     V
a|_ _ _ _ _ _ _ _ _ _
  0 1 2 3 4 5 6 7 8 9


//  SUBTRACTING AN INTEGER FROM A POINTER


If p points to the array element a[i], then p - j points to a[i - j].


//  SUBTRACTING ONE POINTER FROM ANOTHER


When one pointer is subtracted from another, the result is the distance
    (measured in array elements) between the pointers.
So if p points to a[i] and q points to a[j], then p - q is equal to i - j:

p = &a[5];
q = &a[1];

i = p - q;  // i is 4
i = q - p;  // i is -4


//  COMPARING POINTERS


Using relational operators to compare two pointers is useful only when both
    point to elements of the same array.
The outcome of the comparison depends on the relative positions of the two
    elements in the array:

p = &a[5];
q = &a[1];

p <= q is 0
p >= q is 1


//  POINTERS TO COMPOUND LITERALS


A compound literal (C99) is a feature used to create an array with no name:

int *p = (int []){3, 0, 3, 4, 1};

Using a compound literal saves us the trouble of first declaring an array
    variable and then making p point to the first element of that array:

int a[] = {3, 0, 3, 4, 1};
int *p = &a[0];


//  12.2                USING POINTERS FOR ARRAY PROCESSING


Pointer arithmetic allows us to visit the elements of an array by repeatedly
    incrementing a pointer variable:

//program fragment: sums the elements of array a
#define N 10
...
int a[N], sum, *p;
...
sum = 0;
for (p = &a[0]; p < &a[n]; p++)
    sum += *p;

The condition p < &a[N] is safe to perform, since the loop doesn't attempt to
    examine its value.
We could have easily written this loop without pointers by using subscripting.
It is argued that using pointers can save execution time, but some C compilers
    actually produce better code for loops that utilize subscripting


//  COMBINING THE * AND ++ OPERATORS


Consider the case of staring a value into an array element and then advancing
    to the next element:

a[i++] = j;

using pointers:

*p++ = j;

Because the postfix version of ++ takes precedence over *, the compiler sees
    this as

*(p++) = j;

The value of p++ is p.  //the value before being incremented
Thus, the value of *(p++) will be *p (the object to which p is pointing).
We could write (*p)++, which returns the value of the object that p points to,
   and then increments that object (p itself is unchanged).

*p++ or *(p++) - Value of expression is *p before increment; increment p later
(*p)++         - Value of expression is *p before increment; increment *p later
*++p or *(++p) - Increment p first; value of expression is *p after increment
++*p or ++(*p) - Increment *p first; value of expression is *p after increment

Instead of writing:

for (p = &a[0]; p < &a[N]; p++)
    sum += *p;

to sum the elements of the array a, we could write:

p = &a[0];
while (p < &a[N])
    sum += *p++;

The * and -- operators mix in the same way as * and ++.
We can rewrite the stack example of Section 10.2 by including these operators.
The variable top can be replaced by a pointer variable that points initially to
    element 0 of the contents array:

int *top_ptr = &contents[0];

Here are the updated push and pop functions:

void push(int i)
{
    if (isfull())
        stack_overflow();
    else
        *top_ptr++ = i;
}

int pop(void)
{
    if (is_empty())
        stack_underflow();
    else
        return *--top_ptr;
}


//  12.3                USING AN ARRAY NAME AS A POINTER


The name of an array can be used as a pointer to the first element in the array
For example, suppose a is declared as follows:

int a[10];

Using a as a pointer to the first element in the array, we can modify a[0]:

*a = 7;     //stores 7 in a[0]

We can modify a[1] through the pointer a + 1:

*(a + 1) = 12;

In general, a + i is the same as &a[i] (both represent a pointer to element i
    of a)
This can make it easier to write loops that step through an array.
Consider this loop from Section 12.2:

for (p = &a[0]; p < &a[n]; p++)
    sum += *p;

To simplify the loop, we can replace &a[0] by a and &a[N] by a + N:

for (p = a; p < a + N; p++)
    sum += *p;

Although an array name can be used as a pointer, it's not possible to assign it
    a new value. Attempting to make it point elsewhere is an error:

while (*a != 0)
    a++;            // WRONG

To fix, we can always copy a into a pointer variable, then change the pointer
    variable:

p = a;
while (*p != 0)
    p++;

 
//  reverse3.c      REVERSING A SERIES OF NUMBERS (REVISITED)


#include <stdio.h>

#define N 10

int main(void)
{
    int a[N], *p;

    printf("Enter %d numbers: ", N);
    for (p = a; p < a + N; p++)
        scanf("%d", p);

    printf("In reverse order:");
    for (p = a + N - 1; p >= a; p--)
        printf(" %d", *p);
    printf("\n");

    return 0;
}


//  ARRAY ARGUMENTS (REVISITED)


When passed to a function, an array name is always treated as a pointer:

int find_largest(int a[], int n)
{
    int i, max;

    max = a[0];
    for (i = 1; i < n; i++)
        if (a[i] > max)
            max = a[i];
    return max;
}

Suppose we call find_largest as follows:

largest = find_largest(b, N);

This call causes a pointer to the first element of b to be assigned to a; the
    array itself isn't copied.
The time required to pass an array to a function doesn't depend on the size of
    the array. There's no penalty for passing a large array, since no copy of
    the array is made.
An array parameter can be declared as a pointer if desired. For example,
    find_largest could be defined as follows:

int find_largest(int *a, int n)
{
    ...
}

Declaring a to be a pointer is equivalent to declaring it to be an array; the
    compiler treats the declarations as though they were identical.
A function with an array parameter can be passed an array 'slice.' Suppose we
    want find_largest to locate the largest element in a portion of array b:

largest = find_largest(&b[5], 10);

This will examine elements b[5] through b[14]


//  USING A POINTER AS AN ARRAY NAME


#define N 10
...
int a[N], i, sum = 0, *p = a;
...
for (i = 0; i < N; i++)
    sum += p[i];

the compiler treats p[i] as *(p + i), which is legal pointer arithmetic.


//  12.4                POINTERS AND MULTIDIMENSIONAL ARRAYS


Section 8.2 explained how two-dimensional arrays are stored in row-major order.
    This means that the elements of row 0 come first, then row 1, and so forth.
This is the previously shown way to initialize all elements of a multi-
    dimensional array to zero:

int row, col;
...
for (row = 0; row < NUM_ROWS; row++)
    for (col = 0; col < NUM_COLS; col++)
        a[row][col] = 0;

But if we view a as a one-dimensional array of integers, we can replace the
    pair of loops by a single loop:

int *p;
...
for (p = &a[0][0]; p <= &a[NUM_ROWS-1][NUM_COLS-1]; p++)
    *p = 0;

Each increment of p will point it from a[0][0] to a[0][1] to a[0][2] to
    a[0][NUM_COLS - 1] to a[1][0] to a[1][1] to ...


//  PROCESSING THE ROWS OF A MULTIDIMENSIONAL ARRAY


To visit the elements of row i, we'd initialize p to point to element 0 in row
    i in the array a:

p = &a[i][0];

or we could simply write

p = a[i];

since, for any two-dimensional array a, the expression a[i] is a pointer to the
    first element of row i. For any array a, the expression a[i] is equivalent
    to *(a + i). Thus, &a[i][0] is the same as &( *(a[i] + 0)), which is
    equivalent to &*a[i], which is the same as a[i]:

int a[NUM_ROWS][NUM_COLS], *p, i;
...
for (p = a[i]; p < a[i] + NUM_COLS; p++)\
	*p = 0;

Since a[i] is a pointer to row i of the array a, we can pass a[i] to a function
	that's expecting a one-dimensional array as its argument. We can just as easily use find_largest to determine the largest element in row i of the two-
	dimensional array a:

largest = find_largest(a[i], NUM_COLS);


//	PROCESSING THE COLUMNS OF A MULTIDIMENSIONAL ARRAY


int a[NUM_ROWS][NUM_COLS], (*p)[NUM_COLS], i;
...
for (p = &a[0]; p < &a[NUM_ROWS]; p++)
	(*p)[i] = 0;

The parentheses around *p in (*p)[NUM_COLS] are required, as the compiler would
	treat p as an array of pointers without them. p++ advances p to the
	beginning of the next row. With (*p)[i], *p represents an entire row of a,
	so (*p)[i] selects the element in column i of that row. The parentheses in
	(*p)[i] are essential, as the compiler would interpret *p[i] as *(p[i]).


//	USING THE NAME OF A MULTIDIMENSIONAL ARRAY AS A POINTER


The name of any array can be used as a pointer, regardless of how many dimen-
	sions it has.

int a[NUM_ROWS][NUM_COLS];

a is NOT a pointer to a[0][0]; instead, it's a pointer to a[0].
C regards a not as a two-dimensional array but as a one-dimensional array whose
	elements are one-dimensional arrays. When used as a pointer, a has type
	int (*)[NUM_COLS]  (pointer to an integer array of length NUM_COLS).
Knowing that a points to a[0] is useful for simplifying loops that process the
	elements of a two-dimensional array. For example, instead of writing:

for (p = &a[0]; p < &a[NUM_ROWS]; p++)
	(*p)[i] = 0;

to clear column i of the array a, we can write

for (p = a; p < a + NUM_ROWS; p++)
	(*p)[i] = 0;

You can 'trick' a function to accept a multidimensional array into thinking it
	is a one-dimensional array, although you need to be careful:

largest = find_largest(a, NUM_ROWS * NUM_COLS);	//WRONG

The compiler will reject this because the type of a is int (*)[NUM_COLS] but
	find_largest is expecting an argument of type int *. The correct call is:

largest = find_largest(a[0], NUM_ROWS * NUM_COLS);

a[0] points to element 0 in row 0, and it has type int * (after conversion by
	the compiler), so the latter call will work correctly.


//	12.5				POINTERS AND VARIABLE-LENGTH ARRAYS (C99)


An ordinary pointer variable being used to point to an element of a one-
	dimensional array:

void f(int n)
{
	int a[n], *p;
	p = a;
	...
}

When the VLA has more than one dimension, the type of the pointer depends on
	the length of each dimension except for the first:

void f(int m, int n)
{
	int a[m][n], (*p)[n];
	p = a;
	...
}

Since the type of p depends on n, which isn't constant, p is said to have a
	"variably modified type."
Note that the validity of an assignment such as p = a can't always be deter-
    mined by the compiler. For example, the following code will compile but is
    correct only if m and n are equal:

//risky code
int a[m][n], (*p)[m];
    p = a;

The declaration of a variably modified type must be inside the body of a
    function or in a function prototype.
Pointer arithmetic works with VLAs just as it does for ordinary arrays:

int a[m][n];

A pointer capable of pointing to a row of a would be declared as follows:

int (*p)[n];

The loop to clear column i is almost identical to the one used in Section 12.4:

for (p = a; p < a + m; p++)
    (*p)[i] = 0;
