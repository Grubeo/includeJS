#ifndef JAVASCRIPT_IN_CPP
#define JAVASCRIPT_IN_CPP
    #if __cplusplus>201103L

        #include "include/Atom.hpp"
        #include "include/hidden_util.hpp"
        #include "include/Object.hpp"
        #include "include/Array.hpp"
        #include "include/string.hpp"
        #include "include/function.hpp"
        #include "include/var.hpp"
        #include "include/Number.hpp"
        #include "include/iterator.hpp"
        #include "include/math.hpp"

        #include "src/hidden_util.cpp"
        #include "src/Object.cpp"
        #include "src/Array.cpp"
        #include "src/string.cpp"
        #include "src/Number.cpp"
        #include "src/function.cpp"
        #include "src/var.cpp"
        #include "src/iterator.cpp"

        #include "JSON_io.cpp"
        #include "util.cpp"

        #define INLINE [&](js::iterator&& that)->js::Atom*
        #define INLINE_ARG [&](js::iterator&& that, js::iterator &&arguments)->js::Atom*

        #define is ,
        #define null nullptr


    #else
        #error You must have minimum C++11 compiler!
    #endif
#endif
