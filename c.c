//  //v.1 copy input to output
/*
#include <stdio.h>

main()

{

	int c;

	c = getchar();

	while (c != EOF) {

		putchar(c);

		c = getchar();

		}

	}

*/



/*

//  //v.2 copy input to output

#include <stdio.h>

int main()

{
    int c;

    while ((c = getchar()) != EOF)

        putchar(c);

}

*/

/* invalid code
#include <stdio.h>

int main()

    int c;

    for c != EOF{

        while (getchar(c))
        {
            putchar(c);
            printf("%d\n", c)
        }
*/

#include <stdio.h>

 // count characters in input; 1st version

main()

 {

     long nc;

     nc = 0;

     while (getchar() != EOF)

         ++nc;

     printf("%ld\n", nc);

 }


//#include <stdio.h>

 // /* count characters, v.2 */

/*
 int main()

 {

    double nc;

    for (nc = 0; getchar() != EOF; ++nc)

    ;
    printf("%.0f\n", nc);

    }

*/
