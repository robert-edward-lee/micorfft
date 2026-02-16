#ifndef HPP_MF_CONST_MATH_ABS
#define HPP_MF_CONST_MATH_ABS

namespace mf { namespace cm {
template<typename T> constexpr T abs(T x) noexcept {
    return x >= T(0) ? x : -x;
}
/**
 * @brief Функция знака https://ru.wikipedia.org/wiki/Sgn
 */
template<typename T> constexpr T sgn(T x) noexcept {
    return (T(0) < x) - (x < T(0));
}
}} /* namespace mf::cm */

#endif /* HPP_MF_CONST_MATH_ABS */
