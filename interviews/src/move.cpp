#include <iostream>
#include <utility> // for std::move

class MyClass {
public:
    MyClass() { std::cout << "Default constructor called" << std::endl; }
    MyClass(const MyClass&) { std::cout << "Copy constructor called" << std::endl; }
    MyClass(MyClass&&) { std::cout << "Move constructor called" << std::endl; }
};

int move_copy() {
    MyClass obj1; // Create an object using the default constructor

    

    // Move the object to another object
    MyClass obj2 = std::move(obj1);

    // Create a new object and move it
    MyClass obj3 = std::move(MyClass());

    // Copy - undefined behaviour, obj1 was moved
    // but it actually works! But shouldn't be relied on
    MyClass obj4 = obj1;

    

    return 0;
}