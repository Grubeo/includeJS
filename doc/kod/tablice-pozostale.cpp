#include "js/index.html"

int main()
{
	using namespace js;
	
	var table = new Array{ 39, 10, 12, 20 };
	var table_reversed = cast<Array>(table).reverse();
	
	auto compare = [](iterator leftIt, iterator rightIt)->bool {
        if((*leftIt)->type() == "number" && (*rightIt)->type() == "number") {
            auto left = cast<Number>(leftIt);
            auto right = cast<Number>(rightIt);
            return ( left->get() < right->get() );
        } else return false;
    };
	
	var table_sorted = cast<Array>(table).sort(compare);
	
	var small_1 = new Array{3, 4};
	var small_2 = new Array{"Hello", "World"};
	
	var table_concat = cast<Array>(table).concat(small_1, small_2);
}
