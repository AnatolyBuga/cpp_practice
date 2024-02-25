// module;
#include <expected>
#include <iostream>
#include <stdexcept>
//https://stackoverflow.com/questions/65384277/error-failed-to-read-compiled-module-no-such-file-or-directory
#include "udfs/vector.hpp"

// export module MyVectorModule;

MyVector::MyVector(int s) 
    :elem{new double[s]}, sz{s} // initialize members
{
    std::cout << "Default constructor called" << std::endl;
}

MyVector::MyVector(std::initializer_list<double> lst) // initialize with a list
:elem{new double[lst.size()]}, sz{static_cast<int>(lst.size())}
{
    std::copy(lst.begin(),lst.end(),elem); // 
}


// TODO CHECK WHY adding destructor results in this error 
// BUT adding MyVector(const MyVector& a); makes it work again
auto MyVector::my_new(int s) -> std::expected<MyVector, MyError> { // trailing return type
    return MyVector(10);
};

auto MyVector::size() const -> int { // trailing return type
    return sz;
};

MyVector::MyVector(const MyVector& a)
: elem{new double[a.sz]}, sz{a.sz}
 {
    std::cout << "Copy constructor" << std::endl;
    for(int i=0; i!=sz; ++i){
        elem[i] = a.elem[i]; // copy each elem
    }
}

MyVector& MyVector::operator=(const MyVector& a) {
    std::cout << "Copy assignment" << std::endl;
    double* p = new double[a.sz];
    for (int i=0; i!=a.sz; ++i) p[i] = a.elem[i];
    delete[] elem;
    elem = p;
    sz = a.sz;
    return *this;
}

MyVector::MyVector(MyVector&& a): elem{a.elem}, sz{a.sz} {
    std::cout << "Move constructor" << std::endl;
    a.elem = nullptr;
    a.sz = 0;
}


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

auto f2(MyVector v) -> MyVector
{
    return v;
}



void vector_playground() {
    std::cout << "Inside Vector Playground" << std::endl;
    MyVector v(5);
    // MyVector v2 = 7; not allowed due to explicit 
    try {
        v[10];
    } catch(const std::out_of_range& err) {
        std::cout << err.what() << '\n';
    }
    MyVector vv = MyVector{1,2,3};


    // cast to reference must be from type (not ref/ptr)
    // dynamic_cast to reference can result in error
    try {
        Container& c = dynamic_cast<Container&>(vv);
    } catch(const std::bad_cast& ex) {
        std::cout << "["<<ex.what()<<"]" << std::endl;
    } 

    // cast to ptr must be from ptr
    // no need to catch
    if(Container* pc = dynamic_cast<Container*>(&vv)){
         std::cout << "I am container" << std::endl;
    }  
    v = vv; // copy assignment
    MyVector v2 = vv; // copy constructor

    // std::move is a kind of cast
    // it returns an rvalue ref 
    auto v3 = std::move(v2); // don't use v2 after

    std::cout << "before ffffffffff22222222" << std::endl;
    f2(v3); // copy, then move
    std::cout << "before ffffffffff22222222 with move" << std::endl;
    f2(std::move(v3));
}