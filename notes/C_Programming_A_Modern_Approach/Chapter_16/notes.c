/*** CHAPTER            16             STRUCTURES, UNIONS, AND ENUMERATIONS ***/


//              16.1 STRUCTURE VARIABLES


for comparison, remember that arrays have two important properties. One, all
    elements of an array have the same type. Two, to select an array element, we
    specify its position (as an integer subscript).
for structures, its elements are known as members, and they aren't required to
    have the same type. Furthermore, the members of a structure have names; to
    select a particular member, we specify its name, not its position.


// Declaring Structure Variables


struct {
    int number;
    char name[NAME_LEN+1];
    int on_hand;
} part1, part2;

this structure variable has three members: number (part number), name (part
    name), and on_hand (quantity of part). struct specifies a type, while part1
    and part2 are variables.
members of a structure are stored in memory in the order in which they're de-
    clared
each structure represents a new scope; any names declared in that scope won't
    conflict with other names in a program (in C terminology, we say that each
    structure has a separate "name space" for its members):

struct {
    int number;
    char name[NAME_LEN+1];
    int on_hand;
} part1, part2;

struct {
    char name[NAME_LEN+1];
    int number;
    char sex;
} employee1, employee2;

number and name members in the part* structures don't conflict with number and
    name members in employee1 and employee2


// Initializing Structure Variables


struct {
    int number;
    char name[NAME_LEN+1];
    int on_hand;
} part1 = {528, "Disk drive", 10},
  part2 = {914, "Printer cable", 5};

the values in the initializer must appear in the same order as the members of
    the structure


// Designated Initializers


{.number = 528, .name = "Disk drive", .on_hand = 10}

the combination of the period and the member name is called a "designator".
designated initializers have several advantages:
-they're easier to read and check for correctness
-the values in the initializer don't have to be placed in the same order that
    the members are listed in the structure. And since the order doesn't matter,
    the order of the members can be changed in the future without affecting de-
    signated initializers.
not all values listed in a designated initializer need be prefixed by a design-
    ator:

{.number = 528, "Disk drive", .on_hand = 10}

"Disk drive" doesn't have a designator, so the compiler assumes that it initial-
    izes the member that follows number in the structure. Any members that the
    initializer fails to account for are set to zero.
 

// Operations on Structures


To access a member within a structure, we write the name of the structure first,
    then a period, then the name of the member:

printf("Part number: %d\n", part1.number);
printf("Part name: %s\n", part1.name);
printf("Quantity on hand: %d\n", part1.on_hand);

members of a structure are lvalues, so they can appear on the left side of an
    assignment or as the operand in an increment or decrement expression:

part1.number = 258;
part1.on_hand++;

the period that we use to access a structure member is acctually a C operator.
    It has the same precedence as the postfix ++ and -- operators, so it takes
    preference over nearly all other operators:

scanf("%d", &part1.on_hand);

in the above line, the . operator takes precedence over the & operator

part2 = part1;

in the above line, the above statement will copy part1.number into part2.number,
   part1.name into part2.name, and so on
even though you cannot copy arrays this way (a[] = b[] does not work), you can
    embed an array in a structure, and copying the structure will copy the array
    to the other structure:

struct { int a[10]; } a1, a2;

a1 = a2; /* legal, since a1 and a2 are structures */

the = operator can be used only with structures of "compatible" types. Two
    structures declared at the same time (as part1 and part2 were) are compat-
    ible.
! C provides no operations on entire structures. In particular, we can't use the
    == and != operators to test whether two structures are equal or not equal. !


//              16.2 STRUCTURE TYPES


if several structure variables with identical membersare declared at the same
    time, there will be no problem. But if we need to declare the variables at
    different points in the program, then problems arise:

struct {
    int number;
    char name[NAME_LEN+1];
    int on_hand;
} part1;

struct {
    int number;
    char name[NAME_LEN+1];
    int on_hand;
} part2;

repeating structure information will bloat the program. Changing the program
    later will be risky, since we can't easily gaurantee that the declarations
    will remain consistent.
the biggest problem is that part1 and part2 don't have compatible types. As a
    result, part1 can't be assigned to part2, and vice versa.
we also don't have a name for the type of part1 or part2, we can't use them as
    arguments in function calls
to avoid these problems, we have two ways to name structures:
-declare a "structure tag"
-use typedef to define a type name


// Declaring a Structure Tag


struct part {
    int number;
    char name[NAME_LEN+1];
    int on_hand;
};

once we've created the part tag, we can use it to declare variables:

struct part part1, part2;

you can declare a structure tag with structure variables at the same time:

struct part {
    int number;
    char name[NAME_LEN+1];
    int on_hand;
} part1, part2;

all structures declared to have type struct part are compatible with one another

struct part part1 = {528, "Disk drive", 10};
struct part part2;

part2 = part1;  /* legal */


// Defining a Structure Type


typedef struct {
    int number;
    char name[NAME_LEN+1];
    int on_hand;
} Part;

declaring variables:

Part part1, part2;

we can choose either to declare a structure tag or to use typedef. But when 
    a structure is to be used in a linked list, using a structure tag is manda-
    tory.


// Structures as Arguments and Return Values


void print_part(struct part p)
{
    printf("Part number: %d\n", p.number);
    printf("Part name: %s\n", p.name);
    printf("Quantity on hand: %d\n", p.on_hand);
}

a call of print_part might look like:

print_part(part1);

a second function that returns a part structure that it constructs from its
    arguments:

struct part build_part(int number, const char *name, int on_hand)
{
    struct part p;

    p.number = number;
    strcpy(p.name, name);
    p.on_hand = on_hand;
    return p;
}

it's legal for build_part's parameters to have names that match the members of
    the part structure, since the structure has its own name space
here's how build_part might be called:

part1 = build_part(528, "Disk drive", 10);

! Passing a structure to a function and returning a structure from a function
    both require making a copy of all members in the structure. As a result,
    these operations impose a fair amount of overhead on a program. To avoid
    this, it's sometimes advisable to pass a pointer to a structure instead of
    passing the structure itself.
Additionally, <stdio.h> defines a type named FILE, which is typically a
    structure. Each FILE structure stores information about the state of an open
    file and therefore must be unique in a program. Every function in <stdio.h>
    that opens a file returns a pointer to a FILE structure, and every function
    that performs an operation on an open file requires a FILE pointer as an
    argument. !

initializing a structure variable inside a function to match another structure:

void f(struct part part1)
{
    struct part part2 = part1; // part2 is the variable being initialized
    ...
}


// Compound Literals


compound literals can be used to create a structure without first storing it in
    a variable:

print_part((struct part) {528, "Disk drive", 10});
           ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

the compound literal, pointed at above, creates a part structure containing the
    members 528, "Disk drive", and 10, in that order. This structure is then
    passed to print_part, which displays it.
assigning a compound literal to a variable:

part1 = (struct part) {528, "Disk drive", 10};

a compound literal may contain designators, just like a designated initializer:

print_part((struct part) {.on_hand = 10,
                          .name = "Disk drive",
                          .number = 528});


//              16.3 NESTED ARRAYS AND STRUCTURES


arrays may have structures as their elements, and structures may contain arrays
    and structures as members


// Nested Structures


suppose we have this first structure:

struct person_name {
    char first[FIRST_NAME_LEN+1];
    char middle_initial;
    char last[LAST_NAME_LEN+1];
};

we can use the person_name structure as part of a larger structure:

struct student {
    struct person_name name;
    int id, age;
    char sex;
} student1, student2;

accessing student1's first name, middle initial, or last name requires two
    applications of the . operator:

strcpy(student1.name.first, "Fred");

one advantage of making name a structure (instead of having first,
    middle_initial, and last be members of the student structure) is that we can
    more easily treat names as units of data. For example, if we were to write a
    function that displays a name, we could pass it just one argument (a
    person_name structure) instead of three arguments:

display_name(student1.name);

likewise, copying the information from a person_name structure to the name mem-
    ber of a strudent structure would take on assignment instead of three:

struct person_name new_name;
...
student1.name = new_name;


// Arrays of Structures


a common combination of arrays and structures is to have an array whose elements
    are structures:

struct part inventory [100];

to access one of the parts in the array, we'd use subscripting. To print the
    part stored in position i, for example, we could write:

print_part(inventory[i]);

accessing a member within a part structure requires a combination of subscript-
    ing and member selection. To assign 883 to member of inventory[i]:

inventory[i].number = 883;

accessing a single character in a part name requires subscripting, followed by
    selection, followed by subscripting. To change the name stored in
    inventory[i] to an empty string:

inventory[i].name[0] = '\0';


// Initializing an Array of Structures


suppose we're working on a program that will need access to the country codes
    used when making international telephone calls:

struct dialing_code {
    char *country;
    int code;
};

note that country is a pointer, which would be a problem if we were planning to
    use dialing_code structures as variables, but we're not. When we initialize
    a dialing_code structure, country will end up pointing to a string literal.
to declare an array of these structures and initialize it to contain the codes
    for some of the world's most populous nations:

const struct dialing_code country_codes[] =
    {{"Argentina",          54}, {"Bangladesh",          880},
     {"Brazil",             55}, {"Burma (Myanmar)",      95},
     ("China",              86}, {"Colombia",             57},
...
     {"United States",       1}, {"Vietnam",              84}};

the inner braces around each structure value are optional
suppose we want to initialize the inventory array to contain a single part:

struct part inventory[100] = 
    {[0].number = 528, [0].on_hand = 10, [0].name[0] = '\0'};


// Maintaining a Parts Database


this will be an example program that maintains a database of parts stored in a
    warehouse. the program will offer operations that insert (i), search (s),
    update (u), print (p), and quit (q):

Enter operation code: _i_
Enter part number: _528_
Enter part name: _Disk_drive_
Enter quantity on hand: _10_

Enter operation code: _s_
Enter part number: _528_
Part name: _Disk_drive_
Quantity on hand: _10_

Enter operation code: _u_
Enter part number: _528_
Enter change in quantity on hand: _-2_

Enter operation code: _p_
Part Number     Part Name                   Quantity on Hand
    528         Disk drive                          8
    924         Printer cable                       5

for now, this program will be split into three files: inventory.c, readline.h,
    and readline.c


//              inventory.c     (maintains a parts database (array version))


#include <stdio.h>
#include "readline.h"

#define NAME_LEN 25
#define MAX_PARTS 100

struct part {
    int number;
    char name[NAME_LEN+1];
    int on_hand;
} inventory[MAX_PARTS];

int num_parts = 0;

int find_part(int number);
void insert(void);
void search(void);
void update(void);
void print(void);

int main(void)
{
    char code;

    for (;;) {
        printf("Enter operation code: ");
        scanf(" %c", &code);
        while (getchar() != '\n')   // skips to end of line
            ;
// if the user enters abc, a would get stored in code, bc\n would be left in the
// buffer, so the while loop clears the buffer so the leftover chars aren't
// present when the for loop restarts
        switch (code) {
            case 'i': insert();
                      break;
            case 's': search();
                      break;
            case 'u': update();
                      break;
            case 'p': print();
                      break
            case 'q': return 0;
            default: printf("Illegal code\n");
        }
        printf("\n");
    }
}

int find_part(int number)
{
    int i;

    for (i = 0; i < num_parts; i++)
        if (inventory[i].number == number)
            return i;
    return -1;
}

void insert(void)
{
    int part_number;

    if (num_parts == MAX_PARTS) {
        printf("Database is full; can't add more parts.\n");
        return;
    }

    printf("Enter part number: ");
    scanf("%d", &part_number);
    if (find_part(part_number) >= 0) {
        printf("part already exists.\n");
        return;
    }

    inventory[num_parts].number = part_number;
    printf("Enter part name: ");
    read_line(inventory[num_parts].name, NAME_LEN);
    printf("Enter quantity on hand: ");
    scanf("%d", &inventory[num_parts].on_hand);
    num_parts++;
}

void search(void)
{
    int i, number;

    printf("Enter part number: ");
    scanf("%d", &number);
    i = find_part(number);
    if (i >= 0) {
        printf("Part name: %s\n", inventory[i].name);
        printf("Quantity on hand: %d\n", inventory[i].on_hand);
    } else
        printf("Part not found.\n");
}

void update(void)
{
    int i, number, change;

    printf("Enter part number: ");
    scanf("%d", &number);
    i = find_part(number);
    if (i >= 0) {
        printf("Enter change in quantity on hand: ");
        scanf("%d", &change);
        inventory{i}.on_hand += change;
    } else
        printf("Part not found.\n");
}

void print(void)
{
    int i;

    printf("Part Number   Part Name                   "
            "Quantity on Hand\n");
    for (i = 0; i < num_parts; i++)
        printf("%7d       %-25s%lld\n", inventory[i].number,
                inventory[i].name, inventory[i].on_hand);
}

" %c" allows scanf to skip over white space, including a new-line character that
    terminated a previous line of input
find_part is a helper function that isn't called from main, but allows us to
    avoid redundant code by simplifying the insert, search, and update functions
since read_line is unrelated to the other functions in inventory.c and is
    potentially reusable in other programs, it is separate from inventory.c


//              readline.h


#ifndef READLINE_H
#define READLINE_H

int read_line(char str[], int n);

#endif


//              readline.c


#include <ctype.h>
#include <stdio.h>
#include "readline.h"

int read_line(char str[], int n)
{
    int ch i = 0;

    while (isspace(ch = getchar()))
        ;
    while (ch != '\n' && ch != EOF) {
        if (i < n)
            str[i++] = ch;
        ch = getchar();
    }
    str[i] = '\0';
    return i;
}

isspace(ch = getchar()) will keep reading past white-space characters until it
    reaches a non-white-space character, which it will store in ch
ch has type int because getchar() returns an int value


//              16.4 UNIONS


unions only allocate enough space for the largest of the members, which overlay
    each other within this space
union members are stored at the same memory address, while structure members are
    stored at different memory addresses
assigning a value to one member alters the values of the other members as well

union {
    int i;
    double d;
} u;

members of a union are accessed in the same way as members of a structure

u.i = 82;
u.d = 74.8;

since the compiler overlays storage for the members of a union, storing 74.8 in
    u.d causes the value of u.i to become lost
we can declare union tags and union types in the same way declare structure tags
    and types
unions can also be copied using the = operator, passed to functions, and return-    ed by functions
unions can even be initialized in a manner similar to structures

union {
    int i;
    double d;
} u = {0};

designated initializers can also be used with unions

union {
    int i;
    double d;
} u = {.d = 10.0};

only one member can be initialized, but it doesn't have to be the first one


// Using Unions to Save Space


suppose we are designing a structure that will contain this information:
-Books: Title, author, number of pages
-Mugs: Design
-Shirts: Design, colors available, sizes available

our first design attempt might result in the following structure

struct catalog_item {
    int stock_number;
    double price;
    int item_type;
    char title[TITLE_LEN+1];
    char author[AUTHOR_LEN+1];
    int num_pages;
    char design[DESIGN_LEN+1];
    int colors;
    int sizes;
};

item_type would have on of the values BOOK, MUG, or SHIRT
colors and sizes would store encoded combinations of colors and sizes
although this structure is usable, it wastes space since only part of the infor-
    mation in the structure is common to all items in the catalog

struct catalog_item {
    int stock_number;
    double price;
    int item_type;
    union {
        struct {
            char title[TITLE_LEN+1];
            char author[AUTHOR_LEN+1];
            int num_pages;
        } book;
        struct {
            char design[DESIGN_LEN+1];
        } mug;
        struct {
            char design[DESIGN_LEN+1];
            int colors;
            int sizes;
        } shirt;
    } item;
};

notice that the union (named item) is a member of the catalog_item structure,
    and the book, mug, and shirt structures are members of item
if c is a catalog_item structure that represents a book, we can print the book's
    title in the following way:

printf("%s", c.item.book.title);

normally, it's not a good idea to store a value into one member of a union and
    then access the data through a different member, because assigning to one
    member of a union causes the values of the other members to be undefined.
! however, you can do this if two or more of the members of the union are
    structures, and the structures begin with one or more matching members.
    These members need to be in the same order and have compatible types, but
    do not need to have the same name. If one of the structures is currently
    valid, then the matching members in the other structures will also be
    valid. !
the union embedded in catalog_item contains three structures as members, two of
    which (mug and shirt) begin with a matching member (design). If we assign a
    value to one of the design members:

strcpy(c.item.mug.design, "Cats");

the design member in the other structure will be defined and have the same value

printf("%s", c.item.shirt.design); //prints "Cats"


// Using Unions to Build Mixed Data Structures


let's say we need an array whose elements are a mixture of int and double
    values. Since array elements must be of the same type, it seems impossible
    to create such an array. To get around this, we can define a union type
    whose members represent the different kinds of data to be stored:

typedef union {
    int i;
    double d;
} Number;

Next, we create an array whose elements are Number values:

Number number_array[1000];

each element of number_array is a Number union. A Number union can store either
    an int value or a double value, making it possible to store a mixture of int
    and double values in number_array:

number_array[0].i = 5;
number_array[1].d = 8.395;


// Adding a "Tag Field" to a Union


there's no easy way to tell which member of a union was last changed and there-
    fore contains a meaningful value. Consider the problem of writing a function
    that displays the value currently stored in a Number union:

void print_number(Number n)
{
    if (n contains an integer)
        printf("%d", n.i);
    else
        printf("%g", n.d);
}

unfortunately, there's no way for print_number to determine whether n contains
    an integer or a floating-point number
to keep track of this information, we can embed the union within a structure
    that has one other member: a "tag field" or "discriminant," whose purpose is
    to remind us what's currently stored in the union. In the catalog_item
    structure, item_type served this purpose

#define INT_KIND 0
#define DOUBLE_KIND 1

typedef struct {
    int kind;  // tag field
    union {
        int i;
        double d;
    } u;
} Number;

each time we assign a value to a member of u, we'll also change kind to remind
    us which member of u we modified

n.kind = INT_KIND;
n.u.i = 82;

when we need to retrieve the number stored in a NUmber variable, kind will tell
    us which member of the union was the last to be assigned a value

void print_number(Number n)
{
    if (n.kind == INT_KIND)
        printf("%d", n.u.i);
    else
        printf("%g", n.u.d);
}


//              16.5 ENUMERATIONS


the "enumerated type" is a type whose values are listed ("enumerated") by the
    programmer, who must create a name (an "enumeration constant") for each of
    the values. The following example enumerates the values that can be assigned
    to the variables s1 and s2:

enum {CLUBS, DIAMONDS, HEARTS, SPADES} s1, s2;

enumerations have little in common with structures and unions, though they are
    declared in a similar way
the names of enumeration constants must be different from other identifiers
    declared in the enclosing scope
enumeration constants are similar to constants created with the #define
    directive, but not equivalent. For one thing, enumeration constants are sub-    ject to C's scope rules


// Enumeration Tags and Type Names


as with structures and unions, there are two ways to name an enumeration: by
    declaring a tag or by using typedef to create a genuine type name
enumeration tags resemble structure and union tags

enum suit {CLUBS, DIAMONDS, HEARTS, SPADES};

suit variables would be declared in the following way

enum suit s1, s2;

as an alternative, we could use typedef to make Suit a type name

typedef enum {CLUBS, DIAMONDS, HEARTS, SPADES} Suit;
Suit s1, s2;

in C89, using typedef to name an enumeration is an excellent way to create a
    Boolean type

typedef enum {FALSE, TRUE} Bool;


// Enumerations as Integers


C treats enumeration variables and constants as integers
by default, the compiler assigns the inegers 0, 1, 2, ... to the constants in a
    particular enumeration
we can choose different values for enumeration constants if we like

enum suit {CLUBS = 1, DIAMONDS = 2, HEARTS = 3, SPADES = 4};

the values of enumeration constants may be arbitrary integers, listed in no par-
    ticular order

enum dept {RESEARCH = 20, PRODUCTION = 10, SALES = 25};

it's even legal for two or more enumeration constants to have the same value
when no value is specified for an enumeration constant, its value is one greater
    than the value of the previous constant

enum EGA_colors {BLACK, LT_GRAY = 7, DK_GRAY, WHITE = 15
                   0                    8

since enumeration values are nothing but thinly disguised integers, C allows us
    to mix them with ordinary integers

int i;
enum {CLUBS, DIAMONDS, HEARTS, SPADES} s;

i = DIAMONDS;   // i is now 1
s = 0;          // s is now 0 (CLUBS)
s++;            // s is now 1 (DIAMONDS)
i = s + 2;      // i is now 3

the compiler treats s as a variable of some integer type; CLUBS, DIAMONDS,
    HEARTS, and SPADES are just names for the integers 0, 1, 2, and 3

! it's dangerous to use an integer as an enumeration value. For example, we
    might accidentally store the number 4 (which doesn't correspond to any suit)    into s. !


// Using Enumerations to Declare "Tag Fields"


enumerations are perfect for determining which member of a union was the last to
    be assigned a value

typedef struct {
    enum {INT_KIND, DOUBLE_KIND} kind;
    union {
        int i;
        double d;
    } u;
} Number;

the advantages are that we've done away with the INT_KIND and DOUBLE_KIND macros    (they're now enumeration constants), and it's now obvious that kind has only
    two possible values


//              NOTES


using sizeof to determine the number of bytes in a structure can yield a larger
    size than expected. Some computers require that the address of certain data
    items be a multiple of some number of bytes (typically two, four, or eight,
    depending on the item's type). To satisfy this requirement, a compiler will
    align the members of a structure by leaving unused bytes between adjacent
    members. If we assume that data items must begin on a multiple of four
    bytes, the 'char a' member of an s structure will be followed by a three-
    byte hole. This can happen even if the hole would be applied at the end of
    a structure. But, there cannot be a hole at the beginning of a structure;
    holes are only allowed between or after the last member. One consequence is
    that a pointer to the first member of a structure is guaranteed to be the
    same as a pointer to the entire structure (note that the two pointers won't
    have the same type).
a structure can have both a tag and a typedef name. In fact, the tag and the
    typedef name can even be the same, although that's not required:

typedef struct part {
    int number;
    char name[NAME_LEN+1];
    int on_hand;
} part;

to share a structure type among several files
