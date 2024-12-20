#ifndef HPP_MF_UTILS_MATH
#define HPP_MF_UTILS_MATH

#include <cmath>

#include "mf/utils/traits.hpp"
#include "mf/utils/types.hpp"

namespace mf {
static MF_CONST_OR_CONSTEXPR float_max_t PI = 3.141592653589793238462643383279502884l;
static MF_CONST_OR_CONSTEXPR float_max_t SQRT2 = 1.414213562373095048801688724209698079l;
static MF_CONST_OR_CONSTEXPR float_max_t SQRT1_2 = 1.0l / SQRT2;

using std::sin;
using std::cos;

template<typename T> MF_CONSTEXPR typename enable_if<is_integral<T>::value, bool>::type is_pow_of_2(T x) MF_NOEXCEPT {
    return x && !(x & (x - 1));
}
template<typename T> MF_CONSTEXPR typename enable_if<is_integral<T>::value, T>::type log2(T x) MF_NOEXCEPT {
    return sizeof(T) <= sizeof(unsigned)           ? 8 * sizeof(unsigned) - 1 - __builtin_clz(x)
         : sizeof(T) == sizeof(long unsigned)      ? 8 * sizeof(T) - 1 - __builtin_clzl(x)
         : sizeof(T) == sizeof(long long unsigned) ? 8 * sizeof(T) - 1 - __builtin_clzll(x)
                                                   : 0;
}
} // namespace mf

#endif // HPP_MF_UTILS_MATH
