#ifndef HPP_MF_INTEGRAL_CONSTANT
#define HPP_MF_INTEGRAL_CONSTANT

#include "mf/traits/remove_cv.hpp"
#include "mf/utils/config.hpp"

namespace mf {
template<typename T, T v> struct integral_constant {
    static MF_CONST_OR_CONSTEXPR T value = v;
    typedef T value_type;
    typedef integral_constant<T, v> type;
    MF_CONSTEXPR operator value_type() const MF_NOEXCEPT {
        return value;
    }
    MF_CONSTEXPR value_type operator()() const MF_NOEXCEPT {
        return value;
    }
};
typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;

namespace detail {
template<typename T> struct is_integral_helper: false_type {};
template<> struct is_integral_helper<bool>: true_type {};
template<> struct is_integral_helper<char>: true_type {};
template<> struct is_integral_helper<unsigned char>: true_type {};
template<> struct is_integral_helper<signed char>: true_type {};
template<> struct is_integral_helper<wchar_t>: true_type {};
template<> struct is_integral_helper<unsigned short>: true_type {};
template<> struct is_integral_helper<signed short>: true_type {};
template<> struct is_integral_helper<unsigned int>: true_type {};
template<> struct is_integral_helper<signed int>: true_type {};
template<> struct is_integral_helper<unsigned long>: true_type {};
template<> struct is_integral_helper<signed long>: true_type {};
#if MF_CXX_VER > 199711L
template<> struct is_integral_helper<unsigned long long>: true_type {};
template<> struct is_integral_helper<signed long long>: true_type {};
#endif
} // namespace detail
template<typename T> struct is_integral: detail::is_integral_helper<typename remove_cv<T>::type>::type {};
} // namespace mf

#endif // HPP_MF_INTEGRAL_CONSTANT
