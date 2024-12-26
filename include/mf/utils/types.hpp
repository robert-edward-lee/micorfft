#ifndef HPP_MF_UTILS_TYPES
#define HPP_MF_UTILS_TYPES

#include <climits>

#include "mf/utils/config.hpp"
#include "mf/utils/traits.hpp"

#if MF_CXX_VER > 199711L
#include <cstdint>
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

template<int Size> struct FloatTypeWidth {
    typedef typename conditional<
        Size == sizeof(float) * CHAR_BIT,
        float,
        typename conditional<
            Size == sizeof(double) * CHAR_BIT,
            double,
            typename conditional<Size == sizeof(long double) * CHAR_BIT, long double, void>::type>::type>::type type;
};

typedef FloatTypeWidth<32>::type float32_t;
typedef FloatTypeWidth<64>::type float64_t;
typedef float64_t float_max_t;

template<typename IdxType> struct is_valid_fft_type: false_type {};
template<> struct is_valid_fft_type<float32_t>: true_type {};
template<> struct is_valid_fft_type<float64_t>: true_type {};

} // namespace mf

#endif // HPP_MF_UTILS_TYPES
