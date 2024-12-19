#ifndef HPP_MF_FFT
#define HPP_MF_FFT

#include <cstdint>

#include "mf/transposition.hpp"

namespace mf {
template<typename FloatType, typename IdxType, IdxType Size> class Cfft {
public:
    static constexpr IdxType CFFT_LEN = Size;

    Cfft(): pBitRevTable(nullptr), bitRevLength(0) {
        /* 1. создание таблицы для битреверса */
        Transposition<IdxType, Size, 8> transpos;
        bitRevLength = transpos.size();
        IdxType *tmp = new(std::nothrow) IdxType[bitRevLength];
        if(!tmp) {
            /* ошибка */
        }
        transpos.fill_table(tmp);
        pBitRevTable = tmp;
        /* 2. создание таблицы поворотных коэффициентов */
    }

private:
    /** points to the Twiddle factor table. */
    FloatType TwiddleCfft[CFFT_LEN];
    /** points to the bit reversal table. */
    const IdxType *pBitRevTable;
    /** bit reversal table length. */
    IdxType bitRevLength;
};
template<typename FloatType, typename IdxType, IdxType Size> class Rfft: public Cfft<FloatType, IdxType, Size / 2> {
public:
    static constexpr IdxType RFFT_LEN = Size;

    Rfft() {}

private:
    /** Twiddle factors real stage  */
    FloatType pTwiddleRfft[RFFT_LEN];
};

} // namespace mf

#endif // HPP_MF_FFT
