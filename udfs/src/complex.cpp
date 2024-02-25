#include <iostream>
using namespace std;

// =, ->, (), [] operators must be defined inside, other can be outside
class complex {
    double re = 0, im = 0;
    public:
        complex() =default;
        complex(double r, double i): re{r}, im{i}{}
        // copy constructor
        complex(const complex& z): re{z.re}, im{z.im} {std::cout << "Copy constructor called" << std::endl; } 
        complex& operator+=(complex z)
        {
            re+=z.re; // add to re and im
            im+=z.im;
            // this is a pointer
            //*this is a dereferenced pointer
            return *this; //a clone/copy of current object, but since we are returning reference 
        }    
        friend ostream& operator<<(ostream& os, const complex& c);
};

// operator defined as standalone funciton
ostream& operator<<(ostream& os, const complex& c)
{
    os << c.re << '-' << c.im;
    return os;
}

complex operator+(complex a, complex b) {
    complex& c = a+=b; // c is a reference to local variable a.
    complex y = c; // copy?
    return y; // copy?
}


void complex_playground() { 
    auto c = complex(1,2);
    auto c2 = complex(3,4);
    std::cout << "complex sum: " << c+c2 << std::endl;
    // c.re; error since private
}