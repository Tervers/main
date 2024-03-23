#include <stdio.h>

int main()
{
	int radius;
	float equation = (4.0f / 3.0f);
	float pi = 3.1415;

	printf("Enter radius (meters): \n");
	scanf("%d", &radius);

	printf("The volume of a sphere with radius of %d meters is %f.\n", radius, (pi * equation * (radius * radius * radius)));

	return 0;

}
