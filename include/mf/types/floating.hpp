#ifndef HPP_MF_TYPES_FLOATING
#define HPP_MF_TYPES_FLOATING

#include <climits>

#include "mf/traits/conditional.hpp"
#include "mf/traits/integral_constant.hpp"

namespace mf {
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
} // namespace mf

#endif // HPP_MF_TYPES_FLOATING
