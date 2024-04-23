/***                         INTEGER TYPES                           ***/

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

short int	//short signed int
unsigned short int	//unsigned short
int
unsigned int
long int	//long
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

//                         INTEGER CONSTANTS

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


