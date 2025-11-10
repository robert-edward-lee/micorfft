#ifndef HPP_MF_BASIC_MATH_HYPERBOLIC
#define HPP_MF_BASIC_MATH_HYPERBOLIC

#include <cmath>

#include "mf/config.hpp"

namespace mf {
using std::sinh;
using std::cosh;
#if defined(__STRICT_ANSI__) || (defined(__GNUC__) && (__cplusplus < 201100))
extern "C" double acosh(double);
extern "C" double asinh(double);
#else
using std::asinh;
using std::acosh;
#endif
} /* namespace mf */

#endif /* HPP_MF_BASIC_MATH_HYPERBOLIC */
