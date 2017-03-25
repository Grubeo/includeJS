#include "../include/Object.hpp"


template<typename ...T> js::Object::Object(T&&...t)
    : js::Atom("Object"), deallocate(true), __proto__(nullptr)
{
    std::vector<Atom*> initializer = { *(iterator(t))...};

    if(initializer.size() % 2 != 0) {
        throw "Oh no! You must have even arg number!";
    }
    std::string entry_name;

    for(std::size_t i=0; i < initializer.size(); i++) {
            if(initializer[i] != nullptr){
                std::string type = initializer[i]->type();

                if(i%2 == 0) {
                    if(type == "string") {
                        entry_name = static_cast<js::string*>(initializer[i])->get();
                    }
                    else if(type == "number") {
                        entry_name = std::to_string( static_cast<js::Number*>(initializer[i])->get() );
                    }
                    else throw "ID must have type string or number!";
                }
                else {
                    operator[](entry_name) = initializer[i];
                }
            }
            else operator[](entry_name);
    }
}

js::Object& js::Object::operator=(const js::Object &obj)
{
    deallocate = true;
    for(auto &x : obj.childrens) {
        childrens[x.first] = js::util::deepCopy(x.second);
    }
}

js::Object::~Object()
{
    if(deallocate) {
        for(auto x : childrens)
            delete x.second;
    }
}

void js::Object::remove(std::string name)
{
    auto it = childrens.find(name);
    delete it->second;
    childrens.erase(it);
}

js::iterator js::Object::operator[](const std::string name)
{
    auto it = childrens.find(name);

    if(it == childrens.end()) {
        bool protoFound = false;
        if(__proto__ != nullptr) {
            it = __proto__->childrens.find(name);

            if(it != __proto__->childrens.end()) {
                protoFound = true;
            }
        }

        if(protoFound == false) {
            while(it == childrens.end()) {
                childrens[name] = nullptr;
                it = childrens.find(name);

            }
        }
    }

    return iterator(&it->second, (Atom*)this);
}



template<typename T>
js::iterator js::Object::operator[](T str)
{
    return operator[](std::string(str));
}

std::string js::Object::toString()
{
    std::string ret = "{";

    for(auto x = childrens.begin(); x != childrens.end();) {
        std::string temp = "\"";
        temp += x->first;
        temp += "\": ";
        if(x->second == nullptr) {
            temp += "null";
        } else temp += x->second->toString();
        if(++x != childrens.end()) temp += ", ";
        ret += temp;
    }

    ret += "}";
    return ret;
}

std::vector<js::Atom*> js::Object::pointers()
{
    std::vector<js::Atom*> pointers;
    for(auto x : childrens)
        pointers.push_back(x.second);

    deallocate = false;
    return pointers;
}

js::Object* js::Object::setPrototypeOf(js::Object &dest, js::Object *src)
{
    dest.__proto__ = src;
    return &dest;
}

js::Object* js::Object::setPrototypeOf(js::Object *dest, js::Object *src)
{
    dest->__proto__ = src;
    return dest;
}

js::Array* js::Object::keys(js::Object *obj)
{
    Array *ret = new Array;
    for(auto &x : obj->childrens)
        ret->push(x.first);

    return ret;
}

std::ostream& operator<<(std::ostream& os, js::Object& obj)
{
    os << obj.toString();
    return os;
}

js::iterator js::iterator::operator[](const std::string pos)
{
    if((*it)->type() == "Object") {
        return ((Object*)(*it))->operator[](pos);
    } else throw "Bad operator";
}
