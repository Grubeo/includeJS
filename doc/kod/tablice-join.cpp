#include "js/index.hpp"

int main()
{
    using namespace js;
	var table = new Array{ "Hello", 10, "World", 20 };
	std::string result = cast<Array>(table).join(" ");
}
