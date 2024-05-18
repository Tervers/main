#include <stdio.h>
#include <stdbool.h>

int main(void)
{
    bool fsc = 0; //first space check
    short i, len;
    char ch, term;
    char word[i], sentence[len];//terminating character, sentence [length]

    printf("Enter a sentence: ");

    for (len = 0; ;) {

        ch = getchar();
        if (ch == '\n') {

    	    for (i = 0; len >= 0; i++, len--) {

        	ch = sentence[len];
		word[i] = ch;
		if (ch == ' ') {

	            for (; i >= 0; i--) {
		        putchar(word[i]);
		    }

	        }

	    }
	    break;
        }

        else if (ch == '.' || ch == '!' || ch == '?')
            term = ch;

	else {
            sentence[len] = ch;
	    len++;
	}

    }


    putchar(term);

    return 0;
}
