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



