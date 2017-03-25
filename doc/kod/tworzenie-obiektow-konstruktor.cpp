#include <iostream>

int main()
{
    var Dog = new Function(INLINE {
        that["name"] = "Doge";
		that["sound"] = "Woof";
        return null;
    });
	
	var dog = Dog();
	
	std::cout << dog["name"] << " says " << dog["sound"];
}
