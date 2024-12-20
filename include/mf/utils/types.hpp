#ifndef HPP_MF_UTILS_TYPES
#define HPP_MF_UTILS_TYPES

#include "mf/utils/config.hpp"

namespace mf {
template<bool Cond, class T1, class T2> struct conditional {
    typedef T1 type;
};
template<class T1, class T2> struct conditional<false, T1, T2> {
    typedef T2 type;
};

template<int Size> struct UIntTypeWidth {
    typedef typename conditional<
        Size == sizeof(unsigned char) * 8,
        unsigned char,
        typename conditional<
            Size == sizeof(unsigned short) * 8,
            unsigned short,
            typename conditional<Size == sizeof(unsigned int) * 8,
                                 unsigned int,
                                 typename conditional<Size == sizeof(unsigned long) * 8,
                                                      unsigned long,
                                                      typename conditional<Size == sizeof(unsigned long long) * 8,
                                                                           unsigned long long,
                                                                           void>::type>::type>::type>::type>::type type;
};

typedef typename UIntTypeWidth<16>::type uint16_t;
typedef typename UIntTypeWidth<32>::type uint32_t;

#if MF_CXX_VER > 199711L
template<typename IdxType> struct uint_fast {};
template<> struct uint_fast<uint16_t> {
    using type = std::uint_fast16_t;
};
template<> struct uint_fast<uint32_t> {
    using type = std::uint_fast32_t;
};
#else
template<typename IdxType> struct uint_fast {
    typedef uint32_t type;
};
#endif

template<int Size> struct FloatTypeWidth {
    typedef typename conditional<
        Size == sizeof(float) * 8,
        float,
        typename conditional<Size == sizeof(double) * 8,
                             double,
                             typename conditional<Size == sizeof(long double) * 8, long double, void>::type>::type>::
        type type;
};

typedef FloatTypeWidth<32>::type float32_t;
typedef FloatTypeWidth<64>::type float64_t;
typedef float64_t float_max_t;

} // namespace mf

#endif // HPP_MF_UTILS_TYPES
