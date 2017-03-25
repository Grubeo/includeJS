#include "Atom.hpp"
#include "Number.hpp"
#include <functional>

namespace js
{
    namespace __math__tools
    {
        template<typename T>
        Atom* bin_op(Atom *lhs, Atom *rhs, T op)
        {
            if(lhs->type() == rhs->type() && lhs->type() == "number") {
                Number *direct_lhs = static_cast<Number*>(lhs);
                Number *direct_rhs = static_cast<Number*>(rhs);
                return new Number(op(*direct_lhs, *direct_rhs));
            } else throw "I DON'T RECOGNIZE THAT TYPE";
            return NULL;
        }
    }
}

js::Atom* operator*(js::Atom &lhs, js::Atom &rhs)
{
    std::function<double(double,double)> mul = [](double lhs, double rhs)->double {
        return lhs*rhs;
    };
    return js::__math__tools::bin_op(&lhs, &rhs, mul);
}


js::Atom* operator/(js::Atom &lhs, js::Atom &rhs)
{
    std::function<double(double,double)> div = [](double lhs, double rhs)->double {
        return lhs/rhs;
    };
    return js::__math__tools::bin_op(&lhs, &rhs, div);
}
