// module;
#include <expected>
#include <iostream>
#include <stdexcept>
//https://stackoverflow.com/questions/65384277/error-failed-to-read-compiled-module-no-such-file-or-directory
#include "udfs/vector.hpp"

// export module MyVectorModule;

template<typename T>
MyVector<T>::MyVector(int s) 
    :elem{new T[s]}, sz{s} // initialize members
{
    std::cout << "Default constructor called" << std::endl;
}
template<typename T>
MyVector<T>::MyVector(std::initializer_list<double> lst) // initialize with a list
:elem{new T[lst.size()]}, sz{static_cast<int>(lst.size())}
{
    std::copy(lst.begin(),lst.end(),elem); // 
}


// TODO CHECK WHY adding destructor results in this error 
// BUT adding MyVector(const MyVector& a); makes it work again
template<typename T>
auto MyVector<T>::my_new(int s) -> std::expected<MyVector, MyError> { // trailing return type
    return MyVector(10);
};
template<typename T>
auto MyVector<T>::size() const -> int { // trailing return type
    return sz;
};
template<typename T>
MyVector<T>::MyVector(const MyVector& a)
: elem{new T[a.sz]}, sz{a.sz}
 {
    std::cout << "Copy constructor" << std::endl;
    for(int i=0; i!=sz; ++i){
        elem[i] = a.elem[i]; // copy each elem
    }
}
template<typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector& a) {
    std::cout << "Copy assignment" << std::endl;
    T* p = new T[a.sz];
    for (int i=0; i!=a.sz; ++i) p[i] = a.elem[i];
    delete[] elem;
    elem = p;
    sz = a.sz;
    return *this;
}
template<typename T>
MyVector<T>::MyVector(MyVector&& a): elem{a.elem}, sz{a.sz} {
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
template<typename T>
auto f2(MyVector<T> v) -> MyVector<T>
{
    return v;
}



void vector_playground() {
    std::cout << "Inside Vector Playground" << std::endl;
    MyVector<int> v(5);
    // MyVector v2 = 7; not allowed due to explicit 
    try {
        v[10];
    } catch(const std::out_of_range& err) {
        std::cout << err.what() << '\n';
    }
    MyVector<int> vv = MyVector<int>{1,2,3};


    // cast to reference must be from type (not ref/ptr)
    // dynamic_cast to reference can result in error
    try {
        Container<int>& c = dynamic_cast<Container<int>&>(vv);
    } catch(const std::bad_cast& ex) {
        std::cout << "["<<ex.what()<<"]" << std::endl;
    } 

    // cast to ptr must be from ptr
    // no need to catch
    if(Container<int>* pc = dynamic_cast<Container<int>*>(&vv)){
         std::cout << "I am container" << std::endl;
    }  
    v = vv; // copy assignment
    MyVector<int> v2 = vv; // copy constructor

    // std::move is a kind of cast
    // it returns an rvalue ref 
    auto v3 = std::move(v2); // don't use v2 after

    std::cout << "before ffffffffff22222222" << std::endl;
    f2(v3); // copy, then move
    std::cout << "before ffffffffff22222222 with move" << std::endl;
    f2(std::move(v3));
}