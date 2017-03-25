#include <iostream>

#include "js/index.hpp"

#include <string>
#include <vector>
#include <iterator>
#include <windows.h>

namespace colors
{
    const int BLACK = 0;
    const int WHITE = 0x7;
    const int GREY = 0x8;
    const int RED = 0xC;

}

template<typename T> void setColor(T color)
{
    HANDLE console;
    console = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute(console, color);
}

void first_example()
{
    using namespace js;

    var bar = new Object {
        "previous" is loadJSON("example.json"), // Hello JSON my old friend
        "good" is new Array {"morning", "kids", "gun"},
        "count" is 1,
        "invoke_me" is new Function( INLINE {
            that["count"] += that["previous"]["count"];
            return null;
        })
    };

    bar["invoke_me"]();
    std::cerr << "Object " << bar << std::endl;

    remove(bar, "previous");
    saveJSON("example.json", bar);
}

void second_example()
{
    js::var tab = new js::Array {50, 2, 3, 4, 45};

    js::cast<js::Array>(tab)->forEach({
        std::cout << std::endl << position << ": " << element;
    });

    std::cout << std::endl << js::cast<js::Array>(tab)->join(" - ");
}

void third_example()
{
    using namespace js;
    std::cout << std::endl;
    var vector = new Object;
    vector["first"] = 30;
    vector["second"] = 1999;
    vector["display"] = new Function(INLINE { std::cout << "[" << that["first"] << "," << that["second"] << "]"; });
    vector["display"]();
    std::cout << std::endl << vector;
}

#include <random>

void fourth_example()
{
    static std::mt19937 engine;

    auto random = [&](int down, int up)->int{
        std::uniform_int_distribution<> dist(down, up);
        return dist(engine);
    };

    using namespace js;
    var RandomVector = new Function(INLINE {
        that["x"] = random(-100, 100);
        that["y"] = random(-100, 100);
        return null;
    });

    var rand2D = RandomVector();
    std::cout << rand2D << std::endl;

    var vec3D = new Object {
        "z" is random(-100,100)
    };

    RandomVector.call(vec3D);
    std::cout << vec3D << std::endl;
}

void fifth_example()
{
    using namespace js;

    var array = new Array {30, 20, 10, 60, 40};

    auto compare = [](iterator leftIt, iterator rightIt)->bool {
        if((*leftIt)->type() == "number" && (*rightIt)->type() == "number") {
            auto left = cast<Number>(leftIt);
            auto right = cast<Number>(rightIt);
            return ( left->get() < right->get() );
        } else return false;
    };

    auto direct = cast<Array>(array);

    std::cout << "Before sort: " << direct << std::endl;
    std::cout << "After reverse: " << direct->reverse() << std::endl;
    std::cout << "After sort: " << direct->sort(compare) << std::endl;


    var small_1 = new Array {1, 2};
    var small_2 = new Array {3, 4};

    std::cout << "After concat with [1,2] and [3,4]: " << direct->concat(small_1, small_2) << std::endl;
    std::cout << "After sort: " << direct->sort(compare) << std::endl;
}

void sixth_example()
{
    using namespace js;
    var weather = loadJSON("http://api.openweathermap.org/data/2.5/weather?q=Paledzie&APPID=3eff4ce7445113a4ccb7540ffc3f46e4&units=metric");
    std::cout << "In Paledzie, we have " << weather["main"]["temp"] << " degrees!" << std::endl;
}

#include <cmath>
void seventh_example()
{
    using namespace js;

    var QuadraticFunction = new Function(INLINE_ARG {
        if(arguments != null) {
            copy("a", that, arguments);
            copy("b", that, arguments);
            copy("c", that, arguments);
        }
        else {
            that["a"] = 0;
            that["b"] = 0;
            that["c"] = 0;
        }

        that["calc"] = new Function(INLINE{
            if(that["a"] == 0) {
                return -that["b"] / that["c"];
            } else {
                double a = cast<Number>(that["a"])->get();
                double b = cast<Number>(that["b"])->get();
                double c = cast<Number>(that["c"])->get();
                double delta = b*b - 4*a*c;

                if(delta > 0) {
                    double sqrtDelta = std::sqrt(delta);
                    double x1 = (-b + sqrtDelta) / (2*a);
                    double x2 = (-b - sqrtDelta) / (2*a);
                    return new Object {
                        "x1" is x1,
                        "x2" is x2
                    };
                } else if(delta == 0) {
                    return new Number(-b / (2 * a));
                } else return new Object;
            }
        });
        return null;
    });

    var qf = QuadraticFunction(new Object{
        "a" is 1,
        "b" is 4,
        "c" is 4
    });

    var ans = qf["calc"]();
    std::cout << "Answer: " << ans << std::endl;
}

template<typename T> int error(T arg)
{
    setColor((colors::BLACK << 8 | colors::RED));
    std::cerr << std::endl << arg << std::endl;
    setColor((colors::BLACK << 8 | colors::WHITE));
    return 0xBAD;
}

int main(int argc, char *argv[])
{
    bool internetAccess = [&]()->bool {
        std::vector<std::string> args(argv, argv + argc);
        auto result = std::find(args.begin(), args.end(), "--internet");
        return result != args.end();
    }();

    try {
        std::cout << "#First step! Loading JSON, invoking 'invoke_me' and saving JSON\n\n";
        first_example();

        std::cout << "\n#Second step! Effect of forEach and join function\n";
        second_example();

        std::cout << "\n\n#Third step! Another object filling example\n";
        third_example();

        std::cout << "\n\n#4th step! Construct functions!\n\n";
        fourth_example();

        std::cout << "\n\n#5th step! Array methods example\n\n";
        fifth_example();

        if(internetAccess) {
            std::cout << "\n\n#6th step! Actual weather for Paledzie (near Poznan in Poland) with OpenWeather!\n\n";
            sixth_example();
        } else {
            std::cout << std::endl << "To do 6th step please run with \"--internet\"" << std::endl;
        }

        std::cout << "\n\n#7th step! Quadratic Function!\n\n";
        seventh_example();

        return 0;
    } catch(const char *str) {
        return error(str);
    } catch(char c) {
        return error(c);
    }
}
