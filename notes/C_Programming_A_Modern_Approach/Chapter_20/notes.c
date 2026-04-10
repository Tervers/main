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

i = 21;   // i is now 21 (binary 0000000000010101)
j = 56;   // j is now 56 (binary 0000000000111000)
i &= j;   // i is now 16 (binary 0000000000010000)
i ^= j;   // i is now 40 (binary 0000000000101000)
i |= j;   // i is now 56 (binary 0000000000111000)


// Using the Bitwise Operators to Access Bits


When we do low-level programming, we'll often need to store information as sin-
    gle bits or collections of bits. In graphics programming, for example, we
    may want to squeeze two or more pixels into a single byte. Using the bitwise
    operators, we can extract or modify data that's stored in a small number of
    bits.
Let's assume that i is a 16-bit unsigned short variable:

> Setting a bit: Suppose that we want to set bit 4 of i. (We'll assume that the
    leftmost (or "most significant") bit is numbered 15 and the least signifi-
    cant is numbered 0.) The easiest way to set bit 4 is to 'or' the value of i
    with the constant 0x0010 (a "mask" that contains a 1 bit in position 4):

i = 0x0000;     // i is now 0000000000000000
i |= 0x0010;    // i is now 0000000000010000

More generally, if the position of the bit is stored in the variable j, we can
    use a shift operator to create the mask:

i |= 1 << j;    // sets bit j

For example, if j has the value 3, then 1 << j is 0x0008.

> Clearing a bit: To clear bit 4 of i, we'd use a mask with a 0 bit in position
    4 and 1 bits everywhere else:

i = 0x00ff;     // i is now 0000000011111111
i &= ~0x0010;   // i is now 0000000011101111

// First, ~ changes 0x0010 from 0000000000010000 to 1111111111101111, then &
// compares 1111111111101111 to
//          0000000011111111, which results in
//          0000000011101111

Using the same idea, we can easily write a statement that clears a bit whose
    position is stored in a variable:

i &= ~(1 << j);   // clears bit j

> Testing a bit: The following if statement tests whether bit 4 of i is set:

if (i & 0x0010) ...   // tests bit 4

To test whether bit j is set, we'd use the following statement:

if (i & 1 << j) ...   // tests bit j

To make working with bits easier, we'll often give them names. For example, sup-
    pose that we want bits 0, 1, and 2 of a number to correspond to the colors
    blue, green, and red, respectively. First, we d3efine names that represent
    the three bit positions:

#define BLUE 1
#define GREEN 2
#define RED 4

Setting, clearing, and testing the BLUE bit would be done as follows:

i |= BLUE;          // sets BLUE bit
i &= ~BLUE;         // clears BLUE bit
if (i & BLUE) ...   // tests BLUE bit

It's also easy to set, clear, or test several bits at a time:

i |= BLUE | GREEN;          // sets BLUE and GREEN bits
i &= ~(BLUE | GREEN);       // clears BLUE and GREEN bits
if (i & (BLUE | GREEN)) ... // tests BLUE and GREEN bits

The if statement tests whether either the BLUE bit or the GREEN bit is set.


// Using the Bitwise Operators to Access Bit-Fields


Dealing with a group of several consecutive bits (a bit-field) is slightly more
    complicated than working with single bits. Here are examples of the two most
    common bit-field operations:

> Modifying a bit-field: requires a bitwise 'and' (to clear the bit-field), fol-
    lowed by a bitwise 'or' (to store new bits in the bit-field). The following
    statement shows how we might store the binary value 101 in bits 4-6 of the
    variable i:

i = i & ~0x0070 | 0x0050;       // stores 101 in bits 4-6
// 0x0070 = 0000000001110000, 0x0050 = 0000000001010000
// ~0x0070 occurs first, result then & compares to i, finally | 0x0050 happens
// at the end, producing 0000000001010000

The & operator clears bits 4-6 of i; the | operator then sets bits 6 and 4. No-
    tice that i |=0x0050 by itself wouldn't always work: it would set bits 6 and
    4 but not change bit 5. To generalize the example a little, let's assume
    that the variable j contains the value to be stored in bits 4-6 of i. We'll
    need to shift j into position before performing the bitwise 'or':

i = (i & ~0x0070) | (j << 4);

The | operator has lower precedence than & and <<, so we can drop the parenthe-
    ses if we wish:

i = i & ~0x0070 | j << 4;

> Retrieving a bit-field: When the bit-field is at the right end of a number (in
    the least significant bits), fetching its value is easy:

j = i & 0x0007;         // retrieves bits 0-2

If the bit-field isn't at the right end of i, then we can first shift the bit-
    field to the end before extracting the field using the & operator:

j = (i >> 4) & 0x0007;  // retrieves bits 4-6


// PROGRAM: XOR Encryption


One of the simplest ways to encrypt data is to exclusive-or (XOR) each character    with a secret key. Suppose that the key is the & character. If we XOR this
    key with the character z, we'll get the \ character (assuming that we're us-
    ing the ASCII character set):

    00100110 (ASCII &)
XOR 01111010 (ASCII z)
    01011100 (ASCII \)

To decrypt a message, we just apply the same algorithm. In other words, by en-
    crypting an already-encrypted message, we'll recover the original message.
    If we XOR the & character with the \ character, for example, we'll get the
    original character, z:

    00100110 (ASCII &)
XOR 01011100 (ASCII \)
    01111010 (ASCII z)

The following program, xor.c, encrypts a message by XORing each character with
    the & character. The original message can be entered by the user or read
    from a file using input redirection; the encrypted message can be viewed on
    the screen or saved in a file using output redirection.
To encrypt a file (say, named msg), you can save it the encrypted message as so:

xor <msg >newmsg

To recover the original message, we'd use the command

xor <newmsg

Our program won't change some characters, like digits. XORing these characters
    with & would produce invisible control characters, which could cause prob-
    lems with some operating systems. Chapter 22 shows how to avoid these prob-
    lems, but for now, we'll use the isprint function to make sure that both the
    original character and the new (encrypted) character are printing characters    (i.e. not control characters). If either character fails this test, we'll
    have the program write the original character instead of the new character.


//              xor.c


#include <ctype.h>
#include <stdio.h>

#define KEY '&'

int main(void)
{
    int orig_char, new_char;

    while ((orig_char = getchar()) != EOF) {
        new_char = orig_char ^ KEY;
        if (isprint(orig_char) && isprint(new_char))
            putchar(new_char);
        else
            putchar(orig_char);
    }
    return 0;
}


//              20.2 BIT-FIELDS IN STRUCTURES


Although the techniques of 20.1 allow us to work with bit-fields, these techni-
    ques can be tricky to use and potentially confusing. As an alternative, we
    can declare structures whose members represent bit-fields.
As an example, let's look at how MS-DOS stores the date at which a file was
    created or last modified. Since days, months, and years are small numbers,
    storing them as normal integers would waste space. Instead, DOS allocates
    only 16 bits for a date, with 5 bits for the day, 4 bits for the month, and
    7 bits for the year.

 _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
|             |       |         |
     year       month     day

Using bit-fields, we can define a C structure with an identical layout:

struct file_date {
    unsigned int day: 5;
    unsigned int month: 4;
    unsigned int year: 7;
};

The number after each member indicates its length in bits. Since the members all
    have the same type, we can condense the declaration if we want:

struct file_date {
    unsigned int day: 5, month: 4, year: 7;
};

The type of a bit-field must be either int, unsigned int, or signed int. Using
    int is ambiguous; some compilers treat the field's high-order bit as a sign
    bit, but others don't
! For portability, declare bit-fields to be either unsigned int or signed int. !
In C99, bit-fields may also have type _Bool. C99 compilers may allow additional
    bit-field types.
We can use a bit-field just like any other member of a structure:

struct file_date fd;

fd.day = 28;
fd.month = 12;
fd.year = 8;        // represents 1988

Note that the year member is stored relative to 1980 (the year the world began,
    according to Microsoft). After these assignments, the fd variable will have
    the following appearance:

 _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
|0 0 0 1 0 0 0|1 1 0 0|1 1 1 0 0|

We could have used the bitwise operators to accomplish the same effect; using
    these operators might even make the program a little faster. However, having
    a readable program is usually more important than saving a few microseconds.
Bit-fields do have one restriction that doesn't apply to other members of a
    structure. Since bit-fields don't have addresses in the usual sense, C
    doesn't allow us to apply the address operator (&) to a bit-field. Because
    of this rule, functions such as scanf can't store data directly in a bit-
    field:

scanf("%d", &fd.day);   // WRONG

Of course, we can always use scanf to read input into an ordinary variable and
    then assign it to fd.day.


// How Bit-Fields Are Stored


The rules concerning how the compiler handles bit-fields depend on the notion of
    'storage units.' The size of a storage unit is implementation-defined; typi-
    cal values are 8 bits, 16 bits, and 32 bits. As it processes a structure de-
    claration, the compiler packs bit-fields one by one into a storage unit,
    with no gaps between the fields, until there's not enough room for the next
    field. At that point, some compilers skip to the beginning of the next stor-
    age unit, while others split the bit-field across storage units. (Which one
    occurs is implementation-defined.) The order in which bit-fields are allo-
    cated (left to right or right to left) is also implementation-defined.
Our file_date example assumes that storage units are 16 bits long. (An 8-bit
    storage unit would also be acceptable, provided that the compiler splits the
    month field across two storage units.) We also assume that bit-fields are
    allocated from right to left (with the first bit-field occupying the low-
    order bits).
C allows us to omit the name of any bit-field. Unnamed bit-fields are useful as
    'padding' to ensure that other bit fields are properly positioned. Consider
    the time associated with a DOS file, which is stored in the following way:

struct file_time {
    unsigned int seconds: 5;
    unsigned int minutes: 6;
    unsigned in hours: 5;
};

(You may be wondering how it's possible to store the seconds -- a number between
    0 and 59 -- in a field with only 5 bits. Well, DOS cheats: it divides the
    number of seconds by 2, so the seconds member is actually between 0 and 29.)
    If we're not interested in the seconds field, we can leave out its name:

struct file_time {
    unsigned int : 5;       // not used
    unsigned int minutes: 6;
    unsigned int hours: 5;
};

The remaining bit-fields will be aligned as if the seconds field were still pre-
    sent.
Another trick that we can use to control the storage of bit-fields is to specify
    0 as the length of an unnamed bit-field:

struct s {
    unsigned int a: 4;
    unsigned int : 0;
    unsigned int b: 8;
};

A 0-length bit-field is a signal to the compiler to align the following bit-
    field at the beginning of a storage unit. If storage units are 8 bits long,
    the compiler will allocate 4 bits for the a member, skip 4 bits to the next
    storage unit, and then allocate 8 bits for b. If storage units are 16 bits
    long, the compiler will allocate 4 bits for a, skip 12 bits, and then allo-
    cate 8 bits for b.


//              20.3 OTHER LOW-LEVEL TECHNIQUES


// Definiting Machine-Dependent Types


Since the char type occupies one byte, we'll sometimes treat characters as
    bytes, using them to store data that's not necessarily in character form.
    When we do so, it's a good idea to define a BYTE type:

typedef unsigned char BYTE;

The x86 architecture makes extensive use of 16-bit words, so the following defi-    nition would be useful for that platform:

typedef unsigned short WORD;


// Using Unions to Provide Multiple Views of Data


We can use unions to view a block of memory in two or more different ways. This
    first example will be based on the file_date structure. Since a file_date
    structure fits into two bytes, we can think of any two-byte value as a file_    date structure. In particular, we could view an unsigned short value as a 
    file_date structure (assuming that short integers are 16 bits long). The
    following union allows us to easily convert a short integer to a file date
    or vice versa:

union int_date {
    unsigned short i;
    struct file_date fd;
};

With this union, we could fetch a file date from disk as two bytes, then extract
    its month, day, and year fields. Conversely, we could construct a date as a
    file_date structure, then write it to disk as a pair of bytes.
As an example of how we might use the int_date union, here's a function that,
    when passed an unsigned short argument, prints it as a file date:

void print_date(unsigned short n)
{
    union int_date u;

    u.i = n;
    printf("%d/%d/%d\n", u.fd.month, u.fd.day, u.fd.year + 1980);
}
// Since unions only hold data (in a particular memory location) for one member,
// the data that is already there for one member can be used by the other member

Using unions to allow multiple views of data is especially useful when working
    with registers, which are often divided into smaller units. x86 processors,
    for example, have 16-bit registers named AX, BX, CX, and DX. Each of these
    registers can be treated as two 8-bit registers. AX, for example, is divided
    into registers named AH and AL (high and low).
When writing low-level applications for x86-based computers, we may need varia-
    bles that represent the contents of the AX, BX, CX, and DX registers. We
    want access to both the 16- and 8-bit registers; at the same time, we need
    to take their relationships into account (a change to AX affects both AH and    AL; changing AH or AL modifies AX). The solution is to set up two struc-
    tures, one containing members that correspond to the 16-bit registers, and
    the other containing members that match the 8-bit registers. We then create
    a union that encloses the two structures:

union {
    struct {
        WORD ax, bx, cx, dx;
    } word;
    struct {
        BYTE al, ah, bl, bh, cl, ch, dl, dh;
    } byte;
} regs;

The members of the word structure will be overlaid with the members of the byte
    structure; for example, ax will occupy the same memory as al and ah. An ex-
    ample of how the regs union might be used:

regs.byte.ah = 0x12;
regs.byte.al = 0x34;
printf("AX: %hx\n", regs.word.ax);

Changing ah and al affects ax, so the output will be

AX: 1234

Note that the byte structure lists al before ah, even though the AL register is
    the 'low' half of AX and AH is the 'high' half. Here's the reason. When a
    data item consists of more than one byte, there are two logical ways to
    store it in memory: with the bytes in the 'natural' order (with the leftmost
    byte stored first) or with the bytes in reverse order (the leftmost byte is
    stored last). The first alternative is called "big-endian"; the second is
    known as "little-endian." C doesn't require a specific byte ordering, since
    that depends on the CPU on which a program will be executed. Some CPUs use
    the big-endian approach and some use the little-endian approach. What does
    this have to do with the byte structure? It turns out that x86 processors
    assume that data is stored in little-endian order, so the first byte of
    regs.word.ax is the low byte.
We don't normally need to worry about byte ordering. However, programs that deal
    with memory at a low level must be aware of the order in which bytes are
    stored (as the regs example illustrates). It's also relevant when working
    with files that contain non-character data.

! Be careful when using unions to provide multiple views of data. Data that is
    valid in its original format may be invalid when viewed as a different type,
    causing unexpected problems. !


// Using Pointers as Addresses


An address often has the same number of bits as an integer (or long integer).
    Creating a pointer that represents a specific address is easy: we just cast
    an integer into  apointer. For example, here's how we might store the ad-
    dress 1000 (hex) in a pointer variable:

BYTE *p;

p = (BYTE *) 0x1000;    // p contains address 0x1000


// PROGRAM: Viewing Memory Locations


This next program allows the user to view segments of computer memory; it relies
    on C's willingness to allow an integer to be used as a pointer. Most CPUs
    execute programs in 'protected mode,' however, which means that a program
    can access only those portions of memory that belong to the program. This
    prevents a program from accessing (or changing) memory that belongs to an-
    other application or to the operating system itself. As a result, we'll only
    be able to use our program to view areas of memory that have been allocated
    for use by the program itself. Going outside these regions will cause the
    program to crash.
The viewmemory.c program begins by displaying the address of its own main func-
    tion as well as the address of one of its variables. The program next
    prompts the user to enter an address (in the form of a hexadecimal integer)
    plus the number of bytes to view. The program then displays a block of bytes
    of the chosen length, starting at the specified address.
Bytes are displayed in groups of 10 (except for the last group, which may have
    fewer than 10 bytes). The address of a group of bytes is displayed at the
    beginning of a line, followed by the bytes in the group (displayed as hexa-
    decimal numbers); followed by the same bytes displayed as characters (just
    in case the bytes happen to represent characters, as some of them may). Only
    printing characters (as determined by the isprint function) will be display-
    ed; other characters will be shown as periods.
We'll assume that int values are stored using 32 bits and that addresses are al-
    so 32 bits long. Addresses are displayed in hexadecimal, as is customary.


//              viewmemory.c


#include <ctype.h>
#include <stdio.h>

typedef unsigned char BYTE;

int main(void)
{
    unsigned int addr;
    int i, n;
    BYTE *ptr;

    printf("Address of main function: %x\n", (unsigned int) main);
    printf("Address of addr variable: %x\n", (unsigned int) &addr);

    printf("\nEnter a (hex) address: ");
    scanf("%x", %addr);
    printf("Enter number of bytes to view: ");
    scanf("%d", &n);

    printf("\n");
    printf(" Address              Bytes              Characters\n");
    printf(" -------  -----------------------------  ----------\n");

    ptr = (BYTE *) addr;
    for (; n > 0; n-= 10) {
      printf("%8X  ", (unsigned int) ptr);
      for (i = 0; i < 10 && i < n; i++)
        printf("%.2X ", *(ptr + i));
      for (; i < 10; i++)
        printf("   ");
      printf(" ");
      for (i = 0; i < 10 && i < n; i++) {
        BYTE ch = *(ptr + i);
        if (!isprint(ch))
            ch = '.';
        printf("%c", ch);
      }
      printf("\n");
      ptr += 10;
    }

    return 0;
}

-----------------------------------------------------------
The condition i < 10 && i < n causes the loops to execture 10 times or n times,
    whichever is smaller. There's also a for statement that compensates for any
    missing bytes in the last group by displaying three spaces for each missing
    byte. That way, the characters that follow the last group of bytes will a-
    lign properly with the chracter groups on previous lines.
The %X conversion specifier is similar to %x, the difference is that %X displays
    the hexadecimal digits as upper-case letters while %x displays them in lower    case.


// The volatile Type Qualifier


On some computers, certain memory locations are "volatile"; the value stored at
    such a location can change as a program is running, even though the program
    itself isn't storing new values there. For example, some memory locations
    might hold data coming directly from input devices.
The volatile type qualifier allows us to inform the compiler if any of the data
    used in a program is volatile. volatile typically appears in the declaration
    of a pointer variable that will point to a volatile memory location:

volatile BYTE *p;   // p will point to a volatile byte

Suppose p points to a memory location that contains the most recent character
    typed at the user's keyboard. This location is volatile: its value changes
    each time the user enters a character. We might use the following loop to
    obtain characters from the keyboard and store them in a buffer array:

while ('buffer not full') {
    'wait for input';
    buffer[i] = *p;
    if (buffer[i++] == '\n')
        break;
}

A sophisticated compiler might notice that this loop changes neither p nor *p,
    so it could optimize the program by altering it so that *p is fetched just
    once:

'store *p in a register;
while ('buffer not full') {
    'wait for input';
    buffer[i] = 'value stored in register';
    if (buffer[i++] == '\n')
        break;
}

The optimized program will fill the buffer with many copies of the same charac-
    ter -- not exactly what we had in mind. Declaring that p points to volatile
    data avoids this problem by telling the compiler that *p must be fetched
    from memory each time it's needed.
