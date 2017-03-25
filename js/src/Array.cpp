#include "../include/Array.hpp"

js::Array::Array() : Atom("Array") {}

template<typename ...T> js::Array::Array(T&&...t) : Atom("Array"), tab({ *(iterator(t))...}) {}

js::Array& js::Array::operator=(const js::Array &arr)
{
    for(auto &x : arr.tab) {
        tab.push_back(js::util::deepCopy(x));
    }
}

js::Array::~Array()
{
    for(auto x : tab)
        delete x;
}

js::iterator js::Array::operator[](const std::size_t it)
{
    while(it >= tab.size()) {
        tab.push_back(nullptr);
    }

    return iterator(&(*(tab.begin() + it)), (Atom*) this);
}


std::string js::Array::toString()
{
    std::string ret = "[";
    for(auto x = tab.begin(); x != tab.end();)
    {
        std::string temp;
        if(*x == nullptr) {
            temp += "undefined";
        }
        else temp += (*x)->toString();
        if(++x != tab.end())
            temp += ", ";
        ret += temp;
    }
    ret += "]";
    return ret;
}

void js::Array::push(iterator&& it)
{
    tab.push_back(*it);
}

void js::Array::push(iterator& it)
{
    tab.push_back(*it);
}

std::ostream& operator<<(std::ostream& os, js::Array& arr)
{
    os << arr.toString();
    return os;
}

js::iterator js::iterator::operator[](const int pos)
{
    if((*it)->type() == "Array") {
        return ((Array*)(*it))->operator[](pos);
    } else return *this;
}

void js::Array::for_each(std::function<void(std::size_t, js::iterator element)> func)
{
    for(std::size_t i=0; i < length(); i++) {
        func(i, tab[i]);
    }
}

std::string js::Array::join(std::string connector)
{
    std::string str;
    for(std::size_t i=0; i < length(); i++) {
        str += tab[i]->toString();
        if(i != length()-1)
            str += connector;
    }
    return str;
}

js::Array* js::Array::sort(std::function<bool(iterator,iterator)> compare)
{
    std::sort(tab.begin(), tab.end(), compare);
    return this;
}

js::Array* js::Array::reverse()
{
    std::reverse(tab.begin(), tab.end());
    return this;
}

template<typename T> js::Array* js::Array::concat(const T& t)
{
    auto arr = js::cast<Array>((Atom*) t);

    for(auto x : arr->tab) {
        tab.push_back(js::util::deepCopy(x));
    }

    return this;
}

template<typename T, typename... Args> js::Array* js::Array::concat(const T& t,const Args&... args)
{
    auto arr = js::cast<Array>((Atom*) t);

    for(auto x : arr->tab) {
        tab.push_back(js::util::deepCopy(x));
    }
    return concat(args...);
}
