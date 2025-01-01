#ifndef HPP_MF_BASIC_MATH_CONSTANTS
#define HPP_MF_BASIC_MATH_CONSTANTS

#include "mf/config.hpp"
#include "mf/types/floating.hpp"

#if defined(__cpp_constexpr)
#define MF_SPECIALIZE_CONST(n, v, t, s) \
    template<> struct n<t> { \
        static constexpr t value = MF_DO_CONCAT(v, s); \
    };
#else
#define MF_SPECIALIZE_CONST(n, v, t, s) \
    template<> struct n<t> { \
        static const t value; \
    }; \
    const t n<t>::value = MF_DO_CONCAT(v, s);
#endif

#if defined(__cpp_variable_templates)
#define MF_DECLARE_CONST(n, v) \
    template<typename T> struct n {}; \
    template<typename T> constexpr T MF_DO_CONCAT(n, _v) = n<T>::value; \
    MF_SPECIALIZE_CONST(n, v, float, f) \
    MF_SPECIALIZE_CONST(n, v, double, l) \
    MF_SPECIALIZE_CONST(n, v, long double, l)
#else
#define MF_DECLARE_CONST(n, v) \
    template<typename T> struct n {}; \
    MF_SPECIALIZE_CONST(n, v, float, f) \
    MF_SPECIALIZE_CONST(n, v, double, l) \
    MF_SPECIALIZE_CONST(n, v, long double, l)
#endif

namespace mf {
MF_DECLARE_CONST(pi, 3.141592653589793238462643383279502884e+00)
MF_DECLARE_CONST(two_pi, 6.283185307179586476925286766559005768e+00)
MF_DECLARE_CONST(inv_pi, 3.183098861837906715377675267450287240689192e-01)
MF_DECLARE_CONST(sqrt2, 1.414213562373095048801688724209698079e+00)
MF_DECLARE_CONST(sqrt1_2, 7.071067811865475244008443621048490392e-01)
} // namespace mf

#endif // HPP_MF_BASIC_MATH_CONSTANTS
