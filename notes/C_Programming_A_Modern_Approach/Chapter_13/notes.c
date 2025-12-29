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

char date1[8] = "June 14";

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
