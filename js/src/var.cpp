#include "../include/var.hpp"

js::var::var(js::Atom *p)
    : js::Atom(p->type()), ptr(p), parent(nullptr), deletePointers(true) {}

js::var::var(const js::var& v)
    : js::Atom(v.ptr->type()), ptr(v.ptr), parent(v.parent),  deletePointers(false) {}

js::var::var(js::var&& v)
    : js::Atom(v.ptr->type()), ptr(v.ptr), parent(v.parent), deletePointers(true)
{
    v.deletePointers = false;
}

js::var::var(js::iterator& it)
    : js::Atom((*it)->type()), ptr(*it),  parent(it.getParent()) {}

js::var::var(js::iterator&& it)
    :js::Atom((*it)->type()), ptr(*it),  parent(it.getParent()) {}

js::var::~var()
{
    if(deletePointers)
        delete ptr;
}

js::var::operator js::Atom*() const
{
    return ptr;
}

std::string js::var::toString()
{
    return ptr->toString();
}

js::var& js::var::operator=(js::iterator& it)
{
    ptr = (Atom*) it;
    parent = it.getParent();
    return *this;
}

js::iterator js::var::operator[] (const std::string str)
{
    if(ptr->type() == "Object") {
        return ((js::Object*)ptr)->operator[](str);
    } else throw "Bad operator!";
}

js::iterator js::var::operator[] (const int pos)
{
    if(ptr->type() == "Array") {
        return ((js::Array*)ptr)->operator[](pos);
    } else throw "Bad operator!";
}

js::Atom* js::var::operator()()
{

    if(ptr->type() == "function")
    {
        Function *direct_ptr = (Function*) ptr;
        if(parent == nullptr) {
            direct_ptr->that = new Object;
        } else direct_ptr->that = parent;

        js::Atom* ret;

        if(direct_ptr->args == 1) {
            ret = direct_ptr->operator()(direct_ptr->that);
        } else ret = direct_ptr->operator()(direct_ptr->that, nullptr);

        if(((Object*)direct_ptr->that)->lenght() == 0) {
            delete direct_ptr->that;
            direct_ptr->that = nullptr;
        }

        if(ret == nullptr) {
            return direct_ptr->that;
        }
        return ret;
    } else return nullptr;
}

js::Atom* js::var::operator()(const js::iterator &arg)
{
    if(ptr->type() == "function")
    {
        Function *direct_ptr = (Function*)ptr;
        if(parent == nullptr) {
            direct_ptr->that = new Object;
        } else direct_ptr->that = parent;

        js::Atom* ret;
        if(direct_ptr->args == 2) {
            ret = direct_ptr->operator()(direct_ptr->that, arg);
        } else throw "BAD EXEC";

        if(((Object*)direct_ptr->that)->lenght() == 0) {
            delete direct_ptr->that;
            direct_ptr->that = nullptr;
        }
        if(ret == nullptr) {
            return direct_ptr->that;
        }
        return ret;
    } else return nullptr;
}

template<typename T>
js::Atom* js::var::operator()(T val)
{
    return operator()(iterator(val));
}

template<typename T, typename ...Args>
js::Atom* js::var::operator()(T val, Args ...args)
{
    auto arr = new Array{iterator(val), iterator(args)...};
    return operator()(iterator(arr));
}


js::Atom* js::var::call(js::Atom* context)
{
    if(ptr->type() == "function")
    {
        Function *direct_ptr = (Function*) ptr;
        return direct_ptr->operator()(context);
    } else return nullptr;
}
