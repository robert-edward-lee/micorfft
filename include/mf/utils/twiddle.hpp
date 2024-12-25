#ifndef HPP_MF_TWIDDLE
#define HPP_MF_TWIDDLE

#include <iostream>

#include "mf/utils/math.hpp"
#include "mf/utils/types.hpp"

namespace mf {

/**
 * @tparam DataType Тип действительных данных ждя вычисления БПФ
 * @tparam IdxType Тип индексации массива
 * @tparam Size Размер БПФ
 * @param[out] table Ссылка на таблицу
 * @brief Функция для генерации таблицы коэффициентов для комплексного БПФ
 */
template<typename DataType, typename IdxType, IdxType Size>
MF_CONSTEXPR void fill_twiddle_coeff(DataType (&table)[Size]) MF_NOEXCEPT {
    typedef typename uint_fast<IdxType>::type idx_fast_t;
    MF_CONST_OR_CONSTEXPR float_max_t factor = float_max_t(2) * PI / float_max_t(Size / 2);
    for(idx_fast_t n = 0; n != Size / 2; ++n) {
        table[2 * n + 0] = DataType(cos(float_max_t(n) * factor)); /* real */
        table[2 * n + 1] = DataType(sin(float_max_t(n) * factor)); /* imag */
    }
}
/**
 * @tparam DataType Тип действительных данных ждя вычисления БПФ
 * @tparam IdxType Тип индексации массива
 * @tparam Size Размер БПФ
 * @param[out] table Ссылка на таблицу
 * @brief Функция для генерации таблицы коэффициентов для действительного БПФ
 */
template<typename DataType, typename IdxType, IdxType Size>
MF_CONSTEXPR void fill_rfft_twiddle_coeff(DataType (&table)[Size]) MF_NOEXCEPT {
    typedef typename uint_fast<IdxType>::type idx_fast_t;
    MF_CONST_OR_CONSTEXPR float_max_t factor = float_max_t(2) * PI / float_max_t(Size);
    for(idx_fast_t n = 0; n != Size / 2; ++n) {
        table[2 * n + 0] = DataType(sin(float_max_t(n) * factor)); /* real */
        table[2 * n + 1] = DataType(cos(float_max_t(n) * factor)); /* imag */
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
