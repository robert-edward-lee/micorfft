#ifndef HPP_MF_WINDOWS
#define HPP_MF_WINDOWS

#include "mf/utils/config.hpp"
#include "mf/utils/math.hpp"

namespace mf {

template<typename DataType, size_t Size> class Windows {
    static MF_CONST_OR_CONSTEXPR DataType N = DataType(Size);

public:
    ////////////////////////////////////////////////////////////////////////////
    //                            B-spline windows                            //
    ////////////////////////////////////////////////////////////////////////////
    static void rect(DataType (&win)[Size]) MF_NOEXCEPT {
        for(size_t n = 0; n != N; ++n) {
            win[n] = DataType(1);
        }
    }
    static void bartlett(DataType (&win)[Size]) MF_NOEXCEPT {
        static MF_CONST_OR_CONSTEXPR DataType subtractor = (N - DataType(1)) / DataType(2);
        static MF_CONST_OR_CONSTEXPR DataType divider = (N - DataType(1)) / DataType(2);
        for(size_t n = 0; n != Size; ++n) {
            win[n] = DataType(1) - abs((DataType(n) - subtractor) / divider);
        }
    }
    static void triang(DataType (&win)[Size]) MF_NOEXCEPT {
        static MF_CONST_OR_CONSTEXPR DataType subtractor = (N - DataType(1)) / DataType(2);
        static MF_CONST_OR_CONSTEXPR DataType divider = Size % 2 ? (N + DataType(1)) / DataType(2) : N / DataType(2);
        for(size_t n = 0; n != N; ++n) {
            win[n] = DataType(1) - abs((DataType(n) - subtractor) / divider);
        }
    }
    static void parzen(DataType (&win)[Size]) MF_NOEXCEPT {
        for(size_t n = 0; n != Size; ++n) {
            DataType x = abs(DataType(2) * n - (N - DataType(1))) / N;
            DataType y = DataType(1) - x;

            x = DataType(1) - DataType(6) * x * x + DataType(6) * x * x * x;
            y = DataType(2) * y * y * y;

            win[n] = min(x, y);
        }
    }
};

} // namespace mf

#endif // HPP_MF_WINDOWS
