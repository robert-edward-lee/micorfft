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
// clang-format off
MF_DECLARE_CONST(pi,        3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214808651e+00)
MF_DECLARE_CONST(two_pi,    6.28318530717958647692528676655900576839433879875021164194988918461563281257241799725606965068423413596429617303e+00)
MF_DECLARE_CONST(inv_pi,    3.1830988618379067153776752674502872406891929148091289749533468811779359526845307018022760553250617191214568545351e-01)

MF_DECLARE_CONST(sqrt2,     1.41421356237309504880168872420969807856967187537694807317667973799073247846210703885038753432764157273501384623e+00)
MF_DECLARE_CONST(sqrt1_2,   7.07106781186547524400844362104849039284835937688474036588339868995366239231053519425193767163820786367506923115e-01)
} // namespace mf

#endif // HPP_MF_BASIC_MATH_CONSTANTS
