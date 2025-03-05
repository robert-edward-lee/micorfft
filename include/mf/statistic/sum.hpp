#ifndef HPP_MF_STATISTIC_SUM
#define HPP_MF_STATISTIC_SUM

#include "mf/config.hpp"
#include "mf/types/integral.hpp"

namespace mf {
template<typename DataType, size_t Size>
MF_NODISCARD MF_OPTIMIZE(3) MF_CONSTEXPR_14 DataType sum(const DataType (&data)[Size],
                                                         DataType init = DataType(0)) MF_NOEXCEPT {
    typedef typename uint_fast<typename idx_type_chooser<Size>::type>::type idx_t;

    MF_CONST_OR_CONSTEXPR idx_t BLK_SIZE = 4;
    MF_CONST_OR_CONSTEXPR idx_t BLKS = Size / BLK_SIZE;
    MF_CONST_OR_CONSTEXPR idx_t RESIDUE = Size % BLK_SIZE;

    for(idx_t i = 0; i != BLKS; ++i) {
        init += data[BLK_SIZE * i + 0];
        init += data[BLK_SIZE * i + 1];
        init += data[BLK_SIZE * i + 2];
        init += data[BLK_SIZE * i + 3];
    }

    MF_IF_CONSTEXPR(RESIDUE != 0) {
        for(idx_t i = BLKS * BLK_SIZE; i != Size; ++i) {
            init += data[i];
        }
    }

    return init;
}
template<typename DataType, size_t Size>
MF_OPTIMIZE(3) MF_CONSTEXPR_14 void sum(const DataType (&data)[Size], DataType *init) MF_NOEXCEPT {
    typedef typename uint_fast<typename idx_type_chooser<Size>::type>::type idx_t;

    MF_CONST_OR_CONSTEXPR idx_t BLK_SIZE = 4;
    MF_CONST_OR_CONSTEXPR idx_t BLKS = Size / BLK_SIZE;
    MF_CONST_OR_CONSTEXPR idx_t RESIDUE = Size % BLK_SIZE;

    for(idx_t i = 0; i != BLKS; ++i) {
        *init += data[BLK_SIZE * i + 0];
        *init += data[BLK_SIZE * i + 1];
        *init += data[BLK_SIZE * i + 2];
        *init += data[BLK_SIZE * i + 3];
    }

    MF_IF_CONSTEXPR(RESIDUE != 0) {
        for(idx_t i = BLKS * BLK_SIZE; i != Size; ++i) {
            *init += data[i];
        }
    }
}
} // namespace mf

#endif // HPP_MF_STATISTIC_SUM
