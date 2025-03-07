#ifndef HPP_MF_TRANSPOSITION
#define HPP_MF_TRANSPOSITION

#include <bitset>
#include <cstring>
#include <iostream>

#include "mf/config.hpp"
#include "mf/traits.hpp"
#include "mf/types.hpp"

namespace mf {
/**
 * @tparam N Размер БПФ
 * @tparam Radix Основание БПФ
 * @brief Класс для генерации таблицы индексов перестановок
 */
template<size_t N, size_t Radix> class Transposition {
    MF_STATIC_ASSERT((trait::is_pow_of_2<N>::value) && N > Radix);

    typedef typename smallest_integral_type<N>::type idx_t;
    typedef typename fastest_integral_type<N>::type idx_fast_t;

public:
    static MF_CONST_OR_CONSTEXPR idx_t log2N = trait::log2<N>::value;
    static MF_CONST_OR_CONSTEXPR idx_t log2Radix = trait::log2<Radix>::value;
    static MF_CONST_OR_CONSTEXPR idx_t bits_list_size = log2N / log2Radix + !!(log2N % log2Radix);

    MF_CONSTEXPR_14 Transposition() MF_NOEXCEPT {
        /* decompose */
        idx_t bits_list[bits_list_size];
        for(idx_fast_t i = 0; i != log2N / log2Radix; ++i) {
            bits_list[i] = log2Radix;
        }

        MF_IF_CONSTEXPR(log2N % log2Radix) {
            bits_list[bits_list_size - 1] = log2N % log2Radix;
        }
        /* make permutation idx */
        for(idx_fast_t i = 0; i != N; ++i) {
            idx_t x = i;
            idx_t result = 0;
            for(idx_t j = 0; j != bits_list_size; ++j) {
                const idx_t mask = idx_t(-1) >> (sizeof(idx_t) * 8 - bits_list[j]);
                result = (result << bits_list[j]) | (x & mask);
                x >>= bits_list[j];
            }
            perm_idx[i] = result;
        }
    }

    MF_CONSTEXPR_14 void fill_table(idx_t *p) const MF_NOEXCEPT {
        std::bitset<N> checked;
        idx_t pi = 0;
        for(idx_fast_t i = 0; i != N; ++i) {
            if(!checked[i]) {
                checked[i] = true;
                /* проверка, что цикл не единичный */
                idx_t j = i;
                idx_t cnt = 0;
                while(!checked[perm_idx[j]]) {
                    j = perm_idx[j];
                    ++cnt;
                }
                j = i;
                /* если цикл не единичный, то добавляем в таблицу */
                if(cnt) {
                    const idx_t tmp = j;
                    while(!checked[perm_idx[j]]) {
                        p[pi++] = tmp;
                        j = perm_idx[j];
                        p[pi++] = j;
                        checked[j] = true;
                    }
                }
            }
        }
    }

private:
    idx_t perm_idx[N];
};

template<typename idx_t, idx_t N> MF_CONSTEXPR_14 void print_bit_rev_index_table(const idx_t (&table)[N]) {
    printf("const uint16_t armBitRevIndexTable[%d] ARM_DSP_TABLE_ATTRIBUTE = {\n", N);
    printf("/* , size %d*/\n", N);
    for(idx_t i = 0; i != N / 2; ++i) {
        printf("   %d, %d,\n", table[2 * i] * 4, table[2 * i + 1] * 4);
    }
    printf("};\n");
}

} // namespace mf

#endif // HPP_MF_TRANSPOSITION
