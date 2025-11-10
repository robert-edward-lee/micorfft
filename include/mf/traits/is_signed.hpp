#ifndef HPP_MF_TRAITS_IS_SIGNED
#define HPP_MF_TRAITS_IS_SIGNED

#include "mf/config.hpp"
#include "mf/traits/integral_constant.hpp"
#include "mf/traits/is_arithmetic.hpp"
#include "mf/traits/is_floating.hpp"

namespace mf {
namespace detail {
template<typename T, bool = is_arithmetic<T>::value> struct is_signed_helper: false_type {};
template<typename T> struct is_signed_helper<T, true>: integral_constant<bool, T(-1) < T(0)> {};
template<typename T> struct is_signed_selector: conditional<is_floating<T>::value, true_type, is_signed_helper<T> > {};
} /* namespace detail */
template<typename T> struct is_signed: detail::is_signed_selector<T>::type {};
} /* namespace mf */

#endif /* HPP_MF_TRAITS_IS_SIGNED */
