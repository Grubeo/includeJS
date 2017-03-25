#ifndef _JS_NUMBER_HPP
#define _JS_NUMBER_HPP

#include "Atom.hpp"

namespace js
{
    class Number : public Atom
    {
            double num;
        public:
            Number(double n);
            template<typename T> Number(T arg) : Atom("number"), num(arg) {}
            void set(double);
            double get();
            operator double();
            operator int();
            std::string toString();
    };
}

#endif
