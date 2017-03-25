#include "../include/string.hpp"

js::string::string(std::string str)
    : Atom("string"), content(str)  {}

std::string js::string::get()
{
    return content;
}

void js::string::set(std::string str)
{
    content = str;
}

std::string js::string::toString()
{
    return std::string("\"") + content + std::string("\"");
}
