#ifndef HPP_MF_DOT_MATH_COMPLEX
#define HPP_MF_DOT_MATH_COMPLEX

#include "mf/config.hpp"
#include "mf/types/complex.hpp"

namespace mf {
template<typename DataType, size_t Size>
MF_OPTIMIZE(3) MF_CONSTEXPR_14 void magnitude_sqr(const DataType (&src)[Size * 2], DataType (&dst)[Size]) {
    typedef typename uint_fast<typename idx_type_chooser<Size>::type>::type idx_t;

    MF_CONST_OR_CONSTEXPR idx_t BLK_SIZE = 4;
    MF_CONST_OR_CONSTEXPR idx_t BLKS = Size / BLK_SIZE;
    MF_CONST_OR_CONSTEXPR idx_t RESIDUE = Size % BLK_SIZE;

    for(idx_t i = 0; i != BLKS; ++i) {
        dst[BLK_SIZE * i + 0] = src[2 * BLK_SIZE * i + 0] * src[2 * BLK_SIZE * i + 0]
                              + src[2 * BLK_SIZE * i + 1] * src[2 * BLK_SIZE * i + 1];
        dst[BLK_SIZE * i + 1] = src[2 * BLK_SIZE * i + 2] * src[2 * BLK_SIZE * i + 2]
                              + src[2 * BLK_SIZE * i + 3] * src[2 * BLK_SIZE * i + 3];
        dst[BLK_SIZE * i + 2] = src[2 * BLK_SIZE * i + 4] * src[2 * BLK_SIZE * i + 4]
                              + src[2 * BLK_SIZE * i + 5] * src[2 * BLK_SIZE * i + 5];
        dst[BLK_SIZE * i + 3] = src[2 * BLK_SIZE * i + 6] * src[2 * BLK_SIZE * i + 6]
                              + src[2 * BLK_SIZE * i + 7] * src[2 * BLK_SIZE * i + 7];
    }

    MF_IF_CONSTEXPR(RESIDUE != 0) {
        for(idx_t i = BLKS * BLK_SIZE; i != Size; ++i) {
            dst[i] = src[2 * i] * src[2 * i] + src[2 * i + 1] * src[2 * i + 1];
        }
    }
}

template<typename DataType, size_t Size>
MF_OPTIMIZE(3) MF_CONSTEXPR_14 void magnitude_sqr(const Complex<DataType> (&csrc)[Size], DataType (&dst)[Size]) {
    typedef typename uint_fast<typename idx_type_chooser<Size>::type>::type idx_t;

    MF_CONST_OR_CONSTEXPR idx_t BLK_SIZE = 4;
    MF_CONST_OR_CONSTEXPR idx_t BLKS = Size / BLK_SIZE;
    MF_CONST_OR_CONSTEXPR idx_t RESIDUE = Size % BLK_SIZE;

    const DataType(&src)[Size * 2] = (const DataType(&)[Size * 2]) csrc;
    for(idx_t i = 0; i != BLKS; ++i) {
        dst[BLK_SIZE * i + 0] = src[2 * BLK_SIZE * i + 0] * src[2 * BLK_SIZE * i + 0]
                              + src[2 * BLK_SIZE * i + 1] * src[2 * BLK_SIZE * i + 1];
        dst[BLK_SIZE * i + 1] = src[2 * BLK_SIZE * i + 2] * src[2 * BLK_SIZE * i + 2]
                              + src[2 * BLK_SIZE * i + 3] * src[2 * BLK_SIZE * i + 3];
        dst[BLK_SIZE * i + 2] = src[2 * BLK_SIZE * i + 4] * src[2 * BLK_SIZE * i + 4]
                              + src[2 * BLK_SIZE * i + 5] * src[2 * BLK_SIZE * i + 5];
        dst[BLK_SIZE * i + 3] = src[2 * BLK_SIZE * i + 6] * src[2 * BLK_SIZE * i + 6]
                              + src[2 * BLK_SIZE * i + 7] * src[2 * BLK_SIZE * i + 7];
    }

    MF_IF_CONSTEXPR(RESIDUE != 0) {
        for(idx_t i = BLKS * BLK_SIZE; i != Size; ++i) {
            dst[i] = src[2 * i] * src[2 * i] + src[2 * i + 1] * src[2 * i + 1];
        }
    }
}

template<typename DataType, size_t Size> MF_OPTIMIZE(3) MF_CONSTEXPR_14 void conjugate(DataType (&data)[Size * 2]) {
    typedef typename uint_fast<typename idx_type_chooser<Size>::type>::type idx_t;

    MF_CONST_OR_CONSTEXPR idx_t BLK_SIZE = 4;
    MF_CONST_OR_CONSTEXPR idx_t BLKS = Size / BLK_SIZE;
    MF_CONST_OR_CONSTEXPR idx_t RESIDUE = Size % BLK_SIZE;

    for(idx_t i = 0; i != BLKS; ++i) {
        data[2 * BLK_SIZE * i + 1] = -data[2 * BLK_SIZE * i + 1];
        data[2 * BLK_SIZE * i + 3] = -data[2 * BLK_SIZE * i + 3];
        data[2 * BLK_SIZE * i + 5] = -data[2 * BLK_SIZE * i + 5];
        data[2 * BLK_SIZE * i + 7] = -data[2 * BLK_SIZE * i + 7];
    }

    MF_IF_CONSTEXPR(RESIDUE != 0) {
        for(idx_t i = BLKS * BLK_SIZE; i != Size; ++i) {
            data[2 * i + 1] = -data[2 * i + 1];
        }
    }
}

template<typename DataType, size_t Size>
MF_OPTIMIZE(3) MF_CONSTEXPR_14 void conjugate(Complex<DataType> (&cdata)[Size]) {
    typedef typename uint_fast<typename idx_type_chooser<Size>::type>::type idx_t;

    MF_CONST_OR_CONSTEXPR idx_t BLK_SIZE = 4;
    MF_CONST_OR_CONSTEXPR idx_t BLKS = Size / BLK_SIZE;
    MF_CONST_OR_CONSTEXPR idx_t RESIDUE = Size % BLK_SIZE;

    DataType(&data)[Size * 2] = (DataType(&)[Size * 2]) cdata;
    for(idx_t i = 0; i != BLKS; ++i) {
        data[2 * BLK_SIZE * i + 1] = -data[2 * BLK_SIZE * i + 1];
        data[2 * BLK_SIZE * i + 3] = -data[2 * BLK_SIZE * i + 3];
        data[2 * BLK_SIZE * i + 5] = -data[2 * BLK_SIZE * i + 5];
        data[2 * BLK_SIZE * i + 7] = -data[2 * BLK_SIZE * i + 7];
    }

    MF_IF_CONSTEXPR(RESIDUE != 0) {
        for(idx_t i = BLKS * BLK_SIZE; i != Size; ++i) {
            data[2 * i + 1] = -data[2 * i + 1];
        }
    }
}

template<typename DataType, size_t Size, bool Inverse>
MF_OPTIMIZE(3) MF_CONSTEXPR_14 void scale(DataType (&data)[Size * 2], DataType factor) {
    typedef typename uint_fast<typename idx_type_chooser<Size>::type>::type idx_t;

    MF_CONST_OR_CONSTEXPR idx_t BLK_SIZE = 4;
    MF_CONST_OR_CONSTEXPR idx_t BLKS = Size / BLK_SIZE;
    MF_CONST_OR_CONSTEXPR idx_t RESIDUE = Size % BLK_SIZE;

    MF_IF_CONSTEXPR(Inverse) {
        for(idx_t i = 0; i != BLKS; ++i) {
            data[8 * i + 0] = factor * data[8 * i + 0];
            data[8 * i + 1] = factor * -data[8 * i + 1];
            data[8 * i + 2] = factor * data[8 * i + 2];
            data[8 * i + 3] = factor * -data[8 * i + 3];
            data[8 * i + 4] = factor * data[8 * i + 4];
            data[8 * i + 5] = factor * -data[8 * i + 5];
            data[8 * i + 6] = factor * data[8 * i + 6];
            data[8 * i + 7] = factor * -data[8 * i + 7];
        }
    } else {
        for(idx_t i = 0; i != BLKS; ++i) {
            data[2 * BLK_SIZE * i + 0] = factor * data[2 * BLK_SIZE * i + 0];
            data[2 * BLK_SIZE * i + 1] = factor * data[2 * BLK_SIZE * i + 1];
            data[2 * BLK_SIZE * i + 2] = factor * data[2 * BLK_SIZE * i + 2];
            data[2 * BLK_SIZE * i + 3] = factor * data[2 * BLK_SIZE * i + 3];
            data[2 * BLK_SIZE * i + 4] = factor * data[2 * BLK_SIZE * i + 4];
            data[2 * BLK_SIZE * i + 5] = factor * data[2 * BLK_SIZE * i + 5];
            data[2 * BLK_SIZE * i + 6] = factor * data[2 * BLK_SIZE * i + 6];
            data[2 * BLK_SIZE * i + 7] = factor * data[2 * BLK_SIZE * i + 7];
        }
    }

    MF_IF_CONSTEXPR(Inverse) {
        MF_IF_CONSTEXPR(RESIDUE != 0) {
            for(idx_t i = BLKS * BLK_SIZE; i != Size; ++i) {
                data[2 * i + 0] = factor * data[2 * i + 0];
                data[2 * i + 1] = factor * -data[2 * i + 1];
            }
        }
    } else {
        MF_IF_CONSTEXPR(RESIDUE != 0) {
            for(idx_t i = BLKS * BLK_SIZE; i != Size; ++i) {
                data[2 * i + 0] = factor * data[2 * i + 0];
                data[2 * i + 1] = factor * data[2 * i + 1];
            }
        }
    }
}

template<typename DataType, size_t Size, bool Inverse>
MF_OPTIMIZE(3) MF_CONSTEXPR_14 void scale(Complex<DataType> (&cdata)[Size], DataType factor) {
    typedef typename uint_fast<typename idx_type_chooser<Size>::type>::type idx_t;

    MF_CONST_OR_CONSTEXPR idx_t BLK_SIZE = 4;
    MF_CONST_OR_CONSTEXPR idx_t BLKS = Size / BLK_SIZE;
    MF_CONST_OR_CONSTEXPR idx_t RESIDUE = Size % BLK_SIZE;

    DataType(&data)[Size * 2] = (DataType(&)[Size * 2]) cdata;
    MF_IF_CONSTEXPR(Inverse) {
        for(idx_t i = 0; i != BLKS; ++i) {
            data[2 * BLK_SIZE * i + 0] = factor * data[2 * BLK_SIZE * i + 0];
            data[2 * BLK_SIZE * i + 1] = factor * -data[2 * BLK_SIZE * i + 1];
            data[2 * BLK_SIZE * i + 2] = factor * data[2 * BLK_SIZE * i + 2];
            data[2 * BLK_SIZE * i + 3] = factor * -data[2 * BLK_SIZE * i + 3];
            data[2 * BLK_SIZE * i + 4] = factor * data[2 * BLK_SIZE * i + 4];
            data[2 * BLK_SIZE * i + 5] = factor * -data[2 * BLK_SIZE * i + 5];
            data[2 * BLK_SIZE * i + 6] = factor * data[2 * BLK_SIZE * i + 6];
            data[2 * BLK_SIZE * i + 7] = factor * -data[2 * BLK_SIZE * i + 7];
        }
    } else {
        for(idx_t i = 0; i != BLKS; ++i) {
            data[2 * BLK_SIZE * i + 0] = factor * data[2 * BLK_SIZE * i + 0];
            data[2 * BLK_SIZE * i + 1] = factor * data[2 * BLK_SIZE * i + 1];
            data[2 * BLK_SIZE * i + 2] = factor * data[2 * BLK_SIZE * i + 2];
            data[2 * BLK_SIZE * i + 3] = factor * data[2 * BLK_SIZE * i + 3];
            data[2 * BLK_SIZE * i + 4] = factor * data[2 * BLK_SIZE * i + 4];
            data[2 * BLK_SIZE * i + 5] = factor * data[2 * BLK_SIZE * i + 5];
            data[2 * BLK_SIZE * i + 6] = factor * data[2 * BLK_SIZE * i + 6];
            data[2 * BLK_SIZE * i + 7] = factor * data[2 * BLK_SIZE * i + 7];
        }
    }

    MF_IF_CONSTEXPR(RESIDUE != 0) {
        MF_IF_CONSTEXPR(Inverse) {
            for(idx_t i = BLKS * BLK_SIZE; i != Size; ++i) {
                data[2 * i + 0] = factor * data[2 * i + 0];
                data[2 * i + 1] = factor * -data[2 * i + 1];
            }
        } else {
            for(idx_t i = BLKS * BLK_SIZE; i != Size; ++i) {
                data[2 * i + 0] = factor * data[2 * i + 0];
                data[2 * i + 1] = factor * data[2 * i + 1];
            }
        }
    }
}
} // namespace mf

#endif // HPP_MF_DOT_MATH_COMPLEX
