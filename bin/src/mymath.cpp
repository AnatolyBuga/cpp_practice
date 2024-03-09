#include <cmath>
#include <iostream>

#ifdef USE_MY_SQRT
#  include "mysqrt.h"
#endif

namespace mathfunctions {
double sqrt(double x)
{
// which square root function should we use?
#ifdef USE_MY_SQRT
  return detail::mysqrt(x);
#else
  return std::sqrt(x);
#endif
}
}

void run_mymath() {
    std::cout<< mathfunctions::sqrt(100) <<std::endl;
}