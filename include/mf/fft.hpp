#ifndef HPP_MF_FFT
#define HPP_MF_FFT

#include "mf/transposition.hpp"
#include "mf/twiddle.hpp"
#include "mf/utils/math.hpp"
#include "mf/utils/types.hpp"

namespace mf {

template<typename DataType, typename IdxType, IdxType Size> class Cfft {
    MF_STATIC_ASSERT(is_valid_fft_type<DataType>::value);
    MF_STATIC_ASSERT(is_valid_idx_type<IdxType>::value);

public:
    static MF_CONST_OR_CONSTEXPR IdxType CFFT_LEN = Size;

    MF_CONSTEXPR_14 Cfft() MF_NOEXCEPT: pBitRevTable(nullptr), bitRevLength(0) {
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
        fill_twiddle_coeff<DataType, IdxType, CFFT_LEN * 2>(TwiddleCfft);
    }

    ~Cfft() { /* TODO: отказаться от выделения на куче! */
        delete[] pBitRevTable;
    }

    MF_CONSTEXPR_14 void forward(DataType *p) const MF_NOEXCEPT {
        cfft<false, true>(p);
    }
    MF_CONSTEXPR_14 void inverse(DataType *p) const MF_NOEXCEPT {
        cfft<true, true>(p);
    }

protected:
    typedef typename uint_fast<IdxType>::type idx_fast_t;

    template<IdxType L, IdxType TwidCoefModifier> MF_CONSTEXPR_14 void radix8(DataType *pSrc) const MF_NOEXCEPT {
        idx_fast_t ia1, ia2, ia3, ia4, ia5, ia6, ia7;
        idx_fast_t i1, i2, i3, i4, i5, i6, i7, i8;
        idx_fast_t id;
        idx_fast_t n1, n2, j;

        DataType r1, r2, r3, r4, r5, r6, r7, r8;
        DataType t1, t2;
        DataType s1, s2, s3, s4, s5, s6, s7, s8;
        DataType p1, p2, p3, p4;
        DataType co2, co3, co4, co5, co6, co7, co8;
        DataType si2, si3, si4, si5, si6, si7, si8;

        idx_fast_t twidCoefModifier = TwidCoefModifier;

        n2 = L;

        do {
            n1 = n2;
            n2 = n2 >> 3;
            i1 = 0;

            do {
                i2 = i1 + n2;
                i3 = i2 + n2;
                i4 = i3 + n2;
                i5 = i4 + n2;
                i6 = i5 + n2;
                i7 = i6 + n2;
                i8 = i7 + n2;
                r1 = pSrc[2 * i1] + pSrc[2 * i5];
                r5 = pSrc[2 * i1] - pSrc[2 * i5];
                r2 = pSrc[2 * i2] + pSrc[2 * i6];
                r6 = pSrc[2 * i2] - pSrc[2 * i6];
                r3 = pSrc[2 * i3] + pSrc[2 * i7];
                r7 = pSrc[2 * i3] - pSrc[2 * i7];
                r4 = pSrc[2 * i4] + pSrc[2 * i8];
                r8 = pSrc[2 * i4] - pSrc[2 * i8];
                t1 = r1 - r3;
                r1 = r1 + r3;
                r3 = r2 - r4;
                r2 = r2 + r4;
                pSrc[2 * i1] = r1 + r2;
                pSrc[2 * i5] = r1 - r2;
                r1 = pSrc[2 * i1 + 1] + pSrc[2 * i5 + 1];
                s5 = pSrc[2 * i1 + 1] - pSrc[2 * i5 + 1];
                r2 = pSrc[2 * i2 + 1] + pSrc[2 * i6 + 1];
                s6 = pSrc[2 * i2 + 1] - pSrc[2 * i6 + 1];
                s3 = pSrc[2 * i3 + 1] + pSrc[2 * i7 + 1];
                s7 = pSrc[2 * i3 + 1] - pSrc[2 * i7 + 1];
                r4 = pSrc[2 * i4 + 1] + pSrc[2 * i8 + 1];
                s8 = pSrc[2 * i4 + 1] - pSrc[2 * i8 + 1];
                t2 = r1 - s3;
                r1 = r1 + s3;
                s3 = r2 - r4;
                r2 = r2 + r4;
                pSrc[2 * i1 + 1] = r1 + r2;
                pSrc[2 * i5 + 1] = r1 - r2;
                pSrc[2 * i3] = t1 + s3;
                pSrc[2 * i7] = t1 - s3;
                pSrc[2 * i3 + 1] = t2 - r3;
                pSrc[2 * i7 + 1] = t2 + r3;
                r1 = (r6 - r8) * SQRT1_2;
                r6 = (r6 + r8) * SQRT1_2;
                r2 = (s6 - s8) * SQRT1_2;
                s6 = (s6 + s8) * SQRT1_2;
                t1 = r5 - r1;
                r5 = r5 + r1;
                r8 = r7 - r6;
                r7 = r7 + r6;
                t2 = s5 - r2;
                s5 = s5 + r2;
                s8 = s7 - s6;
                s7 = s7 + s6;
                pSrc[2 * i2] = r5 + s7;
                pSrc[2 * i8] = r5 - s7;
                pSrc[2 * i6] = t1 + s8;
                pSrc[2 * i4] = t1 - s8;
                pSrc[2 * i2 + 1] = s5 - r7;
                pSrc[2 * i8 + 1] = s5 + r7;
                pSrc[2 * i6 + 1] = t2 - r8;
                pSrc[2 * i4 + 1] = t2 + r8;

                i1 += n1;
            } while(i1 < L);

            if(n2 < 8) {
                break;
            }

            ia1 = 0;
            j = 1;

            do {
                /*  index calculation for the coefficients */
                id = ia1 + twidCoefModifier;
                ia1 = id;
                ia2 = ia1 + id;
                ia3 = ia2 + id;
                ia4 = ia3 + id;
                ia5 = ia4 + id;
                ia6 = ia5 + id;
                ia7 = ia6 + id;

                co2 = TwiddleCfft[2 * ia1];
                co3 = TwiddleCfft[2 * ia2];
                co4 = TwiddleCfft[2 * ia3];
                co5 = TwiddleCfft[2 * ia4];
                co6 = TwiddleCfft[2 * ia5];
                co7 = TwiddleCfft[2 * ia6];
                co8 = TwiddleCfft[2 * ia7];
                si2 = TwiddleCfft[2 * ia1 + 1];
                si3 = TwiddleCfft[2 * ia2 + 1];
                si4 = TwiddleCfft[2 * ia3 + 1];
                si5 = TwiddleCfft[2 * ia4 + 1];
                si6 = TwiddleCfft[2 * ia5 + 1];
                si7 = TwiddleCfft[2 * ia6 + 1];
                si8 = TwiddleCfft[2 * ia7 + 1];

                i1 = j;

                do {
                    /*  index calculation for the input */
                    i2 = i1 + n2;
                    i3 = i2 + n2;
                    i4 = i3 + n2;
                    i5 = i4 + n2;
                    i6 = i5 + n2;
                    i7 = i6 + n2;
                    i8 = i7 + n2;
                    r1 = pSrc[2 * i1] + pSrc[2 * i5];
                    r5 = pSrc[2 * i1] - pSrc[2 * i5];
                    r2 = pSrc[2 * i2] + pSrc[2 * i6];
                    r6 = pSrc[2 * i2] - pSrc[2 * i6];
                    r3 = pSrc[2 * i3] + pSrc[2 * i7];
                    r7 = pSrc[2 * i3] - pSrc[2 * i7];
                    r4 = pSrc[2 * i4] + pSrc[2 * i8];
                    r8 = pSrc[2 * i4] - pSrc[2 * i8];
                    t1 = r1 - r3;
                    r1 = r1 + r3;
                    r3 = r2 - r4;
                    r2 = r2 + r4;
                    pSrc[2 * i1] = r1 + r2;
                    r2 = r1 - r2;
                    s1 = pSrc[2 * i1 + 1] + pSrc[2 * i5 + 1];
                    s5 = pSrc[2 * i1 + 1] - pSrc[2 * i5 + 1];
                    s2 = pSrc[2 * i2 + 1] + pSrc[2 * i6 + 1];
                    s6 = pSrc[2 * i2 + 1] - pSrc[2 * i6 + 1];
                    s3 = pSrc[2 * i3 + 1] + pSrc[2 * i7 + 1];
                    s7 = pSrc[2 * i3 + 1] - pSrc[2 * i7 + 1];
                    s4 = pSrc[2 * i4 + 1] + pSrc[2 * i8 + 1];
                    s8 = pSrc[2 * i4 + 1] - pSrc[2 * i8 + 1];
                    t2 = s1 - s3;
                    s1 = s1 + s3;
                    s3 = s2 - s4;
                    s2 = s2 + s4;
                    r1 = t1 + s3;
                    t1 = t1 - s3;
                    pSrc[2 * i1 + 1] = s1 + s2;
                    s2 = s1 - s2;
                    s1 = t2 - r3;
                    t2 = t2 + r3;
                    p1 = co5 * r2;
                    p2 = si5 * s2;
                    p3 = co5 * s2;
                    p4 = si5 * r2;
                    pSrc[2 * i5] = p1 + p2;
                    pSrc[2 * i5 + 1] = p3 - p4;
                    p1 = co3 * r1;
                    p2 = si3 * s1;
                    p3 = co3 * s1;
                    p4 = si3 * r1;
                    pSrc[2 * i3] = p1 + p2;
                    pSrc[2 * i3 + 1] = p3 - p4;
                    p1 = co7 * t1;
                    p2 = si7 * t2;
                    p3 = co7 * t2;
                    p4 = si7 * t1;
                    pSrc[2 * i7] = p1 + p2;
                    pSrc[2 * i7 + 1] = p3 - p4;
                    r1 = (r6 - r8) * SQRT1_2;
                    r6 = (r6 + r8) * SQRT1_2;
                    s1 = (s6 - s8) * SQRT1_2;
                    s6 = (s6 + s8) * SQRT1_2;
                    t1 = r5 - r1;
                    r5 = r5 + r1;
                    r8 = r7 - r6;
                    r7 = r7 + r6;
                    t2 = s5 - s1;
                    s5 = s5 + s1;
                    s8 = s7 - s6;
                    s7 = s7 + s6;
                    r1 = r5 + s7;
                    r5 = r5 - s7;
                    r6 = t1 + s8;
                    t1 = t1 - s8;
                    s1 = s5 - r7;
                    s5 = s5 + r7;
                    s6 = t2 - r8;
                    t2 = t2 + r8;
                    p1 = co2 * r1;
                    p2 = si2 * s1;
                    p3 = co2 * s1;
                    p4 = si2 * r1;
                    pSrc[2 * i2] = p1 + p2;
                    pSrc[2 * i2 + 1] = p3 - p4;
                    p1 = co8 * r5;
                    p2 = si8 * s5;
                    p3 = co8 * s5;
                    p4 = si8 * r5;
                    pSrc[2 * i8] = p1 + p2;
                    pSrc[2 * i8 + 1] = p3 - p4;
                    p1 = co6 * r6;
                    p2 = si6 * s6;
                    p3 = co6 * s6;
                    p4 = si6 * r6;
                    pSrc[2 * i6] = p1 + p2;
                    pSrc[2 * i6 + 1] = p3 - p4;
                    p1 = co4 * t1;
                    p2 = si4 * t2;
                    p3 = co4 * t2;
                    p4 = si4 * t1;
                    pSrc[2 * i4] = p1 + p2;
                    pSrc[2 * i4 + 1] = p3 - p4;

                    i1 += n1;
                } while(i1 < L);

                j++;
            } while(j < n2);

            twidCoefModifier <<= 3;
        } while(n2 > 7);
    }
    MF_CONSTEXPR_14 void radix8by2(DataType *p1) const MF_NOEXCEPT {
        /* Define new length */
        MF_CONST_OR_CONSTEXPR idx_fast_t L = Size >> 1;

        DataType *pCol1, *pCol2, *pMid1, *pMid2;
        DataType *p2 = p1 + Size;
        const DataType *tw = (const DataType *)&TwiddleCfft;
        DataType t1[4], t2[4], t3[4], t4[4], twR, twI;
        DataType m0, m1, m2, m3;

        pCol1 = p1;
        pCol2 = p2;

        /* Initialize mid pointers */
        pMid1 = p1 + L;
        pMid2 = p2 + L;

        /* do two dot Fourier transform */
        for(idx_fast_t l = L >> 2; l > 0; l--) {
            t1[0] = p1[0];
            t1[1] = p1[1];
            t1[2] = p1[2];
            t1[3] = p1[3];

            t2[0] = p2[0];
            t2[1] = p2[1];
            t2[2] = p2[2];
            t2[3] = p2[3];

            t3[0] = pMid1[0];
            t3[1] = pMid1[1];
            t3[2] = pMid1[2];
            t3[3] = pMid1[3];

            t4[0] = pMid2[0];
            t4[1] = pMid2[1];
            t4[2] = pMid2[2];
            t4[3] = pMid2[3];

            *p1++ = t1[0] + t2[0];
            *p1++ = t1[1] + t2[1];
            *p1++ = t1[2] + t2[2];
            *p1++ = t1[3] + t2[3]; /* col 1 */

            t2[0] = t1[0] - t2[0];
            t2[1] = t1[1] - t2[1];
            t2[2] = t1[2] - t2[2];
            t2[3] = t1[3] - t2[3]; /* for col 2 */

            *pMid1++ = t3[0] + t4[0];
            *pMid1++ = t3[1] + t4[1];
            *pMid1++ = t3[2] + t4[2];
            *pMid1++ = t3[3] + t4[3]; /* col 1 */

            t4[0] = t4[0] - t3[0];
            t4[1] = t4[1] - t3[1];
            t4[2] = t4[2] - t3[2];
            t4[3] = t4[3] - t3[3]; /* for col 2 */

            twR = *tw++;
            twI = *tw++;

            /* multiply by twiddle factors */
            m0 = t2[0] * twR;
            m1 = t2[1] * twI;
            m2 = t2[1] * twR;
            m3 = t2[0] * twI;

            /* R  =  R  *  Tr - I * Ti */
            *p2++ = m0 + m1;
            /* I  =  I  *  Tr + R * Ti */
            *p2++ = m2 - m3;

            /* use vertical symmetry */
            /*  0.9988 - 0.0491i <==> -0.0491 - 0.9988i */
            m0 = t4[0] * twI;
            m1 = t4[1] * twR;
            m2 = t4[1] * twI;
            m3 = t4[0] * twR;

            *pMid2++ = m0 - m1;
            *pMid2++ = m2 + m3;

            twR = *tw++;
            twI = *tw++;

            m0 = t2[2] * twR;
            m1 = t2[3] * twI;
            m2 = t2[3] * twR;
            m3 = t2[2] * twI;

            *p2++ = m0 + m1;
            *p2++ = m2 - m3;

            m0 = t4[2] * twI;
            m1 = t4[3] * twR;
            m2 = t4[3] * twI;
            m3 = t4[2] * twR;

            *pMid2++ = m0 - m1;
            *pMid2++ = m2 + m3;
        }

        /* first col */
        radix8<L, 2>(pCol1);

        /* second col */
        radix8<L, 2>(pCol2);
    }
    MF_CONSTEXPR_14 void radix8by4(DataType *p1) const MF_NOEXCEPT {
        DataType *p2 = p1 + CFFT_LEN / 2;
        DataType *p3 = p2 + CFFT_LEN / 2;
        DataType *p4 = p3 + CFFT_LEN / 2;
        DataType t2[4], t3[4], t4[4], twR, twI;
        DataType m0, m1, m2, m3;

        DataType *pCol1 = p1; /* points to real values by default */
        DataType *pCol2 = p2;
        DataType *pCol3 = p3;
        DataType *pCol4 = p4;
        DataType *pEnd1 = p2 - 1; /* points to imaginary values by default */
        DataType *pEnd2 = p3 - 1;
        DataType *pEnd3 = p4 - 1;
        DataType *pEnd4 = pEnd3 + CFFT_LEN / 2;

        const DataType *tw2, *tw3, *tw4;
        tw2 = tw3 = tw4 = (const DataType *)&TwiddleCfft;

        /* do four dot Fourier transform */
        idx_fast_t twMod2 = 2;
        idx_fast_t twMod3 = 4;
        idx_fast_t twMod4 = 6;

        /* TOP */
        DataType p1ap3_0 = p1[0] + p3[0];
        DataType p1sp3_0 = p1[0] - p3[0];
        DataType p1ap3_1 = p1[1] + p3[1];
        DataType p1sp3_1 = p1[1] - p3[1];

        /* col 2 */
        t2[0] = p1sp3_0 + p2[1] - p4[1];
        t2[1] = p1sp3_1 - p2[0] + p4[0];
        /* col 3 */
        t3[0] = p1ap3_0 - p2[0] - p4[0];
        t3[1] = p1ap3_1 - p2[1] - p4[1];
        /* col 4 */
        t4[0] = p1sp3_0 - p2[1] + p4[1];
        t4[1] = p1sp3_1 + p2[0] - p4[0];
        /* col 1 */
        *p1++ = p1ap3_0 + p2[0] + p4[0];
        *p1++ = p1ap3_1 + p2[1] + p4[1];

        /* Twiddle factors are ones */
        *p2++ = t2[0];
        *p2++ = t2[1];
        *p3++ = t3[0];
        *p3++ = t3[1];
        *p4++ = t4[0];
        *p4++ = t4[1];

        tw2 += twMod2;
        tw3 += twMod3;
        tw4 += twMod4;

        for(idx_fast_t l = (CFFT_LEN / 4 - 2) / 2; l != 0; --l) {
            /* TOP */
            p1ap3_0 = p1[0] + p3[0];
            p1sp3_0 = p1[0] - p3[0];
            p1ap3_1 = p1[1] + p3[1];
            p1sp3_1 = p1[1] - p3[1];
            /* col 2 */
            t2[0] = p1sp3_0 + p2[1] - p4[1];
            t2[1] = p1sp3_1 - p2[0] + p4[0];
            /* col 3 */
            t3[0] = p1ap3_0 - p2[0] - p4[0];
            t3[1] = p1ap3_1 - p2[1] - p4[1];
            /* col 4 */
            t4[0] = p1sp3_0 - p2[1] + p4[1];
            t4[1] = p1sp3_1 + p2[0] - p4[0];
            /* col 1 - top */
            *p1++ = p1ap3_0 + p2[0] + p4[0];
            *p1++ = p1ap3_1 + p2[1] + p4[1];

            /* BOTTOM */
            p1ap3_1 = pEnd1[-1] + pEnd3[-1];
            p1sp3_1 = pEnd1[-1] - pEnd3[-1];
            p1ap3_0 = pEnd1[0] + pEnd3[0];
            p1sp3_0 = pEnd1[0] - pEnd3[0];
            /* col 2 */
            t2[2] = pEnd2[0] - pEnd4[0] + p1sp3_1;
            t2[3] = pEnd1[0] - pEnd3[0] - pEnd2[-1] + pEnd4[-1];
            /* col 3 */
            t3[2] = p1ap3_1 - pEnd2[-1] - pEnd4[-1];
            t3[3] = p1ap3_0 - pEnd2[0] - pEnd4[0];
            /* col 4 */
            t4[2] = pEnd2[0] - pEnd4[0] - p1sp3_1;
            t4[3] = pEnd4[-1] - pEnd2[-1] - p1sp3_0;
            /* col 1 - Bottom */
            *pEnd1-- = p1ap3_0 + pEnd2[0] + pEnd4[0];
            *pEnd1-- = p1ap3_1 + pEnd2[-1] + pEnd4[-1];

            /* COL 2 */
            /* read twiddle factors */
            twR = *tw2++;
            twI = *tw2++;
            /* multiply by twiddle factors */
            /*  let    Z1 = a + i(b),   Z2 = c + i(d) */
            /*   =>  Z1 * Z2  =  (a*c - b*d) + i(b*c + a*d) */

            /* Top */
            m0 = t2[0] * twR;
            m1 = t2[1] * twI;
            m2 = t2[1] * twR;
            m3 = t2[0] * twI;

            *p2++ = m0 + m1;
            *p2++ = m2 - m3;
            /* use vertical symmetry col 2 */
            /* 0.9997 - 0.0245i  <==>  0.0245 - 0.9997i */
            /* Bottom */
            m0 = t2[3] * twI;
            m1 = t2[2] * twR;
            m2 = t2[2] * twI;
            m3 = t2[3] * twR;

            *pEnd2-- = m0 - m1;
            *pEnd2-- = m2 + m3;

            /* COL 3 */
            twR = tw3[0];
            twI = tw3[1];
            tw3 += twMod3;
            /* Top */
            m0 = t3[0] * twR;
            m1 = t3[1] * twI;
            m2 = t3[1] * twR;
            m3 = t3[0] * twI;

            *p3++ = m0 + m1;
            *p3++ = m2 - m3;
            /* use vertical symmetry col 3 */
            /* 0.9988 - 0.0491i  <==>  -0.9988 - 0.0491i */
            /* Bottom */
            m0 = -t3[3] * twR;
            m1 = t3[2] * twI;
            m2 = t3[2] * twR;
            m3 = t3[3] * twI;

            *pEnd3-- = m0 - m1;
            *pEnd3-- = m3 - m2;

            /* COL 4 */
            twR = tw4[0];
            twI = tw4[1];
            tw4 += twMod4;
            /* Top */
            m0 = t4[0] * twR;
            m1 = t4[1] * twI;
            m2 = t4[1] * twR;
            m3 = t4[0] * twI;

            *p4++ = m0 + m1;
            *p4++ = m2 - m3;
            /* use vertical symmetry col 4 */
            /* 0.9973 - 0.0736i  <==>  -0.0736 + 0.9973i */
            /* Bottom */
            m0 = t4[3] * twI;
            m1 = t4[2] * twR;
            m2 = t4[2] * twI;
            m3 = t4[3] * twR;

            *pEnd4-- = m0 - m1;
            *pEnd4-- = m2 + m3;
        }

        /* MIDDLE */
        /* Twiddle factors are */
        /*  1.0000  0.7071-0.7071i  -1.0000i  -0.7071-0.7071i */
        p1ap3_0 = p1[0] + p3[0];
        p1sp3_0 = p1[0] - p3[0];
        p1ap3_1 = p1[1] + p3[1];
        p1sp3_1 = p1[1] - p3[1];

        /* col 2 */
        t2[0] = p1sp3_0 + p2[1] - p4[1];
        t2[1] = p1sp3_1 - p2[0] + p4[0];
        /* col 3 */
        t3[0] = p1ap3_0 - p2[0] - p4[0];
        t3[1] = p1ap3_1 - p2[1] - p4[1];
        /* col 4 */
        t4[0] = p1sp3_0 - p2[1] + p4[1];
        t4[1] = p1sp3_1 + p2[0] - p4[0];
        /* col 1 - Top */
        *p1++ = p1ap3_0 + p2[0] + p4[0];
        *p1++ = p1ap3_1 + p2[1] + p4[1];

        /* COL 2 */
        twR = tw2[0];
        twI = tw2[1];

        m0 = t2[0] * twR;
        m1 = t2[1] * twI;
        m2 = t2[1] * twR;
        m3 = t2[0] * twI;

        *p2++ = m0 + m1;
        *p2++ = m2 - m3;
        /* COL 3 */
        twR = tw3[0];
        twI = tw3[1];

        m0 = t3[0] * twR;
        m1 = t3[1] * twI;
        m2 = t3[1] * twR;
        m3 = t3[0] * twI;

        *p3++ = m0 + m1;
        *p3++ = m2 - m3;
        /* COL 4 */
        twR = tw4[0];
        twI = tw4[1];

        m0 = t4[0] * twR;
        m1 = t4[1] * twI;
        m2 = t4[1] * twR;
        m3 = t4[0] * twI;

        *p4++ = m0 + m1;
        *p4++ = m2 - m3;

        /* first col */
        radix8<CFFT_LEN / 4, 4>(pCol1);

        /* second col */
        radix8<CFFT_LEN / 4, 4>(pCol2);

        /* third col */
        radix8<CFFT_LEN / 4, 4>(pCol3);

        /* fourth col */
        radix8<CFFT_LEN / 4, 4>(pCol4);
    }
    MF_CONSTEXPR void bitreversal(DataType *pSrc) const MF_NOEXCEPT {
        for(idx_fast_t i = 0; i < bitRevLength; i += 2) {
            const idx_fast_t a = pBitRevTable[i] >> 2;
            const idx_fast_t b = pBitRevTable[i + 1] >> 2;
            // real
            std::swap(pSrc[a], pSrc[b]);
            // complex
            std::swap(pSrc[a + 1], pSrc[b + 1]);
        }
    }
    template<bool Inverse, bool BitReverse> MF_CONSTEXPR_14 void cfft(DataType *p1) const MF_NOEXCEPT {
        MF_IF_CONSTEXPR(Inverse) { /* Conjugate input data */
            DataType *pSrc = p1 + 1;
            for(idx_fast_t l = 0; l != Size; ++l) {
                *pSrc = -*pSrc;
                pSrc += 2;
            }
        }

        switch(Size) {
            case 16:
            case 128:
            case 1024:
                radix8by2(p1);
                break;
            case 32:
            case 256:
            case 2048:
                radix8by4(p1);
                break;
            case 64:
            case 512:
            case 4096:
                radix8<Size, 1>(p1);
                break;
            default:
                break;
        }

        MF_IF_CONSTEXPR(BitReverse) { /* BITREVERSE */
            bitreversal(p1);
        }

        MF_IF_CONSTEXPR(Inverse) { /* Conjugate and scale output data */
            MF_CONST_OR_CONSTEXPR DataType factor = DataType(1) / DataType(Size);
            DataType *pSrc = p1;
            for(idx_fast_t l = 0; l != Size; ++l) {
                *pSrc++ *= factor;
                *pSrc = -(*pSrc) * factor;
                pSrc++;
            }
        }
    }

    /** points to the Twiddle factor table. */
    DataType TwiddleCfft[CFFT_LEN * 2];
    /** points to the bit reversal table. */
    const IdxType *pBitRevTable;
    /** bit reversal table length. */
    IdxType bitRevLength;
};

template<typename DataType, typename IdxType, IdxType Size> class Rfft: public Cfft<DataType, IdxType, Size / 2> {
    MF_STATIC_ASSERT(is_valid_fft_type<DataType>::value);
    MF_STATIC_ASSERT(is_valid_idx_type<IdxType>::value);

    typedef Cfft<DataType, IdxType, Size / 2> ParentCfft;

public:
    static MF_CONST_OR_CONSTEXPR IdxType RFFT_LEN = Size;

    MF_CONSTEXPR_14 Rfft() MF_NOEXCEPT {
        /* 1. создание таблицы поворотных коэффициентов */
        fill_rfft_twiddle_coeff<DataType, IdxType, RFFT_LEN>(TwiddleRfft);
    }

    MF_CONSTEXPR_14 void forward(DataType *pIn, DataType *pOut) const MF_NOEXCEPT {
        /* Calculation of RFFT of input */
        ParentCfft::template cfft<false, true>(pIn);
        /* Real FFT extraction */
        stage(pIn, pOut);
    }

    MF_CONSTEXPR_14 void inverse(DataType *pIn, DataType *pOut) const MF_NOEXCEPT {
        /*  Real FFT compression */
        merge(pIn, pOut);
        /* Complex radix-4 IFFT process */
        ParentCfft::template cfft<true, true>(pOut);
    }

    MF_CONSTEXPR_14 void cfft_forward(DataType *p) const MF_NOEXCEPT {
        ParentCfft::template cfft<false, true>(p);
    }

    MF_CONSTEXPR_14 void cfft_inverse(DataType *p) const MF_NOEXCEPT {
        ParentCfft::template cfft<true, true>(p);
    }

private:
    typedef typename uint_fast<IdxType>::type idx_fast_t;

    MF_CONSTEXPR_14 void stage(const DataType *pIn, DataType *pOut) const MF_NOEXCEPT {
        DataType twR, twI; /* RFFT Twiddle coefficients */
        const DataType *pCoeff = TwiddleRfft; /* Points to RFFT Twiddle factors */
        const DataType *pA = pIn; /* increasing pointer */
        const DataType *pB = pIn; /* decreasing pointer */
        DataType xAR, xAI, xBR, xBI; /* temporary variables */
        DataType t1a, t1b; /* temporary variables */
        DataType p0, p1, p2, p3; /* temporary variables */

        idx_fast_t k = ParentCfft::CFFT_LEN - 1; /* Loop Counter */

        /* Pack first and last sample of the frequency domain together */
        xBR = pB[0];
        xBI = pB[1];
        xAR = pA[0];
        xAI = pA[1];

        twR = *pCoeff++;
        twI = *pCoeff++;

        // U1 = XA(1) + XB(1); % It is real
        t1a = xBR + xAR;

        // U2 = XB(1) - XA(1); % It is imaginary
        t1b = xBI + xAI;

        // real(tw * (xB - xA)) = twR * (xBR - xAR) - twI * (xBI - xAI);
        // imag(tw * (xB - xA)) = twI * (xBR - xAR) + twR * (xBI - xAI);
        *pOut++ = DataType(0.5l) * (t1a + t1b);
        *pOut++ = DataType(0.5l) * (t1a - t1b);

        // XA(1) = 1/2*( U1 - imag(U2) +  i*( U1 +imag(U2) ));
        pB = pIn + 2 * k;
        pA += 2;

        do {
            /*
               function X = my_split_rfft(X, ifftFlag)
               % X is a series of real numbers
               L  = length(X);
               XC = X(1:2:end) +i*X(2:2:end);
               XA = fft(XC);
               XB = conj(XA([1 end:-1:2]));
               TW = i*exp(-2*pi*i*[0:L/2-1]/L).';
               for l = 2:L/2
                  XA(l) = 1/2 * (XA(l) + XB(l) + TW(l) * (XB(l) - XA(l)));
               end
               XA(1) = 1/2* (XA(1) + XB(1) + TW(1) * (XB(1) - XA(1))) + i*( 1/2*( XA(1) + XB(1) + i*( XA(1) - XB(1))));
               X = XA;
            */

            xBI = pB[1];
            xBR = pB[0];
            xAR = pA[0];
            xAI = pA[1];

            twR = *pCoeff++;
            twI = *pCoeff++;

            t1a = xBR - xAR;
            t1b = xBI + xAI;

            // real(tw * (xB - xA)) = twR * (xBR - xAR) - twI * (xBI - xAI);
            // imag(tw * (xB - xA)) = twI * (xBR - xAR) + twR * (xBI - xAI);
            p0 = twR * t1a;
            p1 = twI * t1a;
            p2 = twR * t1b;
            p3 = twI * t1b;

            *pOut++ = DataType(0.5l) * (xAR + xBR + p0 + p3); // xAR
            *pOut++ = DataType(0.5l) * (xAI - xBI + p1 - p2); // xAI

            pA += 2;
            pB -= 2;
            k--;
        } while(k);
    }

    MF_CONSTEXPR void merge(const DataType *pIn, DataType *pOut) const MF_NOEXCEPT {
        DataType twR, twI; /* RFFT Twiddle coefficients */
        const DataType *pCoeff = TwiddleRfft; /* Points to RFFT Twiddle factors */
        const DataType *pA = pIn; /* increasing pointer */
        const DataType *pB = pIn; /* decreasing pointer */
        DataType xAR, xAI, xBR, xBI; /* temporary variables */
        DataType t1a, t1b, r, s, t, u; /* temporary variables */

        idx_fast_t k = ParentCfft::CFFT_LEN - 1; /* Loop Counter */

        xAR = pA[0];
        xAI = pA[1];

        pCoeff += 2;

        *pOut++ = 0.5f * (xAR + xAI);
        *pOut++ = 0.5f * (xAR - xAI);

        pB = pIn + 2 * k;
        pA += 2;

        while(k > 0) {
            /* G is half of the frequency complex spectrum */
            // for k = 2:N
            //     Xk(k) = 1/2 * (G(k) + conj(G(N-k+2)) + Tw(k)*( G(k) - conj(G(N-k+2))));
            xBI = pB[1];
            xBR = pB[0];
            xAR = pA[0];
            xAI = pA[1];

            twR = *pCoeff++;
            twI = *pCoeff++;

            t1a = xAR - xBR;
            t1b = xAI + xBI;

            r = twR * t1a;
            s = twI * t1b;
            t = twI * t1a;
            u = twR * t1b;

            // real(tw * (xA - xB)) = twR * (xAR - xBR) - twI * (xAI - xBI);
            // imag(tw * (xA - xB)) = twI * (xAR - xBR) + twR * (xAI - xBI);
            *pOut++ = 0.5f * (xAR + xBR - r - s); // xAR
            *pOut++ = 0.5f * (xAI - xBI + t - u); // xAI

            pA += 2;
            pB -= 2;
            k--;
        }
    }

private:
    /** Twiddle factors real stage  */
    DataType TwiddleRfft[RFFT_LEN];
};

} // namespace mf

#endif // HPP_MF_FFT
