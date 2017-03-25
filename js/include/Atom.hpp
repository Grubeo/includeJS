#ifndef _JS_ATOM_HPP
#define _JS_ATOM_HPP

namespace js
{
    class Atom
    {
        std::string obj_type;
    public:
        Atom(std::string t) : obj_type(t) {}
        virtual ~Atom() {}
        std::string type() { return obj_type; };
        virtual std::string toString() = 0;
    };


}

#include <sstream>
namespace std
{
    template<typename T>
    string to_string(T val)
    {
        std::stringstream ss;
        ss << val;
        return ss.str();
    }
}

std::ostream& operator<<(std::ostream& os, js::Atom *ptr)
{
    os << ptr->toString();
    return os;
}

template<typename T> T* cast(js::Atom*& v)
{
    return (T*)(v);
}

#endif
