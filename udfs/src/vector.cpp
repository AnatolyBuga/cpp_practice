#include "udfs/vector.hpp"
#include <iostream>

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



void vector_playground() {
    std::cout << "Inside Vector Playground" << std::endl;
}