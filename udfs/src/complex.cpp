#include <iostream>
using namespace std;

class complex {
    double re, im;
    public:
        complex(double r, double i): re{r}, im{i}{}
        // complex(complex& z): re{z.re}, im{z.im} {} // copy constructor
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
// NOTE without friend this wouldn't compile 
ostream& operator<<(ostream& os, const complex& c)
{
    os << c.re << '-' << c.im;
    return os;
}

complex operator+(complex a, complex b) {
    complex& c = a+=b;
    complex y = c;
    return y;}


void complex_playground() { 
    auto c = complex(1,2);
    // c.re; error since private
}