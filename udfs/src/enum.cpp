#include "udfs/vector.hpp"
#include <iostream>

// by default constructor, assignment?, and comparisons are defined
enum class Color { red, blue, green };
// plain enum
enum ColorPlain { red, blue, green };

Color& operator++(Color& t) // prefix increment: ++
{
switch (t) {
    case Color::green: {
        std::cout << "green -> blue" << std::endl;
         return t=Color::blue;
    }
    case Color::blue: {
        std::cout << "blue -> red" << std::endl;
        return t=Color::red;}
    case Color::red:{ 
        std::cout << "red -> green" << std::endl;
        return t=Color::green;}
    default: return t;
}
}


void enum_playground() {
    std::cout << "Inside Vector Playground" << std::endl;
    Color c = Color::red;
    Color x = Color{0}; // OK (first element of enum) Color y {6}; // also OK
    int p = int(Color::red);
    // This should be 0 !?
    std::cout << "Color red as int: " << p << std::endl;

    ++x;
    Color z = ++c;

    enum ColorPlain { red, green, blue };
    int col = green;
}