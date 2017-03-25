#include <iostream>
#include "js/index.hpp"

int main()
{
    using namespace js;
	
	var object = new Object {
		"name" is "Doge",
		"sound" is "Woooof"
	};
	
	var say = new Function(INLINE{
		std::cout << that["name"] << " says " << that["sound"] << std::endl;
	});
	
	say.call(object);
}