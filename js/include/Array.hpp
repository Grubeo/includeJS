#ifndef _JS_ARRAY_HPP
#define _JS_ARRAY_HPP

#include "Atom.hpp"
#include "iterator.hpp"
#include <vector>
#include <string>
#include <iterator>
#include <functional>
#include <algorithm>

namespace js
{
    class Array : public Atom
    {
        std::vector<Atom*> tab;

    public:
        Array();

        template<typename ...T> Array(T&&...t);
        ~Array();

        Array& operator=(const Array&);
        iterator operator[](const std::size_t it);
        std::size_t length() { return tab.size(); }
        std::string toString();
        void push(iterator&& it);
        void push(iterator& it);
        void for_each(std::function<void(std::size_t, iterator element)>);
        std::string join(std::string);
        Array* sort(std::function<bool(iterator,iterator)>);
        Array* reverse();

        // for c++ iterators
        std::vector<Atom*>::iterator begin() { return tab.begin(); }
        std::vector<Atom*>::iterator end() { return tab.end(); }

        template<typename T> Array* concat(const T&);
        template<typename T, typename... Args> Array* concat(const T&, const Args&...);
    };
}

#define forEach(code) for_each([&](std::size_t position, js::iterator element) code)

namespace std
{

}

#endif
