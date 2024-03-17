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



//  //v.2 copy input to output

#include <stdio.h>

main()

{
    int c;

    while ((c = getchar()) != EOF)

        putchar(c);
        printf("%3d", EOF);

}
