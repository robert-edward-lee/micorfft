#ifndef HPP_MF_BASIC_MATH_CONSTANTS
#define HPP_MF_BASIC_MATH_CONSTANTS

#include "mf/types/floating.hpp"
#include "mf/utils/config.hpp"

#if defined(__GNUC__) && MF_HAS_FLOAT128_TYPE
// from boost:
// This is the only way we can avoid
// warning: non-standard suffix on floating constant [-Wpedantic]
// when building with -Wall -pedantic.  Neither __extension__
// nor #pragma dianostic ignored work :(
#pragma GCC system_header
#endif

namespace mf {
static MF_CONST_OR_CONSTEXPR float_max_t PI = MF_FLOAT_MAX_C(3.141592653589793238462643383279502884e+00);
static MF_CONST_OR_CONSTEXPR float_max_t SQRT2 = MF_FLOAT_MAX_C(1.414213562373095048801688724209698079e+00);
static MF_CONST_OR_CONSTEXPR float_max_t SQRT1_2 = MF_FLOAT_MAX_C(7.071067811865475244008443621048490392e-01);
} // namespace mf

#endif // HPP_MF_BASIC_MATH_CONSTANTS
