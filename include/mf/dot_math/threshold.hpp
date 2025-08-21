#ifndef HPP_MF_DOT_MATH_THRESHOLD
#define HPP_MF_DOT_MATH_THRESHOLD

#include "mf/config.hpp"
#include "mf/types/integral.hpp"

namespace mf {
template<typename DataType, size_t Size>
MF_OPTIMIZE(3) MF_CONSTEXPR_14 void
limit_by_threshold(DataType (&limited)[Size], const DataType (&threshold)[Size], DataType limiter = 0) MF_NOEXCEPT {
    typedef typename fastest_integral_type<Size>::type idx_t;

    MF_CONST_OR_CONSTEXPR idx_t BLK_SIZE = 4;
    MF_CONST_OR_CONSTEXPR idx_t BLKS = Size / BLK_SIZE;
    MF_CONST_OR_CONSTEXPR idx_t RESIDUE = Size % BLK_SIZE;

    for(idx_t i = 0; i != BLKS; ++i) {
        if(limited[BLK_SIZE * i + 0] < threshold[BLK_SIZE * i + 0]) {
            limited[BLK_SIZE * i + 0] = limiter;
        }
        if(limited[BLK_SIZE * i + 1] < threshold[BLK_SIZE * i + 1]) {
            limited[BLK_SIZE * i + 1] = limiter;
        }
        if(limited[BLK_SIZE * i + 2] < threshold[BLK_SIZE * i + 2]) {
            limited[BLK_SIZE * i + 2] = limiter;
        }
        if(limited[BLK_SIZE * i + 3] < threshold[BLK_SIZE * i + 3]) {
            limited[BLK_SIZE * i + 3] = limiter;
        }
    }

    MF_IF_CONSTEXPR(RESIDUE != 0) {
        for(idx_t i = BLKS * BLK_SIZE; i != Size; ++i) {
            if(limited[i] < threshold[i]) {
                limited[i] = limiter;
            }
        }
    }
}
template<typename DataType, size_t Size>
MF_OPTIMIZE(3) MF_CONSTEXPR_14 void limit_by_threshold(DataType (&result)[Size],
                                                       const DataType (&limited)[Size],
                                                       const DataType (&threshold)[Size],
                                                       DataType limiter = 0) MF_NOEXCEPT {
    typedef typename fastest_integral_type<Size>::type idx_t;

    MF_CONST_OR_CONSTEXPR idx_t BLK_SIZE = 4;
    MF_CONST_OR_CONSTEXPR idx_t BLKS = Size / BLK_SIZE;
    MF_CONST_OR_CONSTEXPR idx_t RESIDUE = Size % BLK_SIZE;

    for(idx_t i = 0; i != BLKS; ++i) {
        result[BLK_SIZE * i + 0] =
            limited[BLK_SIZE * i + 0] < threshold[BLK_SIZE * i + 0] ? limiter : limited[BLK_SIZE * i + 0];
        result[BLK_SIZE * i + 1] =
            limited[BLK_SIZE * i + 1] < threshold[BLK_SIZE * i + 1] ? limiter : limited[BLK_SIZE * i + 1];
        result[BLK_SIZE * i + 2] =
            limited[BLK_SIZE * i + 2] < threshold[BLK_SIZE * i + 2] ? limiter : limited[BLK_SIZE * i + 2];
        result[BLK_SIZE * i + 3] =
            limited[BLK_SIZE * i + 3] < threshold[BLK_SIZE * i + 3] ? limiter : limited[BLK_SIZE * i + 3];
    }

    MF_IF_CONSTEXPR(RESIDUE != 0) {
        for(idx_t i = BLKS * BLK_SIZE; i != Size; ++i) {
            result[i] = limited[i] < threshold[i] ? limiter : limited[i];
        }
    }
}
} // namespace mf

#endif // HPP_MF_DOT_MATH_THRESHOLD
