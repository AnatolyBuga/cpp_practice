// module;
#include <expected>
#include <iostream>
#include <stdexcept>
//https://stackoverflow.com/questions/65384277/error-failed-to-read-compiled-module-no-such-file-or-directory
#include "udfs/vector.hpp"

// export module MyVectorModule;

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
    MyVector(int s);
    auto operator[](int i) -> double& { 
        if (i<0 || i>size()) throw std::out_of_range{"Anatoly's Vector operator []"};
        return elem[i];
        } // element access: subscripting
    auto my_new(int s) -> std::expected<MyVector, MyError>;
    int size(); // { return sz; } defined outside(below)
private:
    double* elem; // pointer to the elements
    int sz; // the number of elements
};

MyVector::MyVector(int s) 
    :elem{new double[s]}, sz{s} // initialize members
{
    std::cout << "Default constructor called" << std::endl;
}

auto MyVector::my_new(int s) -> std::expected<MyVector, MyError> { // trailing return type
    return MyVector(10);
};

auto MyVector::size() -> int { // trailing return type
    return sz;
};
// new allocates to heap and MUST delete
// Different types of new
// https://stackoverflow.com/questions/222557/what-uses-are-there-for-placement-new
void vector_init(Vector1& v, int s) // initialize a MyVector
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
    MyVector v(5);
    try {
        v[10];
    } catch(const std::out_of_range& err) {
        std::cerr << err.what() << '\n';
    }
    
}