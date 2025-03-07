#include <cstdint>
#include <iomanip>
#include <iostream>

#include "mf/basic_math.hpp"
#include "mf/statistic.hpp"
#include "mf/traits.hpp"
#include "mf/types.hpp"
#include "mf/types/fixed.hpp"
#include "mf/utils.hpp"

MF_NODISCARD MF_CONSTEXPR uint32_t quad8(uint32_t x, uint32_t y) MF_NOEXCEPT {
    const uint32_t r = mf::ssat<8>((((int32_t(x) << 24) >> 24) + ((int32_t(y) << 24) >> 24)));
    const uint32_t s = mf::ssat<8>((((int32_t(x) << 16) >> 24) + ((int32_t(y) << 16) >> 24)));
    const uint32_t t = mf::ssat<8>((((int32_t(x) << 8) >> 24) + ((int32_t(y) << 8) >> 24)));
    const uint32_t u = mf::ssat<8>((((int32_t(x) << 0) >> 24) + ((int32_t(y) << 0) >> 24)));
    return (u << 24) | (t << 16) | (s << 8) | r;
}

MF_NODISCARD MF_CONSTEXPR uint32_t quad16(uint32_t x, uint32_t y) MF_NOEXCEPT {
    const int32_t r = mf::ssat<16>((((int32_t(x) << 16) >> 16) + ((int32_t(y) << 16) >> 16)));
    const int32_t s = mf::ssat<16>((((int32_t(x) << 0) >> 16) + ((int32_t(y) << 0) >> 16)));
    return (s << 16) | r;
}

template<typename T, size_t Size> void pr_arr(const T (&cells)[Size]) {
    std::cout << "[ ";
    for(size_t i = 0; i != Size; ++i) {
        std::cout << cells[i] << " ";
    }
    std::cout << "]\n";
}

int main() {
    typedef mf::FixedPoint<int16_t, 15> q15_t;

    q15_t q1 = -8192;
    q15_t q2 = 1;

    std::cout << std::setprecision(sizeof(q15_t) * 8);
    std::cout << q1 << "\n";
    std::cout << q2 << "\n";

    q1 /= q2;

    std::cout << q1 << "\n";
    std::cout << int16_t(q1) << "\n";

    return 0;
}
