#ifndef HPP_MF_UTILS
#define HPP_MF_UTILS

#include <cmath>

#include "mf/utils/traits.hpp"
#include "mf/utils/types.hpp"

namespace mf {
constexpr float_max_t PI = 3.141592653589793238462643383279502884l;
constexpr float_max_t SQRT2 = 1.414213562373095048801688724209698079l;
constexpr float_max_t SQRT1_2 = 1.0l / SQRT2;

using std::sin;
using std::cos;

template<typename T> constexpr enable_if_t<is_integral_v<T>, bool> is_pow_of_2(T x) {
    return x && !(x & (x - T(1)));
}
template<typename T> constexpr enable_if_t<is_integral_v<T>, T> log2(T x) {
    if constexpr(sizeof(T) <= sizeof(unsigned)) {
        return T(8) * sizeof(unsigned) - T(1) - __builtin_clz(x);
    } else if constexpr(sizeof(T) == sizeof(long unsigned)) {
        return T(8) * sizeof(T) - T(1) - __builtin_clzl(x);
    } else if constexpr(sizeof(T) == sizeof(long long unsigned)) {
        return T(8) * sizeof(T) - T(1) - __builtin_clzll(x);
    }
}
} // namespace mf

#endif // HPP_MF_UTILS
