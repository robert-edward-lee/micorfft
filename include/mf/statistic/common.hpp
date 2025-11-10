#ifndef HPP_MF_STATISTIC_COMMON
#define HPP_MF_STATISTIC_COMMON

#include "mf/config.hpp"
#include "mf/types/integral.hpp"

namespace mf { namespace statistic {
template<size_t BlkSize, typename OutDataType, typename InDataType, size_t Size>
MF_NODISCARD MF_OPTIMIZE(3) MF_CONSTEXPR_14 OutDataType loop_unroller(const InDataType (&data)[Size],
                                                                      const OutDataType &init,
                                                                      void (&op)(OutDataType &lhs,
                                                                                 const InDataType &rhs)
                                                                          MF_NOEXCEPT) MF_NOEXCEPT {
    MF_STATIC_ASSERT(!(BlkSize % 2));

    typedef typename fastest_integral_type<Size>::type idx_t;

    MF_CONST_OR_CONSTEXPR idx_t BLKS = Size / BlkSize;
    MF_CONST_OR_CONSTEXPR idx_t RESIDUE = Size % BlkSize;

    OutDataType ret = init;
    for(idx_t i = 0; i != BLKS; ++i) {
        op(ret, data[BlkSize * i + 0]);
        op(ret, data[BlkSize * i + 1]);
        op(ret, data[BlkSize * i + 2]);
        op(ret, data[BlkSize * i + 3]);
        MF_IF_CONSTEXPR(BlkSize > 4) {
            op(ret, data[BlkSize * i + 4]);
            op(ret, data[BlkSize * i + 5]);
            op(ret, data[BlkSize * i + 6]);
            op(ret, data[BlkSize * i + 7]);
        }
        MF_IF_CONSTEXPR(BlkSize > 8) {
            op(ret, data[BlkSize * i + 8]);
            op(ret, data[BlkSize * i + 9]);
            op(ret, data[BlkSize * i + 10]);
            op(ret, data[BlkSize * i + 11]);
            op(ret, data[BlkSize * i + 12]);
            op(ret, data[BlkSize * i + 13]);
            op(ret, data[BlkSize * i + 14]);
            op(ret, data[BlkSize * i + 15]);
        }
    }

    MF_IF_CONSTEXPR(RESIDUE != 0) {
        for(idx_t i = BLKS * BlkSize; i != Size; ++i) {
            op(ret, data[i]);
        }
    }

    return ret;
}

template<size_t BlkSize, typename OutDataType, typename InDataType, size_t Size>
MF_OPTIMIZE(3) MF_CONSTEXPR_14 void loop_unroller(const InDataType (&data)[Size],
                                                  OutDataType &init,
                                                  void (&op)(OutDataType &lhs, const InDataType &rhs)
                                                      MF_NOEXCEPT) MF_NOEXCEPT {
    MF_STATIC_ASSERT(!(BlkSize % 2));

    typedef typename fastest_integral_type<Size>::type idx_t;

    MF_CONST_OR_CONSTEXPR idx_t BLKS = Size / BlkSize;
    MF_CONST_OR_CONSTEXPR idx_t RESIDUE = Size % BlkSize;

    for(idx_t i = 0; i != BLKS; ++i) {
        op(init, data[BlkSize * i + 0]);
        op(init, data[BlkSize * i + 1]);
        op(init, data[BlkSize * i + 2]);
        op(init, data[BlkSize * i + 3]);
        MF_IF_CONSTEXPR(BlkSize > 4) {
            op(init, data[BlkSize * i + 4]);
            op(init, data[BlkSize * i + 5]);
            op(init, data[BlkSize * i + 6]);
            op(init, data[BlkSize * i + 7]);
        }
        MF_IF_CONSTEXPR(BlkSize > 8) {
            op(init, data[BlkSize * i + 8]);
            op(init, data[BlkSize * i + 9]);
            op(init, data[BlkSize * i + 10]);
            op(init, data[BlkSize * i + 11]);
            op(init, data[BlkSize * i + 12]);
            op(init, data[BlkSize * i + 13]);
            op(init, data[BlkSize * i + 14]);
            op(init, data[BlkSize * i + 15]);
        }
    }

    MF_IF_CONSTEXPR(RESIDUE != 0) {
        for(idx_t i = BLKS * BlkSize; i != Size; ++i) {
            op(init, data[i]);
        }
    }
}
}} /* namespace mf::statistic */

#endif /* HPP_MF_STATISTIC_COMMON */
