#include <iostream>

#include "udfs/vector.hpp"

void udfslib::print()
{
    std::cout << "Hello sub-library 1!" << std::endl;
    vector_playground();
    // enum_playground();
    //  union_playground();
}