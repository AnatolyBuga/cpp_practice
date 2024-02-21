#include <iostream>
#include <stdexcept>
#include <expected>

#ifndef __SUBLIB_1_H__
#define __SUBLIB_1_H__
class udfslib
{
public:
    void print();
};
#endif

void vector_playground();
void enum_playground();
void union_playground();

// Class vs struct: https://stackoverflow.com/questions/54585/when-should-you-use-a-class-vs-a-struct-in-c
// struct is public by default - a struct is simply a class with members public by default
// use class when need specific destructors
struct Vector1 {
    double* elem; // pointer to elements
    int sz; // number of elements
};

enum class MyError
{
    invalid_input,
    overflow
};

class MyVector {
public:
    // https://stackoverflow.com/questions/2785612/c-what-does-the-colon-after-a-constructor-mean
    // Reason for initializing the const data member in the initializer list is because no memory is allocated separately for const data member, it is folded in the symbol table due to which we need to initialize it in the initializer list. 
    // Reference members must be initialized using the Initializer List
    // default: https://stackoverflow.com/questions/20828907/the-new-syntax-default-in-c11
    // MyVector(int s) :elem{new double[s]}, sz{s} { std::cout << "Default constructor called" << std::endl; } // construct a Vector
    // virtual methods https://stackoverflow.com/questions/2391679/why-do-we-need-virtual-functions-in-c
    MyVector(int s);
    auto operator[](int i) -> double& { 
        if (i<0 || i>size()) throw std::out_of_range{"Anatoly's Vector operator []"};
        return elem[i];
        } // element access: subscripting
    auto my_new(int s) -> std::expected<MyVector, MyError>;
    virtual int size(); // virtual methods https://stackoverflow.com/questions/2391679/why-do-we-need-virtual-functions-in-c
protected: // if you want to access from child, but NOT from outside
    double* elem; // pointer to the elements
    int sz; // the number of elements
};