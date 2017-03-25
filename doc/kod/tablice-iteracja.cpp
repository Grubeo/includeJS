#include "js/index.hpp"

int main()
{
	using namespace js;
	
	var table = new Array{ "Hello", 10, "World", 20 };
	std::string result1, result2, result3;

	// 1
    for(auto &x : cast<Array>(table))
        result1 += x->toString() + ' ';

    // 2
    cast<Array>(table).forEach({
        result2 += element->toString() + ' ';
    });

    // 3
    for(std::size_t i=0; i < cast<Array>(table).length(); i++)
        result3 += table[i]->toString() + ' ';

}
