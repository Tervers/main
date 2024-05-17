#include <stdio.h>
#include <ctype.h>

#define AVG ((dep[i + 1] - dep[i]) / 2)//the average between two departure times

int main(void)
{
    short uh, um, cm, i;//user hour, user minute, converted min
    short dep[8] = {480, 583, 679, 767, 840, 945, 1140, 1305};
    short arr[8] = {616, 712, 811, 900, 968, 1075, 1280, 1438};
    char mer;

    printf("Enter a 12-hour time: ");
    scanf("%2hd:%2hd %c", &uh, &um, &mer);

    mer = toupper(mer);

    if (mer == 'P' && uh != 12)
        cm = (((uh * 60) + um) + 720);
    else if (mer == 'A' || mer == 'P' && uh == 12)
        cm = ((uh * 60) + um);
    else
        printf("Invalid time.\n");

    printf("%hd\n", cm);

    for (i = 0; i < 8; i++){
            if (cm <= AVG && dep[i] < 720 && arr[i] < 720) {
                    printf("Closest departure time is %2.2hd:%2.2hda.m.,", dep[i] / 60, dep[i] % 60);
                    printf("arriving at %2.2hd:%2.2hda.m.\n", arr[i] / 60, arr[i] % 60);
                    break;
            }
            if (cm >= AVG && dep[i] < 720 && arr[i] < 720) {
                    printf("Closest departure time is %2.2hd:%2.2hda.m.,", dep[i] / 60, dep[i] % 60);
                    printf("arriving at %2.2hd:%2.2hda.m.\n", arr[i] / 60, arr[i] % 60);
                    break;
            }


            if (cm <= AVG && dep[i] < 720 && arr[i] > 720 && arr[i] < 780) {
                    printf("Closest departure time is %2.2hd:%2.2hda.m.,", dep[i] / 60, dep[i] % 60);
                    printf("arriving at %2.2hd:%2.2hdp.m.\n", arr[i] / 60, arr[i] % 60);
                    break;
            }
            if (cm >= AVG && dep[i] < 720 && arr[i] > 720 && arr[i] < 780) {
                    printf("Closest departure time is %2.2hd:%2.2hda.m.,", dep[i] / 60, dep[i] % 60);
                    printf("arriving at %2.2hd:%2.2hdp.m.\n", arr[i] / 60, arr[i] % 60);
                    break;
            }


            if (cm <= AVG && dep[i] > 720 && dep[i] < 780 && arr[i] > 720 && arr[i] < 780) {
                    printf("Closest departure time is %2.2hd:%2.2hdp.m.,", dep[i] / 60, dep[i] % 60);
                    printf("arriving at %2.2hd:%2.2hdp.m.\n", arr[i] / 60, arr[i] % 60);
                    break;
            }
            if (cm >= AVG && dep[i] > 720 && dep[i] < 780 && arr[i] > 720 && arr[i] < 780) {
                    printf("Closest departure time is %2.2hd:%2.2hda.m.,", dep[i] / 60, dep[i] % 60);
                    printf("arriving at %2.2hd:%2.2hdp.m.\n", arr[i] / 60, arr[i] % 60);
                    break;
            }


            if (cm <= AVG && dep[i] > 780 && dep[i] < 780 && arr[i] > 780) {
                    printf("Closest departure time is %2.2hd:%2.2hdp.m.,", dep[i] / 60, dep[i] % 60);
                    printf("arriving at %2.2hd:%2.2hdp.m.\n", ((arr[i] - 720) / 60), arr[i] % 60);
                    break;
            }
            if (cm >= AVG && dep[i] > 780 && dep[i] < 780 && arr[i] > 780) {
                    printf("Closest departure time is %2.2hd:%2.2hda.m.,", dep[i] / 60, dep[i] % 60);
                    printf("arriving at %2.2hd:%2.2hdp.m.\n", ((arr[i] - 720) / 60), arr[i] % 60);
                    break;
            }


            if (cm <= AVG && dep[i] > 780 && arr[i] > 780) {
                    printf("Closest departure time is %2.2hd:%2.2hda.m.,", ((dep[i] - 720) / 60), dep[i] % 60);
                    printf("arriving at %2.2hd:%2.2hdp.m.\n", ((arr[i] - 720) / 60), arr[i] % 60);
                    break;
            }
            if (cm >= AVG && dep[i] > 780 && arr[i] > 780) {
                    printf("Closest departure time is %2.2hd:%2.2hda.m.,", ((dep[i] - 720) / 60), dep[i] % 60);
                    printf("arriving at %2.2hd:%2.2hdp.m.\n", ((arr[i] - 720) / 60), arr[i] % 60);
                    break;
            }
    }
    return 0;
}

