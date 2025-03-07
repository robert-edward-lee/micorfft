#ifndef HPP_MF_STATISTIC_MINMAX
#define HPP_MF_STATISTIC_MINMAX

#include "mf/config.hpp"
#include "mf/types/integral.hpp"

namespace mf {
template<typename DataType, size_t Size>
MF_NODISCARD MF_OPTIMIZE(3) MF_CONSTEXPR_14 typename fastest_integral_type<Size>::type
max_element(const DataType (&data)[Size]) MF_NOEXCEPT {
    typedef typename fastest_integral_type<Size>::type idx_t;

    MF_CONST_OR_CONSTEXPR idx_t BLK_SIZE = 4;
    MF_CONST_OR_CONSTEXPR idx_t BLKS = Size / BLK_SIZE;
    MF_CONST_OR_CONSTEXPR idx_t RESIDUE = Size % BLK_SIZE;

    DataType max_val = data[0];
    idx_t max_idx = 0;
    for(idx_t i = 0; i != BLKS; ++i) {
        idx_t local_idx = BLK_SIZE * i + 0;
        if(data[local_idx] > max_val) {
            max_val = data[local_idx];
            max_idx = local_idx;
        }
        local_idx = BLK_SIZE * i + 1;
        if(data[local_idx] > max_val) {
            max_val = data[local_idx];
            max_idx = local_idx;
        }
        local_idx = BLK_SIZE * i + 2;
        if(data[local_idx] > max_val) {
            max_val = data[local_idx];
            max_idx = local_idx;
        }
        local_idx = BLK_SIZE * i + 3;
        if(data[local_idx] > max_val) {
            max_val = data[local_idx];
            max_idx = local_idx;
        }
    }

    MF_IF_CONSTEXPR(RESIDUE != 0) {
        for(idx_t i = BLKS * BLK_SIZE; i != Size; ++i) {
            if(data[i] > max_val) {
                max_val = data[i];
                max_idx = i;
            }
        }
    }

    return max_idx;
}
template<typename DataType, size_t Size>
MF_NODISCARD MF_OPTIMIZE(3) MF_CONSTEXPR_14 typename fastest_integral_type<Size>::type
max_element(const DataType (&data)[Size], DataType *value) MF_NOEXCEPT {
    typedef typename fastest_integral_type<Size>::type idx_t;

    MF_CONST_OR_CONSTEXPR idx_t BLK_SIZE = 4;
    MF_CONST_OR_CONSTEXPR idx_t BLKS = Size / BLK_SIZE;
    MF_CONST_OR_CONSTEXPR idx_t RESIDUE = Size % BLK_SIZE;

    DataType max_val = data[0];
    idx_t max_idx = 0;
    for(idx_t i = 0; i != BLKS; ++i) {
        idx_t local_idx = BLK_SIZE * i + 0;
        if(data[local_idx] > max_val) {
            max_val = data[local_idx];
            max_idx = local_idx;
        }
        local_idx = BLK_SIZE * i + 1;
        if(data[local_idx] > max_val) {
            max_val = data[local_idx];
            max_idx = local_idx;
        }
        local_idx = BLK_SIZE * i + 2;
        if(data[local_idx] > max_val) {
            max_val = data[local_idx];
            max_idx = local_idx;
        }
        local_idx = BLK_SIZE * i + 3;
        if(data[local_idx] > max_val) {
            max_val = data[local_idx];
            max_idx = local_idx;
        }
    }

    MF_IF_CONSTEXPR(RESIDUE != 0) {
        for(idx_t i = BLKS * BLK_SIZE; i != Size; ++i) {
            if(data[i] > max_val) {
                max_val = data[i];
                max_idx = i;
            }
        }
    }

    if(MF_LIKELY(value)) {
        *value = max_val;
    }

    return max_idx;
}

template<typename DataType, size_t Size>
MF_NODISCARD MF_OPTIMIZE(3) MF_CONSTEXPR_14 typename fastest_integral_type<Size>::type
min_element(const DataType (&data)[Size]) MF_NOEXCEPT {
    typedef typename fastest_integral_type<Size>::type idx_t;

    MF_CONST_OR_CONSTEXPR idx_t BLK_SIZE = 4;
    MF_CONST_OR_CONSTEXPR idx_t BLKS = Size / BLK_SIZE;
    MF_CONST_OR_CONSTEXPR idx_t RESIDUE = Size % BLK_SIZE;

    DataType min_val = data[0];
    idx_t min_idx = 0;
    for(idx_t i = 0; i != BLKS; ++i) {
        idx_t local_idx = BLK_SIZE * i + 0;
        if(data[local_idx] < min_val) {
            min_val = data[local_idx];
            min_idx = local_idx;
        }
        local_idx = BLK_SIZE * i + 1;
        if(data[local_idx] < min_val) {
            min_val = data[local_idx];
            min_idx = local_idx;
        }
        local_idx = BLK_SIZE * i + 2;
        if(data[local_idx] < min_val) {
            min_val = data[local_idx];
            min_idx = local_idx;
        }
        local_idx = BLK_SIZE * i + 3;
        if(data[local_idx] < min_val) {
            min_val = data[local_idx];
            min_idx = local_idx;
        }
    }

    MF_IF_CONSTEXPR(RESIDUE != 0) {
        for(idx_t i = BLKS * BLK_SIZE; i != Size; ++i) {
            if(data[i] < min_val) {
                min_val = data[i];
                min_idx = i;
            }
        }
    }

    return min_idx;
}
template<typename DataType, size_t Size>
MF_NODISCARD MF_OPTIMIZE(3) MF_CONSTEXPR_14 typename fastest_integral_type<Size>::type
min_element(const DataType (&data)[Size], DataType *value) MF_NOEXCEPT {
    typedef typename fastest_integral_type<Size>::type idx_t;

    MF_CONST_OR_CONSTEXPR idx_t BLK_SIZE = 4;
    MF_CONST_OR_CONSTEXPR idx_t BLKS = Size / BLK_SIZE;
    MF_CONST_OR_CONSTEXPR idx_t RESIDUE = Size % BLK_SIZE;

    DataType min_val = data[0];
    idx_t min_idx = 0;
    for(idx_t i = 0; i != BLKS; ++i) {
        idx_t local_idx = BLK_SIZE * i + 0;
        if(data[local_idx] < min_val) {
            min_val = data[local_idx];
            min_idx = local_idx;
        }
        local_idx = BLK_SIZE * i + 1;
        if(data[local_idx] < min_val) {
            min_val = data[local_idx];
            min_idx = local_idx;
        }
        local_idx = BLK_SIZE * i + 2;
        if(data[local_idx] < min_val) {
            min_val = data[local_idx];
            min_idx = local_idx;
        }
        local_idx = BLK_SIZE * i + 3;
        if(data[local_idx] < min_val) {
            min_val = data[local_idx];
            min_idx = local_idx;
        }
    }

    MF_IF_CONSTEXPR(RESIDUE != 0) {
        for(idx_t i = BLKS * BLK_SIZE; i != Size; ++i) {
            if(data[i] < min_val) {
                min_val = data[i];
                min_idx = i;
            }
        }
    }

    *value = min_val;
    return min_idx;
}
} // namespace mf

#endif // HPP_MF_STATISTIC_MINMAX
