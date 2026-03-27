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
    == and != operators to test whether two structures are equal or not equal.


//              16.2 STRUCTURE TYPES



