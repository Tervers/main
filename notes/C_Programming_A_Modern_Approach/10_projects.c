/*** CHAPTER                        10                            PROJECTS ***/


1. Modify the stack example of Section 10.2 so that it stores characters
    instead of integers. Next, add a main function that asks the user to enter
    a series of parentheses and/or braces, then indicates whether or not
    they're properly nested.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define STACK_SIZE 100

int contents[STACK_SIZE];
int top = 0;

void stack_overflow(void)
{
    printf("Stack overflow\n");
    exit(EXIT_FAILURE);
}

void stack_underflow(void)
{
    printf("Stack underflow\n");
    exit(EXIT_FAILURE);
}

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

void push(char i)
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

int main(void)
{
    char ch;

    while (ch = getchar()) {

        if (ch == '\n' && is_empty()) {
            printf("Parentheses/braces are nested properly\n");
            return 0;
        }

        if (ch == '{' || ch == '(')
            push(ch);

        if (ch == '}') {
            if (pop() != '{') {
                printf("Parentheses/braces are NOT nested properly\n");
                exit(EXIT_FAILURE);
            }
        }

        if (ch == ')') {
            if (pop() != '(') {
                printf("Parentheses/braces are NOT nested properly\n");
                exit(EXIT_FAILURE);
            }

        }

    }
}


2. Modify the poker.c program of Section 10.5 by moving the num_in_rank and
    num_in_suit arrays into main, which will pass them as arguments to
    read_cards and analyze_hand.

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_RANKS 13
#define NUM_SUITS 4
#define NUM_CARDS 5

/* external variables */
bool straight, flush, four, three;
int pairs;      /* can be 0, 1, or 2 */

/* prototypes */
int read_cards(int num_in_rank[], int num_in_suit[]);
int analyze_hand(int num_in_rank[], int num_in_suit[]);
void print_result(void);

/*********************************************************
* main: Calls read_cards, analyze_hand, and print_result *
*       repeatedly.                                      *
**********************************************************/
int main(void)
{

int num_in_rank[NUM_RANKS];
int num_in_suit[NUM_SUITS];

    for (;;) {
        read_cards(num_in_rank, num_in_suit);
        analyze_hand(num_in_rank, num_in_suit);
        print_result();
    }
}

/********************************************************
* read_cards: Reads the cards into the external         *
*             variables num_in_rank and num_in_suit;    *
*             checks for bad cards and duplicate cards. *
*********************************************************/
int read_cards(int num_in_rank[], int num_in_suit[])
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

    while (cards_read < NUM_CARDS) 
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


/*********************************************************
* analyze_hand: Determines whether the hand contains a   *
*               straight, a flush, four-of-a-kind,       *
*               and/or three-of-a-kind; determines the   *
*               number of pairs; stores the results into *
*               the external variables straight, flush,  *
*               four, three, and pairs.                  *
**********************************************************/
int analyze_hand(int num_in_rank[], int num_in_suit[])
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
        //return;
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
}


3. Remove the num_in_rank, num_in_suit, and card_exists arrays from the poker.c
    program of Section 10.5. Have the program store the cards in a 5 x 2 array
    instead. Each row of the array will represent a card. For example, if the
    array is named hand, then hand[0][0] will store the rank of the first card
    and hand [0][1] will store the suit of the first card.
// INCOMPLETE
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_RANKS 13
#define NUM_SUITS 4
#define NUM_CARDS 5

/* external variables */
bool straight, flush, four, three;
int pairs;      /* can be 0, 1, or 2 */

/* prototypes */
int read_cards(int num_in_rank[], int num_in_suit[]);
int analyze_hand(int num_in_rank[], int num_in_suit[]);
void print_result(void);

/*********************************************************
* main: Calls read_cards, analyze_hand, and print_result *
*       repeatedly.                                      *
**********************************************************/
int main(void)
{
    for (;;) {
        read_cards(num_in_rank, num_in_suit);
        analyze_hand(num_in_rank, num_in_suit);
        print_result();
    }
}

/********************************************************
* read_cards: Reads the cards into the external         *
*             variables num_in_rank and num_in_suit;    *
*             checks for bad cards and duplicate cards. *
*********************************************************/
int read_cards(int num_in_rank[], int num_in_suit[])
{
    char ch, rank_ch, suit_ch;
    int rank, suit;
    bool bad_card;
    int cards_read = 0;

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
        else {
            num_in_rank[rank]++;
            num_in_suit[suit]++;
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
int analyze_hand(int num_in_rank[], int num_in_suit[])
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
        //return;
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
}


4.

5.

6. Some calculators use a system of writing mathematical expressions known as
    Reverse Polish Notation (RPN). Write a program that evaluates RPN
    expressions.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define STACK_SIZE 100

int contents[STACK_SIZE];
int top = 0;

void stack_overflow(void)
{
    printf("Stack overflow\n");
    exit(EXIT_FAILURE);
}

void stack_underflow(void)
{
    printf("Stack underflow\n");
    exit(EXIT_FAILURE);
}

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

void push(char i)
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

int main(void)
{
    char ch;

    while (ch = getchar()) {

        if (ch == '\n' && is_empty()) {
            printf("Parentheses/braces are nested properly\n");
            return 0;
        }

        if (ch == '{' || ch == '(')
            push(ch);

        if (ch == '}') {
            if (pop() != '{') {
                printf("Parentheses/braces are NOT nested properly\n");
                exit(EXIT_FAILURE);
            }
        }

        if (ch == ')') {
            if (pop() != '(') {
                printf("Parentheses/braces are NOT nested properly\n");
                exit(EXIT_FAILURE);
            }

        }

    }
}
