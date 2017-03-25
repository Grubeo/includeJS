#include "../include/function.hpp"

 js::Atom* js::standard(js::Atom*)
 {
     return nullptr;
 }

 js::Function::Function(std::function<js::Atom*(js::Atom*)> f)
    : js::Atom("function"), func(f), args(1) {}

js::Function::Function(const js::Function &f)
    : js::Atom("function")
{
    if(f.args == 1)
        func = f.func;
    else func2arg = f.func2arg;
}

js::Function& js::Function::operator=(std::function<js::Atom*(js::Atom*)> f)
{
    args = 1;
    func = f;
    return *this;
}

js::Function::Function(std::function<js::Atom*(js::Atom*, js::Atom*)> f)
   : js::Atom("function"), func2arg(f), args(2) {}

js::Function& js::Function::operator=(std::function<js::Atom*(js::Atom*, js::Atom*)> f)
{
   args = 2;
   func2arg = f;
   return *this;
}


js::Atom* js::Function::operator()(js::Atom *sth)
{
    return func(sth);
}

js::Atom* js::Function::operator()(js::Atom *sth, js::Atom *obj)
{
    return func2arg(sth, obj);
}


std::string js::Function::toString()
{
    return "function()";
}
