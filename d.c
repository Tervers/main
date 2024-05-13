#include <stdio.h>

int main(void)
{
    int i, n = 1, digit, digit_seen[10] = {0};
    double user_numbers[n];

    printf("Enter any amount of numbers (0 or less to stop): ");

    for (i = 0;;n++, i++) {
        scanf(" %Lf", &user_numbers[i]);
        if (user_numbers[i] <= 0) {
            n--;
            break;
        }
    }

    //for loop for sequential array read, nesting the while loop below

    for (i = 0;i < n;i++) {
            while (user_numbers[i] > 0) {
                digit = user_numbers[i] % 10;
                digit_seen[digit] += 1;
                user_numbers[i] /= 10;
            }
        }

    printf("Digit:        0  1  2  3  4  5  6  7  8  9\n");
    printf("Occurrences:");

    for (int i = 0; i < (sizeof(digit_seen) / sizeof(digit_seen[0])); i++)
            printf("%3d", digit_seen[i]);

    printf("\n");

    return 0;
}
