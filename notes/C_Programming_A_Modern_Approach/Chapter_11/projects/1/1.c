/*
Modify Programming Project 7 from Chapter 2 so that it includes the following
    function:
    void pay_amount(int dollars, int *twenties, int *tens,
                    int *fives, int *ones);
*/

#include <stdio.h>

void pay_amount(int dollars, int *twenties, int *tens,
                int *fives, int *ones);

int main(void)
{
	int dollars = 0, twenties = 0, tens = 0, fives = 0, ones = 0;

	printf("Enter dollar amount to pay: \n");
	scanf("%d", &dollars);

    pay_amount(dollars, &twenties, &tens, &fives, &ones);

	printf("$20 bills: %d\n", twenties);
	printf("$10 bills: %d\n", tens);
	printf("$5 bills: %d\n", fives);
	printf("$1 bills: %d\n", ones);

	return 0;
}

void pay_amount(int dollars, int *twenties, int *tens,
                int *fives, int *ones)
{
    *twenties = dollars / 20;
    dollars -= (20 * (dollars / 20));
    *tens = dollars / 10;
    dollars -= (10 * (dollars / 10));
    *fives = dollars / 5;
    dollars -= (5 * (dollars / 5));
    *ones = dollars;
}