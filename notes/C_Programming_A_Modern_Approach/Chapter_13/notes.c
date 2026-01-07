/*** CHAPTER                          13                           STRINGS ***/



//              13.1 STRING LITERALS


A "string literal" is a sequence of characters enclosed within double quotes:
"When you come to a fork in the road, take it."
String literals may contain escape sequences.


// Continuing a String Literal


If a string literal is too long to fit on a line, you can end the first line
	with a backslash character (\). The string MUST	continue at the beginning
	of the next line, which will ruin the program's indented structure.
Alternatively, when two or more string literals are adjacent (separated only by
	white space), the compiler will join them into a single string:
	printf("When  you come to a for in the road, take it.   "
		   "--Yogi Berra");


// How String Literals Are Stored


C treats string literals as character arrays. A C compiler will set aside n + 1
	bytes of memory for the string. This memory will contain the characters in
	the	string, plus the 1 extra character, the "null character," to mark the
	end of the string. A null character is a byte whose bits are all 0, which
	is represented by the \0 escape sequence.
For example, "abc" is stored as an array of four characters: a, b, c, \0.
String literals may be empty: "".
Since a string literal is an array, the compiler treats it as a pointer of type
	char *.
Both printf and scanf expect a value of type char * as their first argument.


// Operations on String Literals


In general, we can use a string literal wherever C allows a char * pointer.
For example:

char *p;

p = "abc";

This assignment doesn't copy the characters in "abc"; it just makes p point to
	the first character of the string.
String literals can use subscripting:

char ch;

ch = "abc"[1];

The new value of ch will be the letter 'b'. [0] is a, [2] is c, [3] is \0.
This property of string literals isn't used much, but is occasionally handy:

char digit_to_hex_char(int digit)
{
	return "0123456789ABCDEF"[digit];
}

!! Attempting to modify a string literal causes undefined behavior:

char *p = "abc";

*p = 'd';     /*** WRONG ***/


// String Literals versus Character Constants


A string literal containing a single character ins't the same as a character
	constant. "String literal" "a" is a pointer to memory address that contains
	"a" (followed by a null character). "Character constant" 'a' is represented
	by an integer (the numerical code for a character).


//              13.2 STRING VARIABLES

A string variable can be initialized at the same time it's declared:

char date1[8] = "June 14";// date1 is a string variable, "June 14" initializer

"June 14" is NOT a string literal right here. C views it as an abbreviation for
	an initializer. We could have written:

char date1[8] = {'J', 'u', 'n', 'e', ' ', '1', '4', '\0'};

If the initializer is too short to fill the string variable, the compiler fills
	the unused elements with null characters:

char date2[9] = "June 14";

would appear to the compiler as June 14\0\0.

A string variable CANNOT be longer than the initializer.
!! However, the initializer can be the same length of the variable minus the
	null character:

char date3[7] = "June 14";

There's no room for a null character, so the compiler won't attempt to store 
	one, making the array unusabled as a _string_.

You may omit the length of the string variable:

char date4[] = "June14";

!! Just because the length isn't specified doesn't mean the array's length can
	be changed later; once compiled, the length of date4 is fixed at eight.


// Character Arrays versus Character Pointers


char date[] = "June 14";
vs.
char *date = "June 14";

We can use either version of date as a string, due to the close relationship be-
	tween arrays and pointers.
Any function expecting to be passed a character array or character pointer will
	accept either version of date as an argument.
!! However, there are still differences between the two:
	In date[], the characters stored in date can be modified, like the elements
		of an array. *date points to a string literal, which shouldn't be
		modified.
	In date[], date is an array name. *date is a variable that can be made to
		point to other strings during program execution.
If you need a modifiable string, you must set up an array of characters; a
    pointer variable isn't enough and won't allocate enough memory for a string
    since a string length was never indicated.
To use a pointer as a string:

char str[STR_LEN+1], *p;

p = str;

p now points to the first character of str. Another possibility is to make p
    point to a dynamically allocated string.


//              13.3 READING AND WRITING STRINGS


// Writing Strings Using printf and puts


%s allows printf to write a string:

char str[] = "Are we having fun yet?";

printf("%s\n", str);

To print only part of a string, you can use %.ps, where p is the number of char-
    acters to be displayed:

printf("%.6s\n", str);      // This will print "Are we"

The %ms conversion will display a string in a field of size m (strings longer
    than m will be printed in full, not truncated). If the string is shorter
    than m, it will be right-justified. To force left justification, use a minus
    sign in front of m. m and p can be combined in the form of %m.ps
You can also use puts to write strings:

puts(str);

puts only has one argument (the string to be printed). Puts always writes an
    additional new-line character.


// Reading Strings Using scanf and gets


%s allows scanf to read a string into a character array:

scanf("%s", str);

!! There is no need to put the & operator in front of str, as it is an array and
    is treated as a pointer when passed to a function.
When scanf is called, it skips white space, then reads characters and stores
    them in str until it encounters a white-space character.
scanf always stores a null character at the end of the string.
A string _read_ using scanf will never (!should never?) contain white space.
    scanf also won't usually read a full line of input due to a new-line or tab 
    character.
Use gets to be able to read an entire line of input at a time.
gets reads input characters into an array, then stores a null character.
gets doesn't skip white space before reading a string.
gets reads until it finds a new-line character, but instead of storing the new-
    line character, it will discard it and store a null character instead.


// Reading Strings Character by Character


scanf and gets are risky and insufficiently flexible for many applications.
As an alternative, we can write our own input functions. One such prototype may
	look like this:

int read_line(char str[], int n);

str is the array into which we'll store the input, and n is the maximum number
	of characters to be read. If the input contains more than n characters,
	read_line will discard the additional characters. We'll have read_line
	return the number of characters it actually stores, even if we don't always
	need this value. The loop terminates when the new-line character is read.
	!! We should also have the loop terminate if getchar fails to read a char-
	acter, but this will be ignored for now. The completed function:

int read_line(char str[], int n)
{
	int ch, i = 0;

	while ((ch = getchar()) != '\n')
		if (i < n)
			str[i++] = ch;
	str[i] = '\0';		/* terminates string */
	return i;			/* number of characters stored */
}

! Note that ch has int type rather than char, since getchar returns the numeric
	value of the character that it reads.
! Since scanf and gets automatically put a null character at the end of an input
	string, it is now our responsibility to do so with our function.


//				13.4 ACCESSING THE CHARACTERS IN A STRING


Since strings are stored as arrays, we can use subscripting to access characters
	in a string.
Suppose we need a function that counts the number of spaces in a string:

int count_spaces(const char s[])
{
	int count = 0, i;

	for (i = 0; s[i] != '\0'; i++)
		if (s[i] == ' ')
			count++;
	return count;
}

const will indicate that the function won't alter the array.
If s were not a string, the function would need a second argument specifying the
    length of the array. But since s is a string, we can just test for the null
    character.
Most C programmers wouldn't write count_spaces this way; they would instead use
    pointer arithmetic:

int count_spaces(const char *s)
{
    int count = 0;

    for (; *s != '\0'; s++)
        if (*s == ' ')
            count++;
    return count;
}

!! const here does NOT prevent count_spaces from modifying s; it's there to
    prevent the function from modifying what s points to. And since s is a copy
    of the pointer that is passed to count_spaces, incrementing s doesn't affect
    the original pointer.
The form of the parameter (s[] or *s) does not affect what can be supplied to
    the argument. It can be either an array name, a pointer variable, or a
    string literal; count_spaces cannot tell the difference.


//              13.5 USING THE C STRING LIBRARY


!! Direct attempts to copy or compare strings will fail:

char str1[10], str2[10];

str1 = "abc";   /*** WRONG ***/
str2 = str1;    /*** WRONG ***/

Initializing an array using = is legal:

char str1[10] = "abc"; // While declarating, = is NOT the assignment operator

Attempting to compare strings using a relational or equality operator is legal
    but won't produce the desired result:

if (str1 == str2) ...   /*** WRONG ***/

This statement compares str1 and str2 as pointers; it doesn't compare the con-
    tents of the two arrays. Since str1 and str2 have different addresses, the
    expression str1 == str2 must have the value 0.

string.h provides functions for performing operations on strings.
Most functions of string.h require at least one string as an argument.
String parameters are declared to have type char *, allowing the argument to be
    a character array, a variable of type char *, or a string literal.
!! Watch out for string paramters that aren't declared const, as such parameters
    may be modified when the function is called (i.e. the corresponding argu-
    ment shouldn't be a string literal).


// The strcpy (String Copy) Function


char *strcpy(char *s1, const char *s2);

strcpy copies the string pointed to by s2 into the array pointed to by s1.
strcpy copies characters from s2 to s1 up to (and including) the first null
    character in s2.
strcpy returns s1 (a pointer to the destination string).
strcpy compensates for the inability to use the assignment operator to copy
    strings. Suppose we want to store the string "abcd" in str2:

str2 = "abcd";  /*** WRONG ***/

Instead, we can use strcpy:

strcpy(str2, "abcd");   /* str2 now contains "abcd" */

We can't assign str2 to str1 directly, but we can call strcpy:

strcpy(str1, str2);     /* str1 now contains "abcd" */

We don't usually need the value that strcpy returns. Occasionally, we can use
    strcpy as part of a larger expression:

strcpy(str1, strcpy(str2, "abcd"));   //both str1 and str2 now contain "abcd"

strcpy has no way to verify that str2 will fit into str1. If str2 is longer than
	str1, undefined behavior occurs.
strncpy is a safer, yet slower, way to copy a string. strncpy provides a third
	argument that limits the number of characters to be copied:

strncpy(str1, str2, sizeof(str1));

!! If str2 is longer than str1, strncpy will not append a null character to
	str1. A safer way of using strncpy:

strncpy(str1, str2, sizeof(str1) - 1);
str1[sizeof(str1)-1] = '\0';


// The strlen (String Length) Function


strlen prototype:

size_t strlen(const char *s);

size_t is a typedef name that represents an unsigned integer type.
strlen returns the length of a string s, not including the first null character:

int len;

len = strlen("abc");	// 3
len = strlen("");		// 0
strcpy(str1, "abc");	//
len = strlen(str1);		// 3


// The strcat (String Concatenation) Function


strcat prototype:

char *strcat(char *s1, const char *s2);

strcat appends s2 to the end of s1, then returns s1 (a pointer to the resulting
	string):

strcpy(str1, "abc");
strcat(str1, "def");	/* str1 now contains "abcdef" */
strcpy(str1, "abc");
strcpy(str2, "def");
strcat(str1, str2);		/* str1 now contains "abcdef" */

The value returned by strcat is normally discarded.
Some examples of how the return value may be used, though:

strcpy(str1, "abc");
strcpy(str2, "def");
strcat(str1, strcat(str2, "ghi"));
	/* str1 now contains "abcdefghi"; str2 contains "defghi" */

!! The effect of strcat is undefined if the array pointed to by str1 isn't long
	enough to accommodate str2:

char str1[6] = "abc";

strcat(str1, "def");	/*** WRONG ***/

!! strcat will attempt to add d, e, f, and \0 to the end of str1.
strncat is a safer but slower version of strcat:

strncat(str1, str2, sizeof(str1) - strlen(str1) - 1);

strncat will terminate str1 with a null character, which isn't included in the
	third argument. The third argument calculates the amount of space remaining
	in str1 and then subtracts 1 to ensure that there will be room for the \0.


The strcmp (String Comparison) Function


strcmp prototype:

int strcmp(const char *s1, const char *s2);

strcmp compares s1 to s2, returning a value less than, equal to, or greater than
	0, depending on whether s1 is less than, equal to, or greater than s2:

if (strcmp(str1, str2) < 0)		/* is str1 < str2? */
	...

if (strcmp(str1, str2) <= 0)	/* is str1 <= str2? */
	...

strcmp compares strings based on their lexicographic ordering (dictionary-like).
strcmp considers s1 to be less than s2 if either one of the following conditions
	is satisfied:
	- The first i characters of s1 and s2 match, but the (i+1)st character of s1
		is less than the (i+1)st character of s2. ("abd" < "abe")
	- All characters of s1 match s2, but s1 is shorter than s2. ("abc" < "abcd")
strcmp compares characters by looking at their ASCII numerical codes.
Helpful ASCII character set properties:
	- The characters in each of the sequences A-Z, a-z, and 0-9 have consecutive
   		codes.
	- All upper-case letters are less than all lower-case letters (In ASCII, 65-
		90 represent upper-case letters; 97-122 represent lower-case letters).
	- Digits are less than letters (48-57 represent digits).
	- Spaces are less than all printing characters (space char has the value 32)


// Printing a One-Month Reminder List 		REMIND.C


sprintf is a library function that writes output into a string:

sprintf(day_str, "%2d", day);	/* writes the value of day into day_str */

sprintf automatically adds a null character when it's done writing.


								REMIND.C

#include <stdio.h>
#include <string.h>

#define MAX_REMIND 50
#define MSG_LEN 60

int read_line(char str[], int n);

int main(void)
{
	char reminders[MAX_REMIND][MSG_LEN+3];
	char day_str[3], msg_str[MSG_LEN+1];
	int day, i, j, num_remind = 0;

	for (;;) {
		if (num_remind == MAX_REMIND) {
			printf("-- No space left --\n");
			break;
		}

		printf("Enter day and reminder: ");\
		scanf("%2d", &day);
		if (day == 0)
			break;
		sprintf(day_str, "%2d", day);
		read_line(msg_str, MSG_LEN);

		for (i = 0; i < num_remind; i++)
			if (strcmp(day_str, reminders[i]) < 0)
				break;
		for (j = num_remind; j > i; j--)
			strcpy(reminders[j], reminders[j-1]);

		strcpy(reminders[i], day_str);
		strcat(reminders[i], msg_str);

		num_remind++;
	}

	printf("/nDay Reminder\n");
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


remind.c demonstrates the use of strcpy, strcat, and strcmp functions, but lacks
	many practical features for a reminder program (such as saving reminders in
	a file when the program terminates).


//				13.6 STRING IDIOMS


Trying out any of the versions of strlen and strcat in this section will require
	you to alter the name of the function (we're not allowed to write a function
	that has the same name as a standard library function; in fact, all names
	that begin with str and a lower-case letter are reserved).


// Searching for the End of a String


size_t strlen(const char *s)
{
	size_t n;

	for (n = 0; *s != '/0'; s++)
		n++;
	return n;
}

Let's condense the function. First, we'll move the initialization of n to its
	declaration:

size_t strlen(const char *s)
{
	size_t n = 0;

	for (; *s++;)
		n++;
	return n;
}

Replacing the for statement with a while statement:

size_t strlen(const char *s)
{
	size_t n = 0;

	while (*s++)
		n++;
	return n;
}

Although we've condensed strlen, we likely haven't increased its speed. This
	version will run faster (at least with some compilers):

size_t strlen(const char *s)
{
	const char *p = s;

	while (*s)
		s++;
	return s - p;
}

This version of strlen computes the length of the string by locating the posi-
	tion of the null character, then subtracting from it the position of the
	first character in the string. The improvement in speed comes from not
	having to increment n inside the while loop. !! Without const, the compiler
	would notice that assigning s to p places the string that s points to at
	risk.

while (*s)
	s++;

and

while (*s++)
	;

Both these idioms mean "search for the null character at the end of a string."
	The first version leaves s pointing to the null character. The second ver-
	sion is more concise, but leaves s pointing just past the null character.


// Copying a String


First strcat version:

char *strcat(char *s1, const char *s2)
{
	char *p = s1;

	while (*p != '\0')
		p++;
	while (*s2 != '\0') {
		*p = *s2;
		p++;
		s2++;
	}
	*p = '\0';
	return s1;
}

This will append the contents of s2 onto the end of s1 and then append a null
	character to the end of s1.
The second version of strcat:

char *strcat(char *s1, const char *s2)
{
	char *p = s1;

	while (*p)
		p++;
	while (*p++ = *s2++)
		;
	return s1;
}

The heart of this function is the "string copy" idiom:

while (*p++ = *s2++)
	;

Since the primary operator inside the parenthesis is assignment, the while
	statement tests the value of the assignment (the character that was copied).
	All characters except the null character test true, so the loop won't term-
	inate until the null character has been copied. And since the loop termin-
	ates after the assignment, we don't need a separate statement to put a null
	character at the end of the new string.


//				13.7 ARRAYS OF STRINGS


A simple way to store an array of strings:

char planets[][8] = {"Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn",
					 "Uranus", "Neptune", "Pluto"};

A visualization of what this array will look like:

  0 1 2 3 4 5 6 7 
0 M e r c u r y \0
1 V e n u s \0\0\0
2 E a r t h \0\0\0
3 M a r s \0\0\0\0
4 J u p i t e r \0
5 S a t u r n \0\0
6 U r a n u s \0\0
7 N e p t u n e \0
8 P l u t o \0\0\0

This inefficiency of wasted space (extra null characters) is common when working
	with strings. We can create a "ragged array" whose rows have different
	lengths by creating an array whose elements are pointers to strings:

char *planets[] = {"Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn",
					 "Uranus", "Neptune", "Pluto"};

Now the array will look like:

0 M e r c u r y \0
1 V e n u s \0
2 E a r t h \0
3 M a r s \0
4 J u p i t e r \0
5 S a t u r n \0
6 U r a n u s \0
7 N e p t u n e \0
8 P l u t o \0

To access one of the planet names, all we need to do is subscript the planets
	array (this example searches for strings beginning with the letter M):
	
for (i = 0; i < 9; i++)
	if (planets[i][0] == 'M')
		printf("%s begins with M\n", planets[i]);


// Command-Line Arguments


To obtain access to command-line arguments in our programs, we must define main
	as a function with two parameters (argc and argv):

int main(int argc, char *argv[])
{
	...
}

argc ("argument count") is the number of command-line arguments (including the
	name of the program itself).
argv ("argument vector") is an array of pointers to the command-line arguments
	(which are stored in string form).
argv[0] points to the name of the program, while argv[1] through argv[argc-1]
	point to the remaining command-line arguments.
argv has one additional element, argv[argc], which is always a null pointer (a
	special pointer that points to nothing). The macro NULL represents a null
	pointer.
If the user enters the command line

	ls -l remind.c

then argc will be 3, argv[0] will point to a string containing the program name 	(ls), argv[1] will point to the string "-1", argv[2] will point to the
	string "remind.c", and argv[3] will be a null pointer.
The program name may actually include a path (to the program executable) or
	other information that depends on the operating system. If the program name
	isn't available, argv[0] points to an empty string.
A program that expects command-line arguments will set up a loop that examines
	each argument in turn. One way to write such a loop is to use an integer
	variable as an index into the argv array. This following loop prints the
	command-line arguments, one per line:

int i;

for (i = 1; i < argc; i++)
	printf("%s\n", argv[i]);

Alternatively, we can set up a pointer to argv[1], then increment the pointer
	repeatedly through the rest of the array, testing for a null pointer to
	terminate the loop:

char **p;

for (p = &argv[1]; *p != NULL; p++)
	printf("%s\n", *p);

Setting p equal to &argv[1] makes sense; argv[1] is a pointer to a character, so
	&argv[1] is a pointer to a pointer. *p != NULL is OK, since *p and NULL are
	both pointers. p points to an array element, so incrementing it will advance
	it to the next element. Printing *p is fine, since *p points to the first
	character in a string.


// Checking Planet Names			PLANET.C


This next program illustrates how to access command-line arguments. The program
	will check whether the user-inputed strings are planets or not:


									PLANET.C

#include <stdio.h>
#include <string.h>

#define NUM_PLANETS 9

int main(int argc, char *argv[])
{
	char *planets[] = {"Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn",
					   "Uranus", "Neptune", "Pluto"};

	int i, j;

	for (i = 1; i < argc; i++) {
		for (j = 0; j < NUM_PLANETS; j++)
			if (strcmp(argv[i], planets[j]) == 0) {
				printf("%s is planet %d\n", argv[i], j + 1);
				break;
			}
		if (j == NUM_PLANETS)
			printf("%s is not a planet\n", argv[i]);
	}

	return 0;
}


// 								Additional Notes


Minimum string literal length allowed by compiler: 509 (C89), 4095 (C99)
Not every array of characters requires a null character since not every array of
	characters is used as a string. You do NOT need a null chracter if you'll
	only be performing operations on individual characters.
printf and scanf expect their first argument to have type char *, which means
	that a string 'variable' can be used instead of a string literal:

char fmt[] = "%d\n";
int i;
...
printf(fmt, i);

if getchar can't read a character, either because of an error or because of end-
	of-file, getchar returns the value EOF, which has type int. Here's a revised
	version of read_line that tests whether the return value of getchar is EOF:

int read_line(char str[], int n)
{
	int ch, i = 0;

	while ((ch = getchar()) != '\n' && ch != EOF)
		if (i < n)
			str[i++] = ch;
	str[i] = '\0';
	return i;
}


