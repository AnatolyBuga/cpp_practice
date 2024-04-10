#include <iostream>
#include "udfs/vector.hpp"

void newDetection(auto obj) {
    if constexpr(requires{obj.toString(); }) {
        std::cout << obj.toString() << "\n";
    } else {
        std::cout << "Object is not a string \n";
    }
}

template<typename C, typename P>
int count(const C& c, P pred) // assume that C is a container and P is a predicate on its elements
{
int cnt = 0;
for (const auto& x : c)
    if (pred(x))
    ++cnt;
return cnt;
}

template<typename T, int N=0>
class Less_than {
const T val; // value to compare against
public:
Less_than(const T& v) :val{v} { }
bool operator()(const T& x) const { return x<val; } // call operator
constexpr int size() { return N; }
};

template <class T>
constexpr T viscosity = 0.4;

template <class T>
constexpr std::pair<T, T> external_acceleration = { T{}, T{-9.8} };

template<typename T, typename T2>
constexpr bool Assignable = std::is_assignable<T&,T2>::value;

template<typename T>
void test_assignable()
{
static_assert(Assignable<T&,double>, "can't assign a double to a T");
// static_assert(Assignable<T&,std::string>, "can't assign a string to a T"); 
}

template<typename C>
using Value_type = C::value_type;

template<typename Container>
void algo(Container& c)
{
MyVector<Value_type<Container>> vec; // keep results here
// ...
}




void templs_playground(){
    auto v = MyVector<int>{4,5,6, -10};
    auto lt = Less_than(0);
    std::cout << count(v, lt) << std::endl;

    auto vis2 = 2*viscosity<double>;
    auto acc = external_acceleration<float>;

    test_assignable<float>();

}

