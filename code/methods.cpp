// A 'method' is properly called a 'member function'.
#include <iostream>
#include "sales_item.h"
int main()
{
	sales_item item1, item2;
	std::cin >> item1 >> item2;
	if (item1.isbn() == item2.isbn())  {
		std::cout << item1 + item2 << std::endl;
		return 0;
	} else {
		std::cerr << "Data must refer to same ISBN"
			<< std::endl;
		return -1;
	}
}
