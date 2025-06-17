#ifndef HPP_MF_TRAITS_MATH
#define HPP_MF_TRAITS_MATH

#include "mf/config.hpp"
#include "mf/traits/integral_constant.hpp"
#include "mf/traits/is_integral.hpp"
#include "mf/types/integral.hpp"

#if defined(__cpp_variable_templates)
#define MF_TRAITS_MATH_DECLARE_VARIABLE_TEMPLATES(n) \
    template<typename T, T X> constexpr typename n<T, X>::value_type MF_DO_CONCAT(n, _v) = n<T, X>::value;
#else
#define MF_TRAITS_MATH_DECLARE_VARIABLE_TEMPLATES(n)
#endif

namespace mf { namespace trait {
template<typename T, T X> struct is_pow_of_2: integral_constant<bool, X && !(X & (X - 1))> {
    MF_STATIC_ASSERT_MSG(is_integral<T>::value, "Type T must be integral");
    MF_STATIC_ASSERT_MSG((X >= 0), "is_pow_of_2 is not defined for X < 0");
};
MF_TRAITS_MATH_DECLARE_VARIABLE_TEMPLATES(is_pow_of_2)

namespace detail {
template<typename T, T X, bool = (X == 1)> struct log2_impl: integral_constant<T, 1 + log2_impl<T, (X >> 1)>::value> {
    MF_STATIC_ASSERT_MSG(is_integral<T>::value, "Type T must be integral");
    MF_STATIC_ASSERT_MSG((X > 0), "log2 is not defined for X <= 0");
};
template<typename T, T X> struct log2_impl<T, X, true>: integral_constant<T, 0> {};
} // namespace detail
template<typename T, T X> struct log2: detail::log2_impl<T, X> {};
MF_TRAITS_MATH_DECLARE_VARIABLE_TEMPLATES(log2)

namespace detail {
template<typename T, T X, bool = (X == 1), bool = (X == 0)>
struct clp2_impl: integral_constant<T, 1 << (log2<T, X - 1>::value + 1)> {
    MF_STATIC_ASSERT_MSG(is_integral<T>::value, "Type T must be integral");
    MF_STATIC_ASSERT_MSG((X > 0), "clp2 is not defined for X < 0");
};
template<typename T, T X> struct clp2_impl<T, X, true, false>: integral_constant<T, 1> {};
template<typename T, T X> struct clp2_impl<T, X, false, true>: integral_constant<T, 0> {};
} // namespace detail
template<typename T, T X> struct clp2: detail::clp2_impl<T, X> {};
MF_TRAITS_MATH_DECLARE_VARIABLE_TEMPLATES(clp2)
}} // namespace mf::trait

#undef MF_TRAITS_MATH_DECLARE_VARIABLE_TEMPLATES

#endif // HPP_MF_TRAITS_MATH
