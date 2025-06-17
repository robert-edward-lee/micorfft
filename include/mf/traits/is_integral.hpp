#ifndef HPP_MF_TRAITS_IS_INTEGRAL
#define HPP_MF_TRAITS_IS_INTEGRAL

#include "mf/config.hpp"
#include "mf/traits/integral_constant.hpp"
#include "mf/traits/remove_cv.hpp"

namespace mf {
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
#else
// TODO что то тут сделать!
template<> struct is_integral_helper<size_t>: true_type {};
#endif
} // namespace detail
template<typename T> struct is_integral: detail::is_integral_helper<typename remove_cv<T>::type>::type {};
} // namespace mf

#endif // HPP_MF_TRAITS_IS_INTEGRAL
