#ifndef HPP_MF_TRAITS_IS_ARITHMETIC
#define HPP_MF_TRAITS_IS_ARITHMETIC

#include "mf/config.hpp"
#include "mf/traits/integral_constant.hpp"
#include "mf/traits/is_floating.hpp"
#include "mf/traits/is_integral.hpp"

namespace mf {
template<typename T> struct is_arithmetic: integral_constant<bool, is_integral<T>::value || is_floating<T>::value> {};
} /* namespace mf */

#endif /* HPP_MF_TRAITS_IS_ARITHMETIC */
