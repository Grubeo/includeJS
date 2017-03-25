#ifndef _JS_STRING_HPP
#define _JS_STRING_HPP

#include <string>

namespace js
{
    class string : public Atom
    {
        std::string content;
    public:
        string(std::string str);

        std::string get();
        void set(std::string str);

        std::string toString(); 
    };
}

#endif
