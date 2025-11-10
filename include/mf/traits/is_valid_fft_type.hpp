#ifndef HPP_MF_TRAITS_IS_VALID_FFT_TYPE
#define HPP_MF_TRAITS_IS_VALID_FFT_TYPE

#include "mf/traits/remove_cv.hpp"
#include "mf/types/floating.hpp"
#include "mf/types/integral.hpp"

namespace mf {
namespace detail {
template<typename T> struct is_valid_fft_type_helper: false_type {};
#if MF_HAS_FLOAT32_TYPE
template<> struct is_valid_fft_type_helper<float32_t>: true_type {};
#endif
#if MF_HAS_FLOAT64_TYPE
template<> struct is_valid_fft_type_helper<float64_t>: true_type {};
#endif
#if MF_HAS_FLOAT80_TYPE
template<> struct is_valid_fft_type_helper<float80_t>: true_type {};
#endif
#if MF_HAS_FLOAT128_TYPE
template<> struct is_valid_fft_type_helper<float128_t>: true_type {};
#endif
} /* namespace detail */
template<typename T> struct is_valid_fft_type: detail::is_valid_fft_type_helper<typename remove_cv<T>::type> {};
} /* namespace mf */

#endif /* HPP_MF_TRAITS_IS_VALID_FFT_TYPE */
