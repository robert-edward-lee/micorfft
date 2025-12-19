#ifndef HPP_MF_CONST_MATH
#define HPP_MF_CONST_MATH

#if defined(__cpp_constexpr) && __cpp_constexpr >= 201304
#include <limits>

#include "basic_math/constants.hpp"

namespace mf { namespace cm {
namespace detail {
template<typename T> constexpr T sqrt_recurrent(T a, T xk, T xk_1) noexcept {
    return xk == xk_1 ? xk : sqrt_recurrent(a, (xk + a / xk) / T(2), xk);
}

template<typename T> constexpr T exp_recurrent(T x, T res = 1, T term = 1, unsigned n = 1) noexcept {
    term *= x / T(n);
    res += term;
    return term < res * std::numeric_limits<T>::epsilon() ? res : exp_recurrent(x, res, term, n + 1);
}
} /* namespace detail */

template<typename T> constexpr T sqrt(T x) noexcept {
    return 0 <= x && x < std::numeric_limits<T>::infinity() ? detail::sqrt_recurrent<T>(x, x, 0)
                                                            : std::numeric_limits<T>::quiet_NaN();
}

template<typename T> constexpr T exp(T x) noexcept {
    return x == 0   ? T(1)
         : x < -700 ? T(0)
         : x > 700  ? std::numeric_limits<T>::infinity()
         : x < 0    ? T(1) / detail::exp_recurrent(-x)
                    : detail::exp_recurrent(x);
}

template<typename T> constexpr T exp2(T x) noexcept {
    return exp(x * ln2<T>::value);
}

template<typename T> constexpr T exp10(T x) noexcept {
    return exp(x * ln10<T>::value);
}

}} /* namespace mf::cm */

#endif /* __cpp_constexpr */

#endif /* HPP_MF_CONST_MATH */
