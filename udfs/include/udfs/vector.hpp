#ifndef __SUBLIB_1_H__
#define __SUBLIB_1_H__
class udfslib
{
public:
    void print();
};
#endif

void vector_playground();

// Class vs struct: https://stackoverflow.com/questions/54585/when-should-you-use-a-class-vs-a-struct-in-c
// struct is public by default - a struct is simply a class with members public by default
// use class when need specific destructors
struct Vector1 {
    double* elem; // pointer to elements
    int sz; // number of elements
};

enum class Color { red, blue, green };

class Vector {
public:
    // https://stackoverflow.com/questions/2785612/c-what-does-the-colon-after-a-constructor-mean
    // Reason for initializing the const data member in the initializer list is because no memory is allocated separately for const data member, it is folded in the symbol table due to which we need to initialize it in the initializer list. 
    // Reference members must be initialized using the Initializer List
    // default: https://stackoverflow.com/questions/20828907/the-new-syntax-default-in-c11
    Vector(int s) :elem{new double[s]}, sz{s} { } // construct a Vector
    double& operator[](int i) { return elem[i]; } // element access: subscripting
    int size(); // { return sz; } defined in vector.cpp
private:
    double* elem; // pointer to the elements
    int sz; // the number of elements
};
