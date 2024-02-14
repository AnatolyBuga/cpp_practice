#include <iostream>

#ifndef __SUBLIB_1_H__
#define __SUBLIB_1_H__
class udfslib
{
public:
    void print();
};
#endif

// void vector_playground();
void enum_playground();
void union_playground();

// Class vs struct: https://stackoverflow.com/questions/54585/when-should-you-use-a-class-vs-a-struct-in-c
// struct is public by default - a struct is simply a class with members public by default
// use class when need specific destructors
struct Vector1 {
    double* elem; // pointer to elements
    int sz; // number of elements
};

