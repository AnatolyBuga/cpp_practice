#include <iostream>
#include <concepts>
#include <vector>

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


void concepts_playground() {
    std::cout << add(1, 2) << std::endl; // OK, int satisfies the Addable concept
    //std::cout << add("Hello, ", "world!") << std::endl; // Error, const char* does not satisfy the Addable concept

    std::vector<int> vec{1, 2, 3};
    std::cout << "Size of vector: " << getSize(vec) << std::endl; // OK, std::vector<int> satisfies the HasSize concept
    // std::cout << getSize(42) << std::endl; // Error, int does not satisfy the HasSize concept
   

    std::vector<int> vec2{1, 2, 3 };
    printThirdElement(vec2); // OK, std::vector<int> satisfies the ContainerWithAtLeastThreeElements concept
    printThirdElement(std::vector<int>{1, 2}); // Error, std::vector<int> does not satisfy the ContainerWithAtLeastThreeElements concept
    

}