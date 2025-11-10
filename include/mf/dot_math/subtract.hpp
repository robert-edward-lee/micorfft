#ifndef HPP_MF_DOT_MATH_SUBTRACT
#define HPP_MF_DOT_MATH_SUBTRACT

#include "mf/dot_math/common.hpp"

namespace mf {
namespace dot_math {
template<typename DataType>
MF_OPTIMIZE(3) MF_CONSTEXPR DataType sub(const DataType &lhs, const DataType &rhs) MF_NOEXCEPT {
    return lhs - rhs;
}
template<typename DataType>
MF_OPTIMIZE(3) MF_CONSTEXPR void sub_assign(DataType &lhs, const DataType &rhs) MF_NOEXCEPT {
    lhs -= rhs;
}
} /* namespace dot_math */

template<typename DataType, size_t Size>
MF_OPTIMIZE(3) MF_CONSTEXPR_14 void subtract(DataType (&difference)[Size],
                                             const DataType (&minuend)[Size],
                                             const DataType (&subtrahend)[Size]) MF_NOEXCEPT {
    dot_math::loop_unroller<16>(difference, minuend, subtrahend, dot_math::sub<DataType>);
}

template<typename DataType, size_t Size>
MF_OPTIMIZE(3) MF_CONSTEXPR_14 void
subtract(DataType (&difference)[Size], const DataType (&minuend)[Size], const DataType &subtrahend) MF_NOEXCEPT {
    dot_math::loop_unroller<16>(difference, minuend, subtrahend, dot_math::sub);
}

template<typename DataType, size_t Size>
MF_OPTIMIZE(3) MF_CONSTEXPR_14 void subtract(DataType (&minuend)[Size],
                                             const DataType (&subtrahend)[Size]) MF_NOEXCEPT {
    dot_math::loop_unroller<16>(minuend, subtrahend, dot_math::sub_assign);
}

template<typename DataType, size_t Size>
MF_OPTIMIZE(3) MF_CONSTEXPR_14 void subtract(DataType (&minuend)[Size], const DataType &subtrahend) MF_NOEXCEPT {
    dot_math::loop_unroller<16>(minuend, subtrahend, dot_math::sub_assign);
}

} /* namespace mf */

#endif /* HPP_MF_DOT_MATH_SUBTRACT */
