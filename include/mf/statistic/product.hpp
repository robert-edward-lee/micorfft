#ifndef HPP_MF_STATISTIC_PRODUCT
#define HPP_MF_STATISTIC_PRODUCT

#include "mf/statistic/common.hpp"

namespace mf {
namespace statistic {
template<typename LhsDataType, typename RhsDataType>
MF_OPTIMIZE(3) MF_CONSTEXPR void product_op(LhsDataType &lhs, const RhsDataType &rhs) MF_NOEXCEPT {
    lhs *= rhs;
}
} // namespace statistic

template<typename OutDataType, typename DataType, size_t Size>
MF_NODISCARD MF_OPTIMIZE(3) MF_CONSTEXPR_14 OutDataType product(const DataType (&data)[Size],
                                                                const OutDataType &init = OutDataType(1)) MF_NOEXCEPT {
    return statistic::loop_unroller<16>(data, init, statistic::product_op<OutDataType>);
}
template<typename OutDataType, typename DataType, size_t Size>
MF_OPTIMIZE(3) MF_CONSTEXPR_14 void product(const DataType (&data)[Size], OutDataType &init) MF_NOEXCEPT {
    statistic::loop_unroller<16>(data, init, statistic::product_op);
}
} // namespace mf

#endif // HPP_MF_STATISTIC_PRODUCT
