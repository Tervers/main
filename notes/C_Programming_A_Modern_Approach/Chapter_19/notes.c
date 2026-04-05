/*** CHAPTER                       19                        PROGRAM DESIGN ***/


//              19.1 MODULES


When designing a program, it's often useful to view it as a number of indepen-
    dent "modules." A module is a collection of services, some of which are made
    available to other parts of the program (the "clients"). Each module has an
    "interface" that describes the available services. The details of the mod-
    ule -- including the source code for the services themselves -- are stored
    in the module's "implementation."
In the context of C, 'services' are functions. The 'interface' of a module is a
    header file containing prototypes for the functions that will be made avail-
    able to 'clients'(source files). The 'implementation' of a module is a
    source file that contains definitions of the module's functions.
The C library is itself a collection of modules. Each header in the library
    serves as the interface to a module. <stdio.h>, for example, is the inter-
    face to a module containing I/O functions, while <string.> is the interface
    to a module containing string-handling functions.
Dividing a program into modules has several advantages:
> Abstraction: If modules are properly designed, we can treat them as
    "abstractions;" we know what they do, but we don't worry about the details
    of how they do it. Thanks to abstraction, it's not necessary to understand
    how the entire program works in order to make changes to one part of it. It
    also makes it easier for members of a team to work on the same program.
> Reusability: Any module that provides services is potentially reusable in
    other programs. Since it's often hard to anticipate future uses of a module,
    it's a good idea to design modules for reusability.
> Maintainability: A small bug will usually affect only a single module imple-
    mentation, making the bug easier to locate and fix. Once the bug has been
    fixed, rebuilding the program requires only a recompilation of the module
    implementation (followed by linking the entire program). On a larger scale,
    we could replace an entire module implementation, perhaps to improve per-
    formance or when transporting the program to a different platform.
Maintainability is the most critical advantage. Designing a program in a modular
    fashion makes maintenance much easier.


// Cohesion and Coupling


Good module interfaces aren't random collections of declarations. In a well-
    designed program, modules should have two properties:
> "High cohesion": The elements of each module should be closely related to one
    another; we might think of them as cooperating toward a common goal. High
    cohesion makes modules easier to use and makes the entire program easier to
    understand.
> "Low coupling": Modules should be as independent of each other as possible.
    Low coupling makes it easier to modify the program and reuse modules.
In our calculator problem, the stack module is clearly cohesive: its functions
    represent operations on a stack. There's little coupling in the program. The
    calc.c file depends on stack.h (and stack.c depends on stack.h, of course),
    but there are no other apparent dependencies.


// Types of Modules


Because of the need for high cohesion and low coupling, modules tend to fall in-
    to certain typical categories:
> A "data pool" is a collection of related variables and/or constants. In C, a
	module of this type is often just a header file. From a design standpoint,
	putting variables in header files isn't usually a good idea, but collecting
	related constants in a header file can often be useful. In the C library,
	<float.h> and <limits.h> are both data pools.
> A "library" is a collection of related functions. The <string.h> header, for
	example, is the interface to a library of string-handling functions.
> An "abstract object" is a collection of functions that operate on a hidden
	data structure. (In this chapter, the term "object" has a different meaning
	than in the rest of the book. In C terminology, an object is simply a block
	of memory that can store a value. In this chapter, however, an object is a
	collection of data bundled with operations on the data. If the data is hid-
	den, the object is "abstract.") The stack module we've been discussing be-
	longs to this category.
> An "abstract data type (ADT)" is a type whose representation is hidden. Client
	modules can use the type to declare variables, but have no knowledge of the
	structure of those variables. For a client module to perform an operation on
	such a variable, it must call a function provided by the abstract data type
	module. Abstract data types play a significant role in modern programming.


//				19.2 INFORMATION HIDING


A well-designed module often keeps some information secret from its clients.
	Clients of our stack module, for example, have no need to know whether the
	stack is stored in an array, in a linked list, or in some other form. Delib-
	erately concealing information from clients of a module is known as "infor-"
	"mation hiding." Information hiding has two primary advantages:
> "Security": If clients don't know how the stack is stored, they won't be able
	to corrupt it by tampering with its internal workings.
> "Flexibility": Making changes -- no matter how large -- to a module's internal
	workings won't be difficult. For example, we could implement the stack as an
	array at first, then later switch to a linked list or other representation.
	We'll have to rewrite the implementation of the module, of course, but -- if
	the module was designed properly -- we won't have to alter the module's
	interface.
In C, the major tool for enforcing information hiding is the static storage
	class. Declaring a variable with file scope to be static gives it internal
	linkage, thus preventing it from being accessed from other files, including
	clients of the module. (Declaring a function to be static is also useful --
	the function can be directly ccalled only by other functions in the same
	file.)


// A Stack Module


To see the benefits of information hiding, let's look at two implementations of
	a stack module, one using an array and the other a linked list. The module's
	header file will have the following appearance:


//				stack.h


#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

void make_empty(void);
bool is_empty(void);
bool is_full(void);
void push(int i);
int pop(void);

#endif


//				stack1.c


#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

#define STACK_SIZE 100

static int contents[STACK_SIZE];
static int top = 0;

static void terminate(const char *message)
{
	printf("%s\n", message);
	exit(EXIT_FAILURE);
}

void make_empty(void)
{
	top = 0;
}

bool is_empty(void)
{
	return top == 0;
}

bool is_full(void)
{
	return top == STACK_SIZE;
}

void push(int i)
{
	if (is_full())
		terminate("Error in push: stack is full.");
	contents[top++] = i;
}

int pop(void)
{
	if (is_empty())
		terminate("Error in pop: stack is empty.");
	return contents[--top];
}

The variables that make up the stack (contents and top) are both declared
    static, since there's no reason for the rest of the program to access them
    directly. terminate is also declared static. This function isn't part of the
    module's interface; instead, it's designed for use solely within the imple-
    mentation of the module.
As a matter of style, some programmers use macros to indicate which functions
    and variables are 'public' (accessible elsewhere in the program) and which
    are 'private' (limited to a single file):

#define PUBLIC   // empty
#define PRIVATE static

The reason for writing PRIVATE instead of static is that the latter has more
    than one use in C; PRIVATE makes it clear that we're using it to enforce
    information hiding:

PRIVATE int contents[STACK_SIZE];
PRIVATE int top = 0;

PRIVATE void terminate(const char *message) {...}

PUBLIC void make_empty(void) {...}

PUBLIC bool is_empty(void) {...}
    
PUBLIC bool is_full(void) {...}

PUBLIC void push(void) {...}

PUBLIC int pop(void) {...}

Now we'll switch to a linked-list implementation of the stack module:


//              stack2.c


#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

struct node {
    int data;
    struct node *next;
};

static struct node *top = NULL;

static void terminate(const char *message)
{
    printf("%s/n", message);
    exit(EXIT_FAILURE);
}

void make_empty(void)
{
    while (!is_empty())
        pop();
}

bool is_empty(void)
{
    return top == NULL;
}

bool is_full(void)
{
    return false;
}

void push(int i)
{
    struct node *new_node = malloc(sizeof(struct node));
    if (new_node == NULL)
        terminate("Error in push: stack is full.");

    new_node->data = i;
    new_node->next = top;
    top = new_node;
}

int pop(void)
{
    struct node *old_top;
    int i;

    if (is_empty())
        terminate("Error in pop: stack is empty.");

    old_top = top;
    i = top->data;
    top = top->next;
    free(old_top);
    return i;
}

Note that the is_full function returns false every time it's called. A linked
    list has no limit on its size, so the stack will never be full. It's poss-
    ible (but not likely) that the program might run out of memory, which will
    cause the push function to fail, but there's no easy way to test for that
    condition in advance.
Our stack example shows clearly the advantage of information hiding: it doesn't
    matter whether we use stack1.c or stack2.c to implement the stack module.
    Both versions match the module's interface, so we can switch from one to the
    other without having to make changes elsewhere in the program.


//              19.3 ABSTRACT DATA TYPES


A module that serves as an abstract object, like the stack module in the prev-
    ious section, has a serious disadvantage: there's no way to have multiple
    instances of the object (more than one stack, in this case). To accomplish
    this, we'll need to go a step further and create a new 'type.'
Once we've defined a Stack type, we'll be able to have as many stacks as we
    want:

Stack s1, s2;

make_empty(&s1);
make_empty(&s2);
push(&s1, 1);
push(&s2, 2);
if (!is_empty(&s1))
    printf("%d\n", pop(&s1));   //prints "1"

We're not really sure what s1 and s2 are (structures? pointers?), but it doesn't
    matter. To clients, s1 and s2 are 'abstractions' that respond to certain op-
    erations (make_empty, is_empty, is_full, push, and pop).
Let's convert our stack.h header so that it provides a Stack type, where Stack
    is a structure. Doing so will require adding a Stack (or Stack *) parameter
    to each function. The header will now look like this:

#define STACK_SIZE 100

typedef struct {
    int contents[STACK_SIZE];
    int top;
} Stack;

void make_empty(Stack *s);
bool is_empty(const Stack *s);
bool is_full(const Stack *s);
void push(Stack *s, int i);
int pop(Stack *s);

The stack parameters to make_empty, push, and pop need to be pointers, since
    these functions modify the stack. The parameter to is_empty and is_full
    doesn't need to be a pointer, but I've made it one anyway. Passing these
    functions a Stack 'pointer' instead of a Stack 'value' is more efficient,
    since the latter would result in a structure being copied.


// Encapsulation


Unfortunately, Stack isn't an 'abstract' data type, since stack.h reveals what
    the Stack type really is. Nothing prevents clients from using a Stack vari-
    able as a structure;

Stack s1;

s1.top = 0;
s1.contents[top++] = 1;

Providing access to the top and contents members allows clients to corrupt the
    stack. Worse still, we won't be able to change the way stacks are stored
    without having to assess the effect of the change on clients.
What we need is a way to prevent clients from how the Stack type is represented.
    C has only limited support for "encapsulating" types in this way. Newer C-
    based languages, including C++, Java, and C#, are better equipped for this
    purpose.


// Incomplete Types


The only tool that C gives us for encapsulation is the "incomplete type." (In-
    complete types were mentioned in 17.9 and in 17's Q&A section). The C stan-
    dard describes incomplete types as 'types that describe objects but lack in-
    formation needed to determine their sizes.' For example, the declaration:

struct t;    //incomplete declaration of t

tells the compiler that t is a structure tag but doesn't describe the members of
    the structure. As a result, the compiler doesn't have enough information to
    determine the size of such a structure. The intent is that an incomplete
    type will be completed elsewhere in the program.
As long as a type remains incomplete, its uses are limited. Since the compiler
    doesn't know the size of an incomplete type, it can't be used to declare a
    variable:

struct t s;   //WRONG

However, it's perfectly legal to define a pointer type that references an incom-
    plete type:

typedef struct t *T;

This type definition states that a variable of type T is a pointer to a struc-      ture with tag t. We can now perform other operations that are legel for
    pointers. (The size of a pointer doesn't depend on what it points to, which
    explains why C allows this behavior.) What we can't do, though, is apply the
    -> operator to one of these variables, since the compiler knows nothing
    about the members of a t structure.


//              19.4 A STACK ABSTRACT DATA TYPE



