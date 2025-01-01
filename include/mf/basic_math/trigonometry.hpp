#ifndef HPP_MF_BASIC_MATH_TRIGONOMETRY
#define HPP_MF_BASIC_MATH_TRIGONOMETRY

#include <cmath>

#include "mf/basic_math/constants.hpp"
#include "mf/config.hpp"

namespace mf {
using std::sin;
using std::cos;

template<typename T, bool Norm> MF_CONSTEXPR T sinc(T x) {
    const T arg = Norm ? (pi<T>::value * x) : x;
    return x != T(0) ? sin(arg) / arg : T(1);
}
template<typename T> MF_CONSTEXPR T sinc(T x) {
    const T arg = pi<T>::value * x;
    return x != T(0) ? sin(arg) / arg : T(1);
}
} // namespace mf

#endif // HPP_MF_BASIC_MATH_TRIGONOMETRY
