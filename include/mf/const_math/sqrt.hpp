#ifndef HPP_MF_CONST_MATH_SQRT
#define HPP_MF_CONST_MATH_SQRT

#include <limits>

namespace mf { namespace cm {
namespace detail {
template<typename T> constexpr T sqrt_recurrent(T a, T xk, T xk_1 = T(0)) noexcept {
    return xk == xk_1 ? xk : sqrt_recurrent(a, (xk + a / xk) / T(2), xk);
}
} /* namespace detail */
template<typename T> constexpr T sqrt(T x) noexcept {
    return 0 <= x && x < std::numeric_limits<T>::infinity() ? detail::sqrt_recurrent<T>(x, x)
                                                            : std::numeric_limits<T>::quiet_NaN();
}
}} /* namespace mf::cm */

#endif /* HPP_MF_CONST_MATH_SQRT */
