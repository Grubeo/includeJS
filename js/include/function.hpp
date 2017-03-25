#ifndef _JS_FUNCTION_HPP
#define _JS_FUNCTION_HPP

#include "Atom.hpp"
#include <functional>
#include "iterator.hpp"
#include <string>

namespace js
{
    Atom* standard(Atom*);

    class Function : public Atom
    {
        union {
            std::function<Atom*(Atom*)> func;
            std::function<Atom*(Atom*, Atom*)> func2arg;
        };
    public:
        unsigned short args;

        ~Function() {}
        Function(std::function<Atom*(Atom*)> f = standard);
        Function& operator=(std::function<Atom*(Atom*)>);

        Function(std::function<Atom*(Atom*, Atom*)>);
        Function& operator=(std::function<Atom*(Atom*, Atom*)>);

        Function(const Function&);

        Atom* that;
        Atom* operator()(Atom*);
        Atom* operator()(Atom*, Atom*);
        std::string toString();
    };
}

#endif
