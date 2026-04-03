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



