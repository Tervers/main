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
