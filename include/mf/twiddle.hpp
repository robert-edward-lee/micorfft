#ifndef HPP_MF_TWIDDLE
#define HPP_MF_TWIDDLE

#include <cmath>
#include <iostream>

#include "mf/utils.hpp"

namespace mf {

template<typename DataType, typename IdxType, IdxType Size> constexpr void fill_twiddle_coeff(DataType (&table)[Size]) {
    constexpr float_max_t factor = float_max_t(2) * PI / float_max_t(Size / 2);
    for(uint_fast_t<IdxType> i = 0; i != Size / 2; ++i) {
        table[2 * i] = std::cos(float_max_t(i) * factor);
        table[2 * i + 1] = std::sin(float_max_t(i) * factor);
    }
}

template<typename DataType, typename IdxType, IdxType Size>
constexpr void fill_rfft_twiddle_coeff(DataType (&table)[Size]) {
    constexpr float_max_t factor = float_max_t(2) * PI / float_max_t(Size);
    for(uint_fast_t<IdxType> i = 0; i != Size / 2; ++i) {
        table[2 * i] = std::sin(float_max_t(i) * factor);
        table[2 * i + 1] = std::cos(float_max_t(i) * factor);
    }
}

template<typename DataType, typename IdxType, IdxType Size>
constexpr void print_twiddle_coeff(const DataType (&table)[Size]) {
    printf("const float32_t twiddleCoef_%d[%d] ARM_DSP_TABLE_ATTRIBUTE = {\n", Size / 2, Size);
    for(uint_fast_t<IdxType> i = 0; i != Size / 2; ++i) {
        printf("    %.09ff, %.09ff,\n", table[2 * i], table[2 * i + 1]);
    }
    printf("};\n");
}

template<typename DataType, typename IdxType, IdxType Size>
constexpr void print_rfft_twiddle_coeff(const DataType (&table)[Size]) {
    printf("const float32_t twiddleCoef_rfft_%d[%d] ARM_DSP_TABLE_ATTRIBUTE = {\n", Size, Size);
    for(uint_fast_t<IdxType> i = 0; i != Size / 2; ++i) {
        printf("    %.09ff, %.09ff,\n", table[2 * i], table[2 * i + 1]);
    }
    printf("};\n");
}

} // namespace mf

#endif // HPP_MF_TWIDDLE
