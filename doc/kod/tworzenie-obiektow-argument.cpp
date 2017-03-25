#include <iostream>

int main()
{
    var Dog = new Function(INLINE_ARG {
        that["name"] = *arguments;
		that["sound"] = "Woof";
        return null;
    });

	var dog = Dog("Spike");

	std::cout << dog["name"] << " says " << dog["sound"];
}
