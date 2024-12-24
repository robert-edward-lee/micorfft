#ifndef HPP_MF_TRANSPOSITION
#define HPP_MF_TRANSPOSITION

#include <bitset>
#include <cstring>
#include <iostream>

#include "mf/utils/math.hpp"
#include "mf/utils/traits.hpp"
#include "mf/utils/types.hpp"

namespace mf {
/**
 * @tparam IdxType Тип индекса
 * @tparam N Размер БПФ
 * @tparam Radix Основание БПФ
 * @brief Класс для генерации таблицы индексов перестановок
 */
template<typename IdxType, IdxType N, IdxType Radix> class Transposition {
    MF_STATIC_ASSERT(is_valid_idx_type<IdxType>::value);
    MF_STATIC_ASSERT((is_pow_of_2<IdxType, N>::value) && N > Radix);
    typedef typename uint_fast<IdxType>::type idx_fast_t;

public:
    static MF_CONST_OR_CONSTEXPR IdxType log2N = log2<IdxType, N>::value;
    static MF_CONST_OR_CONSTEXPR IdxType log2Radix = log2<IdxType, Radix>::value;
    static MF_CONST_OR_CONSTEXPR IdxType bits_list_size = log2N / log2Radix + !!(log2N % log2Radix);

    MF_CONSTEXPR_14 Transposition() MF_NOEXCEPT {
        /* decompose */
        IdxType bits_list[bits_list_size];
        for(idx_fast_t i = 0; i != log2N / log2Radix; ++i) {
            bits_list[i] = log2Radix;
        }

        MF_IF_CONSTEXPR(log2N % log2Radix) {
            bits_list[bits_list_size - 1] = log2N % log2Radix;
        }
        /* make permutation idx */
        for(idx_fast_t i = 0; i != N; ++i) {
            IdxType x = i;
            IdxType result = 0;
            for(IdxType j = 0; j != bits_list_size; ++j) {
                IdxType mask = IdxType(-1) >> (sizeof(IdxType) * 8 - bits_list[j]);
                result = (result << bits_list[j]) | (x & mask);
                x = x >> bits_list[j];
            }
            perm_idx[i] = result;
        }
    }

    MF_CONSTEXPR_14 IdxType fill_table(IdxType *p) const MF_NOEXCEPT {
        std::bitset<N> checked;
        IdxType pi = 0, tmp;
        for(idx_fast_t i = 0; i != N; ++i) {
            if(!checked[i]) {
                checked[i] = true;
                /* проверка, что цикл не единичный */
                IdxType j = i;
                IdxType cnt = 0;
                while(!checked[perm_idx[j]]) {
                    j = perm_idx[j];
                    ++cnt;
                }
                /* если цикл не единичный, то добавляем в таблицу */
                j = i;
                if(cnt) {
                    tmp = j;
                    while(!checked[perm_idx[j]]) {
                        p[pi++] = tmp * 2;
                        j = perm_idx[j];
                        p[pi++] = j * 2;
                        checked[j] = true;
                    }
                }
            }
        }
        return pi;
    }

private:
    IdxType perm_idx[N];
};

template<typename IdxType, IdxType N> MF_CONSTEXPR void print_bit_rev_index_table(const IdxType (&table)[N]) {
    typedef typename uint_fast<IdxType>::type idx_fast_t;
    printf("const uint16_t armBitRevIndexTable[%d] ARM_DSP_TABLE_ATTRIBUTE = {\n", N);
    printf("/* , size %d*/\n", N);
    for(idx_fast_t i = 0; i != N / 2; ++i) {
        printf("   %d, %d,\n", table[2 * i] * 4, table[2 * i + 1] * 4);
    }
    printf("};\n");
}

} // namespace mf

#endif // HPP_MF_TRANSPOSITION
