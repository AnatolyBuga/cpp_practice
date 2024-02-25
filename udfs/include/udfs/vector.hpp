#include <iostream>
#include <stdexcept>
#include <expected>
#include <string>
#include <memory>

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
void complex_playground();

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

class Container {
    public:
        virtual double& operator[](int) = 0; // pure virtual function
        virtual int size() const = 0; // const member function 
        virtual ~Container() {} // destructor (§5.2.2)
};


class MyVector: public Container {
public:
    // https://stackoverflow.com/questions/2785612/c-what-does-the-colon-after-a-constructor-mean
    // Reason for initializing the const data member in the initializer list is because no memory is allocated separately for const data member, it is folded in the symbol table due to which we need to initialize it in the initializer list. 
    // Reference members must be initialized using the Initializer List
    // default: https://stackoverflow.com/questions/20828907/the-new-syntax-default-in-c11
    // MyVector(int s) :elem{new double[s]}, sz{s} { std::cout << "Default constructor called" << std::endl; } // construct a Vector
    // virtual methods https://stackoverflow.com/questions/2391679/why-do-we-need-virtual-functions-in-c
    explicit MyVector(int s); // int to vec conversion, explicit means MyVector v = 7 is an error
    MyVector(std::initializer_list<double>); // initialise with {}

    MyVector(const MyVector& a); // copy constructor
    MyVector& operator=(const MyVector& a); // copy assignment

    //&& means rvalue reference
    // rvalue is a value you can't assign to (eg an int returned by a function call)
    // noone can assign to rvalue, so we can steal/move it
    // lvalue is something that can appear on the left side of assignment
    MyVector(MyVector&& a); //move constructor
    MyVector& operator=(MyVector&& a); //move assignment

    auto operator[](int i) -> double& override { 
        if (i<0 || i>size()) throw std::out_of_range{"Anatoly's Vector operator []"};
        return elem[i];
        } // element access: subscripting
    auto my_new(int s) -> std::expected<MyVector, MyError>;
    virtual int size() const override; // const means method is not going to change Data of the class
    // virtual methods https://stackoverflow.com/questions/2391679/why-do-we-need-virtual-functions-in-c
    ~MyVector(){delete[] elem;}
protected: // if you want to access from child, but NOT from outside
    double* elem; // pointer to the elements
    int sz; // the number of elements
    std::unique_ptr<std::string> dummy = nullptr;
};