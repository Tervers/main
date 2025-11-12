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


//          Example: Using External Variables to Implement a Stack
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


//          Pros and Cons of External Variables


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


//          Guessing a Number          guess.c


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



