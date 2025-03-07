#ifndef HPP_MF_DOT_MATH_SUBTRACT
#define HPP_MF_DOT_MATH_SUBTRACT

#include "mf/config.hpp"
#include "mf/types/integral.hpp"

namespace mf {
template<typename DataType, size_t Size>
MF_OPTIMIZE(3) MF_CONSTEXPR_14 void subtract(DataType (&difference)[Size],
                                             const DataType (&minuend)[Size],
                                             const DataType (&subtrahend)[Size]) MF_NOEXCEPT {
    typedef typename fastest_integral_type<Size>::type idx_t;

    MF_CONST_OR_CONSTEXPR idx_t BLK_SIZE = 4;
    MF_CONST_OR_CONSTEXPR idx_t BLKS = Size / BLK_SIZE;
    MF_CONST_OR_CONSTEXPR idx_t RESIDUE = Size % BLK_SIZE;

    for(idx_t i = 0; i != BLKS; ++i) {
        difference[BLK_SIZE * i + 0] = minuend[BLK_SIZE * i + 0] - subtrahend[BLK_SIZE * i + 0];
        difference[BLK_SIZE * i + 1] = minuend[BLK_SIZE * i + 1] - subtrahend[BLK_SIZE * i + 1];
        difference[BLK_SIZE * i + 2] = minuend[BLK_SIZE * i + 2] - subtrahend[BLK_SIZE * i + 2];
        difference[BLK_SIZE * i + 3] = minuend[BLK_SIZE * i + 3] - subtrahend[BLK_SIZE * i + 3];
    }

    MF_IF_CONSTEXPR(RESIDUE != 0) {
        for(idx_t i = BLKS * BLK_SIZE; i != Size; ++i) {
            difference[i] = minuend[i] - subtrahend[i];
        }
    }
}

template<typename DataType, size_t Size>
MF_OPTIMIZE(3) MF_CONSTEXPR_14 void subtract(DataType (&minuend)[Size],
                                             const DataType (&subtrahend)[Size]) MF_NOEXCEPT {
    typedef typename fastest_integral_type<Size>::type idx_t;

    MF_CONST_OR_CONSTEXPR idx_t BLK_SIZE = 4;
    MF_CONST_OR_CONSTEXPR idx_t BLKS = Size / BLK_SIZE;
    MF_CONST_OR_CONSTEXPR idx_t RESIDUE = Size % BLK_SIZE;

    for(idx_t i = 0; i != BLKS; ++i) {
        minuend[BLK_SIZE * i + 0] -= subtrahend[BLK_SIZE * i + 0];
        minuend[BLK_SIZE * i + 1] -= subtrahend[BLK_SIZE * i + 1];
        minuend[BLK_SIZE * i + 2] -= subtrahend[BLK_SIZE * i + 2];
        minuend[BLK_SIZE * i + 3] -= subtrahend[BLK_SIZE * i + 3];
    }

    MF_IF_CONSTEXPR(RESIDUE != 0) {
        for(idx_t i = BLKS * BLK_SIZE; i != Size; ++i) {
            minuend[i] -= subtrahend[i];
        }
    }
}

} // namespace mf

#endif // HPP_MF_DOT_MATH_SUBTRACT
