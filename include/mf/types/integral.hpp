#ifndef HPP_MF_TYPES_INTEGRAL
#define HPP_MF_TYPES_INTEGRAL

#include <climits>
#include <cstddef>

#include "mf/config.hpp"
#include "mf/traits/conditional.hpp"
#include "mf/traits/integral_constant.hpp"
#include "mf/traits/make_signed.hpp"
#include "mf/traits/remove_cv.hpp"

#if MF_CXX_VER > 199711L
#include <cstdint>
#endif

namespace mf {
using std::size_t;
typedef make_signed<size_t>::type ssize_t;
using std::ptrdiff_t;

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
typedef UIntTypeWidth<64>::type uint64_t;

namespace detail {
template<size_t Size> struct uint_fast_helper {};
#if MF_CXX_VER > 199711L
template<> struct uint_fast_helper<1> {
    typedef std::uint_fast8_t type;
};
template<> struct uint_fast_helper<2> {
    typedef std::uint_fast16_t type;
};
template<> struct uint_fast_helper<4> {
    typedef std::uint_fast32_t type;
};
template<> struct uint_fast_helper<8> {
    typedef std::uint_fast64_t type;
};
#else
template<> struct uint_fast_helper<1> {
    typedef unsigned type;
};
template<> struct uint_fast_helper<2> {
    typedef unsigned type;
};
template<> struct uint_fast_helper<4> {
    typedef unsigned type;
};
template<> struct uint_fast_helper<8> {
    typedef uint64_t type;
};
#endif
} // namespace detail
template<typename IdxType> struct uint_fast: detail::uint_fast_helper<sizeof(IdxType)> {};

// clang-format off
template<size_t Size> struct smallest_integral_type {
    typedef
        typename conditional<Size <= (size_t(1) << size_t(7)),   uint8_t,
        typename conditional<Size <= (size_t(1) << size_t(15)), uint16_t,
        typename conditional<Size <= (size_t(1) << size_t(31)), uint32_t,
                                                                uint64_t>::type>::type>::type type;
};
// clang-format on
template<size_t Size> struct fastest_integral_type {
    typedef typename detail::uint_fast_helper<sizeof(typename smallest_integral_type<Size>::type)>::type type;
};
} // namespace mf

#endif // HPP_MF_TYPES_INTEGRAL
