int i = 42;
int &r = i;   	 // & follows a type and is part of a declaration; r is a reference
int *p;       	 // * follows a type and is part of a declaration; p is a pointer
p = &i;       	 // & is used in an expression as the address-of operator
*p = i;       	 // * is used in an expression as the dereference operator
int *p = i;   	 /* invalid */
int &r2 = *p; 	 // & is part of the declaration; * is the dereference operator
int* p1, p2; 	 // p1 is a pointer to int; p2 is an int
	int *p1, *p2;  // both p1 and p2 are pointers to int - \
	int* p1;       // p1 is a pointer to int - - - - - - - - > both styles can define pointers/references
	int* p2;       // p2 is a pointer to int - - - - - - - /
