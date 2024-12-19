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
    static_assert(is_valid_idx_type_v<IdxType>);
    static_assert(is_pow_of_2(N) && N > Radix);

public:
    constexpr Transposition() {
        constexpr IdxType log2N = log2(N);
        constexpr IdxType log2Radix = log2(Radix);
        constexpr IdxType bits_list_size = log2N / log2Radix + !!(log2N % log2Radix);

        /* decompose */
        IdxType bits_list[bits_list_size];
        for(uint_fast_t<IdxType> i = 0; i != log2N / log2Radix; ++i) {
            bits_list[i] = log2Radix;
        }

        if constexpr(log2N % log2Radix) {
            bits_list[bits_list_size - 1] = log2N % log2Radix;
        }
        /* make permutation idx */
        IdxType perm_idx[N];
        for(uint_fast_t<IdxType> i = 0; i != N; ++i) {
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
            for(uint_fast_t<IdxType> i = 0; i != c.size() - 1; ++i) {
                table[table_size++] = c[i] * 8;
                table[table_size++] = c[c.size() - 1] * 8;
            }
        }
    }

    constexpr IdxType size() const noexcept {
        return table_size;
    }
    constexpr void fill_table(IdxType *t) const noexcept {
        if(!t) {
            return;
        }
        std::memcpy(t, table, table_size * sizeof(IdxType));
    }

    void print() const noexcept {
        std::cout << "[";
        for(uint_fast_t<IdxType> i = 0; i != table_size - 2; i += 2) {
            std::cout << "[" << table[i] << ", " << table[i + 1] << "], ";
        }
        std::cout << "[" << table[table_size - 2] << ", " << table[table_size - 1] << "]]\n";
    }

    template<IdxType Size> void print_transpos(const IdxType (&bits_list)[Size]) {
        std::cout << log2(N) << " [";
        for(uint_fast_t<IdxType> it = std::begin(bits_list); it != std::end(bits_list) - 1; ++it) {
            std::cout << *it << ", ";
        }
        std::cout << *(std::end(bits_list) - 1) << "]\n";
    }
    template<IdxType Size> void print_rev(const IdxType (&perm_idx)[Size]) {
        std::cout << "[";
        for(uint_fast_t<IdxType> it = std::begin(perm_idx); it != std::end(perm_idx) - 1; ++it) {
            std::cout << *it << ", ";
        }
        std::cout << *(std::end(perm_idx) - 1) << "]\n";
    }

private:
    template<typename ItemType> class container {
        static constexpr IdxType INIT_SIZE = 4;
        static constexpr IdxType STEP = 2;

    public:
        constexpr container() noexcept: items(nullptr), len(0), cap(0) {}
        ~container() noexcept {
            if(items) {
                delete[] items;
            }
        }

        container(const container &) = delete;
        container &operator=(const container &) = delete;

        constexpr container(container &&other) noexcept: items(other.items), len(other.len), cap(other.cap) {
            other.items = nullptr;
            other.len = 0;
            other.cap = 0;
        }
        constexpr container &operator=(container &&other) noexcept {
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

        constexpr bool append(const ItemType &v) noexcept {
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
        constexpr bool append(ItemType &&v) noexcept {
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

        constexpr IdxType size() const noexcept {
            return len;
        }

        constexpr ItemType &operator[](IdxType i) noexcept {
            return items[i];
        }
        constexpr const ItemType &operator[](IdxType i) const noexcept {
            return items[i];
        }

        class iterator {
        public:
            constexpr iterator(ItemType *p) noexcept: it(p) {}

            constexpr iterator &operator++() noexcept {
                ++it;
                return *this;
            }
            constexpr const iterator &operator++() const noexcept {
                ++it;
                return *this;
            }
            constexpr bool operator!=(const iterator &rhs) const noexcept {
                return it != rhs.it;
            }
            constexpr const ItemType &operator*() const noexcept {
                return *it;
            }

        private:
            ItemType *it;
        };
        constexpr iterator begin() const noexcept {
            return iterator(items);
        }
        constexpr iterator end() const noexcept {
            return iterator(items + len);
        }

        void print() const noexcept {
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
        void print(void (*item_printer)(const ItemType &)) const noexcept {
            std::cout << "[";
            if(len) {
                for(uint_fast_t<IdxType> i = 0; i != len - 1; ++i) {
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
        constexpr bool realloc(IdxType new_cap) noexcept {
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
    constexpr container<container<IdxType>> oneline2cyclic(const IdxType (&oneline)[N]) {
        container<container<IdxType>> cyclic_form;
        std::bitset<N> checked;
        for(uint_fast_t<IdxType> i = 0; i != N; ++i) {
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

template<typename IdxType> constexpr void print_bit_rev_index_table(const IdxType *table, IdxType size) {
    printf("const uint16_t armBitRevIndexTable[%d] ARM_DSP_TABLE_ATTRIBUTE = {\n", size);
    printf("/* , size %d*/\n", size);
    for(uint_fast_t<IdxType> i = 0; i != size / 2; ++i) {
        printf("   %d, %d,\n", table[2 * i], table[2 * i + 1]);
    }
    printf("};\n");
}

} // namespace mf

#endif // HPP_MF_TRANSPOSITION
