#include <stdio.h>

int main(void)
{
    int m1, m2, m3, d1, d2, d3, y1, y2, y3;

    for (;;) {
        printf("Enter a date (mm/dd/yy): ");
        scanf("%d/%d/%d", &m1, &d1, &y1);

    if (y1 == 0 && m1 == 0 && d1 == 0) {
        printf("%2.2d/%2.2d/%2.2d is the earliest date", m3, d3, y3);
        return 0;   }

        else if (y1 < y2) {
            y3 = y1;
            m3 = m1;
            d3 = d1; }

        else if (y1 == y2 && m1 < m2) {
            y3 = y1;
            m3 = m1;
            d3 = d1; }

        else if (y1 == y2 && m1 == m2 && d1 < d2) {
            y3 = y1;
            m3 = m1;
            d3 = d1; }

        else if (y2 < y1) {
            y3 = y2;
            m3 = m2;
            d3 = d2; }

        else if (y2 == y1 && m2 < m1) {
            y3 = y2;
            m3 = m2;
            d3 = d2; }

        else if (y2 == y1 && m2 == m1 && d2 < d1) {
            y3 = y2;
            m3 = m2;
            d3 = d2; }

        else {
            y3 = y1;
            m3 = m1;
            d3 = d1;
            }
        }
