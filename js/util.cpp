#ifndef _JS_UTIL_CPP
#define _JS_UTIL_CPP

#include "include/var.hpp"

namespace js
{
    void remove(js::var& Vit, std::string name)
    {
        js::Atom *it = Vit;
        if(it->type() == "Object") {
            js::Object *obj = static_cast<js::Object*>(it);
            obj->remove(name);
        }
    }

    template<typename Dest, typename Src>
    void copy(Dest dest, Src src)
    {
        dest = (js::Atom*) src;
    }

    template<typename Index, typename Dest, typename Src>
    void copy(Index index, Dest dest, Src src)
    {
        dest[index] = (js::Atom*) src[index];
    }

    template<typename T> T& cast(js::Atom *ptr)
    {
        return *((T*)ptr);
    }
}

#endif
