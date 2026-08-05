/*** CHAPTER                          11                          POINTERS ***/


//  11.1                        POINTER VARIABLES


Byte - 8 bits of information: |0|1|0|1|0|0|1|1|
Each byte has a unique address
An executable program consists of both:
    1. code (machine instructions corresponding to statements in the original C
            program).
    2. data (variables in the original program)
Each variable occupies one or more bytes of data

Address     Contents
    0       01010011
    1       01110101
    2       01110011
    3       01100001
    4       01101110
              ...
   n-1      01000011

The address of the first byte is said to be the address of the variable

              ...
   2000           \ 
   2001           / i (i occupies 2000 and 2001, so i's address is 2000)
              ...

Pointer variables store the address of a variable / object
When we store the address of a variable i in the pointer variable p, we say
    that p points to i
A pointer is just an address, and a pointer variable is just a variable that
    can store an address


//  DECLARING POINTER VARIABLES


int *p;   //p is a pointer variable capable of pointing to objects of type int

Pointer variables can appear in declarations along with other variables:

int i, j, a[10], b[20], *p, *q;

C requires that every pointer variable point only to objects of a particular
    type (the referenced type):

int *p;     /* points only to integers   */
double *q;  /* points only to doubles    */
char *r;    /* points only to characters */

A pointer variable can point to another pointer


//  11.2              THE ADDRESS AND INDIRECTION OPERATORS


&: Address Operator - If x is a variable, then &x is the address of x in memory
*: Indirection Operator - If p is a pointer, then *p represents the object to
    which p currently points


// THE ADDRESS OPERATOR


Declaring a pointer variable sets aside space for a pointer but doesn't make
    it point to an object: //int *p;
We must initialize p before we use it. One way is to assign it the address of
    some variable (or lvalue) using the & (address) operator:
    int i, *p;
    ...
    p = &i;
It's possible to initialize a pointer variable at the time we declare it:
    int i;
    int *p = &i;
We can even combine the declaration of i with the declaration of p, provided
    that i is declared first:
    int i, *p = &i;


// THE INDIRECTION OPERATOR


The * (indirection) operator can access what's stored in a pointer object
If p points to i, we can print the value of i:
    printf("%d\n", *p);
You can think * as the inverse of &:
    j = *&i;  /* same as j = i; */
As long as p points to i, *p is an alias for i
*p has the same value as i
changing the value of *p also changes the value of i:
    p = &i;
    i = 1;
    printf("%d\n", i);  /* prints 1 */
    printf("%d\n", *p); /* prints 1 */
    *p = 2;
    printf("%d\n", i);  /* prints 2 */
    printf("%d\n", *p); /* prints 2 */


//  11.3                      POINTER ASSIGNMENT


C allows the use of the assignment operator to copy pointers, provided that
    they have the same type:
    int i, j, *p, *q;
    p = &i; // this statement is an example of pointer assignment
    q = p;  // another example, now both pointers point to i
Now we can change i by assigning a new value to either *p or *q
p = q; is NOT the same as *p = *q;:
    p = &i;
    q = &j;
    i = 1;
    *q = *p; //copies the value that p points to (i) into the object that q
             //points to (j)


//  11.4                    POINTERS AS ARGUMENTS


We know that a variable supplied as an argument in a function call is protected
    against change, because C passes arguments by value
Instead of passing variable x as the argument to a function, we can supply &x,
    a pointer to x
We'll declare the corresponding parameter p to be a pointer
When the function is called, p will have the value &x, hence *p (the object
    that p points to) will be an alias for x
void decompose(double x, long *int_part, double *frac_part)
{
    *int_part = (long) x;
    *frac_part = x - *int_part;
}
We'll call decompose in the following way:
    decompose(3.14159, &i, &d);
Because of the & operator in front of i and d, the arguments to decompose are
    pointers to i and d, not the values
int i;
...
scanf("%d", &i);
We put the & operator in front of i so that scanf is given a pointer to i; that
    pointer tells scanf where to put the value that it reads
int i, *p;
...
p = &i;
scanf("%d", p);  //valid
Since p contains the address of i, scanf will read an integer and store it in i
scanf("%d", &p); //wrong
scanf here would read an integer and store it in p (a pointer) instead of in i


//  maxmin.c    FINDING THE LARGEST AND SMALLEST ELEMENTS IN AN ARRAY


#include <stdio.h>

#define N 10

void max_min(int a[], int n, int *max, int *min);

int main(void)
{
    int b[N], i, big, small;

    printf("Enter %d numbers: ", N);
    for (i = 0; i < N; i++)
        scanf("%d", &b[i]);

    max_min(b, N, &big, &small);

    printf("Largest: %d\n", big);
    printf("Smallest: %d\n", small);

    return 0;
}

void max_min(int a[], int n, int *max, int *min)
{
    int i;

    *max = *min = a[0];
    for (i = 1; i < n; i++) {
        if (a[i] > *max)
            *max = a[i];
        else if (a[i] < *min)
            *min = a[i];
    }
}


// USING const TO PROTECT ARGUMENTS


Using pointers may increase efficiency, as passing the value of a variable can
    waste time and space if the variable requires a large amount of storage
const won't change an object whose address is passed to a function
    void f(const int *p)
    {
        *p = 0;     /*** WRONG ***/
    }
This use of const indicates that p is a pointer to a "constant integer."
    Attempting to modify *p is an error that the compiler will detect.


//  11.5                    POINTERS AS RETURN VALUES


The following function, when given pointers to two integers, returns a pointer
    to whichever integer is larger:
    int *max(int *a, int *b)
    {
        if (*a > *b)
            return a;
        else
            return b;
    }
When we call max, we'll pass pointers to two int variables and store the result
    in a pointer variable:
    int *p, i, j;
    ...
    p = max(&i, &j);
A function can also return a pointer to an external variable or to a local
    variable that's been declared static
NEVER return a pointer to an automatic local variable:
    int *f(void)
    {
        int i;
        ...
        return &i;
    }
The variable i doesn't exist once f returns, so the pointer to it will be
    invalid.
Pointers can point to array elements:
    &a[i]  //pointer to element i of a
The following function returns a pointer to the middle element of the array a,
    assuming that a has n elements:
    int *find_middle(int a[], int n) {
        return &a[n/2];
    }


//                                  Q & A


Q:
There seems to be an inconsistency between the declaration
    int *p = &i;
and the statement
    p = &i;
Why isn't p preceded by a * symbol in the statement, as it is in the
    declaration?

A:
int *p = &i;  //* here is not the indirection operator, this one informs the
              //compiler that p is a pointer to an int
*p = &i;  /*** WRONG ***/
This statement is wrong because it assigns the address of i to the object that
    p points to, not to p itself

Q: The following declaration is confusing:
    void f(const int *p);
Does this say that f can't modify p?

A:
No. It says that f can't change the integer that p points to; it doesn't pre-
    vent f from changing p itself.
    void f(const int *p)
    {
        int j;

        *p = 0;     /*** WRONG ***/
        p = &j;     /* legal */
    }
Since arguments are passed by value, assigning p a new value (by making it
    point somewhere else) won't have any effect outside the function.

Q:
Is it legal to use const in this fashion?
    void f(int * const p);

A:
Yes. Putting const before p's type protects the object that p points to.
    Putting const after p's type protects p itself:
    void f(int * const p)
    {
        int j;

        *p = 0;     /* legal */
        p = &j;     /*** WRONG ***/
    }
This feature is not used very often. Since p is merely a copy of another
    pointer (the argument when the function is called), there's rarely any
    reason to protect it.
Even rarer is the need to protect both p and the object it points to:
    void f(const int * const p)
    {
        int j;

        *p = 0;     /*** WRONG ***/
        p = &j;     /*** WRONG ***/
    }
