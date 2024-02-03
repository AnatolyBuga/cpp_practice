#include <iostream>
void newDetection(auto obj) {
    if constexpr(requires{obj.toString(); }) {
        std::cout << obj.toString() << "\n";
    } else {
        std::cout << "Object is not a string \n";
    }
}