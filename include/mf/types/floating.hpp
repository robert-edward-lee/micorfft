#ifndef HPP_MF_TYPES_FLOATING
#define HPP_MF_TYPES_FLOATING

#include <cfloat>

#include "mf/utils.hpp"

#define MF_FLOAT_MAX_WIDTH 0
#define MF_HAS_FLOAT16_TYPE 0
#define MF_HAS_FLOAT32_TYPE 0
#define MF_HAS_FLOAT64_TYPE 0
#define MF_HAS_FLOAT80_TYPE 0
#define MF_HAS_FLOAT128_TYPE 0

#if !defined(FLT_RADIX) || ((defined(FLT_RADIX) && (FLT_RADIX != 2)))
#error The compiler does not support any radix-2 floating-point types required for <mf/types/floating.hpp>.
#endif

#if defined(FLT_MANT_DIG) && defined(FLT_MAX_EXP) // float test
#if FLT_MANT_DIG == 11 && FLT_MAX_EXP == 16 && !MF_HAS_FLOAT16_TYPE
#define MF_FLOAT16_TYPE float
#undef MF_FLOAT_MAX_WIDTH
#define MF_FLOAT_MAX_WIDTH 16
#undef MF_HAS_FLOAT16_TYPE
#define MF_HAS_FLOAT16_TYPE 1
#define MF_FLOAT16_C(x) MF_CONCAT(x, f)
#define MF_FLOAT16_MIN FLT_MIN
#define MF_FLOAT16_MAX FLT_MAX
#elif FLT_MANT_DIG == 24 && FLT_MAX_EXP == 128 && !MF_HAS_FLOAT32_TYPE
#define MF_FLOAT32_TYPE float
#undef MF_FLOAT_MAX_WIDTH
#define MF_FLOAT_MAX_WIDTH 32
#undef MF_HAS_FLOAT32_TYPE
#define MF_HAS_FLOAT32_TYPE 1
#define MF_FLOAT32_C(x) MF_CONCAT(x, f)
#define MF_FLOAT32_MIN FLT_MIN
#define MF_FLOAT32_MAX FLT_MAX
#elif FLT_MANT_DIG == 53 && FLT_MAX_EXP == 1024 && !MF_HAS_FLOAT64_TYPE
#define MF_FLOAT64_TYPE float
#undef MF_FLOAT_MAX_WIDTH
#define MF_FLOAT_MAX_WIDTH 64
#undef MF_HAS_FLOAT64_TYPE
#define MF_HAS_FLOAT64_TYPE 1
#define MF_FLOAT64_C(x) MF_CONCAT(x, f)
#define MF_FLOAT64_MIN FLT_MIN
#define MF_FLOAT64_MAX FLT_MAX
#elif FLT_MANT_DIG == 64 && FLT_MAX_EXP == 16384 && !MF_HAS_FLOAT80_TYPE
#define MF_FLOAT80_TYPE float
#undef MF_FLOAT_MAX_WIDTH
#define MF_FLOAT_MAX_WIDTH 80
#undef MF_HAS_FLOAT80_TYPE
#define MF_HAS_FLOAT80_TYPE 1
#define MF_FLOAT80_C(x) MF_CONCAT(x, f)
#define MF_FLOAT80_MIN FLT_MIN
#define MF_FLOAT80_MAX FLT_MAX
#elif FLT_MANT_DIG == 113 && FLT_MAX_EXP == 16384 && MF_HAS_FLOAT128_TYPE
#define MF_FLOAT128_TYPE float
#undef MF_FLOAT_MAX_WIDTH
#define MF_FLOAT_MAX_WIDTH 128
#undef MF_HAS_FLOAT128_TYPE
#define MF_HAS_FLOAT128_TYPE 1
#define MF_FLOAT128_C(x) MF_CONCAT(x, f)
#define MF_FLOAT128_MIN FLT_MIN
#define MF_FLOAT128_MAX FLT_MAX
#endif
#endif // float test

#if defined(DBL_MANT_DIG) && defined(DBL_MAX_EXP) // double test
#if DBL_MANT_DIG == 11 && DBL_MAX_EXP == 16 && !MF_HAS_FLOAT16_TYPE
#define MF_FLOAT16_TYPE double
#undef MF_FLOAT_MAX_WIDTH
#define MF_FLOAT_MAX_WIDTH 16
#undef MF_HAS_FLOAT16_TYPE
#define MF_HAS_FLOAT16_TYPE 1
#define MF_FLOAT16_C(x) (x)
#define MF_FLOAT16_MIN DBL_MIN
#define MF_FLOAT16_MAX DBL_MAX
#elif DBL_MANT_DIG == 24 && DBL_MAX_EXP == 128 && !MF_HAS_FLOAT32_TYPE
#define MF_FLOAT32_TYPE double
#undef MF_FLOAT_MAX_WIDTH
#define MF_FLOAT_MAX_WIDTH 32
#undef MF_HAS_FLOAT32_TYPE
#define MF_HAS_FLOAT32_TYPE 1
#define MF_FLOAT32_C(x) (x)
#define MF_FLOAT32_MIN DBL_MIN
#define MF_FLOAT32_MAX DBL_MAX
#elif DBL_MANT_DIG == 53 && DBL_MAX_EXP == 1024 && !MF_HAS_FLOAT64_TYPE
#define MF_FLOAT64_TYPE double
#undef MF_FLOAT_MAX_WIDTH
#define MF_FLOAT_MAX_WIDTH 64
#undef MF_HAS_FLOAT64_TYPE
#define MF_HAS_FLOAT64_TYPE 1
#define MF_FLOAT64_C(x) (x)
#define MF_FLOAT64_MIN DBL_MIN
#define MF_FLOAT64_MAX DBL_MAX
#elif DBL_MANT_DIG == 64 && DBL_MAX_EXP == 16384 && !MF_HAS_FLOAT80_TYPE
#define MF_FLOAT80_TYPE double
#undef MF_FLOAT_MAX_WIDTH
#define MF_FLOAT_MAX_WIDTH 80
#undef MF_HAS_FLOAT80_TYPE
#define MF_HAS_FLOAT80_TYPE 1
#define MF_FLOAT80_C(x) (x)
#define MF_FLOAT80_MIN DBL_MIN
#define MF_FLOAT80_MAX DBL_MAX
#elif DBL_MANT_DIG == 113 && DBL_MAX_EXP == 16384 && MF_HAS_FLOAT128_TYPE
#define MF_FLOAT128_TYPE double
#undef MF_FLOAT_MAX_WIDTH
#define MF_FLOAT_MAX_WIDTH 128
#undef MF_HAS_FLOAT128_TYPE
#define MF_HAS_FLOAT128_TYPE 1
#define MF_FLOAT128_C(x) (x)
#define MF_FLOAT128_MIN DBL_MIN
#define MF_FLOAT128_MAX DBL_MAX
#endif
#endif // double test

#if defined(LDBL_MANT_DIG) && defined(LDBL_MAX_EXP) // long double test
#if LDBL_MANT_DIG == 11 && LDBL_MAX_EXP == 16 && !MF_HAS_FLOAT16_TYPE
#define MF_FLOAT16_TYPE long double
#undef MF_FLOAT_MAX_WIDTH
#define MF_FLOAT_MAX_WIDTH 16
#undef MF_HAS_FLOAT16_TYPE
#define MF_HAS_FLOAT16_TYPE 1
#define MF_FLOAT16_C(x) MF_CONCAT(x, l)
#define MF_FLOAT16_MIN LDBL_MIN
#define MF_FLOAT16_MAX LDBL_MAX
#elif LDBL_MANT_DIG == 24 && LDBL_MAX_EXP == 128 && !MF_HAS_FLOAT32_TYPE
#define MF_FLOAT32_TYPE long double
#undef MF_FLOAT_MAX_WIDTH
#define MF_FLOAT_MAX_WIDTH 32
#undef MF_HAS_FLOAT32_TYPE
#define MF_HAS_FLOAT32_TYPE 1
#define MF_FLOAT32_C(x) MF_CONCAT(x, l)
#define MF_FLOAT32_MIN LDBL_MIN
#define MF_FLOAT32_MAX LDBL_MAX
#elif LDBL_MANT_DIG == 53 && LDBL_MAX_EXP == 1024 && !MF_HAS_FLOAT64_TYPE
#define MF_FLOAT64_TYPE long double
#undef MF_FLOAT_MAX_WIDTH
#define MF_FLOAT_MAX_WIDTH 64
#undef MF_HAS_FLOAT64_TYPE
#define MF_HAS_FLOAT64_TYPE 1
#define MF_FLOAT64_C(x) MF_CONCAT(x, l)
#define MF_FLOAT64_MIN LDBL_MIN
#define MF_FLOAT64_MAX LDBL_MAX
#elif LDBL_MANT_DIG == 64 && LDBL_MAX_EXP == 16384 && !MF_HAS_FLOAT80_TYPE
#define MF_FLOAT80_TYPE long double
#undef MF_FLOAT_MAX_WIDTH
#define MF_FLOAT_MAX_WIDTH 80
#undef MF_HAS_FLOAT80_TYPE
#define MF_HAS_FLOAT80_TYPE 1
#define MF_FLOAT80_C(x) MF_CONCAT(x, l)
#define MF_FLOAT80_MIN LDBL_MIN
#define MF_FLOAT80_MAX LDBL_MAX
#elif LDBL_MANT_DIG == 113 && LDBL_MAX_EXP == 16384 && MF_HAS_FLOAT128_TYPE
#define MF_FLOAT128_TYPE long double
#undef MF_FLOAT_MAX_WIDTH
#define MF_FLOAT_MAX_WIDTH 128
#undef MF_HAS_FLOAT128_TYPE
#define MF_HAS_FLOAT128_TYPE 1
#define MF_FLOAT128_C(x) MF_CONCAT(x, l)
#define MF_FLOAT128_MIN LDBL_MIN
#define MF_FLOAT128_MAX LDBL_MAX
#endif
#endif // long double test

#if !MF_HAS_FLOAT128_TYPE // float128 extension test
#if defined(__GNUC__) && defined(__SIZEOF_INT128__)
#define MF_FLOAT128_TYPE __float128
#undef MF_FLOAT_MAX_WIDTH
#define MF_FLOAT_MAX_WIDTH 128
#undef MF_HAS_FLOAT128_TYPE
#define MF_HAS_FLOAT128_TYPE 1
#define MF_FLOAT128_C(x) MF_CONCAT(x, q)
#define MF_FLOAT128_MIN 3.36210314311209350626267781732175260e-4932q
#define MF_FLOAT128_MAX 1.18973149535723176508575932662800702e+4932q
#elif defined(__INTEL_COMPILER)
#define MF_FLOAT128_TYPE _Quad
#undef MF_FLOAT_MAX_WIDTH
#define MF_FLOAT_MAX_WIDTH 128
#undef MF_HAS_FLOAT128_TYPE
#define MF_HAS_FLOAT128_TYPE 1
#define MF_FLOAT128_C(x) MF_CONCAT(x, q)
#define MF_FLOAT128_MIN 3.36210314311209350626267781732175260e-4932q
#define MF_FLOAT128_MAX 1.18973149535723176508575932662800702e+4932q
#endif
#endif // float128 extension test

namespace mf {
#if MF_HAS_FLOAT16_TYPE
typedef MF_FLOAT16_TYPE float16_t;
#endif

#if MF_HAS_FLOAT32_TYPE
typedef MF_FLOAT32_TYPE float32_t;
#endif

#if MF_HAS_FLOAT64_TYPE
typedef MF_FLOAT64_TYPE float64_t;
#endif

#if MF_HAS_FLOAT80_TYPE
typedef MF_FLOAT80_TYPE float80_t;
#endif

#if MF_HAS_FLOAT128_TYPE
typedef MF_FLOAT128_TYPE float128_t;
#endif

typedef long double float_max_t;
#define MF_FLOAT_MAX_C(x) MF_CONCAT(x, l)
} // namespace mf

#endif // HPP_MF_TYPES_FLOATING
