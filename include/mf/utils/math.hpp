#ifndef HPP_MF_UTILS_MATH
#define HPP_MF_UTILS_MATH

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
#if defined(MF_HAS_BUILTIN_CLZ)
template<typename T> MF_CONSTEXPR typename enable_if<is_integral<T>::value, T>::type log2(T x) MF_NOEXCEPT {
    return sizeof(T) <= sizeof(unsigned)           ? 8 * sizeof(unsigned) - 1 - __builtin_clz(x)
         : sizeof(T) == sizeof(long unsigned)      ? 8 * sizeof(T) - 1 - __builtin_clzl(x)
         : sizeof(T) == sizeof(long long unsigned) ? 8 * sizeof(T) - 1 - __builtin_clzll(x)
                                                   : 0;
}
#else
template<typename T> MF_CONSTEXPR typename enable_if<is_integral<T>::value, T>::type log2(T x) MF_NOEXCEPT {
    return x >= (1 << 30) ? 30
         : x >= (1 << 29) ? 29
         : x >= (1 << 28) ? 28
         : x >= (1 << 27) ? 27
         : x >= (1 << 26) ? 26
         : x >= (1 << 25) ? 25
         : x >= (1 << 24) ? 24
         : x >= (1 << 23) ? 23
         : x >= (1 << 22) ? 22
         : x >= (1 << 21) ? 21
         : x >= (1 << 20) ? 20
         : x >= (1 << 19) ? 19
         : x >= (1 << 18) ? 18
         : x >= (1 << 17) ? 17
         : x >= (1 << 16) ? 16
         : x >= (1 << 15) ? 15
         : x >= (1 << 14) ? 14
         : x >= (1 << 13) ? 13
         : x >= (1 << 12) ? 12
         : x >= (1 << 11) ? 11
         : x >= (1 << 10) ? 10
         : x >= (1 << 9)  ? 9
         : x >= (1 << 8)  ? 8
         : x >= (1 << 7)  ? 7
         : x >= (1 << 6)  ? 6
         : x >= (1 << 5)  ? 5
         : x >= (1 << 4)  ? 4
         : x >= (1 << 3)  ? 3
         : x >= (1 << 2)  ? 2
         : x >= (1 << 1)  ? 1
                          : 0;
}
#endif
} // namespace mf

#endif // HPP_MF_UTILS_MATH
