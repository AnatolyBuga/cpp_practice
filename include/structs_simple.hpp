#include <string>
struct Record {
    std::string name; // name is a member of Record (a string member)
// ...
};

// The only way to make auto fct is to put full definition in .h
Record fct(int arg);
std::string* new_operator();