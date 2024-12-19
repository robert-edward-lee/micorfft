#ifndef HPP_MF_FFT
#define HPP_MF_FFT

#include "mf/transposition.hpp"
#include "mf/twiddle.hpp"
#include "mf/utils.hpp"

namespace mf {
template<typename DataType, typename IdxType, IdxType Size> class Cfft {
    static_assert(is_valid_fft_type_v<DataType>);
    static_assert(is_valid_idx_type_v<IdxType>);

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
        fill_twiddle_coeff(TwiddleCfft);
    }

    /** points to the Twiddle factor table. */
    DataType TwiddleCfft[CFFT_LEN * 2];
    /** points to the bit reversal table. */
    const IdxType *pBitRevTable;
    /** bit reversal table length. */
    IdxType bitRevLength;
private:
};
template<typename DataType, typename IdxType, IdxType Size> class Rfft: public Cfft<DataType, IdxType, Size / 2> {
    static_assert(is_valid_fft_type_v<DataType>);
    static_assert(is_valid_idx_type_v<IdxType>);

public:
    static constexpr IdxType RFFT_LEN = Size;

    Rfft() {
        /*  */
        fill_rfft_twiddle_coeff(TwiddleRfft);
    }

    /** Twiddle factors real stage  */
    DataType TwiddleRfft[RFFT_LEN];
private:
};

} // namespace mf

#endif // HPP_MF_FFT
