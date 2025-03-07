#ifndef HPP_MF_INTEGRAL_CONSTANT
#define HPP_MF_INTEGRAL_CONSTANT

#include "mf/config.hpp"
#include "mf/traits/remove_cv.hpp"

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
} // namespace mf

#endif // HPP_MF_INTEGRAL_CONSTANT
