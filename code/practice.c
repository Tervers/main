#include <stdio.h>
/* print Fahrenheit-Celsius table */

    #define LOWER 0
    #define UPPER 300
    #define STEP 20

main ()
{
    int fahr;
    for (fahr=300; fahr>=0; fahr=fahr-20)  //initialization: fahr=0; control condition: fahr <=300; fahr=fahr+20: increment
        printf("%3d %6.1f\n", fahr, (5.0/9.0)*(fahr-32));
        printf("\n");

    for (fahr=LOWER;fahr<=UPPER;fahr=fahr+STEP)
        printf("%3d %6.1f\n", fahr, (5.0/9.0)*(fahr-32));
}
