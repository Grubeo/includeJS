#include "../include/Number.hpp"
#include <cmath>

js::Number::Number(double n)
    : Atom("number"), num(n) {}

double js::Number::get()
{
    return num;
}

void js::Number::set(double x)
{
    num = x;
}

js::Number::operator double()
{
    return num;
}

js::Number::operator int()
{
    return std::round(num);
}

std::string js::Number::toString()
{
    return std::to_string(num);
}
