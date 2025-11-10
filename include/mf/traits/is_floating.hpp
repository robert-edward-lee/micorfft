#ifndef HPP_MF_TRAITS_IS_FLOATING
#define HPP_MF_TRAITS_IS_FLOATING

#include "mf/config.hpp"
#include "mf/traits/integral_constant.hpp"
#include "mf/traits/remove_cv.hpp"
#include "mf/types/floating.hpp"

namespace mf {
namespace detail {
template<typename T> struct is_floating_helper: false_type {};
#if MF_HAS_FLOAT16_TYPE
template<> struct is_floating_helper<float16_t>: true_type {};
#endif

#if MF_HAS_FLOAT32_TYPE
template<> struct is_floating_helper<float32_t>: true_type {};
#endif

#if MF_HAS_FLOAT64_TYPE
template<> struct is_floating_helper<float64_t>: true_type {};
#endif

#if MF_HAS_FLOAT80_TYPE
template<> struct is_floating_helper<float80_t>: true_type {};
#endif

#if MF_HAS_FLOAT128_TYPE
template<> struct is_floating_helper<float128_t>: true_type {};
#endif
} /* namespace detail */
template<typename T> struct is_floating: detail::is_floating_helper<typename remove_cv<T>::type>::type {};
} /* namespace mf */

#endif /* HPP_MF_TRAITS_IS_FLOATING */
