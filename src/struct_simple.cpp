#include <string>
#include <iostream>
#include "structs_simple.hpp"

using namespace std;

Record fct(int arg){
    // Different types of new
    // https://stackoverflow.com/questions/222557/what-uses-are-there-for-placement-new

    std::string motto {"Who dares wins"}; // motto is local
    auto p = new Record{"Hume"}; // p points to an unnamed Record (created by new)
    std::cout << p->name << std::endl;
    return *p;
}

std::string* new_operator(){
    // Delete can only be used on ALLOCATING expr
    char *buf  = new char[sizeof(string)]; // pre-allocated buffer
    string *p = new (buf) string("hi");    // placement new
    string *q = new string("hi");          // ordinary heap allocation
    // delete q; 
    std::cout << *q << std::endl;
    return q;
}

