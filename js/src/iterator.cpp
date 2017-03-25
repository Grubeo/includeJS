#include "../include/iterator.hpp"

js::iterator::iterator(js::Atom **x, js::Atom *p)
    : it(x), parent(p) {}

js::iterator::iterator(js::Atom *x)
    : it(&parent), parent(x) {}


js::iterator::iterator(double num)
    : parent(nullptr)
{
    parent = new js::Number(num);
    it = &parent;
}

js::iterator::iterator(std::string str)
    : parent(nullptr)
{
    parent = new js::string(str);
    it = &parent;
}

js::iterator::iterator(std::nullptr_t& nil)
    : it(nil), parent(nil)
{

}

bool js::iterator::isNull()
{
    return it == nullptr;
}

bool operator==(js::iterator& it, std::nullptr_t&)
{
    return it.isNull();
}

bool operator!=(js::iterator& it, std::nullptr_t&)
{
    return !it.isNull();
}

js::iterator& js::iterator::operator=(const iterator &arg)
{
    this->operator=((Atom*)arg);
    return *this;
}

js::iterator& js::iterator::operator=(js::Atom *ptr)
{
    if(*it == nullptr)
        delete *it;
    *it = ptr;
    return *this;
}
js::iterator& js::iterator::operator=(std::string str)
{
    if(*it == nullptr)
        delete *it;
    *it = new js::string(str);
    return *this;
}
js::iterator& js::iterator::operator=(int num)
{
    if(*it == nullptr)
        delete *it;
    *it = new js::Number(num);
    return *this;
}

js::iterator& js::iterator::operator=(double num)
{
    if(*it == nullptr)
        delete *it;
    *it = new js::Number(num);
    return *this;
}

js::iterator::operator js::Atom* () const
{
    return *it;
}

js::Atom* js::iterator::operator*()
{
    if(it == nullptr) {
        return nullptr;
    }
    return *it;
}

js::iterator& js::iterator::operator+=(int num)
{

    if((*it)->type() == "number") {
        js::Number *ptr = static_cast<js::Number*>(*it);
        ptr->set(ptr->get() + num);
    }
    return *this;
}

js::iterator& js::iterator::operator+=(js::iterator&& right)
{
    if((*it)->type() == "number") {
        if((*right)->type() == "number") {
            js::Number *ptr = static_cast<js::Number*>(*it);
            js::Number *ptr2 = static_cast<js::Number*>(*right);
            ptr->set(ptr->get() +  ptr2->get());
        }
    }
    return *this;
}

js::Atom* js::iterator::getParent()
{
    return parent;
}

js::Atom* js::iterator::operator()()
{
    if((*it)->type() == "function")
    {
        return ((Function*)(*it))->operator()(parent);
    } else return nullptr;
}

std::ostream& operator<<(std::ostream& os, js::iterator&& it)
{
    os << (*it)->toString();
    return os;
}

js::iterator operator*(const js::iterator &lhs, const js::iterator &rhs)
{
    return *((js::Atom*)lhs) * (*((js::Atom*)rhs));
}

bool operator==(const js::iterator &it, double rhs)
{
    return static_cast<js::Number*>(static_cast<js::Atom*>(it))->get() == rhs;
}

js::iterator operator-(const js::iterator &lhs)
{
    js::iterator temp(-1);
    js::iterator ret = lhs * std::move(temp);
    return ret;
}

js::iterator operator/(const js::iterator &lhs, const js::iterator &rhs)
{
    return *((js::Atom*)lhs) / *((js::Atom*)rhs);
}
