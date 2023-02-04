#include <iostream>
int main()
{
	int sum = 0;
	for (int val = 1; val <= 200; ++val)
		sum += val;
	std::cout << "1 to 200 inclusive is " << sum << std::endl;
	return 0;
}
