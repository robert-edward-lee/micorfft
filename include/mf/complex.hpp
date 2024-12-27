#ifndef HPP_MF_COMPLEX
#define HPP_MF_COMPLEX

#include <complex>

#include "mf/utils/config.hpp"
#include "mf/utils/types.hpp"

namespace mf {

template<typename T> struct Complex: public std::complex<T> {};
#define CREAL(c) ((c).real())
#define CIMAG(c) ((c).imag())

template<typename DataType, typename IdxType, IdxType Size>
MF_OPTIMIZE(3) MF_CONSTEXPR void cmplx_mag_squared(const DataType (&src)[Size * 2], DataType (&dst)[Size]) {
    typedef typename uint_fast<IdxType>::type idx_t;

    MF_CONST_OR_CONSTEXPR idx_t BLK_SIZE = 4;
    MF_CONST_OR_CONSTEXPR idx_t BLKS = Size / BLK_SIZE;
    MF_CONST_OR_CONSTEXPR idx_t RESIDUE = Size % BLK_SIZE;

    for(idx_t i = 0; i != BLKS; ++i) {
        dst[4 * i + 0] = src[8 * i + 0] * src[8 * i + 0] + src[8 * i + 1] * src[8 * i + 1];
        dst[4 * i + 1] = src[8 * i + 2] * src[8 * i + 2] + src[8 * i + 3] * src[8 * i + 3];
        dst[4 * i + 2] = src[8 * i + 4] * src[8 * i + 4] + src[8 * i + 5] * src[8 * i + 5];
        dst[4 * i + 3] = src[8 * i + 6] * src[8 * i + 6] + src[8 * i + 7] * src[8 * i + 7];
    }

    MF_IF_CONSTEXPR(RESIDUE != 0) {
        for(idx_t i = BLKS * BLK_SIZE; i != Size; ++i) {
            dst[i] = src[2 * i] * src[2 * i] + src[2 * i + 1] * src[2 * i + 1];
        }
    }
}

template<typename DataType, typename IdxType, IdxType Size>
MF_OPTIMIZE(3) MF_CONSTEXPR void cmplx_mag_squared(const Complex<DataType> (&csrc)[Size], DataType (&dst)[Size]) {
    typedef typename uint_fast<IdxType>::type idx_t;

    MF_CONST_OR_CONSTEXPR idx_t BLK_SIZE = 4;
    MF_CONST_OR_CONSTEXPR idx_t BLKS = Size / BLK_SIZE;
    MF_CONST_OR_CONSTEXPR idx_t RESIDUE = Size % BLK_SIZE;

    const DataType(&src)[Size * 2] = (const DataType(&)[Size * 2]) csrc;
    for(idx_t i = 0; i != BLKS; ++i) {
        dst[4 * i + 0] = src[8 * i + 0] * src[8 * i + 0] + src[8 * i + 1] * src[8 * i + 1];
        dst[4 * i + 1] = src[8 * i + 2] * src[8 * i + 2] + src[8 * i + 3] * src[8 * i + 3];
        dst[4 * i + 2] = src[8 * i + 4] * src[8 * i + 4] + src[8 * i + 5] * src[8 * i + 5];
        dst[4 * i + 3] = src[8 * i + 6] * src[8 * i + 6] + src[8 * i + 7] * src[8 * i + 7];
    }

    MF_IF_CONSTEXPR(RESIDUE != 0) {
        for(idx_t i = BLKS * BLK_SIZE; i != Size; ++i) {
            dst[i] = src[2 * i] * src[2 * i] + src[2 * i + 1] * src[2 * i + 1];
        }
    }
}

} // namespace mf

#endif // HPP_MF_COMPLEX
