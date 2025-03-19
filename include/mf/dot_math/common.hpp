#ifndef HPP_MF_DOT_MATH_COMMON
#define HPP_MF_DOT_MATH_COMMON

#include "mf/config.hpp"
#include "mf/types/integral.hpp"

namespace mf { namespace dot_math {
/**
 * @brief [out] = [lhs] op [rhs];
 */
template<size_t BlkSize, typename DataType, size_t Size>
MF_OPTIMIZE(3) MF_CONSTEXPR_14 void loop_unroller(DataType (&out)[Size],
                                                  const DataType (&lhs)[Size],
                                                  const DataType (&rhs)[Size],
                                                  DataType (&op)(const DataType &, const DataType &)
                                                      MF_NOEXCEPT) MF_NOEXCEPT {
    MF_STATIC_ASSERT(!(BlkSize % 2));

    typedef typename fastest_integral_type<Size>::type idx_t;

    MF_CONST_OR_CONSTEXPR idx_t BLKS = Size / BlkSize;
    MF_CONST_OR_CONSTEXPR idx_t RESIDUE = Size % BlkSize;

    for(idx_t i = 0; i != BLKS; ++i) {
        out[BlkSize * i + 0] = op(lhs[BlkSize * i + 0], rhs[BlkSize * i + 0]);
        out[BlkSize * i + 1] = op(lhs[BlkSize * i + 1], rhs[BlkSize * i + 1]);
        out[BlkSize * i + 2] = op(lhs[BlkSize * i + 2], rhs[BlkSize * i + 2]);
        out[BlkSize * i + 3] = op(lhs[BlkSize * i + 3], rhs[BlkSize * i + 3]);
        MF_IF_CONSTEXPR(BlkSize > 4) {
            out[BlkSize * i + 4] = op(lhs[BlkSize * i + 4], rhs[BlkSize * i + 4]);
            out[BlkSize * i + 5] = op(lhs[BlkSize * i + 5], rhs[BlkSize * i + 5]);
            out[BlkSize * i + 6] = op(lhs[BlkSize * i + 6], rhs[BlkSize * i + 6]);
            out[BlkSize * i + 7] = op(lhs[BlkSize * i + 7], rhs[BlkSize * i + 7]);
        }
        MF_IF_CONSTEXPR(BlkSize > 8) {
            out[BlkSize * i + 8] = op(lhs[BlkSize * i + 8], rhs[BlkSize * i + 8]);
            out[BlkSize * i + 9] = op(lhs[BlkSize * i + 9], rhs[BlkSize * i + 9]);
            out[BlkSize * i + 10] = op(lhs[BlkSize * i + 10], rhs[BlkSize * i + 10]);
            out[BlkSize * i + 11] = op(lhs[BlkSize * i + 11], rhs[BlkSize * i + 11]);
            out[BlkSize * i + 12] = op(lhs[BlkSize * i + 12], rhs[BlkSize * i + 12]);
            out[BlkSize * i + 13] = op(lhs[BlkSize * i + 13], rhs[BlkSize * i + 13]);
            out[BlkSize * i + 14] = op(lhs[BlkSize * i + 14], rhs[BlkSize * i + 14]);
            out[BlkSize * i + 15] = op(lhs[BlkSize * i + 15], rhs[BlkSize * i + 15]);
        }
    }

    MF_IF_CONSTEXPR(RESIDUE != 0) {
        for(idx_t i = BLKS * BlkSize; i != Size; ++i) {
            out[i] = op(lhs[i], rhs[i]);
        }
    }
}
/**
 * @brief [out] = [lhs] op rhs;
 */
template<size_t BlkSize, typename DataType, size_t Size>
MF_OPTIMIZE(3) MF_CONSTEXPR_14 void loop_unroller(DataType (&out)[Size],
                                                  const DataType (&lhs)[Size],
                                                  const DataType &rhs,
                                                  DataType (&op)(const DataType &, const DataType &)
                                                      MF_NOEXCEPT) MF_NOEXCEPT {
    MF_STATIC_ASSERT(!(BlkSize % 2));

    typedef typename fastest_integral_type<Size>::type idx_t;

    MF_CONST_OR_CONSTEXPR idx_t BLKS = Size / BlkSize;
    MF_CONST_OR_CONSTEXPR idx_t RESIDUE = Size % BlkSize;

    for(idx_t i = 0; i != BLKS; ++i) {
        out[BlkSize * i + 0] = op(lhs[BlkSize * i + 0], rhs);
        out[BlkSize * i + 1] = op(lhs[BlkSize * i + 1], rhs);
        out[BlkSize * i + 2] = op(lhs[BlkSize * i + 2], rhs);
        out[BlkSize * i + 3] = op(lhs[BlkSize * i + 3], rhs);
        MF_IF_CONSTEXPR(BlkSize > 4) {
            out[BlkSize * i + 4] = op(lhs[BlkSize * i + 4], rhs);
            out[BlkSize * i + 5] = op(lhs[BlkSize * i + 5], rhs);
            out[BlkSize * i + 6] = op(lhs[BlkSize * i + 6], rhs);
            out[BlkSize * i + 7] = op(lhs[BlkSize * i + 7], rhs);
        }
        MF_IF_CONSTEXPR(BlkSize > 8) {
            out[BlkSize * i + 8] = op(lhs[BlkSize * i + 8], rhs);
            out[BlkSize * i + 9] = op(lhs[BlkSize * i + 9], rhs);
            out[BlkSize * i + 10] = op(lhs[BlkSize * i + 10], rhs);
            out[BlkSize * i + 11] = op(lhs[BlkSize * i + 11], rhs);
            out[BlkSize * i + 12] = op(lhs[BlkSize * i + 12], rhs);
            out[BlkSize * i + 13] = op(lhs[BlkSize * i + 13], rhs);
            out[BlkSize * i + 14] = op(lhs[BlkSize * i + 14], rhs);
            out[BlkSize * i + 15] = op(lhs[BlkSize * i + 15], rhs);
        }
    }

    MF_IF_CONSTEXPR(RESIDUE != 0) {
        for(idx_t i = BLKS * BlkSize; i != Size; ++i) {
            out[i] = op(lhs[i], rhs);
        }
    }
}
/**
 * @brief [out] op= [rhs];
 */
template<size_t BlkSize, typename DataType, size_t Size>
MF_OPTIMIZE(3) MF_CONSTEXPR_14 void loop_unroller(DataType (&out)[Size],
                                                  const DataType (&rhs)[Size],
                                                  void (&op)(DataType &, const DataType &) MF_NOEXCEPT) MF_NOEXCEPT {
    MF_STATIC_ASSERT(!(BlkSize % 2));

    typedef typename fastest_integral_type<Size>::type idx_t;

    MF_CONST_OR_CONSTEXPR idx_t BLKS = Size / BlkSize;
    MF_CONST_OR_CONSTEXPR idx_t RESIDUE = Size % BlkSize;

    for(idx_t i = 0; i != BLKS; ++i) {
        op(out[BlkSize * i + 0], rhs[BlkSize * i + 0]);
        op(out[BlkSize * i + 1], rhs[BlkSize * i + 1]);
        op(out[BlkSize * i + 2], rhs[BlkSize * i + 2]);
        op(out[BlkSize * i + 3], rhs[BlkSize * i + 3]);
        MF_IF_CONSTEXPR(BlkSize > 4) {
            op(out[BlkSize * i + 4], rhs[BlkSize * i + 4]);
            op(out[BlkSize * i + 5], rhs[BlkSize * i + 5]);
            op(out[BlkSize * i + 6], rhs[BlkSize * i + 6]);
            op(out[BlkSize * i + 7], rhs[BlkSize * i + 7]);
        }
        MF_IF_CONSTEXPR(BlkSize > 8) {
            op(out[BlkSize * i + 8], rhs[BlkSize * i + 8]);
            op(out[BlkSize * i + 9], rhs[BlkSize * i + 9]);
            op(out[BlkSize * i + 10], rhs[BlkSize * i + 10]);
            op(out[BlkSize * i + 11], rhs[BlkSize * i + 11]);
            op(out[BlkSize * i + 12], rhs[BlkSize * i + 12]);
            op(out[BlkSize * i + 13], rhs[BlkSize * i + 13]);
            op(out[BlkSize * i + 14], rhs[BlkSize * i + 14]);
            op(out[BlkSize * i + 15], rhs[BlkSize * i + 15]);
        }
    }

    MF_IF_CONSTEXPR(RESIDUE != 0) {
        for(idx_t i = BLKS * BlkSize; i != Size; ++i) {
            op(out[i], rhs[i]);
        }
    }
}
/**
 * @brief [out] op= rhs;
 */
template<size_t BlkSize, typename DataType, size_t Size>
MF_OPTIMIZE(3) MF_CONSTEXPR_14 void loop_unroller(DataType (&out)[Size],
                                                  const DataType &rhs,
                                                  DataType (&op)(const DataType &, const DataType &)
                                                      MF_NOEXCEPT) MF_NOEXCEPT {
    MF_STATIC_ASSERT(!(BlkSize % 2));

    typedef typename fastest_integral_type<Size>::type idx_t;

    MF_CONST_OR_CONSTEXPR idx_t BLKS = Size / BlkSize;
    MF_CONST_OR_CONSTEXPR idx_t RESIDUE = Size % BlkSize;

    for(idx_t i = 0; i != BLKS; ++i) {
        out[BlkSize * i + 0] = op(out[BlkSize * i + 0], rhs);
        out[BlkSize * i + 1] = op(out[BlkSize * i + 1], rhs);
        out[BlkSize * i + 2] = op(out[BlkSize * i + 2], rhs);
        out[BlkSize * i + 3] = op(out[BlkSize * i + 3], rhs);
        MF_IF_CONSTEXPR(BlkSize > 4) {
            out[BlkSize * i + 4] = op(out[BlkSize * i + 4], rhs);
            out[BlkSize * i + 5] = op(out[BlkSize * i + 5], rhs);
            out[BlkSize * i + 6] = op(out[BlkSize * i + 6], rhs);
            out[BlkSize * i + 7] = op(out[BlkSize * i + 7], rhs);
        }
        MF_IF_CONSTEXPR(BlkSize > 8) {
            out[BlkSize * i + 8] = op(out[BlkSize * i + 8], rhs);
            out[BlkSize * i + 9] = op(out[BlkSize * i + 9], rhs);
            out[BlkSize * i + 10] = op(out[BlkSize * i + 10], rhs);
            out[BlkSize * i + 11] = op(out[BlkSize * i + 11], rhs);
            out[BlkSize * i + 12] = op(out[BlkSize * i + 12], rhs);
            out[BlkSize * i + 13] = op(out[BlkSize * i + 13], rhs);
            out[BlkSize * i + 14] = op(out[BlkSize * i + 14], rhs);
            out[BlkSize * i + 15] = op(out[BlkSize * i + 15], rhs);
        }
    }

    MF_IF_CONSTEXPR(RESIDUE != 0) {
        for(idx_t i = BLKS * BlkSize; i != Size; ++i) {
            out[i] = op(out[i], rhs);
        }
    }
}
}} // namespace mf::dot_math

#endif // HPP_MF_DOT_MATH_COMMON
