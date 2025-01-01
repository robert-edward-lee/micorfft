#ifndef HPP_MF_WINDOWS
#define HPP_MF_WINDOWS

#include "mf/basic_math.hpp"
#include "mf/config.hpp"
#include "mf/types/integral.hpp"

namespace mf {
template<typename DataType, size_t N> class Windows {
    typedef float_max_t type;

public:
    ////////////////////////////////////////////////////////////////////////////
    //                            B-spline windows                            //
    ////////////////////////////////////////////////////////////////////////////
    static void rect(DataType (&win)[N]) MF_NOEXCEPT {
        for(size_t n = 0; n != N; ++n) {
            win[n] = type(1);
        }
    }
    static void bartlett(DataType (&win)[N]) MF_NOEXCEPT {
        static MF_CONST_OR_CONSTEXPR DataType subtractor = (type(N) - type(1)) / type(2);
        static MF_CONST_OR_CONSTEXPR DataType divider = (type(N) - type(1)) / type(2);
        for(size_t n = 0; n != N; ++n) {
            win[n] = type(1) - abs((type(n) - subtractor) / divider);
        }
    }
    static void triang(DataType (&win)[N]) MF_NOEXCEPT {
        static MF_CONST_OR_CONSTEXPR DataType subtractor = (type(N) - type(1)) / type(2);
        static MF_CONST_OR_CONSTEXPR DataType divider = N % 2 ? (type(N) + type(1)) / type(2) : type(N) / type(2);
        for(size_t n = 0; n != N; ++n) {
            win[n] = type(1) - abs((type(n) - subtractor) / divider);
        }
    }
    static void parzen(DataType (&win)[N]) MF_NOEXCEPT {
        for(size_t n = 0; n != N; ++n) {
            DataType x = abs(type(2) * type(n) - (type(N) - type(1))) / type(N);
            DataType y = type(1) - x;

            x = type(1) - type(6) * x * x + type(6) * x * x * x;
            y = type(2) * y * y * y;

            win[n] = min(x, y);
        }
    }
};
} // namespace mf

#endif // HPP_MF_WINDOWS
