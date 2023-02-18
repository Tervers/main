#include <iostream>
int main()
{
	int i = 3, i2 = 5;
	int &ival = i, &ival2 = i2;
	int *p1, *p2;
		std::cout << *p1 + &ival2 << std::endl;
		std::cout << *p2 * &ival << std::endl;
	*p1 = &ival2;
		std::cout << *p1 + ival << std::endl;
		return 0;
}
