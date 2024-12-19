#ifndef HPP_MF_UTILS
#define HPP_MF_UTILS

#include <cstdint>
#include <type_traits>

namespace mf {
using std::uint16_t;
using std::uint32_t;

template<typename IdxType> struct uint_fast {
    using type = void;
};
template<> struct uint_fast<uint16_t> {
    using type = std::uint_fast16_t;
};
template<> struct uint_fast<uint32_t> {
    using type = std::uint_fast32_t;
};
template<typename IdxType> using uint_fast_t = typename uint_fast<IdxType>::type;

template<typename IdxType> struct is_valid_idx_type: std::false_type {};
template<> struct is_valid_idx_type<uint16_t>: std::true_type {};
template<> struct is_valid_idx_type<uint32_t>: std::true_type {};
template<typename IdxType> constexpr bool is_valid_idx_type_v = is_valid_idx_type<IdxType>::value;

using float32_t = float;
using float64_t = double;
using float_max_t = long double;

template<typename IdxType> struct is_valid_fft_type: std::false_type {};
template<> struct is_valid_fft_type<float32_t>: std::true_type {};
template<> struct is_valid_fft_type<float64_t>: std::true_type {};
template<typename IdxType> constexpr bool is_valid_fft_type_v = is_valid_fft_type<IdxType>::value;

constexpr float_max_t PI = 3.141592653589793238462643383279502884l;
constexpr float_max_t SQRT2 = 1.414213562373095048801688724209698079l;
constexpr float_max_t SQRT1_2 = 1.0l / SQRT2;

template<typename IdxType> constexpr std::enable_if_t<std::is_integral_v<IdxType>, bool> is_pow_of_2(IdxType x) {
    return x && !(x & (x - IdxType(1)));
}
template<typename IdxType> constexpr std::enable_if_t<std::is_integral_v<IdxType>, IdxType> log2(IdxType x) {
    if constexpr(sizeof(IdxType) <= sizeof(unsigned)) {
        return IdxType(8) * sizeof(unsigned) - IdxType(1) - __builtin_clz(x);
    } else if constexpr(sizeof(IdxType) == sizeof(long unsigned)) {
        return IdxType(8) * sizeof(IdxType) - IdxType(1) - __builtin_clzl(x);
    } else if constexpr(sizeof(IdxType) == sizeof(long long unsigned)) {
        return IdxType(8) * sizeof(IdxType) - IdxType(1) - __builtin_clzll(x);
    }
}
} // namespace mf

#endif // HPP_MF_UTILS
