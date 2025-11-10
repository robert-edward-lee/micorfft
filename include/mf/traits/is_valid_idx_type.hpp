#ifndef HPP_MF_TRAITS_IS_VALID_IDX_TYPE
#define HPP_MF_TRAITS_IS_VALID_IDX_TYPE

#include "mf/traits/integral_constant.hpp"
#include "mf/traits/remove_cv.hpp"
#include "mf/types/integral.hpp"

namespace mf {
namespace detail {
template<typename T> struct is_valid_idx_type_helper: false_type {};
template<> struct is_valid_idx_type_helper<uint8_t>: true_type {};
template<> struct is_valid_idx_type_helper<uint16_t>: true_type {};
template<> struct is_valid_idx_type_helper<uint32_t>: true_type {};
} /* namespace detail */
template<typename T> struct is_valid_idx_type: detail::is_valid_idx_type_helper<typename remove_cv<T>::type> {};
} /* namespace mf */

#endif /* HPP_MF_TRAITS_IS_VALID_IDX_TYPE */
