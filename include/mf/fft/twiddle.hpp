#ifndef HPP_MF_TWIDDLE
#define HPP_MF_TWIDDLE

#include <iostream>

#include "mf/basic_math/constants.hpp"
#include "mf/basic_math/trigonometry.hpp"
#include "mf/config.hpp"
#include "mf/types.hpp"

namespace mf {
/**
 * @tparam DataType Тип действительных данных ждя вычисления БПФ
 * @tparam IdxType Тип индексации массива
 * @tparam Size Размер БПФ
 * @param[out] table Ссылка на таблицу
 * @brief Функция для генерации таблицы коэффициентов для комплексного БПФ
 */
template<typename DataType, typename IdxType, IdxType Size>
MF_CONSTEXPR_14 void fill_cfft_twiddle_coeff(DataType (&table)[Size]) MF_NOEXCEPT {
    typedef typename uint_fast<IdxType>::type idx_fast_t;
    MF_CONST_OR_CONSTEXPR float_max_t factor = float_max_t(2) * pi<float_max_t>::value / float_max_t(Size / 2);
    for(idx_fast_t i = 0; i != Size / 2; ++i) {
        table[2 * i] = cos(float_max_t(i) * factor);
        table[2 * i + 1] = sin(float_max_t(i) * factor);
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
MF_CONSTEXPR_14 void fill_rfft_twiddle_coeff(DataType (&table)[Size]) MF_NOEXCEPT {
    typedef typename uint_fast<IdxType>::type idx_fast_t;
    MF_CONST_OR_CONSTEXPR float_max_t factor = float_max_t(2) * pi<float_max_t>::value / float_max_t(Size);
    for(idx_fast_t i = 0; i != Size / 2; ++i) {
        table[2 * i] = sin(float_max_t(i) * factor);
        table[2 * i + 1] = cos(float_max_t(i) * factor);
    }
}
} // namespace mf

#endif // HPP_MF_TWIDDLE
