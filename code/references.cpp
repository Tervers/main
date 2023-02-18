#include <iostream>
int main()
{
	int i, &ri = i;
	i = 5; ri = 10;
	std::cout << i << " " << ri << std::endl;
	//writes "10 10" to output due to ri changing
	//the value of i before i is called.
	return 0;
}
