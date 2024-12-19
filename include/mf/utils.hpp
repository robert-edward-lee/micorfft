#ifndef HPP_MF_UTILS
#define HPP_MF_UTILS

#include <type_traits>

namespace mf {
template<typename T> constexpr std::enable_if_t<std::is_integral_v<T>, bool> is_pow_of_2(T x) {
    return x && !(x & (x - T(1)));
}
template<typename T> constexpr std::enable_if_t<std::is_integral_v<T>, T> log2(T x) {
    if constexpr(sizeof(T) <= sizeof(unsigned)) {
        return T(8) * sizeof(T) - T(1) - __builtin_clz(x);
    } else if constexpr(sizeof(T) == sizeof(long unsigned)) {
        return T(8) * sizeof(T) - T(1) - __builtin_clzl(x);
    } else if constexpr(sizeof(T) == sizeof(long long unsigned)) {
        return T(8) * sizeof(T) - T(1) - __builtin_clzll(x);
    }
}
} // namespace mf

#endif // HPP_MF_UTILS
