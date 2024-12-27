#ifndef HPP_MF_TRAITS_IS_POW_OF_2
#define HPP_MF_TRAITS_IS_POW_OF_2

#include "mf/traits/integral_constant.hpp"

namespace mf {
template<typename T, T x> struct is_pow_of_2: integral_constant<bool, x && !(x & (x - 1))> {};
} // namespace mf

#endif // HPP_MF_TRAITS_IS_POW_OF_2
