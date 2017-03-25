#ifndef _JS_VAR_HPP
#define _JS_VAR_HPP

#include "Atom.hpp"
#include "iterator.hpp"

namespace js
{
    class var : public Atom
    {
        Atom *ptr;
        Atom *parent;
        bool deletePointers;
    public:
        var(Atom *p);
        var(const var&);
        var(var&&);
        ~var();
        operator Atom*() const;
        std::string toString();

        var(js::iterator& it);
        var(js::iterator&& it);


        void waiveClaim(bool wc) { deletePointers = wc; }

        var& operator=(js::iterator& it);
        js::iterator operator[] (const std::string str);
        js::iterator operator[] (const int pos);
        Atom* call(Atom* context);
        Atom* operator()();
        Atom* operator()(const js::iterator&);

        template<typename T>
        Atom* operator()(T);

        template<typename T, typename ...Args>
        Atom* operator()(T,Args ...);
    };
}

#endif
