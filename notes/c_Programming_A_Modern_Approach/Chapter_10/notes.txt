/*** CHAPTER                    10                    PROGRAM ORGANIZATION ***/


//          10.1          Local Variables


Local variable - a variable declared in the body of a function
By default, local variables have automatic storage duration^1 and block scope^2
1: Storage for local variable is automatically allocated when function is
    called, and deallocated when function returns
2: The variable is visible from its point of declaration to the end of the
    enclosing function body
Variable declarations do not have to be placed at the beginning of a function,
     leaving the possibility to have a very small scope

// Static local variables

Static storage duration - A variable declared with static has permanent storage
    location, so it retains its value throughout the execution of the program
A static local variable still has block scope

// Parameters

Parameters also have automatic storage duration and block scope


//          10.2          External Variables


External (global) variable - a variable declared outside the body of a function
External variables have static storage duration and file scope^1
1: The variable is visible from its point of declaration to the end of the file


// Example: Using External Variables to Implement a Stack
                   (program fragment)                   

#include <stdbool.h>

#define STACK_SIZE 100

/* external variables */
int contents[STACK_SIZE];
int top = 0;

void make_empty(void)
{
    top = 0;
}

bool is_empty(void)
{
    return top == 0;
}

bool is_full(void)
{
    return top == STACK_SIZE;
}

void push(int i)
{
    if (is_full())
        stack_overflow();
    else
        contents[top++] = i;
}

int pop(void)
{
    if (is_empty())
        stack_underflow();
    else
        return contents[--top];
}


// Pros and Cons of External Variables


In most cases, its better for functions to communicate through parameters
    rather than sharing variables:
    -If we chance an external variable during program maintenance (i.e.
        changing its type), we'll need to check every function in the same file
        to see how the change affects it
    -If an external variable is assigned an incorrect value, it may be hard to
        identify the guilty function
    -Functions that rely on external variables are hard to reuse in other
        programs. To reuse the function, we'll have to drag along any
        external variables that it needs
Avoid using the same external variable for different purposes in different
    functions (i.e. declare i in each for function that needs it, don't declare
    i as an external variable for all functions to use)
External variables should have meaningful names, while local variables don't
    always need meaningful names


// Guessing a Number          guess.c


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NUMBER 100

/* external variable */
int secret_number

/* prototypes */
void initialize_number_generator(void);
void choose_new_secret_number(void);
void read_guesses(void);

int main(void)
{
    char command;

    printf("Guess the secret number between 1 and %d.\n\n", MAX_NUMBER):
    initialize_number_generator();
    do {
        choose_new_secret_number();
        printf("A new number has been chosen.\n");
        read_guesses();
        printf("Play again? (Y/N) ");
        scanf(" %c", &command);
        printf("\n");
    } while (command == 'y' || command == 'Y');

    return 0;
}

void initialize_number_generator(void)
{
    srand((unsigned) time(NULL));
}

void choose_new_secret_number(void)
{
    secret_number = rand() % MAX_NUMBER + 1;
}

void read_guesses(void)
{
    int guess, num_guesses = 0;

    for (;;) {
        num_guesses++;
        printf("Enter guess: ");
        scanf("%d", &guess);
        if (guess == secret_number) {
            printf("You won in %d guesses!\n\n", num_guesses);
            return;
        } else if (guess < secret_number)
              printf("Too low; try again.\n");
          else
              printf("Too high; try again.\n");
    }
}


This program relies on an external variable. This variable could be moved into
    the main function. We can modify choose_new_secret_number so that it
    returns the new number, and we can read_guesses so that secret_number
    can be passed to it as an argument.


//          10.3          Blocks


Blocks are compound { statements } that contain declarations as well:
    { declarations statements }

if (i > j) {
    /* swap values of i and j */
    int temp = i;
    i = j;
    j = temp;
}

Block variables have automatic storage duration and block scope
Block variables can be declared static to give it static storage duration
The body of a function is a block
Putting temporary variables in blocks has two advantages:
    -It avoids cluttering the declarations at the beginning of the function
        body with variables that are used only briefly
    -It reduces name conflicts


//          10.4          Scope


When a declaration inside a block names an identifier that's already visible
    (because it has file scope or because it's declared in an enclosing block),
    the new declaration temporarily "hides" the old one, and the identifier
    takes on a new meaning. At the end of the block, the identifier regains its
    old meaning

int i;            /* Declaration 1 */

void f(int i)     /* Declaration 2 */
{
    i = 1;        /* from 2 */
}

void g(void)
{
    int i = 2;    /* Declaration 3 */

    if (i > 0) {  /* from 3 */
        int i;    /* Declaration 4 */

        i = 3;    /* from 4 */
    }

    i = 4;        /* from 3 */
}

void h(void)
{
    i = 5;        /* from 1 */
}

The i = 1 assignment refers to the parameter in Dec. 2, not the variable in
    Dec. 1, since Dec. 2 hides Dec. 1
The i > 0 test refers to the variable in Dec. 3, since Dec. 3 hides Dec. 1 and
    Dec. 2 is out of scope
The i = 3 assignment refers to the variable in Dec. 4, which hides Dec. 3
The i = 4 assignment refers to the variable in Dec. 3. It can't refer to Dec.
    4, which is out of scope
The i = 5 assignment refers to the variable in Dec. 1


//          10.5          Organizing a C Program


We've seen that a program may contain the following:
    -Preprocessing directives such as #include and #define
    -Type definitions
    -Declarations of external variables
    -Function prototypes
    -Function definitions
A preprocessing directive doesnt take effect until the line on which it appears
A type name can't be used until it's been defined
A variable can't be used until it's declared
A function must be defined or declared before its first call (starting w/ C99)
There are several ways to organize a program so that these rules are obeyed.
    One possible ordering:
        #include directives
        #define directives
        Type definitions
        Declarations of external variables
        Prototypes for functions other than main
        Definition of main
        Definitions of other functions
Suggested: Precede each function definition by a boxed comment that gives the
    name of the function, explains its purpose, discusses the meaning of each
    parameter, describes its return value (if any), and lists any side effects
    it has (such as modifying external variables)

// Classifying a Poker Hand          poker.c

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_RANKS 13
#define NUM_SUITS 4
#define NUM_CARDS 5

/* external variables */
int num_in_rank[NUM_RANKS];
int num_in_suit[NUM_SUITS];
bool straight, flush, four, three;
int pairs;      /* can be 0, 1, or 2 */

/* prototypes */
void read_cards(void);
void analyze_hand(void);
void print_result(void);

/*********************************************************
* main: Calls read_cards, analyze_hand, and print_result *
*       repeatedly.                                      *
**********************************************************/
int main(void)
{
    for (;;) {
        read_cards();
        analyze_hand();
        print_result();
    }
}

/********************************************************
* read_cards: Reads the cards into the external         *
*             variables num_in_rank and num_in_suit;    *
*             checks for bad cards and duplicate cards. *
*********************************************************/
void read_cards(void)
{
    bool card_exists[NUM_RANKS][NUM_SUITS];
    char ch, rank_ch, suit_ch;
    int rank, suit;
    bool bad_card;
    int cards_read = 0;

    for (rank = 0; rank < NUM_RANKS; rank++) {
        num_in_rank[rank] = 0;
        for (suit = 0; suit < NUM_SUITS; suit++)
            card_exists[rank][suit] = false;
    }

    for (suit = 0; suit < NUM_SUITS; suit++)
        num_in_suit[suit] = 0;
        while (cards_read < NUM_CARDS) {
        bad_card = false;

        printf("Enter a card: ");

        rank_ch = getchar();
        switch (rank_ch) {
            case '0':           exit(EXIT_SUCCESS);
            case '2':           rank = 0; break;
                                            case '3':           rank = 1; break;
            case '4':           rank = 2; break;
            case '5':           rank = 3; break;
            case '6':           rank = 4; break;
            case '7':           rank = 5; break;
            case '8':           rank = 6; break;
            case '9':           rank = 7; break;
            case 't': case 'T': rank = 8; break;
            case 'j': case 'J': rank = 9; break;
            case 'q': case 'Q': rank = 10; break;
            case 'k': case 'K': rank = 11; break;
            case 'a': case 'A': rank = 12; break;
            default:            bad_card = true;
        }

        suit_ch = getchar();
        switch (suit_ch) {
            case 'c': case 'C': suit = 0; break;
            case 'd': case 'D': suit = 1; break;
            case 'h': case 'H': suit = 2; break;
            case 's': case 'S': suit = 3; break;
            default:            bad_card = true;
        }

        while ((ch = getchar() != '\n'))
            if (ch != ' ') bad_card = true;

        if (bad_card)
            printf("Bad card; ignored.\n");
        else if (card_exists[rank][suit])
            printf("Duplicate card; ignored.\n");
        else {
            num_in_rank[rank]++;
            num_in_suit[suit]++;
            card_exists[rank][suit] = true;
            cards_read++;
            }
    }
}

/*********************************************************
* analyze_hand: Determines whether the hand contains a   *
*               straight, a flush, four-of-a-kind,       *
*               and/or three-of-a-kind; determines the   *
*               number of pairs; stores the results into *
*               the external variables straight, flush,  *
*               four, three, and pairs.                  *
**********************************************************/
void analyze_hand(void)
{
    int num_consec = 0;
    int rank, suit;

    straight = false;
    flush = false;
    four = false;
    three = false;
    pairs = 0;

    /* check for flush */
    for (suit = 0; suit < NUM_SUITS; suit++)
        if (num_in_suit[suit] == NUM_CARDS)
            flush = true;

    /* check for straight */
    rank = 0;
    while (num_in_rank[rank] == 0) rank++;
        for (; rank < NUM_RANKS && num_in_rank[rank] > 0; rank++)
        num_consec++;
    if (num_consec == NUM_CARDS) {
        straight = true;
        return;
    }

    /* check for 4-of-a-kind, 3-of-a-kind, and pairs */
    for (rank = 0; rank < NUM_RANKS; rank++) {
        if (num_in_rank[rank] == 4) four = true;
        if (num_in_rank[rank] == 3) three = true;
        if (num_in_rank[rank] == 2) pairs++;
    }
}

/*********************************************************
* print_result: Prints the classification of the hand,   *
*               based on the values of the external      *
*               variables straight, flush, four, three,  *
*               and pairs.                               *
**********************************************************/
void print_result(void)
{
    if (straight && flush) printf("Straight flush");
    else if (four)         printf("Four of a kind");
    else if (three &&
             pairs == 1)   printf("Full house");
    else if (flush)        printf("Flush");
    else if (straight)     printf("Straight");
    else if (three)        printf("Three of a kind");
    else if (pairs == 2)   printf("Two pairs");
    else if (pairs == 1)   printf("Pair");
        else                   printf("High card");

    printf("\n\n");
}


//          Additional Notes          Q & A


When a function is called recursively, fresh copies are madeof its automatic
    variables for each call. This doesn't occur for static variables, where all
    calls of the function will share the same static variables.

int i = 1;

void f(void)
{
    int j = i;
    int i = 2;
    ...
}

The score of a local variable doesn't begin until its declaration. Therefore,
    the declaration of j refers to the external variable named i, so j = 1
