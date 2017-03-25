#include <iostream>

int main()
{
    var Pair = new Function(INLINE_ARG {
        that["first"] = arguments[0];
		that["second"] = arguments[1];
        return null;
    });

	var dogs = Pair("Spike", "Doge");
    std::cout << dogs << std::endl;
}
