#include <stdio.h>

int main(void)
{
    short uh, um, ct;      //users entered hours, user minutes: converted time

    printf("Enter a 24-hour time: ");
    scanf("%2hd:%2hd", &uh, &um);

    ct = ((uh * 60) + um);

    if (ct <= 531)
        printf("Closest departure time is 8:00 a.m. arriving at 10:16 a.m.\n");
    else if (ct >=532 && ct <= 630)
        printf("Closest departure time is 9:43 a.m. arriving at 11:52 a.m.\n");
    else if (ct >=631 && ct <= 722)
        printf("Closest departure time is 11:19 a.m. arriving at 1:31 p.m.\n");
    else if (ct >=723 && ct <= 803)
        printf("Closest departure time is 12:47 p.m. arriving at 3:00 p.m.\n");
    else if (ct >=804 && ct <= 892)
        printf("Closest departure time is 2:00 p.m. arriving at 4:08 p.m.\n");
    else if (ct >=893 && ct <= 1042)
        printf("Closest departure time is 3:45 p.m. arriving at 5:55 p.m.\n");
    else if (ct >=1043 && ct <= 1139)
        printf("Closest departure time is 7:00 p.m. arriving at 9:20 p.m.\n");
    else
        printf("Closest departure time is 9:45 p.m. arriving at 11:58 p.m.\n");

    return 0;
}
