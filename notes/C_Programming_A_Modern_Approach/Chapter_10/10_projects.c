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

bool straight, flush, four, three;
int pairs;

int read_cards(int num_in_rank[], int num_in_suit[]);
int analyze_hand(int num_in_rank[], int num_in_suit[]);
void print_result(void);

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

int analyze_hand(int num_in_rank[], int num_in_suit[])
{
    int num_consec = 0;
    int rank, suit;

    straight = false;
    flush = false;
    four = false;
    three = false;
    pairs = 0;

    for (suit = 0; suit < NUM_SUITS; suit++)
        if (num_in_suit[suit] == NUM_CARDS)
            flush = true;

    rank = 0;
    while (num_in_rank[rank] == 0) rank++;
    for (; rank < NUM_RANKS && num_in_rank[rank] > 0; rank++)
        num_consec++;
    if (num_consec == NUM_CARDS) {
        straight = true;
        //return;
    }

    for (rank = 0; rank < NUM_RANKS; rank++) {
        if (num_in_rank[rank] == 4) four = true;
        if (num_in_rank[rank] == 3) three = true;
        if (num_in_rank[rank] == 2) pairs++;
    }
}

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

bool straight, flush, four, three;
int pairs;

int read_cards(int num_in_rank[], int num_in_suit[]);
int analyze_hand(int num_in_rank[], int num_in_suit[]);
void print_result(void);

int main(void)
{
    for (;;) {
        read_cards(num_in_rank, num_in_suit);
        analyze_hand(num_in_rank, num_in_suit);
        print_result();
    }
}

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

int analyze_hand(int num_in_rank[], int num_in_suit[])
{
    int num_consec = 0;
    int rank, suit;

    straight = false;
    flush = false;
    four = false;
    three = false;
    pairs = 0;

    for (suit = 0; suit < NUM_SUITS; suit++)
        if (num_in_suit[suit] == NUM_CARDS)
            flush = true;

    rank = 0;
    while (num_in_rank[rank] == 0) rank++;
    for (; rank < NUM_RANKS && num_in_rank[rank] > 0; rank++)
        num_consec++;
    if (num_consec == NUM_CARDS) {
        straight = true;
        //return;
    }

    for (rank = 0; rank < NUM_RANKS; rank++) {
        if (num_in_rank[rank] == 4) four = true;
        if (num_in_rank[rank] == 3) three = true;
        if (num_in_rank[rank] == 2) pairs++;
    }
}

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

double contents[STACK_SIZE];
int top = 0;

void stack_overflow(void)
{
    printf("Expression is too complex\n");
    exit(EXIT_FAILURE);
}

void stack_underflow(void)
{
    printf("Not enough operands in expression\n");
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

void push(double i)
{
    if (is_full())
        stack_overflow();
    else
        contents[top++] = i;
}

double pop(void)
{
    if (is_empty())
        stack_underflow();
    else
        return contents[--top];
}

int main(void)
{
    char ch;

    printf("Enter an RPN expression: ");
    printf("Top = %d.\n", top);

    while (scanf(" %c", &ch)) {
	switch (ch) {
            case '0': 
	    case '1':
	    case '2':
	    case '3':
	    case '4':
	    case '5':
	    case '6':
	    case '7':
	    case '8':
	    case '9':
                push(ch - 48.0L); printf("Top = %g ch = %c\n", top, ch); break;

            case '+':
		double operator2 = pop();
		double operator1 = pop();
		push(operator1 += operator2);
		printf("+ %g\n", contents[top - 1]);
		break;

            case '-':
		operator2 = pop();
		operator1 = pop();
		push(operator1 -= operator2);
		printf("+ %g\n", contents[top - 1]);
		break;

            case '*':
		operator2 = pop();
		operator1 = pop();
		push(operator1 *= operator2);
		printf("+ %g\n", contents[top - 1]);
		break;

            case '/':
		operator2 = pop();
		operator1 = pop();
		push(operator1 /= operator2);
		printf("+ %g\n", contents[top - 1]);
		break;

            case '=':
                printf("Value of expression: %g\n", pop());
                if (top >= 1) stack_overflow();
                if (top < 0) stack_underflow();
                printf("Enter an RPN expression: ");
                break;

            case 'q':
                return 0;
        }
    }
}


7. Write a program that prompts the user for a number and then displays the
    number, using characters to simulate the effect of a seven-segment display.
    Characters other than digits should be ignored. Maximum number of digits is
    controlled by a macro named MAX_DIGITS, which has a value of 10; extra
    digits are ignored. Use two external arrays. One is the segments array
    (C08-e06), which stores data representing the correspondence between digits
    and segments. The other array, digits, will be an array of characters with
	4 rows (since each segmented digit is four characters high) and MAX_DIGITS
	* 4 columns (digits are 3 characters wide, but a space is needed between
    digits for readability). Write your program as four functions: main,
    clear_digits_array, process_digit, and print_digits_array:
    	void clear_digits_array(void);
		void process_digit(int digit, int position);
		void print_digits_array(void);

    clear_digits_array will store blank characters into all elements of the
    digits array. process_digit will store the seven-segment representation of
    digit into a specified position in the digits array (positions range from 0
    to MAX_DIGITS - 1). print_digits_array will display the rows of the digits
    array, each on a single line, producing output such as that shown in the
    example.

//code works, but does not provide error-checking
#include<stdio.h>

#define MAX_DIGITS 10

char digits[3][MAX_DIGITS * 4];
const int segments[10][7] = {{1, 1, 1, 1, 1, 1, 0},
							 {0, 1, 1, 0, 0, 0, 0},
							 {1, 1, 0, 1, 1, 0, 1},
							 {1, 1, 1, 1, 0, 0, 1},
							 {0, 1, 1, 0, 0, 1, 1},
							 {1, 0, 1, 1, 0, 1, 1},
							 {1, 0, 1, 1, 1, 1, 1},
							 {1, 1, 1, 0, 0, 0, 0},
							 {1, 1, 1, 1, 1, 1, 1},
							 {1, 1, 1, 1, 0, 1, 1}};

void clear_digits_array(void) {
	for (int i = 0; i < MAX_DIGITS * 4; i++)
		for (int j = 0; j < 3; j++)
			digits[j][i] = ' ';
}

void process_digit(int digit, int position) {
    for (int i = 0; i < 7; i++) {
        if (segments[digit][i] == 1) {
            switch (i) {
                case 0:
                    digits[0][(position * 4) + 1] = '_'; break;

                case 1:
                    digits[1][(position * 4) + 2] = '|'; break; 

                case 2:
                    digits[2][(position * 4) + 2] = '|'; break; 

                case 3:
                    digits[2][(position * 4) + 1] = '_'; break;

                case 4:
                    digits[2][(position * 4)] = '|'; break;

                case 5:
                    digits[1][(position * 4)] = '|'; break;

                case 6:
                    digits[1][(position * 4) + 1] = '_'; break;
	        }
        }
    }
}

void print_digits_array(void) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < MAX_DIGITS * 4; j++) {
            printf("%c", digits[i][j]);
        }
        printf("\n");
    }
}

int main(void)
{
	int user_number[MAX_DIGITS];
	
	printf("Enter a number (up to 10 digits long): ");

    for (int i = 0; i < MAX_DIGITS; i++) {
        user_number[i] = getchar() - '0';
        if (user_number[i] < 0 || user_number[i] > 9)
            user_number[i--] = 0;
        if (user_number[i] == '\n')
            break;
    }

	clear_digits_array();

	for (int i = 0; i < MAX_DIGITS; i++)
		process_digit(user_number[i], i);

    print_digits_array();

    return 0;
}
