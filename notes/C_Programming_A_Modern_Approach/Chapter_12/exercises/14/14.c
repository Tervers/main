/*

Assume that the following array contains a week's worth of hourly temperature
    readings, with each row containing the readings for one day:

int temperatures[7][24];

Write a statement that uses the search function (see Exercise 7) to search the
    entire temperatures array for the value 32.

*/

bool search(const int a[], int n, int key)
{
    const int *p = a;

    for (p = a; p < a + n; p++)
        if (key == *p)
            return true;

    return false;
}

int main(void)
{
    int key;
    const int temperatures[7][24];

    printf("What temperature are you looking for?");
    scanf("%d", &key);

    search(temperatures[0], 7 * 24, key);
}
