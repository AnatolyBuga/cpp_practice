#include <iostream>
#include <concepts>
#include <vector>
#include <ranges>
#include <iterator>
#include <type_traits>
#include <ranges>

// Define a concept requiring the addition operation to be valid
template<typename T>
concept Addable = requires(T a, T b) {
    { a + b } -> std::convertible_to<T>; // Require the addition operation to be valid and produce a result convertible to T
};

// Function template that accepts types satisfying the Addable concept
template<Addable T>
T add(const T& a, const T& b) {
    return a + b;
}

// Define a concept requiring the presence of a 'size' member function
template<typename T>
concept HasSize = requires(T t) {
    { t.size() } -> std::convertible_to<std::size_t>; // Require the 'size' member function to be callable and return a result convertible to std::size_t
};

// Function template that accepts types satisfying the HasSize concept
template<HasSize T>
std::size_t getSize(const T& container) {
    return container.size();
}

// Define a concept requiring the type to be a container with at least 3 elements
template<typename T>
concept ContainerWithAtLeastThreeElements = requires(T t) {
    { t.size() } -> std::convertible_to<std::size_t>; // Require the 'size' member function
    { t.size() >= 3 }; // Note - this will not actually check size
    // { T(std::declval<typename T::value_type>(), 
    //      std::declval<typename T::value_type>(), 
    //      std::declval<typename T::value_type>()) }; 
};

// Function template that accepts types satisfying the ContainerWithAtLeastThreeElements concept
template<ContainerWithAtLeastThreeElements V3>
void printThirdElement(const V3& container) {
    std::cout << "Third element: " << container[2] << std::endl;
}

/*
template<typename S>
concept Sequence = requires (S a) {
typename range_value_t<S>; // S must have a value type
typename iterator_t<S>; // S must have an iterator type
{ a.begin() } -> same_as<iterator_t<S>>; // S must have a begin() that returns an iterator
{ a.end() } -> same_as<iterator_t<S>>;
requires input_iterator<iterator_t<S>>; // S’s iterator must be an input_iterator
requires same_as<range_value_t<S>, iter_value_t<S>>;
};
*/
template<typename T>
concept Sequence = requires (T s) {
    std::ranges::begin(s); // Must have begin() function
    std::ranges::end(s);   // Must have end() function
};

template<typename T, typename U = T>
concept Number =
requires(T x, U y) { // Something with arithmetic operations and a zero
{x+y} -> std::convertible_to<T>;
x-y; x*y; x/y;
x+=y; x-=y; x*=y; x/=y;
x=x; // copy
x=0;
};

template<typename T, typename U = T>
concept Arithmetic = Number<T,U> && Number<U,T>;


template<Sequence Seq, Number Num>
requires Arithmetic<std::ranges::range_value_t<Seq>,Num>
// equivallent 
// template<typename Seq, typename Num>
// requires Sequence<Seq> && Number<Num> && Arithmetic<range_value_t<Seq>,Num>
// or
// template<Sequence Seq, Arithmetic<range_value_t<Seq>> Num>
Num sum(Seq s, Num v)
{
for (const auto& x : s)
v+=x;
return v;
}

// constraining with concepts - Preffered
Number auto twice(Number auto x) {
    return x+x;
}

//constraining with types
auto thrice(auto x) {
    return x + x + x;
}

// More general
template<std::forward_iterator Iter, Arithmetic<std::iter_value_t<Iter>> Val>
Val accumulate(Iter first, Iter last, Val res)
{
    for (auto p = first; p!=last; ++p)
    res += *p;
    return res;
}

// More simple
template<std::ranges::forward_range R, Arithmetic<std::ranges::range_value_t<R>> Val= std::ranges::range_value_t<R>>
Val accumulate2(const R& r, Val res = 0.0)
{
for (auto x : r)
res += x;
return res;
}

// VARIADIC Templates (any number of args)

template<typename T>
concept Printable = requires(T t) { std::cout << t; }; // just one operation!

// This is needed when tail is empty
// void print()
// {
// // what we do for no arguments: nothing
// }


template<Printable T, Printable... Tail>
void print(T head, Tail... tail)
{
std::cout << head << ' '; // first, what we do for the head
// print(tail...); // then, what we do for the tail
if constexpr(sizeof...(tail)> 0)
print(tail...);
}
template<Printable ...T>
void print2(T&&... args)
{
(std::cout << ... << args) << '\n'; // print all arguments
}


template<Number... T>
int sum_fold(T... v)
{
    // : (v[0]+(v[1]+(v[2]+(v[3]+(v[4]+0)))))
return (v + ... + 0); // add all elements of v starting with 0
}

// Example function that receives the forwarded argument
void someOtherFunction(int& arg) {
    std::cout << "Received lvalue reference: " << arg << std::endl;
}

void someOtherFunction(int&& arg) {
    std::cout << "Received rvalue reference: " << arg << std::endl;
}

template<typename T>
void processAndForward(T&& arg) {
    // Process the argument (in this case, we just print it)
    std::cout << "Argument: " << arg << std::endl;

    // Forward the argument to another function
    // Here, std::forward is used to preserve the original value category
    // when forwarding the argument to another function
    someOtherFunction(std::forward<T>(arg));
}





void concepts_playground() {
    std::cout << add(1, 2) << std::endl; // OK, int satisfies the Addable concept
    //std::cout << add("Hello, ", "world!") << std::endl; // Error, const char* does not satisfy the Addable concept

    std::vector<int> vec{1, 2, 3};
    std::cout << "Size of vector: " << getSize(vec) << std::endl; // OK, std::vector<int> satisfies the HasSize concept
    // std::cout << getSize(42) << std::endl; // Error, int does not satisfy the HasSize concept
   

    std::vector<int> vec2{1, 2, 3 };
    printThirdElement(vec2); // OK, std::vector<int> satisfies the ContainerWithAtLeastThreeElements concept
    printThirdElement(std::vector<int>{1, 2}); // Error, std::vector<int> does not satisfy the ContainerWithAtLeastThreeElements concept

    auto sum = accumulate(begin(vec),end(vec),0.0);
    auto sum2 = accumulate2(vec);
    print(1, 0.0, 'c');
    print2("Hello!", ' ', "World ", 2017);

    int i = 42;
    processAndForward(i);     // Pass an lvalue
    processAndForward(10);    // Pass an rvalue
    

}