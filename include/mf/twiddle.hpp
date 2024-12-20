#ifndef HPP_MF_TWIDDLE
#define HPP_MF_TWIDDLE

#include <iostream>

#include "mf/utils/math.hpp"
#include "mf/utils/types.hpp"

namespace mf {

template<typename DataType, typename IdxType, IdxType Size>
MF_CONSTEXPR void fill_twiddle_coeff(DataType (&table)[Size]) MF_NOEXCEPT {
    typedef typename uint_fast<IdxType>::type idx_fast_t;
    MF_CONST_OR_CONSTEXPR float_max_t factor = float_max_t(2) * PI / float_max_t(Size / 2);
    for(idx_fast_t i = 0; i != Size / 2; ++i) {
        table[2 * i] = cos(float_max_t(i) * factor);
        table[2 * i + 1] = sin(float_max_t(i) * factor);
    }
}

template<typename DataType, typename IdxType, IdxType Size>
MF_CONSTEXPR void fill_rfft_twiddle_coeff(DataType (&table)[Size]) MF_NOEXCEPT {
    typedef typename uint_fast<IdxType>::type idx_fast_t;
    MF_CONST_OR_CONSTEXPR float_max_t factor = float_max_t(2) * PI / float_max_t(Size);
    for(idx_fast_t i = 0; i != Size / 2; ++i) {
        table[2 * i] = sin(float_max_t(i) * factor);
        table[2 * i + 1] = cos(float_max_t(i) * factor);
    }
}

template<typename DataType, typename IdxType, IdxType Size>
MF_CONSTEXPR void print_twiddle_coeff(const DataType (&table)[Size]) MF_NOEXCEPT {
    typedef typename uint_fast<IdxType>::type idx_fast_t;
    printf("const float32_t twiddleCoef_%d[%d] ARM_DSP_TABLE_ATTRIBUTE = {\n", Size / 2, Size);
    for(idx_fast_t i = 0; i != Size / 2; ++i) {
        printf("    %.09ff, %.09ff,\n", table[2 * i], table[2 * i + 1]);
    }
    printf("};\n");
}

template<typename DataType, typename IdxType, IdxType Size>
MF_CONSTEXPR void print_rfft_twiddle_coeff(const DataType (&table)[Size]) MF_NOEXCEPT {
    typedef typename uint_fast<IdxType>::type idx_fast_t;
    printf("const float32_t twiddleCoef_rfft_%d[%d] ARM_DSP_TABLE_ATTRIBUTE = {\n", Size, Size);
    for(idx_fast_t i = 0; i != Size / 2; ++i) {
        printf("    %.09ff, %.09ff,\n", table[2 * i], table[2 * i + 1]);
    }
    printf("};\n");
}

} // namespace mf

#endif // HPP_MF_TWIDDLE
