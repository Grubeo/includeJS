#ifndef _JS_HIDDEN_UTIL_HPP
#define _JS_HIDDEN_UTIL_HPP

#include "Atom.hpp"
#include <utility>
#include <functional>

namespace js
{
    namespace util {
        js::Atom* deepCopy(js::Atom*);
    }
}

#endif
