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

void avg_sum(double a[], int n, double *avg, double *sum)
{
	int i;

	*sum = 0.0;
	for (i = 0; i < n; i++)
		*sum += a[i];
	*avg = *sum / 2;
}



4. Write the following function:
	void swap(int *p, int *q);

When passed the addresses of two variables, swap should exchange the values of
	the variables:
	swap(&i, &j);	/* exchanges values of i and j */


Answer:

void swap(int *p, int *q)
{
	int swap;

	swap = *p;
	*p = *q;
	*q = swap;
}



5. Write the following function:
	void split_time(long total_sec, int *hr, int *min, int *sec);

total_sec is a time represented as the number of seconds since midnight. hr,
	min, and sec are pointers to variables in which the function will store the
	equivalent time in hours (0-23), minutes (0-59), and seconds (0-59)
	respectively.


Answer:

void split_time(long total_sec, int *hr, int *min, int *sec)
{
	*hr = ((total_sec / 60) / 60);
	*min = ((total_sec / 60) % 60);
	*sec = (total_sec % 60);
}



6. Write the following function:
	void find_two_largest(int a[], int n, int *largest, int *second_largest);

When passed an array a of length n, the function will search a for its largest
	and second largest elements, storing them in the variables pointed to by
	largest and second_largest, respectively.


Answer:

void find_two_largest(int a[], int n, int *largest, int *second_largest)
{
	*largest = a[0];
	*second_largest = a[1];

	for (int i = 0, i < n; i++) {
		if (a[i] > *largest) {
			*second_largest = *largest;
			*largest = a[i];
		}
		else if (a[i] > *second_largest)
			*second_largest = a[i];
	}
}



7. Write the following function:
	void split_date(int day_of_year, int year, int *month, int *day);

day_of_year is an integer between 1 and 366, specifying a particular day within
	the year designated by year. month and day point to variables in which the
	function will store the equivalent month (1-12) and day within that month
	(1-31).

//some bugs. should rewrite to assume leap year and fix the rest from there.
Answer:

void split_date(int day_of_year, int year, int *month, int *day)
{
    if (day_of_year <= 31) {
        *month = 1;
        *day = day_of_year;
    }
    else if (day_of_year >= 32 && day_of_year <= 59) {
        *month = 2;
        *day = day_of_year - 31;
    }
    else if (day_of_year >= 60 && day_of_year <= 90) {
        *month = 3;
        *day = day_of_year - 59;
    }
    else if (day_of_year >= 91 && day_of_year <= 120) {
        *month = 4;
        *day = day_of_year - 90;
    }
    else if (day_of_year >= 121 && day_of_year <= 151) {
        *month = 5;
        *day = day_of_year - 120;
    }
    else if (day_of_year >= 152 && day_of_year <= 181) {
        *month = 6;
        *day = day_of_year - 151;
    }
    else if (day_of_year >= 182 && day_of_year <= 212) {
        *month = 7;
        *day = day_of_year - 181;
    }
    else if (day_of_year >= 213 && day_of_year <= 243) {
        *month = 8;
        *day = day_of_year - 212;
    }
    else if (day_of_year >= 244 && day_of_year <= 273) {
        *month = 9;
        *day = day_of_year - 243;
    }
    else if (day_of_year >= 274 && day_of_year <= 304) {
        *month = 10;
        *day = day_of_year - 273;
    }
    else if (day_of_year >= 305 && day_of_year <= 334) {
        *month = 11;
        *day = day_of_year - 304;
    }
    else if (day_of_year >= 335 && day_of_year <= 365) {
        *month = 12;
        *day = day_of_year - 334;
    }

    if ((year % 4) && day_of_year >= 60 && (!(year % 100))
            || ((year % 400) && day_of_year >= 60)) {
        *day = *day - 1;
        if (*day == 0) {
            *month = *month - 1;
            switch (*month) {
                case 2: *day = 29; break;
                case 3: *day = 31; break;
                case 4: *day = 30; break;
                case 5: *day = 31; break;
                case 6: *day = 30; break;
                case 7: *day = 31; break;
                case 8: *day = 31; break;
                case 9: *day = 30; break;
                case 10: *day = 31; break;
                case 11: *day = 30; break;
            }
        }
    }
}



8. Write the following function:
    int *find_largest(int a[], int n);

When passed an array of length n, the function will return a pointer to the
    array's largest element.


Answer:

int *find_largest(int a[], int n)
{
    int largest = a[0], element = 0, i;
    
    for (i = 0; i < n; i++)
        if (a[i] > largest) {
            largest = a[i];
            element = i;
        }
    
    return &a[element];
}
