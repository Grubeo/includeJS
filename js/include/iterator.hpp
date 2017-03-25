#ifndef _JS_ITERATOR_HPP
#define _JS_ITERATOR_HPP

#include "Atom.hpp"
#include "Number.hpp"
#include "string.hpp"
#include "function.hpp"
#include <string>
namespace js
{
    class iterator
    {
        Atom **it;
        Atom *parent;
    public:
        iterator(Atom **x, Atom *p = nullptr);
        iterator(double num);
        iterator(std::string str);
        iterator(Atom*);
        iterator(std::nullptr_t& nil);

        iterator& operator=(const iterator&);
        iterator& operator=(Atom *ptr);
        iterator& operator=(std::string str);
        iterator& operator=(int num);
        iterator& operator=(double num);
        iterator& operator+=(int num);
        iterator& operator+=(iterator&&);

        operator Atom*() const;
        Atom* operator*();

        iterator operator[](const int);
        iterator operator[](const std::string);

        Atom* operator->() const { return *it; }

        Atom* operator()();
        bool isNull();
        Atom* getParent();
    };

    template<typename T> T* cast(const js::iterator& it)
    {
        return (T*)((js::Atom*) it);
    }
}

bool operator==(js::iterator& it, std::nullptr_t&);
bool operator!=(js::iterator& it, std::nullptr_t&);

bool operator==(const js::iterator &it, double rhs);
js::iterator operator/(js::iterator& lhs, js::iterator& rhs);

#endif
