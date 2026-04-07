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


To illustrate how abstract data types can be encapsulated using incpomplete
    types, we'll develop a stack ADT based on the stack module described in
    19.2.


// Defining the Interface for the Stack ADT


The Stack type will be a pointer to a stack_type structure that stores the act-
    ual contents of the stack. This structure is an incomplete type that will be
    completed in the file that implements the stack. The members of this struct-
    ure will depend on how the stack is implemented.


//              stackADT.h (ver.1)


#ifndef STACKADT_H
#define STACKADT_H

#include <stdbool.h>

typedef struct stack_type *Stack;

Stack create(void);
void destroy(Stack s);
void make_empty(Stack s);
bool is_empty(Stack s);
bool is_full(Stack s);
void push(Stack s, int i);
int pop(Stack s);

#endif

Clients that include stackADT.h will be able to declare variables of type Stack,
    each of which is capable of pointing to a stack_type structure. Clients can
    then call the functions declared in stackADT.h to perform operations on
    stack variables. However, clients can't access the members of the stack_type
    structure, since that structure will be defined in a separate file.
Note that each function has a Stack parameter or returns a Stack value. The
    stack functions in 19.3 had parameters of type Stack *. The reason for the
    difference is that a Stack variable is now a pointer; it points to a stack_
    type structure that stores the contents of the stack. If a function needs to
    modify the stack, it changes the structure itself, not the pointer to the 
    structure.
Also note the presence of the create and destroy functions. A module generally
    doesn't need these functions, but an ADT does. create will dynamically allo-
    cate memory for a stack (including the memory required for a stack_type
    structure), as well as initializing the stack to its 'empty' state. destroy
    will release the stack's dynamically allocated memory.
The following client file can be used to test the stack ADT. It creates two
    stacks and performs a variety of operations on them.


//              stackclient.c


#include <stdio.h>
#include "stackADT.h"

int main(void)
{
    Stack s1, s2;
    int n;

    s1 = create();
    s2 = create();

    push(s1, 1);
    push(s2, 2);

    n = pop(s1);
    printf("Popped %d from s1\n", n);
    push(s2, n);
    n = pop(s1);
    printf("Popped %d from s1\n", n);
    push(s2, n);

    destroy(s1);

    while (!is_empty(s2))
        printf("Popped %d from s2\n", pop(s2));

    push(s2, 3);
    make_empty(s2);
    if (is_empty(s2))
        printf("s2 is empty\n");
    else
        printf("s2 is not empty\n");

    destroy (s2);

    return 0;
}

if the stack ADT is implemented correctly, the program should produce the fol-
    lowing output:

Popped 2 from s1
Popped 1 from s1
Popped 1 from s2
Popped 2 from s2
s2 is empty


// Implementing the Stack ADT Using a Fixed-Length Array


We'll have the stackADT.c file define the stack_type structure so that it con-
    tains a fixed-length array (to hold the contents of the stack) along with an
    integer that keeps track of the top of the stack:

struct stack_type {
    int contents[STACK_SIZE];
    int top;
};


//              stackADT.c


#include <stdio.h>
#include <stdlib.h>
#include "stackADT.h"

#define STACK_SIZE 100

struct stack_type {
    int contents[STACK_SIZE];
    int top;
};

static void terminate(const char *message)
{
    printf("%s\n", message);
    exit(EXIT_FAILURE);
}

Stack create(void)
{
    Stack s = malloc(sizeof(struct stack_type));
    if (s == NULL)
        terminate("Error in create: stack could not be create.");
    s->top = 0;
    return s;
}

void destroy(Stack s)
{
    free(s);
}

void make_empty(Stack s)
{
    s->top = 0;
}

bool is_empty(Stack s)
{
    return s->top == 0;
}

bool is_full(Stack s)
{
    return s->top == STACK_SIZE;
}

void push(Stack s, int i)
{
    if (is_full(s))
        terminate("Error in push: stack is full.");
    s->contents[s->top++] = i;
}

int pop(Stack s)
{
    if (is_empty(s))
        terminate("Error in pop: stack is empty.");
    return s->contents[--s->top];
}

The most striking thing about the functions in the file is that they use the ->
    operator, not the . operator, to access the contents and top members of the
    stack_type structure. The s parameter is a pointer to a stack_type struct-
    ure, not a structure itself, so using the . operator would be illegal.


// Changing the Item Type in the Stack ADT


Note that the items in the stack must be integers. This is too restrictive; in
    fact, the item type doesn't really matter. The stack items could just as
    easily be other basic types (float, double, long, etc.) or even structures,
    unions, or pointers, for that matter.
To make the stack ADT easier to modify for different item types, let's add a
    type definition to the stackADT.h header. It will define a type named Item,
    representing the type of data to be stored on the stack.


//              stackADT.h (ver.2)


#ifndef STACKADT_H
#define STACKADT_H

#include <stdbool.h>

typedef int Item;

typedef struct stack_type *Stack;

Stack create(void);
void destroy(Stack s);
void make_empt(Stack s);
bool is_empty(Stack s);
bool is_full(Stack s);
void push(Stack s, Item i);
Item pop(Stack s);

#endif

The stackADT.c file will need to be modified to match the new stackADT.h. The
    stack_type structure will now contain an array whose elements have type Item
    instead of int:

struct stack_type {
    Item contents[STACK_SIZE];
    int top;
};

The stackclient.c file can be used to test the new stackADT.h and stackADT.c
    files to verify that the Stack type still works.


// Implementing the Stack ADT Using a Dynamic Array


Another problem  with the stack ADT as it currently stands is that each stack
    has a fixed maximum size. There are two solutions to this problem. One is to
    implememnt the stack as a linked list. Another is storing stack items in a
    dynamically allocated array.
The crux of the latter approach is to modify the stack_type structure so that
    the conents member is a pointer to the array in which the items are stored,
    not the array itself:

struct stack_type {
    Item *contents;
    int top;
    int size;
};

There is also a new member, size, that stores the stack's maximum size (the
    length of the array that contents points to). We'll use this member to check
    for the 'stack full' condition.
The create function will now have a parameter that specifies the desired maximum
    stack size:

Stack create(int size);

When create is called, it will create a stack_type structure plus an array of
    length size. The contents member of the structure will point to this array.
The stackADT.h file will be the same as before, except that we'll need to add a
    size parameter to the create function.


//              stackADT2.c


#include <stdio.h>
#include <stdlib.h>
#include "stackADT2.h"

struct stack_type {
    Item *contents;
    int top;
    int size;
};

static void terminate(const char *messasge)
{
    printf("%s\n", message);
    exit(EXIT_FAILURE);
}

Stack create(int size)
{
    Stack s = malloc(sizeof(struct stack_type));
    if (s == NULL)
        terminate("Error in create: stack could not be created.");
    s->contents = malloc(size * sizeof(Item));
    if (s->contents == NULL) {
        free(s);
        terminate("Error in create: stack could not be created.");
}
s->top = 0;
s->size = size;
return s;
}

void destroy(Stack s)
{
    free(s->contents);
    free(s);
}

void make_empty(Stack s)
{
    s->top = 0;
}

bool is_empty(Stack s)
{
    return s->top == 0;
}

bool is_full(Stack s)
{
    return s->top == s->size;
}

void push(Stack s, Item i)
{
    if (is_full(s))
        terminate("Error in push: stack is full.");
    s->contents[s->top++] = i;
}

Item pop(Stack s)
{
    if (is_empty(s))
        terminate("Error in pop: stack is empty.");
    return s->contents[--s->top];
}

The create function now calls malloc twice: once to allocate a stack_type
    structure and once to allocate the array that will contain the stack items.
    Either call of malloc could fail, causing terminate to be called. The de-
    stroy function must call free twice to release all the memory allocated by
    create.
The stackclient.c file can again be used to test the stack ADT. The calls of
    create will need to be changed, however, since create now requires an argu-
    ment. For example, we could replace the statements

s1 = create();
s2 = create();

with the following statements:

s1 = create(100);
s2 = create(200);


// Implementing the Stack ADT Using a Linked List


Implementing the stack ADT using a dynamically allocated array gives us more
    flexibility than using a fixed-size array. However, the client is still re-
    quired to specify a maximum size for a stack at the time it's created. If
    we use a linked-list implementation instead, there won't be any preset limit
    on the size of a stack.
At first glance, the stack_type structure seems superfluous; we could just de-
    fine Stack to be struct node * and let a Stack value be a pointer to the
    first node in the list. However, we still need the stack_type structure so
    that the interface to the stack remains unchanged. (If we did away with it,
    any function that modified the stack would need a Stack * parameter instead
    of a Stack parameter.) Moreover, having the stack_type structure will make
    it easier to change the implementation in the future, should we decide to
    store additional information. For example, if we later decide that the
    stack_type structure should contain a count of how many items are currently
    stored in the stack, we can easily add a member to the stack_type structure
    to store this information.
We won't need to make any changes to stackADT.h (we'll use this header file, not
    stackADT2.h).


//              stackADT3.c


#include <stdio.h>
#include <stdlib.h>
#include "stackADT.h"

struct node {
    Item data;
    struct node *next;
};

struct stack_type {
    struct node *top;
};

static void terminate(const char *message)
{
    printf("%s\n", message);
    exit(EXIT_FAILURE);
}

Stack create(void)
{
    Stack s = malloc(sizeof(struct stack_type));
    if (s == NULL)
        terminate("Error in create: stack could not be create.");
    s->top = NULL;
    return s;
}

void destroy(Stack s)
{
    make_empty(s);
    free(s);
}

void make_empty(Stack s)
{
    while (!is_empty(s))
        pop(s);
}

bool is_empty(Stack s)
{
    return s->top == NULL;
}

bool is_full(Stack s)
{
    return false;
}

void push(Stack s, Item i)
{
    struct node *new_mode = malloc(sizeof(struct node));
    if (new_node == NULL)
        terminate("Error in push: stack is full.");

    new_node->data = i;
    new_node->next = s->top;
    s->top = new_node;
}

Item pop(Stack s)
{
    struct node *old_top;
    Item i;

    if (is_empty(s))
        terminate("Error in pop: stack is empty.");

    old_top = s->top;
    i = old_top->data;
    s->top = old_top->next;
    free(old_top);
    return i;
}

===========================================================
Note that the destroy function calls make_empty (to release the memory occupied
    by the nodes in the linked list) before it calls free (to release the memory
    for the stack_type structure).


//              19.5 DESIGN ISSUES FOR ABSTRACT DATA TYPES


// Naming Conventions


The stack ADT functions currently have short, easy-to-understand names: create,
    destroy, make_empty, is_empty, is_full, push, and pop. If we have more than
    one ADT in a program, name clashes are likely, with functions in two modules
    having the same name. (Each ADT will need its own create function, for exam-
    ple.) Therefore, we'll probably need to use function names that incorporate
    the name of the ADT itself, such as stack_create instead of create.


// Error Handling


The stack ADT deals with errors by displaying an error message and terminating
    the program. That's not a bad thing to do. The programmer can avoid popping
    an empty stack or pushing data onto a full stack by being careful to call
    is_empty prior to each call of pop and is_full prior to each call of push,
    so in theory there's no reason for a call of push or pop to fail. (In the
    linked list implementation, however, calling is_full isn't foolproof; a sub-
    sequent call of push can still fail.) Nevertheless, we might want to provide
    a way for a program to recover from these errors rather than terminating.
An alternative is to have the push and pop functions return a bool value to in-
    dicate whether or not they succeeded. push currently has a void return type,
    so it would be easy to modify it to return true if the push operation
    succeeds and false if the stack is full. Modifying the pop function would be
    more difficult, since pop currently returns the value that was popped. How-
    ever, if pop were to return a pointer to this value, instead of the value
    itself, then pop could return NULL to indicate that the stack is empty.
The C standard library contains a parameterized macro named assert that can ter-
    minate a program if a specified condition isn't satisfied. We could use
    calls of this macro as replacements for the if statements and calls of ter-
    minate that currently appear in the stack ADT.


// Generic ADTs


Midway through 19.4, we improved the stack ADT by making it easier to change the
    type of items stored in a stack -- all we had to do was modify the defini-
    tion of the Item type. Also note that our stack ADT suffers from a serious
    flaw: a program can't create two stacks whose items have different types.
    It's easy to create multiple stacks, but those stacks must have items with
    identical types. To allow stacks with different item types, we'd have to
    make copies of the stack ADT's header file and source file and modify one
    set of files so that the Stack type and its associated functions have
    different names.
What we'd like to have is a single "generic" stack type from which we could
    create a stack of integers, a stack of strings, or any other stack that we
    might need. There are various ways to create such a type in C, but none are
    completely satisfactory. The most common approach uses void * as the item
    type, which allows arbitrary pointers to be pushed and popped. With this
    technique, the stackADT.h file would be similar to our original version;
    however, the prototypes of the push and pop functions would have the follow-
    ing appearance:

void push(Stack s, void *p);
void *pop(Stack s);

pop returns a pointer to the item popped from the stack; if the stack is empty,
    it returns a null pointer.
There are two disadvantages to using void * as the item type. One is that this
    approach doesn't work for data that can't be represented in pointer form.
    Items could be strings (which are represented by a pointer to the first
    character in the string) or dynamically allocated structures but not basic
    types such as int and double. The other disadvantage is that error checking
    is no longer possible. A stack that stores void * items will happily allow a
    mixture of pointers of different types; there's no way to detect an error
    caused by pushing a pointer of the wrong type.


// ADTs in Newer Languages


The problems that we've just discussed are dealt with much more cleanly in newer
    C-based languages, such as C++, Java, and C#. Name clashes are prevented by
    defining function names within a class. A stack ADT would be represented by
    a Stack class; the stack functions would belong to this class, and would on-
    ly be recognized by the compiler when applied to a Stack object. These lan-
    guages have a feature known as "exception handling" that allows functions
    such as push and pop to 'throw' an exception when they detect an error con-
    dition. Code in the client can then deal with the error by 'catching' the
    exception. C++, Java, and C# also provide special features for defining gen-
    eric ADTs. In C++, for example, we would define a stack "template," leaving
    the item type unspecified.


//              Q&A




