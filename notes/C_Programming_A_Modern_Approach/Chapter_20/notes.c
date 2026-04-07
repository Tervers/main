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

the ~ operator is unary; the integer promotions are 
