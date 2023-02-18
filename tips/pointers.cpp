int i = 42;
int &r = i;   // & follows a type and is part of a declaration; r is a reference
int *p;       // * follows a type and is part of a declaration; p is a pointer
p = &i;       // & is used in an expression as the address-of operator
*p = i;       // * is used in an expression as the dereference operator
int *p = i;   /* invalid */
int &r2 = *p; // & is part of the declaration; * is the dereference operator
