/*** CHAPTER                          13                           STRINGS ***/



// 13.1 STRING LITERALS


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


// String Variables


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

