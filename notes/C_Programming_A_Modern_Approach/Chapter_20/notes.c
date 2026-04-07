/*** CHAPTER                    20                    LOW-LEVEL PROGRAMMING ***/


//              20.1 BITWISE OPERATORS


// Bitwise Shift Operators


The bitwise shift operators can transform the binary representation of an inte-
    ger by shifting its bits to the left or right.

<< left shift
>> right shift

The operands for << and >> may be of any integer type (including char). The int-
    eger promotions are performed on both operands; the result has the type of
    the left operand after promotion.
The value of i << j is the result when the bits in i are shifted left by j
    places. For each bit that is 'shifted off' the left end of i, a zero bit en-
    ters at the right. The value of i >> j is the result when i is shifted right
    by j places. If i is of an unsigned type or if the value of i is nonnega-
    tive, zeros are added at the left as needed. If i is a negative number, the
    result is implementation-defined; some implementations add zeros at the left
    end, while others preserve the sign bit by adding ones.
For portability, it's best to perform shifts only on unsigned numbers.

unsigned short i, j;

i = 13;        // i is now 13 (binary 0000000000001101
j = i << 2;    // j is now 52 (binary 0000000000110100
j = i >> 2;    // j is now  3 (binary 0000000000000011

As these examples show, neither operator modifies its operands. To modify a var-
    iable by shifting its bits, we'd use the compound assignment operators <<=
    and >>=:

i = 13;        // i is now 13 (binary 0000000000001101
i <<= 2;       // i is now 52 (binary 0000000000110100
i >>= 2;       // i is now 13 (binary 0000000000001101

! The bitwise shift operators have lower precendence than the arithmetic opera-
    tors. For example, i << 2 + 1 means i << (2 + 1), not (i << 2) + 1. !


// Bitwise Complement, And, Exclusive Or, and Inclusive Or


~ bitwise complement
& bitwise and
^ bitwise exclusisve or
| bitwise inclusive or

The ~ operator is unary; the integer promotions are performed on its operand.
    The other operators are binary; the usual arithmetic conversions are per-
    formed on their operands.
The ~, &, and | operators perform Boolean operations on all bits in their oper-
    ands. The ~ operator produces the complement of its operands, with zeros re-
    placed by ones and ones replaced by zeros. The & operator performs a Boolean    'and' operation on all corresponding bits in its two operands. The ^ and |
    operators are similar (both perform a Boolean 'or' operation on the bits in
    their operands); however, ^ produces 0 whenever both operands have a 1 bit,
    whereas | produces 1.
! Don't confuse the bitwise operators & and | with the logical operators && and
    ||. The bitwise operators sometimes produce the same results as the logical
    operators, but they're not equivalent. !

unsigned short i, j, k;

i = 21;      // i is now    21 (binary 0000000000010101)
j = 56;      // j is now    56 (binary 0000000000111000)
k = ~i;      // k is now 65514 (binary 1111111111101010)
k = i & j;   // k is now    16 (binary 0000000000010000)
k = i ^ j;   // k is now    45 (binary 0000000000101101)
k = i | j;   // k is now    65 (binary 0000000000111101)

The value shown for ~i is based on the assumption that an unsigned short value
    occupies 16 bits.
The ~ operator deserves special mention, since we can use it to help make even
    low-level programs more portable. Suppose that we need an integer whose bits
    are all 1. The preferred technique is to write ~0, which doesn't depend on
    the number of bits in an integer. Similarly, if we need an integer whose
    bits are all 1 except for the last five, we could write ~0x1f.
Each of the ~, &, ^, and | operators has a different precedence:

Highest:    ~
            &
            ^
Lowest:     |

As a result, we can combine these operators in expressions without having to use
    parentheses. For example, we could write i & ~j | k instead of (i & (~j)) |
    k and i ^ j & ~k instead of i ^ (j & (~k)). Of course, it doesn't hurt to
    use parentheses to avoid confusion.
! The precedence of &, ^, and | is lower than the precedence of the relational
    and equality operators. Consequently, statements like the following one
    won't have the desired effect:

if (status & 0x4000 != 0) ...

Instead of testing whether status & 0x4000 isn't zero, this statement will eval-
    uate 0x4000 != 0 (which has the value 1), then test whether the value of
    status & 1 isn't zero. !
The compound assignment operators &=, ^=, and |= correspond to the bitwise oper-
    ators &, ^, and |:

i = 21;
