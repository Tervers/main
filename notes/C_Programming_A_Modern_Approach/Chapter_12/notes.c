/*** CHAPTER                     12                    POINTERS AND ARRAYS ***/



//  12.1                    POINTER ARITHMETIC


11.5 showed us how pointers can point to array elements:

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
