#ifndef HPP_MF_UTILS_MATH
#define HPP_MF_UTILS_MATH

#include <algorithm>
#include <cmath>

#include "mf/basic_math/constants.hpp"
#include "mf/basic_math/trigonometry.hpp"
#include "mf/traits/enable_if.hpp"
#include "mf/traits/is_integral.hpp"

namespace mf {
using std::abs;

/**
 * @brief Функция знака https://ru.wikipedia.org/wiki/Sgn
 */
template<typename T> MF_CONSTEXPR T sgn(T x) MF_NOEXCEPT {
    return (T(0) < x) - (x < T(0));
}

template<typename T> MF_CONSTEXPR T sqr(T a) MF_NOEXCEPT {
    return a * a;
}

template<typename T> MF_CONSTEXPR T cub(T a) MF_NOEXCEPT {
    return a * a * a;
}

template<typename T> MF_CONSTEXPR T min(T a, T b) MF_NOEXCEPT {
    return a < b ? a : b;
}
template<typename T> MF_CONSTEXPR T max(T a, T b) MF_NOEXCEPT {
    return a < b ? b : a;
}

template<typename T> MF_CONSTEXPR typename enable_if<is_integral<T>::value, bool>::type is_pow_of_2(T x) MF_NOEXCEPT {
    return x && !(x & (x - 1));
}

template<typename T> MF_CONSTEXPR typename enable_if<is_integral<T>::value, T>::type clp2(T x) MF_NOEXCEPT {
    --x;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    MF_IF_CONSTEXPR(sizeof(T) > 1) {
        x |= x >> 8;
    }
    MF_IF_CONSTEXPR(sizeof(T) > 2) {
        x |= x >> 16;
    }
    MF_IF_CONSTEXPR(sizeof(T) > 4) {
        x |= x >> 32;
    }
    ++x;

    return x;
}

using std::exp;
using std::sqrt;
using std::pow;
} // namespace mf

#endif // HPP_MF_UTILS_MATH
