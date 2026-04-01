/*** CHAPTER                  17                  ADVANCED USES OF POINTERS ***/


//              17.1 DYNAMIC STORAGE ALLOCATION


C's data structures are normally fixed in size. Fixed-size data structures can
    be a problem, since we're forced to chooose their sizes when writing a
    program; we can't change the sizes without modifying the program and com-
    piling it again.
The solution to this problem is dynamic storage allocation: the ability to allo-
    cate storage during program execution. Using dynamic storage allocation, we
    can design data structures that grow and shrink as needed.
Dynamic storage allocation is used most often for strings, arrays, and
    structures.


// Memory Allocation Functions


To allocate storage dynamically, we'll need to call one of the three memory
    allocation functions declared in <stdlib.h>:

> malloc: Allocates a block of memory but doesn't initialize it.
> calloc: Allocates a block of memory and clears it.
> realloc: Resizes a previously allocated block of memory.

Of the three, malloc is the most used.
When we call a memory allocation function to request a block of memory, the
    function has no idea what type of data we're planning to store in the block,
    so it can't return a pointer to an ordinary type such as int or char. In-
    stead, the function returns a value of type void *. a void * value is a
    'generic' pointer; essentially, just a memory address.


// Null Pointers


When a memory allocation function is called, there's always a possibility that
    it won't be able to locate a block of memory large enough to satisfy our
    request. If that should happen, the function will return a "null pointer."
    A null pointer is a "pointer to nothing"; a special value that can be dis-
    tinguished from all valid pointers. !After we've stored the function's
    return value in a pointer variable, we must test to see if it's a null
    pointer.!
The null pointer is represented by a macro named NULL, so we can test malloc's
    return value in the following way:

p = malloc(10000);
if (p == NULL) {
    /* allocation failed; take appropriate action */
}

You can combine the call of malloc with the NULL test:

if ((p = malloc(10000)) == NULL) {
    /* allocation failed; take appropriate action */
}

The NULL macro is defined in six headers: <locale.h>, <stddef.h>, <stdio.h>,
    <stdlib.h>, <string.h>, and <time.h>. In C99, <wchar.h> also defines NULL.
Pointers test true or false in the same way as numbers. All non-null pointers
    test true; only null pointers are false. Instead of writing

if (p == NULL) ...

we could write

if (!p) ..

and instead of writing

if (p != NULL) ...

we could write

if (p) ...


//              17.2 DYNAMICALLY ALLOCATED STRINGS


// Using malloc to Allocate Memory for a String


The malloc function has the following prototype:

void *malloc(size_t size);

malloc allocates a block of size bytes and returns a pointer to it. size has
    type size_t, which is an unsigned integer type defined in the C library.
Using malloc to allocate memory for a string is easy, because C guarantees that
    a char value requires exactly one byte of storage (sizeof(char) is 1). To
    allocate space for a string of n characters, we'd write

p = malloc(n + 1);

    where p is a char * variable. n + 1 allows room for the null character. The
    generic pointer that malloc returns will be converted to char * when the
    assignment is performed. In general, we can assign a void * value to a var-
    iable of any pointer type and vice versa. Nevertheless, some programmers
    prefer to cast malloc's return value:

p = (char *) malloc(n + 1);

Memory allocation using malloc isn't cleared or initialized in any way, so p
    will point to an uninitialized array of n + 1 characters.
Calling strcpy is one way to initialize this array:

strcpy(p, "abc");

The first four characters of the array will now be a, b, c, and \0.


// Using Dynamic Storage Allocation in String Functions


Dynamic storage allocation makes it possible to write functions that return a
    pointer to a 'new' string; a string that didn't exist before the function
    was called. We can use this to write a function that concatenates two
    strings without changing either one.
The function will measure the lengths of the two strings to be concatenated,
    then call malloc to allocate just the right amount of space for the result.
    The function then copies the first string into the new space and calls
    strcat to concatenate the second string:

char *concat(const char *s1, const char *s2)
{
    char *result;

    result = malloc(strlen(s1) + strlen(s2) + 1);
    if (result == NULL) {
        printf("Error: malloc failed in concat\n");
        exit(EXIT_FAILURE);
    }
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

Printing an error message and terminating a program isn't always the right
    action to take. Some programs need to recover from memory allocation
    failures and continue running.
Here's how the concat function might be called:

p = concat("abc", "def");

After the call, p will point to the string "abcdef", which is stored in a dynam-
    ically allocated array. The array is seven characters long, including the
    null character at the end.
! Functions that dynamically allocate storage must be used with care. When the
    string that concat returns is no longer needed, we'll cant to call the free
    function to release the space that the string occupies. If we don't, the
    program may eventually run out of memory.


// Arrays of Dynamically Allocated Strings


In 13.7, we found that storing strings as rows in a two-dimensional array of
    characters can waste space, so we tried setting up an array of pointers to
    string literals. The techniques of 13.7 work just as well if the elements of
    an array are pointers to dynamically allocated strings. To illustrate this
    point, we'll rewrite remind.c, which prints a one-month list of daily re-
    minders.


// PROGRAM: Printing a One-Month Reminder List (Revisited)


In this new program (remind2.c), the array will be one-dimensional; its elements
    will be pointers to dynamically allocated strings. Switching to dynamically
    allocated strings will use space more efficiently. We will no longer need to
    call strcpy as we'll merely move pointers to strings.


//              remind2.c


#include <stdio.h>
#include <stdlib.h>     //new
#include <string.h>

#define MAX_REMIND 50
#define MSG_LEN 60

int read_line(char str[], int n);

int main(void)
{
    char *reminders[MAX_REMIND];    //new
    char day_str[3], msg_str[MSG_LEN+1];
    int day, i, j, num_remind = 0;

    for (;;) {
        if (num_remind == MAX_REMIND) {
            printf("-- No space left --\n");
            break;
        }

        printf("Enter day and reminder: ");
        scanf("%2d", &day);
        if (day == 0)
            break;

        printf("Enter day and reminder: ");
        scanf("%2d", &day);
        if (day == 0)
            break;
        sprintf(day_str, "%2d", day);
        read_line(msg_str, MSG_LEN);

        for (i = 0; i < num_remind; i++)
            if (strcmp(day_str, reminders[i]) < 0)
                break;
        for (j = num_remind; j > i; j--)
            reminders[j] = reminders[j-1];      //new

        reminders[i] = malloc(2 + strlen(msg_str) + 1);     //new
        if (reminders[i] == NULL) {     //new
            printf("-- No space left --\n");    //new
            break;      //new
        }       //new

        strcpy(reminders[i], day_str);
        strcat(reminders[i], msg_str);

        num_remind++;
    }

    printf("\nDay Reminders\n");
    for (i = 0; i < num_remind; i++)
        printf(" %s\n", reminders[i]);

    return 0;
}

int read_line(char str[], int n)
{
    int ch, i = 0;

    while ((ch = getchar()) != '\n')
        if (i < n)
            str[i++] = ch;
    str[i] = '\0';
    return i;
}


//              17.3 DYNAMICALLY ALLOCATED ARRAYS


Although malloc can allocate space for an array, the calloc function is some-
    times used instead, since it initializes the memory that it allocates. The
    realloc function allows us to make an array grow or shrink as needed.


// Using malloc to Allocate Storage for an Array


We can use malloc to allocate space for an array in much the same way we used it
    to allocate space for a string. The primary difference is that the elements
    of an arbitrary array won't necessarily be one byte long, as they are in a
    string. As a result, we'll need to use the sizeof operator to calculate the
    amount of space required for each element.
Suppose we're writing a program that needs an array of n integers, where n is to
    be computed during the execution of the program. We'll first declare a
    pointer variable:

int *a;

once the value of n is known, we'll have the program call malloc to allocate
    space for the array:

a = malloc(n * sizeof(int));

! Always use sizeof when calculating how much space is needed for an array. !
Once it points to a dynamically allocated block of memory, we can ignore the
    fact that a is a pointer and use it instead as an array name. For example,
    we could use the following loop to initialize the array that a points to:

for (i = 0; i < n; i++)
    a[i] = 0;

We also have the option of using pointer arithmetic instead of subscripting to
    access the elements of the array.


// The calloc Function


calloc has the following prototype in <stdlib.h>:

void *calloc(size_t nmemb, size_t size);

calloc allocates space for an array with nmemb elements, each of which is size
    bytes long; it returns a null pointer if the requested space isn't avail-
    able. After allocating the memory, calloc initializes it by setting all bits
    to 0. For example, the following call of calloc allocates space for an array
    of n integers, which are all guaranteed to be zero initially:

a = calloc(n, sizeof(int));

Since calloc clears the memory that it allocates but malloc doesn't, we may
    occasionally want to use calloc to allocate space for an object other than
    an array. By calling calloc with 1 as its first argument, we can allocate
    space for a data item of any type:

struct point { int x, y; } *p;

p = calloc(1, sizeof(struct point));

After this statement has been executed, p will point to a structure whose x and
    y members have been set to zero.


// The realloc Function


realloc can resize an array if we later find that it's too large or too small.
    This is the prototype for realloc that appears in <stdlib.h>:

void *realloc(void *ptr, size_t size);

When realloc is called, ptr must point to a memory block obtained by a previous
    call of malloc, calloc, or realloc. The size parameter represents the new
    size of the block, which may be larger or smaller than the original size.
    Although realloc doesn't require that ptr point to memory that's being used
    as an array, in practice it usually does.
A few C standard rules concerning realloc:
> When it expands a memory block, realloc doesn't initialize the bytes that are
    added to the block.
> If realloc can't enlarge the memory block as requested, it returns a null
    pointer; the data in the old memory block is unchanged.
> If realloc is called with a null pointer as its first argument, it behaves
    like malloc.
> If realloc is called with 0 as its second argument, it frees the memory block.
The C standard stops short of specifying exactly how realloc works. When reduc-
    ing a memory block, realloc should shrink the block in place, not moving the
    data stored in the block. realloc will always attempt to expand a memory
    block without moving it. If it's unable to enlarge the block, realloc will
    allocate a new block elsewhere, then copy the contents of the old block in-
    to the new one.
! Once realloc has returned, be sure to update all pointers to the memory block,
    since it's possible that realloc has moved the block elsewhere. !


//              17.4 DEALLOCATING STORAGE


malloc and the other memory allocation functions obtain memory blocks from a
    storage pool known as the "heap." Calling these functions too often, or ask-
    ing them for large blocks of memory, can exhaust the heap, cause the func-
    tions to return a null pointer.
To make matters worse, a program may allocate blocks of memory and then lose
    track of them, wasting space. Consider the following example:

p = malloc(...);
q = malloc(...);
p = q;

After the first two statements have been executed, p points to one memory block,
    while q points to another. After q is assigned to p, both variables now
    point to the second memory block. There are no pointers to the first block,
    so we'll never be able to use it again.
A block of memory that's no longer accessible to a program is said to be
    "garbage." A program that leaves garbage behind has a "memory leak." Some
    languages provide a "garbage collector" that automatically locates and re-
    cycles garbage, but C doesn't. Instead, each C program is responsible for
    recycling its own garbage by calling the free function to release unneeded
    memory.


// The free Function


The free function has the following prototype in <stdlib.h>:

void free(void *ptr);

Using free is easy; we simply pass it a pointer to a memory block that we no
    longer need:

p = malloc(...);
q = malloc(...);
free(p);
p = q;

! The argument to free must be a pointer that was previously returned by a mem-
    ory allocation function (or it can be a null pointer, in which case the call
    of free has no effect). Passing free a pointer to any other object (such as
    a variable to array element) causes undefined behavior. !


// The "Dangling Pointer" Problem


! Although the free function allows us to reclaim memory that's no longer need-
    ed, using it leads to a new problem: "dangling pointers." The call free(p)
    deallocates the memory block that p points to, but doesn't change p itself.
    Attempting to modify the memory that p points to is a serious error, since
    our program no longer has control of that memory. This is undefined behav-
    ior, which may cause a program crash. !


//              17.5 LINKED LISTS


A "linked list" consists of a chain of structures (called "nodes"), with each
    node containing a pointer to the next node in the chain. The last node in
    the list contains a null pointer.
Previously, we've used an array whenever we've needed to store a collection of
    data items; linked lists give us an alternative. A linked list is more flex-
    ible than an array: we can easily insert and delete nodes in a linked list,
    allowing the list to grow and shrink as needed. On the other hand, we lose
    the 'random access' capability of an array. Any element of an array can be
    accessed in the same amount of time; accessing a node in a linked list is
    fast if the node is close to the beginning of the list, slow if it's near
    the end.


// Declaring a Node Type


To set up a linked list, the first thing we'll need is a structure that repre-
    sents a single node in the list. For simplicity, this node will contain
    nothing but an integer (the node's data) and a pointer to the next node:

struct node {
    int value;
    struct node *next;
};

notice that the next member has type struct node *, which means that it can
    store a pointer to a node structure.
When a structure has a member that points to the same kind of structure, as node
    does, we're required to use a structure tag. Without the node tag, we'd have
    no way to declare the type of next.
We need a way to keep track of where the list begins. We can create a variable
    that always points to the first node in the list:

struct node *first = NULL;

Setting first to NULL indicates that the list is initially empty.


// Creating a Node


As we construct a linked list, we'll want to create nodes one by one. Creating a
    node requires three steps:
1. Allocate memory for the node.
2. Store data in the node.
3. Insert the node into the list.
When we create a node, we'll need a variable that can point to the node tempor-
    arily, until it's been inserted into the list:

struct node *new_node;

We'll use malloc to allocate memory for the new node, saving the return value in
    new_node:

new_node = malloc(sizeof(struct node));

! Be careful to give sizeof the name of the Type to be allocated, not the name
    of a pointer to that type:

new_node = malloc(sizeof(new_node));    // WRONG

Doing this will cause malloc to only allocate enough memory for a pointer to a
    node structure. !
Next, we'll store data in the value member of the new node:

(*new_node).value = 10;

to access the value member of the node, we've applied the indirection operator *
    (to reference the structure to which new_node points), then the selection
    operator . (to select a member of the structure). The parentheses around
    *new_node are mandatory because the . operator would otherwise take prece-
    dence over the * operator.


// The -> Operator


Accessing a member of a structure using a pointer is so common that C provides a
    special operator just for this purpose. Known as "right arrow selection", we
    can use the -> operator as so:

new_node->value = 10;

instead of 

(*new_node).value = 10;

The -> operator is a combination of the * and . operators; it performs indirec-
    tion on new_node to locate the structure that it points to, then selects the
    value member of the structure.
The -> operator produces an lvalue, so we can use it wherever an ordinary vari-
    able would be allowed:

scanf("%d", &new_node->value);

Notice that the & operator is still required, even though new_node is a pointer.
    Without the &, we'd be passing scanf the 'value' of new_node->value, which
    has type int.


// Inserting a Node at the Beginning of a Linked List


One advantage of linked lists is that nodes can be added at any point in the
    list: at the beginning, at the end, or anywhere in the middle. The beginning
    is the easiest, so we start there.
If new_node is pointing to the node to be inserted, and first is pointing to the
    first node in the linked list, then we'll need two statements to insert the
    node into the list. First, we'll modify the new node's next member to point
    to the node that was previously at the beginning of the list:

new_node->next = first;

Second, we'll make first point to the new node:

first = new_node;

Will these statements work if the list is empty when we insert a node? Yes. To
    make sure this is true, let's trace the process of inserting two nodes into
    an empty list. We'll insert a node containing the number 10 first, followed
    by a node containing 20.

first = NULL;
new_node = malloc(sizeof(struct node));
new_node->value = 10;
new_node->next = first;
first = new_node;
new_node = malloc(sizeof(struct node));
new_node->value = 20;
new_node->next = first;
first = new_node;

Inserting a node into a linked list is such a common operation that we'll prob-     ably want to write a function for that purpose:

struct node *add_to_list(struct node *list, int n)
{
    struct node *new_node;

    new_node = malloc(sizeof(struct node));
    if (new_node == NULL) {
        printf("Error: malloc failed in add_to_list\n");
        exit(EXIT_FAILURE);
    }
    new_node->value = n;
    new_node->next = list;
    return new_node;
}

Note that add_to_list doesn't modify the list pointer. Instead, it returns a
    pointer to the newly created node (now at the beginning of the list). When
    we call add_to_list, we'll need to store its return value into first:

first = add_to_list(first, 10);
first = add_to_list(first, 20);

These statements add nodes containing 10 and 20 to the list pointed to by first.
    Getting add_to_list to update first directly, rather than return a new value
    for first, turns out to be tricky (the next section, 17.6, discusses this).
The following function uses add_to_list to create a linked list containing num-
    bers entered by the user:

struct node *read_numbers(void)
{
    struct node *first = NULL;
    int n;

    printf("Enter a series of integers (0 to terminate): ");
    for (;;) {
        scanf("%d", &n);
        if (n == 0)
            return first;
        first = add_to_list(first n);
    }
}

The numbers will be in reverse order within the list, since first always points
    to the node containing the last number entered.


// Searching a Linked List


for (p = first; p != NULL; p = p->next)
    ...

The assignment p = p->next advances the p pointer from one node to the next.
Let's write a function named search_list that searches a list (pointed to by the
    parameter list) for an integer n. If it finds n, search_list will return a
    pointer to the node containing n; otherwise, it will return a null pointer:

struct node *search_list(struct node *list, int n)
{
    struct node *p;

    for (p = list; p != NULL; p = p->next)
        if (p->value == n)
            return p;
    return NULL;
}

We can eliminate the p variable and instead use list itself to keep track of the
    current node:

struct node *search_list(struct node *list, int n)
{
    for (; list != NULL; list = list->next)
        if (list->value == n)
            return list;
    return NULL;
}

Since list is a copy of the original list pointer, there's no harm in changing
    it within the function.
Another alternative is to combine the list->value == n test with the list !=
    NULL test:

struct node *search_list(struct node *list, int n)
{
    for (; list != NULL && list->value != n; list = list->next)
        ;
    return list;
}

Since list is NULL if we reach the end of the list, returning list is correct
    even if we don't find n. This version of search_list might be a bit clearer
    if we used a while statement:

struct node *search_list(struct node *list, int n)
{
    while (list != NULL && list->value != n)
        list = list->next;
    return list;
}


// Deleting a Node from a Linked List


Deleting a node, like creating one, involves three steps:
    1. Locate the node to be deleted.
    2. Alter the previous node so that it "bypasses" the deleted node.
    3. Call free to reclaim the space occupied by the deleted node.
Step 1 is harder than it looks. If we search the list in the obvious way, we'll
    end up with a pointer to the node to be deleted. Unfortunately, we won't be
    able to perform step 2, which requires changing the previous node.
One way to solve step 2 is by creating a 'trailing pointer': as we search the
    list in step 1, we'll keep a pointer to the previous node (prev) as well as
    a pointer to the current node (cur). If list points to the list to be
    searched and n is the integer to be deleted, the following loop implements
    step 1:

for (cur = list, prev = NULL;
    cur != NULL && cur->value != n;
    prev = cur, cur = cur->next)
;

Now for step 3, we just need to release the memory occupied by the current node:

free(cur);

The following function, delete_from_list, uses the strategy that we've just out-
    lined. when given a list and an integer n, the function deletes the first
    node containing n. If no node contains n, delete_from_list does nothing. In
    either case, the function returns a pointer to the list.

struct node *delete_from_list(struct node *list, int n)
{
    struct node *cur, *prev;

    for (cur = list, prev = NULL;
         cur != NULL && cur->value != n;
         prev = cur, cur = cur->next)
        ;
    if (cur == NULL)  // if end of list
        return list;
    if (prev == NULL)  // if n is the first node 
        list = list->next;  // moves list to second node so its position as
                            // first node can be removed
    else
        prev->next = cur->next;
    free(cur);
    return list;
}


// Ordered Lists



