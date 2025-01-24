#ifndef HPP_MF_TRAITS_MATH
#define HPP_MF_TRAITS_MATH

#include "mf/config.hpp"
#include "mf/traits/integral_constant.hpp"
#include "mf/types/integral.hpp"

#if defined(__cpp_variable_templates)
#define MF_TRAITS_MATH_DECLARE_VARIABLE_TEMPLATES(T, n) template<T X> constexpr T MF_DO_CONCAT(n, _v) = n<X>::value;
#else
#define MF_TRAITS_MATH_DECLARE_VARIABLE_TEMPLATES(T, n)
#endif

namespace mf { namespace trait {
template<size_t X> struct is_pow_of_2: integral_constant<bool, X && !(X & (X - 1))> {};
MF_TRAITS_MATH_DECLARE_VARIABLE_TEMPLATES(bool, is_pow_of_2)

template<size_t X> struct log2 {
    static MF_CONST_OR_CONSTEXPR size_t value = 1 + log2<(X >> 1)>::value;
};
template<> struct log2<1> {
    static MF_CONST_OR_CONSTEXPR size_t value = 0;
};
MF_TRAITS_MATH_DECLARE_VARIABLE_TEMPLATES(size_t, log2)

template<size_t X> struct clp2 {
    static MF_CONST_OR_CONSTEXPR size_t value = 1 << (log2<X - 1>::value + 1);
};
template<> struct clp2<1> {
    static MF_CONST_OR_CONSTEXPR size_t value = 1;
};
template<> struct clp2<0> {
    static MF_CONST_OR_CONSTEXPR size_t value = 0;
};
MF_TRAITS_MATH_DECLARE_VARIABLE_TEMPLATES(size_t, clp2)
}} // namespace mf::trait

#undef MF_TRAITS_MATH_DECLARE_VARIABLE_TEMPLATES

#endif // HPP_MF_TRAITS_MATH
