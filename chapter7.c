/*** CHAPTER                       7.1                        INTEGER TYPES ***/

C supports two fundamentally different numeric types: integer and floating
integer type values are whole numbers
floating type values can have a fractional part
integer types are divided into two categories: signed and unsigned
a sign bit is the leftmost bit of a signed integer
a sign bit is 0 if the number is positive or zero, 1 if it is negative
thus the largest 16-bit integer that binary can represent is 32,767 (2e15 - 1)
in binary: 0111111111111111
the largest 32-bit integer is 2,147,483,647 (2e31 - 1)
in binary: 01111111111111111111111111111111
the largest unsigned 16-bit integer is 65,535 (2e16 - 1)
in binary: 1111111111111111
the largest unsigned 32-bit integer is 4,294,967,295 (2e32 - 1)
in binary: 11111111111111111111111111111111
by default, integer variables are signed
declaring a variable unsigned tells the compiler there is no sign bit

integer types come in different sizes
int type is usually 32-bits, but may be 16-bits on older compilers
we use long type when some numbers are too large to store in int
and short type when we need to conserve memory
C allows us to abbreviate by dropping int (some newer languages require this)

short int		//short signed int
unsigned short int	//unsigned short
int
unsigned int
long int		//long
unsigned long int	//unsigned long

values for these types vary by machine, though there are rules compilers must
    follow
short int, int, and long int must cover a minimum range of values
int must not be shorter than short int
long int must not be shorter than int
short int may represent the same values as int
int may have the same range as long int
the limits.h header defines macros which represent the smallest and largest
    values of each integer type

//                          INTEGER TYPES IN C99

C99 also provides long long int and unsigned long long int
these types are required to be at least 64-bits wide
standard signed integer types:
    short int, int, long int, long long int, signed char
standard unsigned integer types:
    unsigned short int, unsigned int, unsigned long int, unsigned long long
    int, unsigned char, _Bool
C99 also allows "extended integer types", both signed and unsigned (128-bit)

//                          INTEGER CONSTANTS

constants are numbers that appear in the program, not numbers that are read,
    written, or computed
constants can be written in decimal (base 10), octal (base 8), or hexadecimal
    (base 16)
237 in octal: (2 x 8e2) + (3 x 8e1) + (7 x 8e0) = 128 + 24 + 7 = 159
1AF in hex: (1 x 16e2) + (10 x 16e1) + (15 x 16e0) = 256 + 160 + 15 = 431

decimals constants contain digits 0 through 9, but must not begin with a 0: 15,
    255, 32767
octal constants use digits 0 to 7, and must begin with a 0: 017, 0377, 077777
hexadecimal constants contain digits 0 through 9 and letters between a and f,
    and always start with 0x: 0xf, 0xff, 0x7fff
all letters in hexadecimal format may be upper or lower case: 0xff, 0xfF, 0xFF,
    0Xff, 0XFf, 0XFF
these are just alternative ways of writing numbers and have no effect on how
    the numbers are stored (integers are always stored in binary)
you can mix notations: 10 + 015 + 0x20 has the value 55 (decimal)
octal and hex are generally used more for writing low-level programs
the type of a decimal integer constant is normally int
if a value is too large, the compiler will try long int, then unsigned long int
for octal or hex, the compiler will progress as follows: int, unsigned int,
    long int, then unsigned long int
to force the compiler to treat a constant as a long integer, follow it with the
    letter L (or l): 15L 0377l 0x7fffL
for unsigned, U or u: 15U 0377U 0x7fffu
0xffffffffUL, 0377lu

//                          INTEGER CONSTANTS IN C99

for long long, LL or ll
can also add U or u before or after LL or ll
without a suffix, the type will be the "smallest" type that can represent the
    value of a constant between int, long int, and long long int
for octal or hex, the list goes in this order: int, unsigned int, long int,
    unsigned long int, long long int, unsigned long long int
any suffix at the end of a constant forces that type
a constant using U must be an unsigned int, unsigned long int, or unsigned long
    long int
a decimal constant using L must be long int or long long int

//                          INTEGER OVERFLOW

its possible that the result of an arithmetic operation can be too large to
    represent
for example, if an arithmetic operation is performed on two int values, and the
    resulting value cannot be represented as an int (due to too many bits),
    then it is said that "overflow" has occurred
overflow occuring with signed operands results in undefined behavior (either a
    wrong result, to even a program crash)
when overlow occurs on unsigned integers, the result is defined: take the
    correct answer modulo 2e^n, where n is the number of bits used to store the
    result
1 + 65,535U = 0

//                          READING AND WRITING INTEGERS

%d only works for int type variables
when reading or writing unsigned integers, use u (unsigned decimal), o, or x

unsigned int u;

scanf("%u", &u);    /* reads  u in base 10 */
printf("%u", u);    /* writes u in base 10 */
scanf("%o", &u);    /* reads  u in base 8 */
printf("%o", u);    /* writes u in base 8 */
scanf("%x", &u);    /* reads  u in base 16 */
printf("%x", u);    /* writes u in base 16 */

for a short integer, put an h in front of d, o, u, or x

short s;

scanf("%hd", &s);
printf("%hd", s);

for a long integer, put l in front of d, o, u, or x

long l;

scanf("%ld", &l);
printf("%ld", l);

for a long long integer (C99), put ll in front of d, o, u, or x

long long ll;

scanf("%lld", &ll);
printf("%lld", ll);

//                         sum2.c -  SUMMING A SERIES OF NUMBERS (REVISITED)

the program from section 6.1 could experience overflow through user input

#include <stdio.h>

int main(void)
{
	long n, sum = 0;

	printf("This program sums a series of integers.\n");
	printf("Enter integers (0 to terminate): ");

	scanf("%ld", &n);
	while (n != 0) {
		sum += n;
		scanf("%ld", &n);
	}
	printf("The sum is : %ld\n", sum);

	return 0;
}

/*** CHAPTER                       7.2                       FLOATING TYPES ***/

floating point types can store numbers with digits after the decimal point,
    or numbers that are exceedingly large or small
there are three floating types:
float - single-precision floating-point
double - double-precision floating-point
long double - extended-precision floating-point
float is suitable when the amount of precision isn't critical (calculating
    temperature to one decimal point)
double provides greater accuracy
long double is extremely accurate ("rarely" used)
C standard doesn't state the precision that float, double, and long double need
    to provide

//			    THE IEEE FLOATING-POINT STANDARD

most computers follow IEEE Standard specifications for floating-point numbers
numbers are stored in three parts: a sign, an exponent, and a fraction
the number of bits in the exponent determines how large or small numbers can be
the number of bits in the fraction determines the precision
in single-precision, the exponent is 8 bits long and the fraction is 23 bits
as a result, a single-precision number has a max value of about 3.40 x 10e38,
    with a precision of about 6 decimal digits
a double-precision numbers has a max value of about 1.79 x 10e308, with a
    precision of about 15 decimal digits
the IEEE standard also describes single extended precision and double extended
    precision formats
it doesn't specify the number of bits in these formats, although it requires
    single extended type occupy at least 43 bits, and double extended type at
    least 79 bits
not all machines follow IEEE standards
you can use macros that define the characteristics of floating types found in
    the <float.h> header
in C99, floating types are divided into two categories:
real floating types - float, double, long double
complex types - float _Complex, double _Complex, long double _Complex

//                          FLOATING CONSTANTS

floating constants can be written in a variety of ways:
57.0  57.  57.0e0  57E0  5.7e1  5.7e+1  .57e2  570.e-1
floating constants are stored as double-precision numbers by default
double values are converted automatically to float when necessary
to force indicate that single precision is required, put f at the end of the
    constant (57.0F)
to indicate long double, put l at the end (57.0L)
C99 provides for writing floating constants in hexadecimal
these constants begin with 0x or 0X ("rarely used")

//                                    READING AND WRITING FLOATING-POINT NUMBERS

%e, %f, and %g are used for single-precision floating point numbers
values of types double and long double require different conversions
when reading (not writing) a value of type double, put l in front of e, f, or g

double d;

scanf("%lf", &d);

when using printf, the e, f, and g conversions can be used to write either
    float or double values (C99 legalizes %le, %lf, and %lg, although the l has
    no effect)
when reading or writing a value of type long double, put an L (no lowercase) in
    front of e, f, or g

long double ld;

scanf("%Lf", &ld);
printf("%Lf", ld);

/*** CHAPTER                      7.3                       CHARACTER TYPES ***/


