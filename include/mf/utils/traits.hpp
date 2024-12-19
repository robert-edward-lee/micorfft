#ifndef HPP_MF_UTILS_TRAITS
#define HPP_MF_UTILS_TRAITS

#include <type_traits>

#include "mf/utils/types.hpp"

namespace mf {
using std::enable_if_t;
using std::is_integral_v;

template<typename IdxType> struct is_valid_idx_type: std::false_type {};
template<> struct is_valid_idx_type<uint16_t>: std::true_type {};
template<> struct is_valid_idx_type<uint32_t>: std::true_type {};
template<typename IdxType> constexpr bool is_valid_idx_type_v = is_valid_idx_type<IdxType>::value;

template<typename IdxType> struct is_valid_fft_type: std::false_type {};
template<> struct is_valid_fft_type<float32_t>: std::true_type {};
template<> struct is_valid_fft_type<float64_t>: std::true_type {};
template<typename IdxType> constexpr bool is_valid_fft_type_v = is_valid_fft_type<IdxType>::value;
} // namespace mf

#endif // HPP_MF_UTILS_TRAITS
