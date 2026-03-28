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
// present when the loop restarts at printf
        switch (code) {

