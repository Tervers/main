/*** CHAPTER                      7.1                        INTEGER TYPES ***/

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
the <limits.h> header defines macros which represent the smallest and largest
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

//                          sum2.c -  SUMMING A SERIES OF NUMBERS (REVISITED)

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

/*** CHAPTER                       7.2                      FLOATING TYPES ***/

floating point types can store numbers with digits after the decimal point,
    or numbers that are exceedingly large or small
there are three floating types:
float - single-precision floating-point
double - double-precision floating-point
long double - extended-precision floating-point
float is suitable when the amount of precision is not critical (calculating
    temperature to one decimal point)
double provides greater accuracy
long double is extremely accurate ("rarely" used)
C standard does not state the precision that float, double, and long double
    need to provide

//                          THE IEEE FLOATING-POINT STANDARD

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
it does not specify the number of bits in these formats, although it requires
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

//                          READING AND WRITING FLOATING-POINT NUMBERS

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

/*** CHAPTER                      7.3                      CHARACTER TYPES ***/

char is the character type
the value of type char varies because different machines may have different
    underlying character sets
ASCII is a common character set
a variable of type char can be assigned any single character

char ch;

ch = 'a';       /* lower-case a */
ch = 'A';       /* upper-case A */
ch = '0';       /* zero         */
ch = ' ';       /* space        */

//                          OPERATIONS ON CHARACTERS

C treats characters as small integers
ASCII character codes range from 0000000 to 1111111, which we can think of as
    the integers from 0 to 127
'a' has the value 97; 'A' has the value 65; '0' is 48; ' ' is 32
character constants actually have int type rather than char type (although this
    will often not matter to us)
when a character appears, C simply uses its integer value

char ch;
int i;

i = 'a';        /*  i is now 97  */
ch = 65;        /* ch is now 'A' */
ch = ch + 1;    /* ch is now 'B' */
ch++;           /* ch is now 'C' */

characters can be compared
this if statement checks whether ch contains a lower-case letter and, if so,
    converts ch to upper case

if ('a' <= ch && ch <= 'z')
  ch = ch - 'a' + 'A';

we can also write a for statement whose control variable steps through all the
    upper-case letters

for (ch = 'A'; ch <= 'Z'; ch++)

these types of programs can hamper portability due assumptions about the under-
    lying character set (like assuming A to Z have consecutive codes)

//                          SIGNED AND UNSIGNED CHARACTERS

signed characters normally have values between -128 and 127
unsigned characters normally have values between 0 and 255
C standard does not specify whether char is a signed or an unsigned type
C89 uses the term "integral types" to refer to both integer types and character
    types
enumerated types are also integral types
C99 does not use integral types; C99 expands the meaning of "integer types" to
    include character types and enumerated types
C99s _Bool type is considered to be an unsigned integer type

//                          ARITHMETIC TYPES

C89 arithmetic types hierarchy:
integral types -
    char ; signed integer types ; unsigned integer types ; enumerated types
floating types

C99 arithmetic types hierarchy:
integer types -
    char ; signed integer types, both standard and extended ; unsigned integer
    types, both standard and extended ; enumerated types
floating types -
    real floating types ; complex types

//                          ESCAPE SEQUENCES

a character constant is usually one character enclosed in single quotes
some special characters cannot be written this way because they are "invisible"
    (new-line character) or because they cannot be entered from the keyboard
an escape sequence is a special notation provided by C
two types of escape sequences: character escapes and numeric escapes

character escapes: /a alert, \b backspace, \f form feed, \n new line, \r
    carriage return, \t horizontal tab, \v vertical tab, \\ backslash, \?
    question mark, \' single quote', \" double quote"
character escapes do not include all non-printing ASCII characters
character escapes are also useless for representing characters beyond the basic
    128 ASCII characters

numeric escapes, which can represent any character, can solve this problem
to write a numeric escape, look up the characters octal or hex value
for example, the ASCII escape character (decimal value: 27) has the value 33 in
    octal and 1B in hex
an octal escape sequence consists of the \ character followed by an octal
    number with at most three digits (must be representable as an unsigned
    char, so maximum value is normally 377 octal)
octal numbers in escape sequences do not have to begin with 0, so the escape
    character could be written \33 or \033
a hexadecimal escape sequence consists of \x followed by a hexadecimal number
the hex number must be representable as an unsigned character (hence it cannot
    exceed FF if characters are eight bits long)
the x must be lower case, but hex digits can be upper or lower case: \x1b, \x1B

when used as a character constant, an escape sequence must be enclosed in
    single quotes: '\33', '\x1B'
escape sequences can appear a bit cryptic, so its a good idea to give them
    names using #define:
#define ESC '/33'   /* ASCII escape character */
trigraph sequences provide a way to represent the characters #, [, \, ], ^, {,
    |, }, and ~
C99 adds universal character names, which resemble escape sequences
unlike escape sequences, universal character names are allowed in identifiers

//                          CHARACTER-HANDLING FUNCTIONS

there is a faster, and more portable, way to convert lower-case letters to
    upper-case using the C toupper library function:

ch = toupper(ch);       /* converts ch to upper case */

toupper checks whether its argument (ch) is lower case
if so, it returns the corresponding upper-case letter
if not, it returns the value of the argument
you can also test it in an if statement:

if (toupper(ch) == 'A') ...

programs need to #include <ctype.h> to make use of toupper

//                        READING AND WRITING CHARACTERS USING scanf AND printf

the %c conversion specification allows scanf and printf to read and write
    single characters:

char ch;

scanf("%c", &ch);   /* reads a single character */
printf("%c", ch);   /* writes a single character */

scanf does not skip white-space characters before reading a character
if the next unread character is a space, then variable ch will contain a space
    after scanf returns
to force scanf to skip white space before reading a character, put a space in
    its format string just before %c:

scanf(" %c", &ch);      /* skips white space, then reads ch */

a space in a scanf string still means skip zero or more white-space characters
since scanf does not normally skip white space, you can easily detect the end
    of an input line
the following loop will read and ignore all remaining characters in the current
    input line:

do {
    scanf("%c", &ch);
} while (ch != '\n');

when scanf is called the next time, it will read the first character on the
    next input line

//                     READING AND WRITING CHARACTERS USING getchar AND putchar

C provides other ways of writing single characters, particularly getchar and
    putchar
putchar writes a single character:

putchar(ch);

each time getchar is called, it reads one character, which it returns
to save this character, we must use assignment to store it in a variable

ch = getchar();     /* reads a character and stores it in ch */\

getchar actually returns an int value
as a result, it is not unusual for a variable to have type int rather than char
getchar does not skip white-space characters as it reads
getchar and putchar save time (compared to scanf and printf) when a program is
    executed
this is because scanf and printf are designed to read and write many kinds of
    data in a variety of formats
getchar and putchar are usually implemented as macros for additional speed
the previous scanf loop can be rewritten using getchar:

do {
    ch = getchar();
} while (ch != '\n');

you can also use getchar in a controlling expression

while ((ch = getchar()) != '\n')
    ;

this loop reads a character, stores it into ch, then tests if ch is not equal
    to the new-line character
if successful, the (empty) loop body is executed, and the loop is tested again
further condensation of the loop:

while (getchar() != '\n')       /* skips rest of line */

you can use getchar to skip an indefinite number of blank characters:

while ((ch = getchar()) == ' ')     /* skips blanks */
    ;

when the loop terminates, ch will contain the first nonblank character that
    getchar encountered
be careful when mixing getchar and scanf calls in the same program
scanf can leave behind characters that it has looked at, but not read:

printf("Enter an integer: ");
scanf("%d", &i);
printf("Enter a command: ");
command = getchar();

after entering an integer, a user hitting the enter button will leave a new-
    line character, which getchar will fetch

//                          DETERMINING THE LENGTH OF A MESSAGE

this next program will calculate the length of a message, displaying this
    prompt:

Enter a message : _Brevity is the soul of wit._
Your message was 27 character(s) long.

the length includes spaces and punctuation, but not the new-line character at
    the end of the message

//                          length.c

#include <stdio.h>

int main(void)
{
    char ch;
    int len = 0;

    printf("Enter a message: ");
    ch = getchar();
    while (ch != '\n') {
        len++;
        ch = getchar ();

    }
    printf("Your message was %d character(s) long.\n", len);

    return 0;
}

we can shorten this program with some idioms involving while loops and getchar

//                          length2.c

#include <stdio.h>

int main(void)
{
    int len = 0;

    printf("Enter a message: ");
    while (getchar() != '\n')
        len++;
    printf("Your message was %d character(s) long.\n", len);

    return 0;
}

/*** CHAPTER                      7.4                      TYPE CONVERSION ***/

when performing arithmetic operations, computers usually require operands to be
    the same number of bits and be stored in the same way (they may be able to
    add two 16-bit integers, but not a 16-bit and a 32-bit together, or a 32-
    bit integer and 32-bit float)
C allows basic types to be mixed in expressions
the C compiler may then have to generate instructions that convert operands to
    other types so the computer can evaluate the expression (if you add a 16-
    bit short and a 32-bit int, the compiler will convert the short to 32-bits)
since these conversions are produced by the compiler and not the programmer,
    they are known as "implicit conversions"
if you want to perform an "explicit conversion", you can use the cast operator
implicit conversions occur during these situations:

- when the operands in an arithmetic or logical expression do not have the same
    type ("usual arithmetic conversions")
- when the type of expression on the right side of an assignment does not match
    the type of variable on the left side
- when the type of argument in a function call does not match the type of the
    corresponding parameter
- when the type of the expression in a return statement does not match the
    functions return type

//                          THE USUAL ARITHMETIC CONVERSIONS

the usual arithmetic conversions are applied to most binary operators,
    including arithmetic, relational, and equality operators
an integer can always be converted to float, as the worst that can happen is a
    minor loss in precision
as for converting float to int, this will delete the fractional part of the
    number, and potentially give us a meaningless result if the original number
    were larger (or smaller) than the largest (or smallest) possible integer
usual arithmetic conversions convert operands to the narrowest (fewer storage
    bytes) type that will safely hold both values
the type of the narrower operand can be made to match the type of the other
    operand ("promotion")
among the most common promotions are "integral promotions" (converts char or
    short to int (sometimes to unsigned int))
the rules for performing the usual arithmetic conversions can be split into two
    cases:

1 - the type of either operand is a floating type
  float -> double -> long double
    if one operand has type long double, then convert the other type to long
        double
    if one operand has type double, then convert the other to double
    if one is float, convert to float
    if one is long int, and the other is double, convert long int to double

2 - neither operand is a floating type
    first perform integral promotion on both operands (so that neither operand
        is a char or short)
  int -> unsigned int -> long int -> unsigned long int
    if one operand is unsigned long int, convert the other to unsigned long int
    ...
    if one operand has type long, and the other unsigned (say, both 32-bit),
        both converted to unsigned long

when a signed is combined with unsigned, the signed is converted to unsigned
the conversion involves adding or subtracting a multiple of n + 1, where n is
    the largest representable value of the unsigned type
suppose int i has value -10
and unsigned int u has value 10
we might assume i < u is 1 (true)
however, i was converted to unsigned int, and -10 became 4,294,967,286
    (assuming 4,294,967,295(n) is the largest unsigned int, n + 1)
therefore i < u is 0
best practice to use unsigned integers as little as possible, and never mix
    them with signed integers

char c;
short in s;
int i;
unsigned int u;
long int l;
unsigned long int ul;
float f;
double d;
long double ld;

i = i + c;	/* c is converted to int		*/
i = i + s;	/* s is converted to int		*/
u = u + i;	/* i is converted to unsigned int	*/
l = l + u;	/* u is converted to long int		*/
ul = ul + l;	/* l is converted to unsigned long int	*/
f = f + ul;	/* ul is converted to float		*/
d = d + f;	/* f is converted to double		*/
ld = ld + d;	/* d is converted to long double	*/

//			    CONVERSION DURING ASSIGNMENT

expressions on the right side of assignment are converted to the type on the
    left side

char c;
int i;
float f;
double d;

i = c;	/* c converted to int */
f = i;	/* i converted to float */
d = f;	/* f converted to double */

assigning floating point numbers to an integer variable drops the fractional
    part of the number

int i;

i = 842.97;	/* i is now 842 */
i = -842.97;	/* i is now -842 */

assigning a value to a variable of narrower type will give a meaningless result
    (or worse) if the value is outside the range of the variables type

c = 10000;	/*** WRONG ***/
i = 1.0e20;	/*** WRONG ***/
f = 1.0e100;	/*** WRONG ***/

it is ideal to append f (3.14159f) to floating point constants if they will be
    assigned to a float variable, otherwise a constant (3.14159) will have type
    double

//			    IMPLICIT CONVERSIONS IN C99

C99 rules for implicit conversion are slightly different due to the additional
    types it introduces
C99 gives each integer type an "integer conversion rank" //rank ~= size

1. long long int, unsigned long long int
2. long int, unsigned long int
3. int, unsigned int
4. short int, unsigned short int
5. char, signed char, unsigned char
6. _Bool
(extended integer and enumerated types are ignored for now)

C99 has "integer promotions" which convert any type whose rank is less than int
    and unsigned int to int (if the value can be represented as int) or
    unsigned int
C99s rules for usual arithmetic conversions are also divided into two cases:

1 - the type of either operand is a floating type
    as long as neither operand has a complex type, the rules are the same as
        before

2 - neither operand is a floating type
    first perform integer promotion on both operands
    if the types of both operands are the same, the process ends
    otherwise, follow these rules, stopping at the first rule that applies:
        if the operands are both signed or both unsigned, convert the type with
            lesser rank to the type with higher rank
        if the unsigned operand has rank greater than or equal to the signed
            operand, convert the signed to unsigned
        if the signed operand can represent all values of the unsigned operand,
            convert the unsigned to signed
        otherwise convert both operands to the unsigned type corresponding to
            the type of the signed operand

arithmetic types can be converted to _Bool
the result of the conversion is 0 if the original value is 0, otherwise it is 1

//                          CASTING

( type-name ) expression
type-name specifies what type the expression should be converted to
this example shows how to use a a cast expression to compute the fractional
    part of a float:

float f, frac_part;

frac_part = f - (int) f;

(int) f represents the value of converting f to type int
usual arithmetic conversion will convert (int) f back to type float before
    subtraction is performed
the difference between f and (int) f is the fractional part of f, which was
    dropped during the cast
you can document type conversions that would occur anyways:

i = (int) f;    /* f is converted to int */

cast allows us to overrule the compiler and force conversions that we want
{
float quotient;
int dividend, divisor;

quotient = dividend / divisor;
}
in the above program, the result of the division (an integer), will be
    converted to float before being stored in quotient
ideally we would convert them to float before division for a more exact answer

quotient = (float) dividend / divisor;

casting dividend to float forces the compiler to convert divisor to float also
cast is a unary operator, which have higher precedence than binary operators

(float) dividend / divisor  ==  ((float) dividend) / divisor
quotient = dividend / (float) divisor;
quotient = (float) dividend / (float) divisor;

casts are sometimes necessary to avoid overflow

long i;
int j = 1000;

i = j * j;  /* overflow may occur */

j * j is 1,000,000, and i is a long, but two int values multiplied will result
    in an int
j * j might be too large to represent int on some machines

i = (long) j * j;   //first j converted to long, forcing second j to convert
i = (long) (j * j); /*** WRONG ***/ //overflow would occur before cast

/*** CHAPTER                     7.5                      TYPE DEFINITIONS ***/

in section 5.2 we created a macro to define a boolean type

#define BOOL int

alternatively with "type definition":

typedef int Bool;   //capitalizing type name is not required

this adds Bool to the list of type names that the compiler will recognize
Bool can now be used in variable declarations, cast expressions, etc.

Bool flag;  /* same as int flag; */

the compiler treats Bool as a synonym for int, thus flag is just an int

//                          ADVANTAGES OF TYPE DEFINITIONS

#define BOOL int

typedef int Bool;   //capitalizing Bool is not required

using typedef to define Bool causes the compiler to add Bool to the list of
    type names it recognizes
this allows Bool to be used in variable declarations, cast expresssions, etc.

Bool flag;  /* same as int flag; */

the compiler treats Bool as int; thus flag is also an int variable

//                          ADVANTAGES OF TYPE DEFINITIONS

type definitions can make a program more understandable

typedef float Dollars;

Dollars cash_in, cash_out;

is more informative than just writing:

float cash_in, cash_out;

type definitions also make a program easier to modify (if we later decide to
    change Dollars to double)

    typedef double Dollars;

this would prevent the need to change variable declarations of Dollars (we
    would need to locate all float variables that only store dollar amounts)

//                          TYPE DEFINITIONS AND PORTABILITY

one problem with porting a program from one computer to another is that types
    have different ranges on different machines

int i;
i = 100000;

this is fine on a 32-bit machine, but will fail on a 16-bit machine
suppose we need variables capable of storing product quanities in the range of
    0-50000
we could use long, but we would rather use int, since arithmetic on int may be
    faster than on long, and also int may take up less space
instead of using int type to declare quantity variables, we can define our own
    "quantity" type

 typedef int Quantity;  //use this type to declare variables
 Quantity q;

 when we port the program to a machine with shorter integers, we will update
     the definition of Quantity:

typedef long Quantity;

while this helps portability, this does not fix other ways Quantity variables
    may be being used (calls of printf and scanf will need their conversion
    specifiers (%d to %ld) updated)
the C library itself uses typedef to create names for types that vary from one
    C implementation to another (these types often end with _t, such as size_t,
    wchar_t, and ptrdiff_t)
the exact definitions of these types vary, but here are some examples:

typedef long int ptrdiff_t;
typedef unsigned long int size_t;
typedef int wchar_t;

in C99, <stdint.h> uses typedef to define names for integer types with a
    particular number of bits (int32_t is a signed integer type with exactly
    32-bits)
using these types is an effective way to make programs more portable

/*** CHAPTER                    7.6                    THE sizeof OPERATOR ***/

the sizeof operator allows programs to determine how much memory is required to    store values of a particular type

sizeof ( type-name )

the value the above expression produces is an unsigned integer representing the
    number of bytes required to store a value belonging to type-name
sizeof (char) is always 1
sizeof (int) is normally 4 on a 32-bit machine
sizeof is a unary operator
sizeof is unusual in that the compiler itself can usually determine the value
    of a sizeof expression
sizeof can also be applied to constants, variables, and expressions
if i and j are int variables, then sizeof (i) is 4 on a 32-bit machine
sizeof (i + j) is also 4
when applied to an expression, sizeof does not require parentheses (sizeof i)
they may still be necessary due to operator precedence
sizeof i + j would be read as (sizeof i) + j
the type of sizeof is size_t, which is an implementation-defined type
in C89, it ls best to convert the value of an expression to a known type
    before printing
size_t is guaranteed to be unsigned, so its safest to cast a sizeof expression
    to unsigned long (C89s largest unsigned type) then print using %lu

printf("Size of int: %lu\n", (unsigned long) sizeof(int));

in C99, size_t can be larger than unsigned long
printf in C99 is capable of displaying size_t values directly without a cast
    using the %z conversion specification (followed by the usual integer codes)

printf("Size of int: %zu\n", sizeof (int));

//			                ADDITIONAL NOTES

a hex constant begins with 0x or 0X
must contain an exponent, which is preceded by the letter P, or p
the exponent may have a sign
the constant may end with f, F, l, or L
the exponent is expressed in decimal and represents a power of 2 (not 10)
0x1.Bp3 represents 1.6875 x 2e3 = 13.5
hex digit B corresponds to the bit pattern 1011
the B is on the right of the period, so each 1 bit represents a negative power:
1      0      1      1
2e-1 + 0    + 2e-3 + 2e-4 = 0.6875
hex numbers have a precise binary representation, whereas decimal constants may
    be subject to tiny rounding errors

printf and scanf have variable-length argument lists
when variable-length argument lists are called, the compiler converts float
    arguments to double automatically
this causes printf to be unable to distinguish between float and double
    arguments, which is why %f works for both float and double in printf
scanf is passed a pointer to a variable
%f tells scanf to store a float at the address passed to it
%lf tells scanf to store a double at that address
scanf will likely store the wrong number of bytes if given the wrong conversion
    specification

if a variable is given a value that is too large, various outcomes may occur
if the value is of an integral type and the variable is unsigned, then the
    extra bits are thrown away; if the variable is signed, the result is
    implementation defined
assigning a float to a variable that is too small produces undefined behavior

type definitions are more powerful than macro definitions
macros cannot define array or pointer types
suppose we try to create a macro to define a "pointer to integer" type:

#define PTR_TO_INT int *

the declaration

PTR_TO_INT p, q, r;

will become

int * p, q, r;

after preprocessing
this results in only p being a pointer; q and r are ordinary integer variables
typedef names are subject to the same scope rules as variables
macro names are replaced by the preprocessor wherever they appear (no scope)

/*** CHAPTER                          7                          EXERCISES ***/

1. Give the decimal value of each of the following integer constants.

(a) 077         //63
(b) 0x77        //119
(c) 0XABC       //2748

2. Which of the following are not legal constants in C? Classify each legal
     constant as either integer or floating-point.

(a) 010E2       //64            /*** 1000; exponent indicates decimal form ***/
(b) 32.1E+5     //3210000 float
(c) 0790        //632 integer   /*** not legal; octal contains digits 0-7 ***/
(d) 100_000     //not legal
(e) 3.978e-2    //0.03987 float

3. Which of the following are not legal types in C?

(a) short unsigned int  //legal
(b) short float         //not legal
(c) long double         //legal
(d) unsigned long       //legal

4. If c is a variable of type char, which one of the following statements is
     illegal?

(a) i += c;  /* i has type int */   //legal
(b) c = 2 * c - 1;                  //legal
(c) putchar(c);                     //legal
(d) printf(c);                      //not legal

5. Which one of the following is not a legal way to write the number 65? Assume
     that the character set is ASCII.

(a) 'A'         //legal
(b) 0b1000001   //legal  // not legal; C does not allow binary representation
(c) 0101        //not legal, ASCII binary codes ranged from 000000 to 1111111
                /*** legal; it is in octal, you dummy ***/
(d) 0x41        //legal

6. For each of the following items of data, specify which one of the types
     char, short, int, or long is the smallest one guaranteed to be large
     enough to store the item.

(a) Days in a month     //char
(b) Days in a year      //short
(c) Minutes in a day    //short
(d) Seconds in a day    //int   /*** long ***/

7. For each of the following character escapes, give the equivalent octal
     escape. Assume the character set is ASCII.

(a) /b  // \10
(b) /n  // \12
(c) /r  // \15
(d) /t  // \11

8. Repeat Exercise 7, but give the equivalent hexadecimal escape.

(a) /b  // \x08
(b) /n  // \x0a
(c) /r  // \x0d
(d) /t  // \x09

9. Suppose that i and j are variables of type int. What is the type of the
     expression i / j + 'a'?

int, as char is already actually an int type

10. Suppose that i is a variable of type int, j is a variable of type long, and
     k is a variable of type unsigned int. What is the type of the expression
     i + (int) j * k?

j is cast as an int type, leaving only int and unsigned int variables. The
     usual arithmetic operations will convert int variables to unsigned int.

11. Suppose that i is a variable of type int, f is a variable of type float,
     and d is a variable of type double. What is the type of the expression
     i * f / d?

The type of the expression will be a double.

12. Suppose that i is a variable of type int, f is a variable of type float,
     and d is a variable of type double. Explain what conversions take place
     during the following statement:  d = i + f;


Usual arithmetic conversions will convert operands to the narrowest type that
     will hold both values. i will be converted to float so that i + f will
     not be truncated. d will then hold the value of i + f, but will stay a
     double type as the type on the right side of assignment will become the
     type on the left side.

13. Assume that a program contains the following declarations:
    char c = '\1';  //numeric escape using octal (0 not required in escape)
    short s = 2;
    int i = -3;
    long m = 5;
    float f = 6.5f;
    double d = 7.5;
    Give the value and the type of each expression listed below.

(a) c * i   // -3 int
(b) s + m   // 7 long
(c) f / c   // 6.5f float
(d) d / s   // 3.75 double
(e) f - d   // -1.0 double
(f) (int) f // 6 int

14. Does the following statement always compute the fractional part of f
     correctly (assuming that f and frac_part are float variables)?

     frac_part = f - (int) f;

     if not, what is the problem?

If f is negative, frac_part will also be negative, but the digits will be
     correct.   /*** integer overflow may occur if f is too large for int to
     support ***/   //if overflow happens with signed integers, the programs
     //behavior is undefined. if unsigned, we get the answer modulo 2e^n, where
     //n is the number of storage bits

15. Use typedef to create types named Int8, Int16, and Int32. Define the types
     so that they represent 8-bit, 16-bit, and 32-bit integers on your machine.

#typedef short Int8     /*** char holds 8-bits ***/
#typedef int Int16      /*** short ***/
#typedef long Int32     /*** int ***/

/*** CHAPTER                    7                     PROGRAMMING PROJECTS ***/

1. Run square2.c and determine the smallest value of n that causes failure. Try
     changing the type of i to short and run the program again. Then try long.
     What can you conclude about the number of bits used to store integer types
     on your machine?

n = 46341 is the smallest value that causes an error. As a short, n = 182. As a
     long, n = 46341. As an int and a long, the program begins to fail once the
     calculated value attempts to surpass 2,147,483,647, hence int and long are
     32-bit types on my machine. As a short, the program fails once the value
     attempts to go above 32,767, hence short is a 16-bit type on my machine.

2. Modify square2.c so that it pauses after every 24 squares and displays the
     following message: "Press Enter to continue...". The program should use
     getchar to read a character. getchar will not allow the program to
     continue until the user presses the Enter key.

#include <stdio.h>

int main(void)
{
    char c;
    short i, n;

    printf("This program prints a table of squares.\n");
    printf("Enter number of entries in table: ");
    scanf("%d", &n);
    getchar();

    for (i = 1; i <= n; i++) {
        printf("%10hd%10hd\n", i, i * i);
        if (i % 24 == 0) {
            printf("Press Enter to continue...\n");
            do {                    //unnecessary line
                putchar(c);         //unnecessary line
            } while (getchar() != '\n');
        }
    }

    return 0;
}

3. Modify sum2.c to sum a series of double values.

#include <stdio.h>

int main(void)
{
	double n, sum = 0;

	printf("This program sums numbers.\n");
	printf("Enter numbers (0 to terminate): ");

	scanf("%lf", &n);
	while (n != 0) {
		sum += n;
		scanf("%lf", &n);
	}
	printf("The sum is : %f\n", sum);

	return 0;
}

4. Write a program that translates an alphabetic phone number into numeric
     form: "Enter phone number: _CALLATT_\n2255288". If the original phone
     number contains nonalphabetic characters, leave them unchanged: "Enter
     phone number: _1-800-COL-LECT_\n1-800-265-5328". You may assume that any
     letters entered by the user are upper case.

#include <stdio.h>
#include <ctype.h>

int main(void)
{
	char c;

	printf("Enter phone number: ");

	for (;;) {
        scanf("%c", &c);
        c = toupper(c);

        if (c >= '0' && c <= '9')
            putchar(c);

        else if (c == '-')
            putchar(c);

        else if (toupper(c) >= 'A' && toupper(c) <= 'Z')
            switch (c) {
                case 'A': case 'B': case 'C':
                        printf("2");
                        break;
                case 'D': case 'E': case 'F':
                        printf("3");
                        break;
                case 'G': case 'H': case 'I':
                        printf("4");
                        break;
                case 'J': case 'K': case 'L':
                        printf("5");
                        break;
                case 'M': case 'N': case 'O':
                        printf("6");
                        break;
                case 'P': case 'Q': case 'R': case 'S':
                        printf("7");
                        break;
                case 'T': case 'U': case 'V':
                        printf("8");
                        break;
                case 'W': case 'X': case 'Y': case 'Z':
                        printf("9");
                        break;
                }

        else if (c == '\n')
            break;

        else
            continue;
	}
	return 0;
}

5. Write a program that computes the value of a SCRABBLE word by summing the
     face values of its letters. (Face values: 1: AEILNORSTU 2: DG 3: BCMP
     4: FHVWY 5: K 8: JX 10: QZ)

#include <stdio.h>
#include <ctype.h>

int main(void)
{
	char l;     //letter value
    short w;    //word value

	printf("Enter a word: ");

    for (;;) {
        scanf("%c", &l);
        l = toupper(l);

        if (l >= 'A' && l <= 'Z')
            switch (l) {
                case 'A': case 'E': case 'I': case 'L': case 'N':
                case 'O': case 'R': case 'S': case 'T': case 'U':
                    w += 1;
                    break;
                case 'D': case 'G':
                    w += 2;
                    break;
                case 'B': case 'C': case 'M': case 'P':
                    w += 3;
                    break;
                case 'F': case 'H': case 'V': case 'W': case 'Y':
                    w += 4;
                    break;
                case 'K':
                    w += 5;
                    break;
                case 'J': case 'X':
                    w += 8;
                    break;
                case 'Q': case 'Z':
                    w += 10;
                    break;
        }

        else if (l == '\n')
            break;
    }

    printf("Scrabble value: %hd", w);

	return 0;
}

6. Write a program that prints the values of sizeof(int), sizeof(short),
     sizeof(long), sizeof(float), sizeof(double), and sizeof(long double).

#include <stdio.h>

int main()
{
    /***                                C89                                ***/
    printf("Size of char: %hu\n", (unsigned char) sizeof(char));
    printf("Size of short: %hu\n", (unsigned char) sizeof(short));
    printf("Size of int: %hu\n", (unsigned char) sizeof(int));
    printf("Size of long: %hu\n", (unsigned char) sizeof(long));
    printf("Size of float: %hu\n", (unsigned char) sizeof(float));
    printf("Size of double: %hu\n", (unsigned char) sizeof(double));
    printf("Size of long double: %hu\n\n", (unsigned char) sizeof(long double));

    /***                                C99                                ***/
    printf("Size of char: %zu\n", sizeof (char));
    printf("Size of short: %zu\n", sizeof (short));
    printf("Size of int: %zu\n", sizeof (int));
    printf("Size of long: %zu\n", sizeof (long));
    printf("Size of float: %zu\n", sizeof (float));
    printf("Size of double: %zu\n", sizeof (double));
    printf("Size of long double: %zu\n", sizeof (long double));

    return 0;
}

7. Modify Chapter 3, Project 6 so that the user may add, subtract, multiply, or
     divide two fractions (by entering either +, -, *, or / between fractions)

#include <stdio.h>

int main(void)
{
    char op;        //operator
    int num1, denom1, num2, denom2, result_num, result_denom;  //numerator

    printf("Enter two fractions to calculate with +, -, *, or /: ");
    scanf("%d/%d %c %d/%d", &num1, &denom1, &op, &num2, &denom2);

    switch (op) {
        case '+':
            result_num = num1 * denom2 + num2 * denom1;
            result_denom = denom1 * denom2;
            printf("The sum is %d/%d\n", result_num, result_denom);
            break;
        case '-':
            result_num = num1 * denom2 - num2 * denom1;
            result_denom = denom1 * denom2;
            printf("The difference is %d/%d\n", result_num, result_denom);
            break;
        case '*':
            result_num = num1 * num2;
            result_denom = denom1 * denom2;
            printf("The product is %d/%d\n", result_num, result_denom);
            break;
        case '/':
            result_num = num1 * denom2;
            result_denom = denom1 * num1;
            printf("The quotient is %d/%d\n", result_num, result_denom);
            break;
    }

    return 0;
}

8. Modify Chapter 5, Project 8 so that the user enters a time using the 12-hour
     clock. The input will have the form "hours:minutes" followed by either A,
     P, AM, or PM. White space is allowed but not required.

#include <stdio.h>

int main(void)
{
    short uh, um, ct;      //users entered hours, user minutes: converted time
    char mer;                //meridiem

    printf("Enter a 12-hour time: ");
    scanf("%2hd:%2hd %c", &uh, &um, &mer);

    if (mer == 'P' || mer == 'p')
        ct = (((uh * 60) + um) + 720);
    else if (mer == 'A' || mer == 'a')
        ct = ((uh * 60) + um);
    else
        printf("Invalid time.\n");

    if (ct <= 531)
        printf("Closest departure time is 8:00 a.m. arriving at 10:16 a.m.\n");
    else if (ct >=532 && ct <= 630)
        printf("Closest departure time is 9:43 a.m. arriving at 11:52 a.m.\n");
    else if (ct >=631 && ct <= 722)
        printf("Closest departure time is 11:19 a.m. arriving at 1:31 p.m.\n");
    else if (ct >=723 && ct <= 803)
        printf("Closest departure time is 12:47 p.m. arriving at 3:00 p.m.\n");
    else if (ct >=804 && ct <= 892)
        printf("Closest departure time is 2:00 p.m. arriving at 4:08 p.m.\n");
    else if (ct >=893 && ct <= 1042)
        printf("Closest departure time is 3:45 p.m. arriving at 5:55 p.m.\n");
    else if (ct >=1043 && ct <= 1139)
        printf("Closest departure time is 7:00 p.m. arriving at 9:20 p.m.\n");
    else if (ct >=1139 && ct <= 1439)
        printf("Closest departure time is 9:45 p.m. arriving at 11:58 p.m.\n");
    else
        printf("Invalid time.\n");

    return 0;
}

9. Write a program that asks the user for a 12-hour time, then displays the
     time in 24-hour form.

#include <stdio.h>

int main(void)
{
    char mer;           //meridiem
    short uh, um, ch;   //users hours, user minutes, converted hours

    printf("Enter a 12-hour time: ");
    scanf("%hd:%hd %c", &uh, &um, &mer);

    if (mer == 'P' || mer == 'p')
        if (uh == 12)
            ch = (uh + 1);
        else
            ch = (uh + 12);
    else if (mer == 'A' || mer == 'a')
        ch = uh;
    else
        printf("Invalid time.\n");

    printf("Equivalent 24-hour time: %hd:%hd%\n", ch, um);

    return 0;
}

10. Write a program that counts the number of vowels in a sentence.

#include <stdio.h>
#include <ctype.h>

int main(void)
{
    char ch;           //character
    int vc = 0;        //vowel count

    printf("Enter a message: ");

    ch = getchar();
    while (ch != '\n') {
        ch = toupper(ch);
        if (ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U')
            vc++;
        ch = getchar();
    }

    printf("Your sentence contains %d vowels.\n", vc);

    return 0;
}

11. Write a program that takes a first name and last name entered by the user
     and displays the last name, a comma, and the first initial, followed by a
     period. The users input may contain extra spaces before the first name,
     between the first and last names, and after the last name.

#include <stdio.h>

int main(void)
{
    char ch, fn = 0, ln = 0;    //character, first name, last name

    printf("Enter a first and last name: ");

    while ((ch = getchar()) != '\n') {
        if (!fn && ch >= 'A' && ch <= 'Z') {
            fn = ch;
            }

        else if (fn && !ln && ch >= 'A' && ch <= 'Z') {
            ln = ch;
            putchar(ch);
            }

        else if (fn && ln)
            putchar(ch);

        else
            ch = getchar();
    }

    printf(", %c.\n", fn);

    return 0;
}

12. Write a program that evaluates an expression. The operands in the
     expression is evaluated from left to right (as in no operator precedence).

#include <stdio.h>

int main()
{
    float cv = 0.0f, no = 0.0f;   //current value, new operand
    char op;        //operator

    printf("Enter an expression: ");
    scanf("%f", &no);
    cv = no;

    while ((scanf("%c", &op))) {
        switch (op){
            case '+':
                scanf("%f", &no);
                cv += no;
                break;
            case '-':
                scanf("%f", &no);
                cv -= no;
                break;
            case '*':
                scanf("%f", &no);
                cv *= no;
                break;
            case '/':
                scanf("%f", &no);
                cv /= no;
                break;
            case '\n':
                printf("Value of expression: %f", cv);
                return 0;
        }
    }
}

13. Write a program that calculates the average word length for a sentence. For
     simplicity, your program should consider a punctuation mark to be part of
     the word to which it is attached. Display the average word length to one
     decimal place.

#include <stdio.h>

int main()
{
    char ch;                //character
    float lc, wc = 1.0f;    //letter count, word count

    printf("Enter a sentence: ");

    while ((scanf("%c", &ch))) {
        lc++;
        if (ch == ' ') {
            lc--;
            wc++;
        }
        if (ch == '\n') {
            lc--;
            printf("Average word length: %f\n", (lc / wc));
            return 0;
        }
    }
}

14. Write a program that uses Newtons method to compute the square root of a
     positive floating-point number. Let x be the number entered by the user.
     Newtons method requires an initial guess y for the square root of x (we
     will use y = 1). Successive guesses are found by computing the average of
     y and x/y. For greater accuracy, your program should use double rather
     than float. Have the program terminate when the absolute value of the
     difference between the old value of y and the new value of y is less than
     the product of .00001 and y.

#include <stdio.h>
#include <math.h>

int main()
{
    int x;              //positive number
    double y = 1.0f, xy = 1.0f, oy, avg; //y, xy, old y, average of y and x/y

    printf("Enter a positive number: ");
    scanf("%d", &x);

    for (;;) {
        xy = (x / y);
        avg = ((y + (x / y)) / 2);
        y = avg;

        if ((fabs(avg - xy) < fabs(0.00001f * y))) {
            printf("Square root: %lf\n", y);
            return 0;
        }
    }
}

15. Write a program that computes the factorial of a positive integer.
    (a) Use a short to store the factorial. What is the largest value of n for
            which the program correctly prints the factorial of n?
    (b) repeat part (a), with an int instead.
    (c) repeat part (a), with an long instead.
    (d) repeat part (a), with an long long instead.
    (e) repeat part (a), with an float instead.
    (f) repeat part (a), with an double instead.
    (g) repeat part (a), with an long double instead.
    (e-g will show a close approximation of the factorial, not the exact value)

#include <stdio.h>

int main()
{
    typedef short Vtype;
    short n, i = 1;      //user entered integer n, increment i
    Vtype f = 1.0;    //factorial of n

    printf("Enter a positive integer: ");
    scanf("%hd", &n);

    for (; i <= n; i++)
        f *= i;

    printf("Factorial of %hd", f);  //conv specs %hd %d %ld %lld %f %lf

    return 0;
}

(a) using short, the largest value of n that prints correctly is 7
(b) using int, the largest value of n is 12
(c) using long, 12
(d) long long 20
(e) float 13, due to loss of precision
(f) double 21, although 22 was only off by about 0.1e-15
(g) long double unable to generate valuable answer (IDE/compiler error?)
