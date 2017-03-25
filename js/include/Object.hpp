#ifndef _JS_OBJECT_HPP
#define _JS_OBJECT_HPP

#include "Atom.hpp"
#include "string.hpp"
#include "iterator.hpp"
#include "Array.hpp"

#include <unordered_map>
#include <string>
#include <vector>
#include <type_traits>

namespace js
{

    class Object : public Atom
    {
        std::unordered_map<std::string, js::Atom*> childrens;
        bool deallocate;
    public:
        Object *__proto__;

        Object() : Atom("Object"), __proto__(nullptr) {}
        template<typename ...T> Object(T&&...t);
        ~Object();

        Object& operator=(const js::Object&);
        iterator operator[](const std::string);
        template<typename T>
        iterator operator[](T str);
        std::vector<Atom*> pointers();
        std::string toString();
        std::size_t lenght() { return childrens.size(); }
        void remove(std::string name);

        static Object* setPrototypeOf(Object&, Object*);
        static Object* setPrototypeOf(Object*, Object*);
        static Array* keys(Object*);
    };
}
#endif
