// Wherever a value is needed, any expression of the same type will do.

/*
*
* #include <stdio.h>        // # = Directive. Include = preprocessor type.
*
* int main(void)            // int = variable type. implies main returns an integer / status code.
*                           // void = main has no argument.
* {
* printf("I love \n");      // printf = 'print formatted' statement. library function call.
* printf("you Michelle.\n");// statements end with a ;.
* return 0;                 // return = statement. value.
* }
*
*/

// gcc -o c c.c             // -o = rename a.out to c

// Preprocessing adds directives (usually handled by compiler) ?preprocessing connects header files to source files?
// Compiles human code into machine (object) code ?human code into binary / assembly?
// Links code with library functions ?links functions from headers to object code?

/*
*
* #directives
*
* int main(void)
*
* {
*
*   declarations;           // int a;
*   initialization;         // int a = 1, b = 2;
*   assignments;            // a = 1; b = 2;
*
*   statements;             // printf("abc\n");
*
* }
*
*/

/*

#include <stdio.h>

int main(void)


{
*
*int height, length, width, volume, weight;
*
*height = 8;
*length = 12;
*width = 10;
*volume = height * length * width;
*weight = (volume + 165) / 166;
*
*printf("Dimensions: %dx%dx%d\n", length, width, height);
*printf("Volume (cubic inches): %d\n", volume);
*printf("Dimensional weight (pounds): %d\n", weight);
*
*return 0;
*
*}
*
*/

// volume = height * length * width;
// printf("%d\n", volume);

// can also be written as:

// printf("%d\n", height * length * width);



 #include <stdio.h>

 int main(void)

{

   int height, length, width, volume, weight;

   printf("Enter height of box: ");
   scanf("%d", &height);   // 'scan formatted' function to accept user input.
   printf("Enter length of box: ");
   scanf("%d", &length);
   printf("Enter width of box: ");
   scanf("%d", &width);
   volume = height * length * width;
   weight = (volume + 165) / 166;

   printf("Volume (cubic inches): %d\n", volume);
   printf("Dimensional weight (pounds): %d\n", weight);

   return 0;

}
