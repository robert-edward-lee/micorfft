#ifndef HPP_MF_TYPES_INTEGRAL
#define HPP_MF_TYPES_INTEGRAL

#include <climits>

#include "mf/config.hpp"
#include "mf/traits/conditional.hpp"
#include "mf/traits/integral_constant.hpp"
#include "mf/traits/remove_cv.hpp"

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

namespace detail {
#if MF_CXX_VER > 199711L
template<typename IdxType> struct uint_fast_helper {};
template<> struct uint_fast_helper<uint8_t> {
    typedef std::uint_fast8_t type;
};
template<> struct uint_fast_helper<uint16_t> {
    typedef std::uint_fast16_t type;
};
template<> struct uint_fast_helper<uint32_t> {
    typedef std::uint_fast32_t type;
};
#else
template<typename IdxType> struct uint_fast_helper {
    typedef unsigned type;
};
#endif
} // namespace detail
template<typename IdxType> struct uint_fast: detail::uint_fast_helper<typename remove_cv<IdxType>::type> {};

template<size_t Size> struct idx_type_chooser {
    typedef
        typename conditional<Size <= (size_t(1) << size_t(6)),
                             uint8_t,
                             typename conditional<Size <= (size_t(1) << size_t(15)), uint16_t, uint32_t>::type>::type
            type;
};
} // namespace mf

#endif // HPP_MF_TYPES_INTEGRAL
