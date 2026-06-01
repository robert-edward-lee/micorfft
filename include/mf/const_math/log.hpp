#ifndef HPP_MF_CONSTS_MATH_LOG
#define HPP_MF_CONSTS_MATH_LOG

#include <limits>

#include "mf/basic_math/constants.hpp"
#include "mf/const_math/exp.hpp"

namespace mf { namespace cm {

namespace detail {
/**
 * @brief ln(u + 1)
 */
template<typename T> constexpr T ln_taylor(T u, T res, T term, unsigned n = 2) noexcept {
    return abs(term) < abs(res) * std::numeric_limits<T>::epsilon()
             ? res
             : ln_taylor(u, res - term * u * T(n - 1) / T(n), -term * u * T(n - 1) / T(n), n + 1);
}
/**
 * @brief ln(x) = ln(2x) - ln(2) / ln(x) = ln(x/2) + ln(2)
 */
template<typename T> constexpr T ln_reduce(T x, T add = T(0)) noexcept {
    return x <= T(0)                               ? -std::numeric_limits<T>::infinity()
         : x == std::numeric_limits<T>::infinity() ? std::numeric_limits<T>::infinity()
         : x == T(1)                               ? add
         : x <= T(0.5)                             ? ln_reduce(T(2) * x, add - ln2<T>::value)
         : x >= T(1.5)                             ? ln_reduce(x / T(2), add + ln2<T>::value)
                                                   : add + detail::ln_taylor(x - T(1), x - T(1), x - T(1));
}
} /* namespace detail */

template<typename T> constexpr T ln(T x) noexcept {
    return detail::ln_reduce(x);
}

template<typename T> constexpr T lg(T x) noexcept {
    return detail::ln_reduce(x) / ln10<T>::value;
}

template<typename T> constexpr T log2(T x) noexcept {
    return detail::ln_reduce(x) / ln2<T>::value;
}

}} /* namespace mf::cm */

#endif /* HPP_MF_CONSTS_MATH_LOG */
