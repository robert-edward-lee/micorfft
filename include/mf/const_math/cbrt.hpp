#ifndef HPP_MF_CONST_MATH_CBRT
#define HPP_MF_CONST_MATH_CBRT

#include <limits>

#include "mf/const_math/abs.hpp"

namespace mf { namespace cm {
namespace detail {
template<typename T> constexpr T cbrt_recurrent(T a, T xk, T xk_1 = T(0)) noexcept {
    return xk == xk_1 ? xk : cbrt_recurrent(a, (T(2) * xk + a / (xk * xk)) / T(3), xk);
}
} /* namespace detail */
template<typename T> constexpr T cbrt(T x) noexcept {
    return abs(x) < std::numeric_limits<T>::infinity() ? detail::cbrt_recurrent<T>(x, x)
                                                       : std::numeric_limits<T>::quiet_NaN();
}
}} /* namespace mf::cm */

#endif /* HPP_MF_CONST_MATH_CBRT */
