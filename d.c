#include <stdio.h>

int main(void)
{
    int s, q, n;
    int sq[5][5] = {0}, stot[5] = {0}, savg[5] = {0};
    int qavg[5] = {0}, qtot[5] = {0}, qh[5] = {0}, ql[5] = {0};

    for (s = 0, n = 1; s <= 4; n++, s++) {
        printf("Enter student %d quiz grades: ", n);
        for (q = 0; q <= 4; q++) {
            scanf("%d", &sq[s][q]);
        }
    }

    for (s = 0; s <= 4; s++) {
        for (q = 0; q <= 4; q++) {

            stot[s] += sq[s][q];

            if (sq[s][4]) {
                savg[s] = (stot[s] / 5);
            }

            qtot[s] += sq[q][s];

            if (sq[4][q]) {
                qavg[s] = (qtot[s] / 5);
            }

            if (sq[q][s] > qh[s]) {
                qh[s] = sq[q][s];
            }
        }
    }

    printf("Student totals:");
    for (s = 0; s <= 4; s++)
        printf(" %d", stot[s]);

    printf("\nStudent averages:");
    for (s = 0; s <= 4; s++)
        printf(" %d", savg[s]);

    printf("\nQuiz averages:");
    for (q = 0; q <= 4; q++)
        printf(" %d", qavg[q]);

    printf("\nQuiz high scores:");
    for (q = 0; q <= 4; q++)
        printf(" %d", qh[q]);

    return 0;
}
