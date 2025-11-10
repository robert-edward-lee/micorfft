#ifndef HPP_MF_TRAITS_IS_VOLATILE
#define HPP_MF_TRAITS_IS_VOLATILE

#include "mf/config.hpp"
#include "mf/traits/integral_constant.hpp"

namespace mf {
template<typename T> struct is_volatile: false_type {};
template<typename T> struct is_volatile<volatile T>: true_type {};

template<typename T> struct is_const: false_type {};
template<typename T> struct is_const<const T>: true_type {};
} /* namespace mf */

#endif /* HPP_MF_TRAITS_IS_VOLATILE */
