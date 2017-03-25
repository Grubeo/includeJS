#include "../include/hidden_util.hpp"

js::Atom* js::util::deepCopy(js::Atom *arg)
{
    std::string arg_type = arg->type();
    js::Atom *retVal = nullptr;

    if(arg_type == "Object") {
        Object *direct = new Object;
        *direct = *dynamic_cast<Object*>(arg);
        retVal = direct;
    }
    else if(arg_type == "number") {
        retVal = new Number(*dynamic_cast<Number*>(arg));
    }
    else if(arg_type == "Array") {
        Array *direct = new Array;
        *direct = *dynamic_cast<Array*>(arg);
        retVal = direct;
    }
    else if(arg_type == "string") {
        retVal = new string(*dynamic_cast<string*>(arg));
    }
    else if(arg_type == "function") {
        retVal = new Function(*dynamic_cast<Function*>(arg));
    }

    return retVal;
}
