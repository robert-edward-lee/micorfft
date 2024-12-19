#ifndef HPP_MF_UTILS
#define HPP_MF_UTILS

#include <cstdint>
#include <type_traits>

namespace mf {
using std::uint16_t;
using std::uint32_t;

template<typename T> struct is_valid_idx_type: std::false_type {};
template<> struct is_valid_idx_type<uint16_t>: std::true_type {};
template<> struct is_valid_idx_type<uint32_t>: std::true_type {};
template<typename T> constexpr bool is_valid_idx_type_v = is_valid_idx_type<T>::value;

using float32_t = float;
using float64_t = double;
using float_max_t = long double;

template<typename T> struct is_valid_fft_type: std::false_type {};
template<> struct is_valid_fft_type<float32_t>: std::true_type {};
template<> struct is_valid_fft_type<float64_t>: std::true_type {};
template<typename T> constexpr bool is_valid_fft_type_v = is_valid_fft_type<T>::value;

constexpr float_max_t PI = 3.141592653589793238462643383279502884l;
constexpr float_max_t SQRT2 = 1.414213562373095048801688724209698079l;
constexpr float_max_t SQRT1_2 = 1.0l / SQRT2;

template<typename T> constexpr std::enable_if_t<std::is_integral_v<T>, bool> is_pow_of_2(T x) {
    return x && !(x & (x - T(1)));
}
template<typename T> constexpr std::enable_if_t<std::is_integral_v<T>, T> log2(T x) {
    if constexpr(sizeof(T) <= sizeof(unsigned)) {
        return T(8) * sizeof(unsigned) - T(1) - __builtin_clz(x);
    } else if constexpr(sizeof(T) == sizeof(long unsigned)) {
        return T(8) * sizeof(T) - T(1) - __builtin_clzl(x);
    } else if constexpr(sizeof(T) == sizeof(long long unsigned)) {
        return T(8) * sizeof(T) - T(1) - __builtin_clzll(x);
    }
}
} // namespace mf

#endif // HPP_MF_UTILS
