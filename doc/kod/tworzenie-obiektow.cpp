#include <iostream>
#include "js/index.hpp"

int main()
{
    using namespace js;
	
	var object = new Object {
		"name" is "Doge",
		"sound" is "Woooof",
		"age" is 5
	};
	
	std::cout << object["name"] << '\n'; // returns "Doge"
	std::cout << object["sound"] << '\n'; // returns "Woooof"
	std::cout << object["age"] << '\n'; // returns 5
}