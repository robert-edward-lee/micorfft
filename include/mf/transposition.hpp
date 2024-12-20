#ifndef HPP_MF_TRANSPOSITION
#define HPP_MF_TRANSPOSITION

#include <bitset>
#include <cstring>
#include <iostream>

#include "mf/utils/math.hpp"
#include "mf/utils/traits.hpp"
#include "mf/utils/types.hpp"

namespace mf {
template<typename IdxType, IdxType N, IdxType Radix> class Transposition {
    MF_STATIC_ASSERT(is_valid_idx_type<IdxType>::value);
    MF_STATIC_ASSERT(is_pow_of_2(N) && N > Radix);
    typedef typename uint_fast<IdxType>::type idx_fast_t;

public:
    static MF_CONST_OR_CONSTEXPR IdxType log2N = log2(N);
    static MF_CONST_OR_CONSTEXPR IdxType log2Radix = log2(Radix);
    static MF_CONST_OR_CONSTEXPR IdxType bits_list_size = log2N / log2Radix + !!(log2N % log2Radix);

    MF_CONSTEXPR_14 Transposition() {

        /* decompose */
        IdxType bits_list[bits_list_size];
        for(idx_fast_t i = 0; i != log2N / log2Radix; ++i) {
            bits_list[i] = log2Radix;
        }

        MF_IF_CONSTEXPR(log2N % log2Radix) {
            bits_list[bits_list_size - 1] = log2N % log2Radix;
        }
        /* make permutation idx */
        IdxType perm_idx[N];
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
        /* cyclic form permutation */
        container<container<IdxType>> cycles = oneline2cyclic(perm_idx);
        for(auto &c: cycles) {
            for(idx_fast_t i = 0; i != c.size() - 1; ++i) {
                table[table_size++] = c[i] * 8;
                table[table_size++] = c[c.size() - 1] * 8;
            }
        }
    }

    MF_CONSTEXPR IdxType size() const MF_NOEXCEPT {
        return table_size;
    }
    MF_CONSTEXPR_14 void fill_table(IdxType *t) const MF_NOEXCEPT {
        if(!t) {
            return;
        }
        std::memcpy(t, table, table_size * sizeof(IdxType));
    }

    void print() const MF_NOEXCEPT {
        std::cout << "[";
        for(idx_fast_t i = 0; i != table_size - 2; i += 2) {
            std::cout << "[" << table[i] << ", " << table[i + 1] << "], ";
        }
        std::cout << "[" << table[table_size - 2] << ", " << table[table_size - 1] << "]]\n";
    }

    template<IdxType Size> void print_transpos(const IdxType (&bits_list)[Size]) {
        std::cout << log2(N) << " [";
        for(idx_fast_t it = std::begin(bits_list); it != std::end(bits_list) - 1; ++it) {
            std::cout << *it << ", ";
        }
        std::cout << *(std::end(bits_list) - 1) << "]\n";
    }
    template<IdxType Size> void print_rev(const IdxType (&perm_idx)[Size]) {
        std::cout << "[";
        for(idx_fast_t it = std::begin(perm_idx); it != std::end(perm_idx) - 1; ++it) {
            std::cout << *it << ", ";
        }
        std::cout << *(std::end(perm_idx) - 1) << "]\n";
    }

private:
    template<typename ItemType> class container {
        static MF_CONST_OR_CONSTEXPR IdxType INIT_SIZE = 4;
        static MF_CONST_OR_CONSTEXPR IdxType STEP = 2;

    public:
        MF_CONSTEXPR container() MF_NOEXCEPT: items(nullptr), len(0), cap(0) {}
        ~container() MF_NOEXCEPT {
            if(items) {
                delete[] items;
            }
        }

        container(const container &) = delete;
        container &operator=(const container &) = delete;

        MF_CONSTEXPR_14 container(container &&other) MF_NOEXCEPT: items(other.items), len(other.len), cap(other.cap) {
            other.items = nullptr;
            other.len = 0;
            other.cap = 0;
        }
        MF_CONSTEXPR_14 container &operator=(container &&other) MF_NOEXCEPT {
            if(this != &other) {
                if(items) {
                    delete[] items;
                }
                items = other.items;
                len = other.len;
                cap = other.cap;
                other.items = nullptr;
                other.len = 0;
                other.cap = 0;
            }
            return *this;
        }

        MF_CONSTEXPR_14 bool append(const ItemType &v) MF_NOEXCEPT {
            bool rc = true;

            if(!cap) {
                rc = realloc(INIT_SIZE);
            } else if(cap == len) {
                rc = realloc(cap * STEP);
            }

            if(!rc) {
                return rc;
            }

            items[len++] = v;
            return rc;
        }
        MF_CONSTEXPR_14 bool append(ItemType &&v) MF_NOEXCEPT {
            bool rc = true;

            if(!cap) {
                rc = realloc(INIT_SIZE);
            } else if(cap == len) {
                rc = realloc(cap * STEP);
            }

            if(!rc) {
                return rc;
            }

            items[len++] = std::move(v);
            return rc;
        }

        MF_CONSTEXPR IdxType size() const MF_NOEXCEPT {
            return len;
        }

        MF_CONSTEXPR_14 ItemType &operator[](IdxType i) MF_NOEXCEPT {
            return items[i];
        }
        MF_CONSTEXPR_14 const ItemType &operator[](IdxType i) const MF_NOEXCEPT {
            return items[i];
        }

        class iterator {
        public:
            MF_CONSTEXPR iterator(ItemType *p) MF_NOEXCEPT: it(p) {}

            MF_CONSTEXPR_14 iterator &operator++() MF_NOEXCEPT {
                ++it;
                return *this;
            }
            MF_CONSTEXPR_14 const iterator &operator++() const MF_NOEXCEPT {
                ++it;
                return *this;
            }
            MF_CONSTEXPR bool operator!=(const iterator &rhs) const MF_NOEXCEPT {
                return it != rhs.it;
            }
            MF_CONSTEXPR const ItemType &operator*() const MF_NOEXCEPT {
                return *it;
            }

        private:
            ItemType *it;
        };
        MF_CONSTEXPR iterator begin() const MF_NOEXCEPT {
            return iterator(items);
        }
        MF_CONSTEXPR iterator end() const MF_NOEXCEPT {
            return iterator(items + len);
        }

        void print() const MF_NOEXCEPT {
            std::cout << "[";
            if(len) {
                for(auto i = 0; i != len - 1; ++i) {
                    std::cout << items[i] << ", ";
                }
                std::cout << items[len - 1];
            } else {
                std::cout << "<null>";
            }
            std::cout << "]\n";
        }
        void print(void (*item_printer)(const ItemType &)) const MF_NOEXCEPT {
            std::cout << "[";
            if(len) {
                for(idx_fast_t i = 0; i != len - 1; ++i) {
                    item_printer(items[i]);
                    std::cout << ", ";
                }
                item_printer(items[len - 1]);
            } else {
                std::cout << "<null>";
            }
            std::cout << "]\n";
        }

    private:
        MF_CONSTEXPR_14 bool realloc(IdxType new_cap) MF_NOEXCEPT {
            if(new_cap <= cap) {
                return false;
            }

            ItemType *tmp = new(std::nothrow) ItemType[new_cap];
            if(tmp == nullptr) {
                return false;
            }

            if(items && len) {
                std::move(items, items + len, tmp);
                delete[] items;
            }

            items = tmp;
            cap = new_cap;
            return true;
        }

        ItemType *items;
        IdxType len;
        IdxType cap;
    };
    MF_CONSTEXPR_14 container<container<IdxType>> oneline2cyclic(const IdxType (&oneline)[N]) {
        container<container<IdxType>> cyclic_form;
        std::bitset<N> checked;
        for(idx_fast_t i = 0; i != N; ++i) {
            if(!checked[i]) {
                container<IdxType> cycle;
                if(!cycle.append(i)) {
                    /* ошибка */
                    std::cout << "if(!cycle.append(i))\n";
                }
                checked[i] = true;
                IdxType j = i;
                while(!checked[oneline[j]]) {
                    j = oneline[j];
                    if(!cycle.append(j)) {
                        /* ошибка */
                        std::cout << "if(!cycle.append(i))\n";
                    }
                    checked[j] = true;
                }
                if(cycle.size() > 1) {
                    if(!cyclic_form.append(std::move(cycle))) {
                        /* ошибка */
                        std::cout << "if(!cyclic_form.append(cycle))\n";
                    }
                }
            }
        }
        /* тут могла бы быть сортировка */
        return cyclic_form;
    }

    IdxType table[2 * N];
    IdxType table_size = 0;
};

template<typename IdxType> MF_CONSTEXPR void print_bit_rev_index_table(const IdxType *table, IdxType size) {
    typedef typename uint_fast<IdxType>::type idx_fast_t;
    printf("const uint16_t armBitRevIndexTable[%d] ARM_DSP_TABLE_ATTRIBUTE = {\n", size);
    printf("/* , size %d*/\n", size);
    for(idx_fast_t i = 0; i != size / 2; ++i) {
        printf("   %d, %d,\n", table[2 * i], table[2 * i + 1]);
    }
    printf("};\n");
}

} // namespace mf

#endif // HPP_MF_TRANSPOSITION
