/*** CHAPTER                         11                          EXERCISES ***/


1. If i is a variable and p points to i, which of the following expressions are
    aliases for i?

    (a) *p      (c) *&p     (e) *i      (g) *&i
    (b) &p      (d) &*p     (f) &i      (h) &*i

Answer:
a, g

2. If i is an int variable and p and q are pointers to int, which of the
    following assignments are legal?

    (a) p = i;      (d) p = &q;     (g) p = *q;
    (b) *p = &i:    (e) p = *&q;    (h) *p = q;
    (c) &p = q;     (f) p = q;      (i) *p = *q;

Answer:
e, f, i

3. The following function supposedly computes the sum and average of the
    numbers in the array a, which has length n. avg and sum point to variables
    that the function should modify. Unfortunately, the function contains
    several errors; find and correct them.

    void avg_sum(double a[], int n, double *avg, double *sum)
    {
        int i;

        sum = 0.0;
        for (i = 0; i < n; i++)
            sum += a[i];
        avg = sum / n;
    }

Answer:

