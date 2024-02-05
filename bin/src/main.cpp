#include <iostream>
#include "structs_simple.hpp"
#include "lib.hpp"
#include "tenor_operator_orderedmap.hpp"
#include "udfs/vector.hpp"
// #define DEBUG see -DDEBUG
// namespace defines a space for particular function names
// so we can call functions from std like std::funcA
// and we can write our own funcA
using namespace std;

int main() {
  #ifdef DEBUG
        cout << "DEBUGGING"<< endl;
  #endif
  std::cout << "Anatoly says Hello, C++ " << __cplusplus << std::endl;
  playground();
  mut_ref();
  new_operator();
  tenor_operator_ordered();

  udfslib mylib;
  mylib.print();
}