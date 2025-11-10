#ifndef HPP_MF_DOT_MATH_MULTIPLICATE
#define HPP_MF_DOT_MATH_MULTIPLICATE

#include "mf/dot_math/common.hpp"

namespace mf {
namespace dot_math {
template<typename DataType>
MF_OPTIMIZE(3) MF_CONSTEXPR DataType mul(const DataType &lhs, const DataType &rhs) MF_NOEXCEPT {
    return lhs * rhs;
}
template<typename DataType>
MF_OPTIMIZE(3) MF_CONSTEXPR void mul_assign(DataType &lhs, const DataType &rhs) MF_NOEXCEPT {
    lhs *= rhs;
}
} /* namespace dot_math */

template<typename DataType, size_t Size>
MF_OPTIMIZE(3) MF_CONSTEXPR_14 void multiplicate(DataType (&product)[Size],
                                                 const DataType (&multiplier)[Size],
                                                 const DataType (&multiplicand)[Size]) MF_NOEXCEPT {
    dot_math::loop_unroller<16>(product, multiplier, multiplicand, dot_math::mul<DataType>);
}

template<typename DataType, size_t Size>
MF_OPTIMIZE(3) MF_CONSTEXPR_14 void
multiplicate(DataType (&product)[Size], const DataType (&multiplier)[Size], const DataType &multiplicand) MF_NOEXCEPT {
    dot_math::loop_unroller<16>(product, multiplier, multiplicand, dot_math::mul);
}

template<typename DataType, size_t Size>
MF_OPTIMIZE(3) MF_CONSTEXPR_14 void multiplicate(DataType (&multiplier)[Size],
                                                 const DataType (&multiplicand)[Size]) MF_NOEXCEPT {
    dot_math::loop_unroller<16>(multiplier, multiplicand, dot_math::mul_assign);
}

template<typename DataType, size_t Size>
MF_OPTIMIZE(3) MF_CONSTEXPR_14 void multiplicate(DataType (&multiplier)[Size],
                                                 const DataType &multiplicand) MF_NOEXCEPT {
    dot_math::loop_unroller<16>(multiplier, multiplicand, dot_math::mul_assign);
}

} /* namespace mf */

#endif /* HPP_MF_DOT_MATH_MULTIPLICATE */
