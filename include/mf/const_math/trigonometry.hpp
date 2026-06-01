#ifndef HPP_MF_CONST_MATH_TRIGONOMETRY
#define HPP_MF_CONST_MATH_TRIGONOMETRY

#include <limits>

#include "mf/basic_math/constants.hpp"

namespace mf { namespace cm {
namespace detail {
template<typename T> constexpr T pm_pi_mod(T x) noexcept {
    return x
         - static_cast<T>(static_cast<unsigned>(x / two_pi<T>::value + (x >= T(0) ? T(0.5) : T(-0.5))))
               * two_pi<T>::value;
}
template<typename T> constexpr T sin_recurrent(T x, T res, T term, unsigned n = 1) noexcept {
    return abs(term) < abs(res) * std::numeric_limits<T>::epsilon()
             ? res
             : sin_recurrent(x, res - term * x / T(2 * n * (2 * n + 1)), -term * x / T(2 * n * (2 * n + 1)), n + 1);
}
template<typename T> constexpr T cos_recurrent(T x, T res = 1, T term = 1, unsigned n = 1) noexcept {
    return abs(term) < abs(res) * std::numeric_limits<T>::epsilon()
             ? res
             : cos_recurrent(x, res - term * x / T(2 * n * (2 * n - 1)), -term * x / T(2 * n * (2 * n - 1)), n + 1);
}
} /* namespace detail */
template<typename T> constexpr T sin(T x) noexcept {
    return x == T(0)                 ? T(0)
         : x == pi<T>::value / T(2)  ? T(1)
         : x == -pi<T>::value / T(2) ? T(-1)
                                     : detail::sin_recurrent(detail::pm_pi_mod(x) * detail::pm_pi_mod(x),
                                                             detail::pm_pi_mod(x),
                                                             detail::pm_pi_mod(x));
}

template<typename T> constexpr T cos(T x) noexcept {
    return x == T(0)                 ? T(1)
         : x == pi<T>::value / T(2)  ? T(0)
         : x == -pi<T>::value / T(2) ? T(0)
                                     : detail::cos_recurrent(detail::pm_pi_mod(x) * detail::pm_pi_mod(x));
}
}} /* namespace mf::cm */

#endif /* HPP_MF_CONST_MATH_TRIGONOMETRY */
