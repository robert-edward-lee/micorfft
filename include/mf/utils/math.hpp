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

template<typename T, T x> struct is_pow_of_2: false_type {};
template<uint16_t x> struct is_pow_of_2<uint16_t, x>: integral_constant<bool, x && !(x & (x - 1))> {};
template<uint32_t x> struct is_pow_of_2<uint32_t, x>: integral_constant<bool, x && !(x & (x - 1))> {};

template<typename T, T x> struct log2 {
    static MF_CONST_OR_CONSTEXPR T value = 1 + log2<T, (x >> 1)>::value;
};
template<> struct log2<uint16_t, 1> {
    static MF_CONST_OR_CONSTEXPR uint16_t value = 0;
};
template<> struct log2<uint16_t, 0> {
    static MF_CONST_OR_CONSTEXPR uint16_t value = -1;
};
template<> struct log2<uint32_t, 1> {
    static MF_CONST_OR_CONSTEXPR uint32_t value = 0;
};
template<> struct log2<uint32_t, 0> {
    static MF_CONST_OR_CONSTEXPR uint32_t value = -1;
};

} // namespace mf

#endif // HPP_MF_UTILS_MATH
