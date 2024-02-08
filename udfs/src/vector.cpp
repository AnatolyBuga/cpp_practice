#include "udfs/vector.hpp"
#include <iostream>

int Vector::size() {
    return sz;
};
// new allocates to heap and MUST delete
// Different types of new
// https://stackoverflow.com/questions/222557/what-uses-are-there-for-placement-new
void vector_init(Vector1& v, int s) // initialize a Vector
{
    v.elem = new double[s]; // allocate an array of s doubles
    v.sz = s;
}

void f(Vector1 v, Vector1& rv, Vector1* pv)
{
    int i1 = v.sz; // access through name
    int i2 = rv.sz; // access through reference
    int i3 = pv->sz; // access through pointer
}

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
}
}

void vector_playground() {
    std::cout << "Inside Vector Playground" << std::endl;
    Color c = Color::red;
    Color x = Color{0}; // OK (first element of enum) Color y {6}; // also OK
    int p = int(Color::red);
    // This should be 0 !?
    std::cout << "Color red as int: " << p << std::endl;

    ++x;
    Color z = ++c;
}