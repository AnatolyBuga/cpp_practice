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
// struct is public by default
// use class when need specific destructors
struct Vector1 {
    double* elem; // pointer to elements
    int sz; // number of elements
};

class Vector {
public:
    Vector(int s) :elem{new double[s]}, sz{s} { } // construct a Vector
    double& operator[](int i) { return elem[i]; } // element access: subscripting
    int size() { return sz; }
private:
    double* elem; // pointer to the elements
    int sz; // the number of elements
};
