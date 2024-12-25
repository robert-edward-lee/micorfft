#ifndef HPP_MF_UTILS_TYPES
#define HPP_MF_UTILS_TYPES

#include <limits>

#include "mf/utils/config.hpp"
#include "mf/utils/traits.hpp"

#if MF_CXX_VER > 199711L
#include <cstdint>
#endif

#if MF_CXX_VER >= 202302
#include <cfloat>
#else
#define __STDC_WANT_IEC_60559_TYPES_EXT__
#include <float.h>
#endif

namespace mf {

template<int Size> struct UIntTypeWidth {
    typedef typename conditional<
        Size == sizeof(unsigned char) * CHAR_BIT,
        unsigned char,
        typename conditional<
            Size == sizeof(unsigned short) * CHAR_BIT,
            unsigned short,
            typename conditional<
                Size == sizeof(unsigned int) * CHAR_BIT,
                unsigned int,
                typename conditional<Size == sizeof(unsigned long) * CHAR_BIT,
                                     unsigned long,
#if MF_CXX_VER > 199711L
                                     typename conditional<Size == sizeof(unsigned long long) * CHAR_BIT,
                                                          unsigned long long,
                                                          void>::type>::type>::type>::type>::type type;
#else
                                     void>::type>::type>::type>::type type;
#endif
};

typedef UIntTypeWidth<8>::type uint8_t;
typedef UIntTypeWidth<16>::type uint16_t;
typedef UIntTypeWidth<32>::type uint32_t;

template<typename IdxType> struct is_valid_idx_type: false_type {};
template<> struct is_valid_idx_type<uint8_t>: true_type {};
template<> struct is_valid_idx_type<uint16_t>: true_type {};
template<> struct is_valid_idx_type<uint32_t>: true_type {};

#if MF_CXX_VER > 199711L
template<typename IdxType> struct uint_fast {};
template<> struct uint_fast<uint8_t> {
    typedef std::uint_fast8_t type;
};
template<> struct uint_fast<uint16_t> {
    typedef std::uint_fast16_t type;
};
template<> struct uint_fast<uint32_t> {
    typedef std::uint_fast32_t type;
};
#else
template<typename IdxType> struct uint_fast {
    typedef unsigned type;
};
#endif

template<size_t Size> struct idx_type_chooser {
    typedef
        typename conditional<Size <= (size_t(1) << size_t(6)),
                             uint8_t,
                             typename conditional<Size <= (size_t(1) << size_t(15)), uint16_t, uint32_t>::type>::type
            type;
};

#if MF_CXX_VER >= 202302
#define MF_HAS_FLOAT16
using std::float16_t;
#define MF_HAS_FLOAT32
using std::float32_t;
#define MF_HAS_FLOAT64
using std::float64_t;
#define UN_HAS_FLOAT128
using std::float128_t;
#else
#if defined(FLT16_MAX)
#define MF_HAS_FLOAT16
typedef _Float16 float16_t;
#endif
#if defined(FLT32_MAX)
#define MF_HAS_FLOAT32
typedef _Float32 float32_t;
#endif
#if defined(FLT64_MAX)
#define MF_HAS_FLOAT64
typedef _Float64 float64_t;
#endif
#if defined(FLT128_MAX)
#define MF_HAS_FLOAT128
typedef _Float128 float128_t;
#endif
#endif

template<int Size> struct FloatTypeWidth {
    typedef typename conditional<
        Size == sizeof(float) * CHAR_BIT,
        float,
        typename conditional<
            Size == sizeof(double) * CHAR_BIT,
            double,
            typename conditional<Size == sizeof(long double) * CHAR_BIT, long double, void>::type>::type>::type type;
};

#if !defined(MF_HAS_FLOAT16) && (defined(__ARM_FP16_FORMAT_IEEE) || defined(__ARM_FP16_FORMAT_ALTERNATIVE))
#define MF_HAS_FLOAT16
typedef __fp16 float16_t;
#endif
#if !defined(MF_HAS_FLOAT32)
#define MF_HAS_FLOAT32
typedef FloatTypeWidth<32>::type float32_t;
#endif
#if !defined(MF_HAS_FLOAT64)
#define MF_HAS_FLOAT64
typedef FloatTypeWidth<64>::type float64_t;
#endif

template<typename IdxType> struct is_valid_fft_type: false_type {};
#if defined(MF_HAS_FLOAT16)
template<> struct is_valid_fft_type<float16_t>: true_type {};
#endif
template<> struct is_valid_fft_type<float32_t>: true_type {};
template<> struct is_valid_fft_type<float64_t>: true_type {};
#if defined(MF_HAS_FLOAT128)
template<> struct is_valid_fft_type<float128_t>: true_type {};
#endif

// typedef float128_t float_max_t;
typedef float64_t float_max_t;

#if defined(MF_HAS_FLOAT128)
#define MF_FLOAT_CONST(x) ((float_max_t)MF_CONCAT(x, f128))
#else
#define MF_FLOAT_CONST(x) ((float_max_t)MF_CONCAT(x, l))
#endif

} // namespace mf

#endif // HPP_MF_UTILS_TYPES
