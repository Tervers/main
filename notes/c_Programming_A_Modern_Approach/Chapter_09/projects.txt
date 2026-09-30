/*** CHAPTER                          9                           PROJECTS ***/


1. Write a program that asks the user to enter a series of integers (which it
    stores in an array), then sorts the integers by calling the function
    selection_sort. When given an array with n elements, selection_sort must do
    the following:

    1. Search the array to find the largest element, then move it to the last
        position in the array.
    2. Call itself recursively to sort the first n - 1 elements of the array.

#include <stdio.h>

void selection_sort(int a[], int n)
{
    int largest = 0, hold = 0;

    if (n == 1)
        return;

    for (int i = 0; i < n - 1; i++)
        if (a[i] > largest){
            largest = a[i];
            hold = a[n - 1];
            a[n - 1] = largest;
            a[i] = hold;
        }

    return selection_sort(a, n - 1);
}

int main(void)
{
    int n = 0;

    printf("How many numbers do you need to sort?\n");
    scanf("%d", &n);

    int a[n];

    printf("Enter the numbers:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    selection_sort(a, n);

    printf("The numbers in sorted order: ");
    for (int i = 0; i < n - 1; i++)
        printf("%d, ", a[i]);

    printf("%d\n", a[n - 1]);

    return 0;
}


2. Modify Programming Project 5 from Chapter 5 so that it uses a function to
    compute the amount of income tax. When passed an amount of taxable income,
    the function will return the tax due.

#include <stdio.h>

float compute(int);

int main(void)
{
    int income = 0;

    printf("Enter income:\n");
    scanf("%d", &income);

    printf("Tax due is: $%.2f\n", compute(income));

    return 0;
}

float compute(int income)
{
    if (income < 750)
        return income * 0.01f;

    else if (income >= 750 && income <= 2249)
        return (((income - 750) * 0.02) + 7.50f);

    else if (income >= 2250 && income <= 3749)
        return (((income - 2250) * 0.02) + 37.50f);

    else if (income >= 3750 && income <= 5249)
        return (((income - 3750) * 0.02) + 82.50);

    else if (income >= 5250 && income <= 6999)
        return (((income - 5250) * 0.02) + 142.50);

    else if (income >= 7000)
        return (((income - 7000) * 0.02) + 230.00f);

    else {
        printf("Try again.\n");
        return 0;
    }
}


3. Modify Programming Project 9 from Chapter 8 so that it includes the
    following functions:
        void generate_random_walk(char walk[10][10]);
        void print_array(char walk[10][10]);

    main first calls generate_random_walk, which initializes the array to
    contain '.' characters and then replaces some of these characters by the
    letters A through Z, as described in the original project. main then calls
    print_array to display the array on the screen.

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define X 10
#define Y 10
#define NoD 4   //Number of Directions

void generate_random_walk(char grid[Y][X]);
void print_array(char grid[Y][X]);

int main(void)
{
    bool u = 0, r = 0, d = 0, l = 0;
    short y, x, dir;
    char grid[Y][X], walk = 'A';

    srand((unsigned) time(NULL));

void generate_random_walk(char grid[Y][X])
{
    for (y = 0; y < Y; y++) {
        for (x = 0; x < X; x++) {
            grid[y][x] = '.';
        }
    }

    for (y = 0, x = 0;;walk++) {
        grid[y][x] = walk;
        if (walk == 'Z') {
            break;
        }

        retry:

        if (u && r && d && l) {
            printf("The walk was unable to finish it's course...\n\n");
            break;
        }

        dir = rand() % NoD;

        switch (dir) {
            case 0:
                if ((y - 1) < 0 || grid[y - 1][x] != '.') {
                    u = 1;
                    goto retry;
                }
                y--;
                u = 0; r = 0; d = 1; l = 0;
                break;

            case 1:
                if ((x + 1) > 9 || grid[y][x + 1] != '.') {
                    r = 1;
                    goto retry;
                }
                x++;
                u = 0; r = 0; d = 0; l = 1;

            case 2:
                if ((y + 1) > 9 || grid[y + 1][x] != '.') {
                    d = 1;
                    goto retry;
                }
                y++;
                u = 1; r = 0; d = 0; l = 0;
                break;

            case 3:
                if ((x - 1) < 0 || grid[y][x - 1] != '.') {
                    l = 1;
                    goto retry;
                }
                x--;
                u = 0; r = 1; d = 0; l = 0;
                break;
            }
        }
}

void print_array(char grid[Y][X])
{
    for (y = 0; y < Y; y++) {
        for (x = 0; x < X; x++) {
            printf("%c ", grid[y][x]);
        }
        printf("\n");
    }
}

    generate_random_walk(grid);
    print_array(grid);

    return 0;
}


4. Modify Programming Project 16 from Chapter 8 so that it includes the
    following functions:
        void read_word(int counts[26]);
        bool equal_array(int counts1[26], int counts2[26]);

    main will call read_word twice, once for each of the two words entered by
    the user. As it reads a word, read_word will use the letters in the word to
    update the counts array, as described in the original project. (main will
    declare two arrays, one for each word. These arrays are used to track how
    many times each letter occurs in the words.) main will then call
    equal_array, passing it the two arrays. equal_array will return true if the
    elements in the two arrays are identical (indicating that the words are
    anagrams) and false otherwise.

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

void read_word(int counts[26]);
bool equal_array(int counts1[26], int counts2[26]);

int main(void)
{
    int i, first_word[26] = {0}, second_word[26] = {0};
    char ch;

    printf("Enter first word: \n");

    void read_word(int counts[26])
    {
        for(;;) {
            ch = getchar();
            if (ch == '\n')
                break;
            else if (isalpha(ch)) {
                if (ch >= 'A' && ch <= 'Z')
                    counts[ch - 'A'] += 1;
                else if (ch >= 'a' && ch <= 'z')
                    counts[ch - 'a'] += 1;
            }
        }
    }

    read_word(first_word);

    printf("Enter second word: \n");
    read_word(second_word);

    bool equal_array(int counts1[26], int counts2[26])
    {          
        for (i = 0;i <= 25;i++) 
            if (first_word[i] != second_word[i])
                return 1;
            if (first_word[25] == second_word[25])
                return 0;

    }

    if (equal_array(first_word, second_word)){
        printf("These words are not anagrams.\n");
        return 0;
    }

    else {
        printf("These words are anagrams.\n");
        return 0;
    }
}


5. Modify Programming Project 17 from Chapter 8 so that it includes the
    following functions:
        void create_magic_square(int n, char magic_square[n][n]);
        void print_magic_square(int n, char magic_square[n][n]);

    After obtaining the number n from the user, main will call
    create_magic_square, pissing it an n x n array that is declared inside
    main. create_magic_square will fill the array with the numbers 1, 2, n^2 as
    described in the original project. main will then call print_magic_square,
    which will display the array in the format described in the original
    project.
 
I never finished that project........


6. Write a function that computes the value of the following polynomial:
    3x^5 + 2x^4 - 5x^3 - x^2 + 7x - 6

    Write a program that asks the user to enter a value for x, calls the
    function to compute the value of the polynomial, and then displays the
    value returned by the function.

#include <stdio.h>

int compute(int x);

int main(void)
{
    int x = 0;

    printf("We are going to compute this polynomial: ");
    printf("3x^5 + 2x^4 - 5x^3 - x^2 + 7x - 6\n");
    printf("Enter a value for x: ");
    scanf("%d", &x);

    printf("When the value of x is %d, the polynomial calculates out to ", x);
    printf("%d.\n", compute(x));

    return 0;
}

int compute(int x)
{
    int total = 0;

    total =  3 * (x * x * x * x * x) + 2 * (x * x * x * x) - 5 * (x * x * x);
    total = total - (x * x) + 7 * x - 6;

    return total;
}


7. The power function of Section 9.6 can be made faster by having it calculate
    x^n in a different way. We first notice that if n is a power of 2, then x^n
    can be computed by squaring. For example, x^4 is the square of x^2, so x^4
    can be computed using only two multiplications instead of three. As it
    happens, this technique can be used even when n is not a power of 2. If n
    is even, we use the formula x^n = ( x^n/2 )^2. If n is odd, then
    x^n = x * x^n-1. Write a recursive function that computes x^n. (The
    recursion ends when n = 0, in which case the function returns 1.) To test
    your function, write a program that asks the user to enter values for x and
    n, calls power to compute x^n, and then displays the value returned by the
    function.

#include <stdio.h>

int power(int x, int n)
{
    if (n == 0)
        return 1;
        
    if (n % 2 != 0)
        return (x * power(x, n - 1));

    if (n % 2 == 0)
        return power(x, n / 2) * power(x, n / 2);
}

int main(void)
{
    int x = 0, n = 0;
    printf("Enter a number for x: ");
    scanf("%d", &x);

    printf("Enter a number for the power you are multiplying x by: ");
    scanf("%d", &n);

    printf("The product of %d multiplied to the power of %d is: ", x, n);
    printf("%d.", power(x, n));

    return 0;
}


8. Write a program that simulates the game of craps, which is played with two
    dice. On the first roll, the player wins if the sum of the dice is 7 or 11.
    The player loses if the sum is 2, 3, or 12. Any other roll is called the
    "point" and the game continues. On each subsequent roll, the player wins if
    he or she rolls the point again. The player loses by rolling 7. Any other
    roll is ignored and the game continues. At the end of each game, the
    program will ask the user whether or not to play again. When the user
    enters a response other than y or Y, the program will display the number of
    wins and losses and then terminate.

    You rolled: 8
    Your point is 8
    You rolled: 3
    You rolled: 10
    You rolled: 8
    You win!

    Play again? _y_

    You rolled: 6
    Your point is 6
    you rolled: 5
    you rolled: 12
    you rolled: 3
    you rolled: 7
    You lose!

    Play again? _y_

    You rolled: 11
    You win!

    Play again? _n_

    Wins: 2  Losses: 1

    Write your program as three functions: main, roll_dice, and play_game. Here
    are the prototypes for the latter two functions:
        int roll_dice(void);
        bool play_game(void);

    roll_dice should generate two random numbers, each between 1 and 6, and
    return their sum. play_game should play one craps game (calling roll_dice
    to determine the outcome of each dice roll); it will return true if the
    player wins and false if the player loses. play_game is also responsible
    for displaying messages showing the results of the player's dice rolls.
    main will call play_game repeatedly, keeping track of the number of wins
    and losses and displaying the "you win" and "you lose" messages. Hint: Use
    the rand function to generate random numbers. See the deal.c program in
    Section 8.2 for an example of how to call rand and the related srand
    function.

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int roll_dice(void);
bool play_game(void);

int main(void)
{
    int wins = 0, losses = 0;
    bool result;
    char answer = 'y';

    srand((unsigned) time(NULL));

    while (answer == 'y' || answer == 'Y') {
        result = play_game();
        if (result == true){
            wins++;
            printf("You won!\n\n");
        }

        if (result == false){
            losses++;
            printf("You lose.\n\n");
        }
            
        printf("Play again? (press y to play again");
        printf(", or any other button to exit): ");
        scanf(" %c", &answer);
    }

    printf("Wins: %d  Losses: %d\n", wins, losses);

    return 0;
}

int roll_dice(void)
{
    int dice1 = 0, dice2 = 0, total = 0;

    dice1 = rand() % 6;
    dice2 = rand() % 6;
    
    total = dice1 + dice2 + 2;

    return total;
}

bool play_game(void)
{
    int roll = 0, point = 0, reroll;
    
    roll = roll_dice();
    point = roll;
    printf("You rolled: %d\n", roll);
   
    switch (roll) {
        case 2: case 3: case 12:
            return false;

        case 7: case 11:
            return true;

        case 4: case 5: case 6: case 8: case 9: case 10:
            printf("Your point is %d\n", point);
            for (;;){
                reroll = roll_dice();
                printf("You rolled: %d\n", reroll);
                if (reroll == point)
                    return true;
                if (reroll == 7)
                    return false;
            }
    }
}
