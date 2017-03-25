#include <iostream>

int main()
{
	var table = new Array{ "Hello", 10, "World", 20, 30 };
	std::cout << table[0] << std::endl; // returns "Hello"
	std::cout << table << std::endl; // returns ["Hello", 10, "World", 20, 30]
}