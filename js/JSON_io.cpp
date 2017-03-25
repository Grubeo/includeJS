
#include "include/Atom.hpp"
#include "include/Object.hpp"
#include "include/Number.hpp"
#include "include/string.hpp"

#include <fstream>
#include <streambuf>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cstdio>

void curlDownload(std::string url, std::string filename)
{

}

namespace js
{
    class JSON_Parser
    {
        std::string input;
        std::size_t position;
    public:
        Object *root;

        JSON_Parser(std::string in) : input(in), position(0) {}

        void skip_whitespace()
        {
            while(isspace(input[position]))
                position++;
        }

        char look_ahead()
        {
            skip_whitespace();
            return input[position];
        }

        template<typename T>
        T from_string(std::string str)
        {
            std::stringstream ss;
            ss << str;
            T ret;
            ss >> ret;
            return ret;
        }

        double parseNumber()
        {
            char c = look_ahead();
            std::string temp;
            temp +=c;
            while(true) {
                c = input[++position];
                switch(c) {
                    case '0':
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9':
                    case '.':
                        temp += c;
                    break;

                    default:
                        if(temp.size() > 0) {
                            position--;
                            return from_string<double>(temp);
                        } else {
                            return 0;
                        }
                }
            }
        }

        std::string parseString()
        {
            char c = look_ahead();
            if(c != '\"') return std::string();

            std::string out;
            do {
                    c = input[++position];
                    if(c == '\"')
                        return out;
                    out += c;
            } while(true);
        }

        Array* parseArray();

        Object* parseObject()
        {
            if(look_ahead() == '{') {
                position++;
                Object *out = new Object;
                std::string key;
                bool isKey = true;
                char c;
                do {
                    if(position >= input.size())
                        throw "BAD JSON FILE IN OBJECT";

                    c = look_ahead();
                    if(c == '\"') {
                         if(isKey) {
                             key = parseString();
                         } else out->operator[](key) = new js::string(parseString());
                    }
                    else if(c == ':') {
                        isKey = false;
                    }
                    else if(c == ',') {
                        isKey = true;
                    }
                    else if(!isKey) {
                        if(c == '{')
                            out->operator[](key) = parseObject();
                        else if(c == '[')
                            out->operator[](key) = parseArray();
                        else if(isdigit(c))
                            out->operator[](key) = parseNumber();
                        else if(c == 'n' and input[position+1] == 'u' and input[position+2] == 'l' and input[position+3] == 'l') {
                            out->operator[](key);
                            position += 3;
                        }
                    } else throw "BAD JSON FILE! IN OBJECT";
                    position++;
                } while(c != '}');
                position--;
                return out;
            }
            else return nullptr;
        }



    };

    js::Atom* loadJSON(std::string filename)
    {
        std::ifstream fin(filename);
        std::string inputString;

        fin.seekg(0, std::ios::end);
        inputString.reserve(fin.tellg());
        fin.seekg(0, std::ios::beg);

        inputString.assign(std::istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>());

        JSON_Parser p(inputString);

        Atom *ret;
        if(inputString.find("{") < inputString.find("[")) {
            ret = p.parseObject();
        }
        else {
            ret = p.parseArray();
        }

        if(ret == nullptr) {
            throw "Cannot parse JSON file";
        }
        return ret;
    }

    template<typename Download>
    js::Atom* loadJSON(std::string filename, Download download = [](std::string url, std::string dest) {
        std::string query = std::string("curl --silent \"") + url + "\" > " + dest;
        std::system(query.c_str());})
    {
        std::string tempFile = std::tmpnam(nullptr);
        download(filename, tempFile);
        js::Atom* readyObject = loadJSON(tempFile);
        std::remove(tempFile.c_str());
        return readyObject;
    }


    void saveJSON(std::string filename, Atom *root)
    {
        std::ofstream fout(filename);
        std::string str = root->toString();
        std::string from = "function()";
        std::size_t start_pos = 0;
        while((start_pos =  str.find(from, start_pos))  != std::string::npos) {
            str.replace(start_pos, from.size(), "null");
            start_pos += 4;
        }
        fout << str;
    }
}

js::Array* js::JSON_Parser::parseArray() {
    if(look_ahead() == '[') {
        position++;
        Array *out = new Array;

        char c = look_ahead();
        do {
            if(c == '\"') {
                out->push(parseString());
            }
            else if(c == ',');
            else if(c == '{')
                out->push(parseObject());
            else if(c == '[')
                out->push(parseArray());
            else if(isdigit(c))
                out->push(parseNumber());

            position++;

            if(position >= input.size())
                throw "BAD JSON FILE! IN ARRAY";

            c = look_ahead();
        } while(c != ']');
        return out;
    }
    else return nullptr;
}
