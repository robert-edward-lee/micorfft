#ifndef HPP_MF_TRAITS_IS_UNSIGNED
#define HPP_MF_TRAITS_IS_UNSIGNED

#include "mf/config.hpp"
#include "mf/traits/integral_constant.hpp"
#include "mf/traits/is_arithmetic.hpp"
#include "mf/traits/is_floating.hpp"

namespace mf {
namespace detail {
template<typename T, bool = is_arithmetic<T>::value> struct is_unsigned_helper: false_type {};
template<typename T> struct is_unsigned_helper<T, true>: integral_constant<bool, T(0) < T(-1)> {};
template<typename T>
struct is_unsigned_selector: conditional<is_floating<T>::value, false_type, is_unsigned_helper<T> > {};
} /* namespace detail */
template<typename T> struct is_unsigned: detail::is_unsigned_selector<T>::type {};
} /* namespace mf */

#endif /* HPP_MF_TRAITS_IS_UNSIGNED */
