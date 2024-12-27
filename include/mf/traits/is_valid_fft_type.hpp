#ifndef HPP_MF_TRAITS_IS_VALID_FFT_TYPE
#define HPP_MF_TRAITS_IS_VALID_FFT_TYPE

#include "mf/types/floating.hpp"

namespace mf {
template<typename IdxType> struct is_valid_fft_type: false_type {};
template<> struct is_valid_fft_type<float32_t>: true_type {};
template<> struct is_valid_fft_type<float64_t>: true_type {};
} // namespace mf

#endif // HPP_MF_TRAITS_IS_VALID_FFT_TYPE
