#ifndef HPP_MF_WINDOWS
#define HPP_MF_WINDOWS

#include <cstdlib>

#include "mf/basic_math.hpp"
#include "mf/config.hpp"
#include "mf/special_math.hpp"
#include "mf/traits/math.hpp"
#include "mf/types.hpp"

#define MF_INCR_REV(ri, i, size) ((ri) = (ri) ^ ((size) - (((size) / 2) / (~(i) & ((i) + 1)))))

namespace mf { namespace windows {
typedef float_max_t float_t;

static MF_CONST_OR_CONSTEXPR float_t ONE = MF_FLOAT_MAX_C(1.0);
static MF_CONST_OR_CONSTEXPR float_t TWO = MF_FLOAT_MAX_C(2.0);
static MF_CONST_OR_CONSTEXPR float_t HALF = ONE / TWO;
static MF_CONST_OR_CONSTEXPR float_t PI = pi<float_t>::value;
static MF_CONST_OR_CONSTEXPR float_t TWO_PI = two_pi<float_t>::value;
static MF_CONST_OR_CONSTEXPR float_t INV_PI = inv_pi<float_t>::value;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                  B-spline windows                                                  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename DataType, size_t N> void rect(DataType (&win)[N]) MF_NOEXCEPT {
    for(size_t n = 0; n != N; ++n) {
        win[n] = ONE;
    }
}
template<typename DataType, size_t N> void bartlett(DataType (&win)[N]) MF_NOEXCEPT {
    static MF_CONST_OR_CONSTEXPR DataType subtractor = (float_t(N) - ONE) / TWO;
    static MF_CONST_OR_CONSTEXPR DataType divider = (float_t(N) - ONE) / TWO;
    for(size_t n = 0; n != N; ++n) {
        win[n] = ONE - abs((float_t(n) - subtractor) / divider);
    }
}
template<typename DataType, size_t N> void triang(DataType (&win)[N]) MF_NOEXCEPT {
    static MF_CONST_OR_CONSTEXPR DataType subtractor = (float_t(N) - ONE) / TWO;
    static MF_CONST_OR_CONSTEXPR DataType divider = N % 2 ? (float_t(N) + ONE) / TWO : float_t(N) / TWO;
    for(size_t n = 0; n != N; ++n) {
        win[n] = ONE - abs((float_t(n) - subtractor) / divider);
    }
}
template<typename DataType, size_t N> void parzen(DataType (&win)[N]) MF_NOEXCEPT {
    for(size_t n = 0; n != N; ++n) {
        DataType x = abs(TWO * float_t(n) - (float_t(N) - ONE)) / float_t(N);
        DataType y = ONE - x;

        x = ONE - float_t(6) * x * x + float_t(6) * x * x * x;
        y = TWO * y * y * y;

        win[n] = min(x, y);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                 Cosine-sum windows                                                 //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename DataType, size_t N> void cosine(DataType (&win)[N]) MF_NOEXCEPT {
    for(size_t n = 0; n != N; ++n) {
        win[n] = sin((PI * (float_t(n) + HALF)) / float_t(N));
    }
}
template<typename DataType, size_t N> void bohman(DataType (&win)[N]) MF_NOEXCEPT {
    for(size_t n = 0; n != N; ++n) {
        const float_t factor = abs(TWO * float_t(n) / (float_t(N) - ONE) - ONE);
        win[n] = (ONE - factor) * cos(PI * factor) + INV_PI * sin(PI * factor);
    }
}
template<typename DataType, size_t N, size_t K> void cosine_sum(DataType (&win)[N], const float_t (&a)[K]) MF_NOEXCEPT {
    for(size_t n = 0; n != N; ++n) {
        win[n] = a[0];
        int sgn = 1;
        for(size_t k = 1; k != K; ++k) {
            sgn *= -1;
            win[n] += float_t(sgn) * a[k] * cos((TWO_PI * float_t(k) * float_t(n)) / (float_t(N) - ONE));
        }
    }
}
template<typename DataType, size_t N> void general_hamming(DataType (&win)[N], float_t alpha) {
    static float_t a[2];
    a[0] = alpha;
    a[1] = ONE - alpha;
    cosine_sum(win, a);
}
template<typename DataType, size_t N> void hamming(DataType (&win)[N]) MF_NOEXCEPT {
    general_hamming(win, MF_FLOAT_MAX_C(0.54));
}
template<typename DataType, size_t N> void hann(DataType (&win)[N]) MF_NOEXCEPT {
    static const float_t a[] = {HALF, HALF};
    cosine_sum(win, a);
}
template<typename DataType, size_t N> void blackman_generic(DataType (&win)[N], float_t alpha) MF_NOEXCEPT {
    static float_t a[3];
    a[0] = (ONE - alpha) / TWO;
    a[1] = HALF;
    a[2] = alpha / TWO;
    cosine_sum(win, a);
}
template<typename DataType, size_t N> void blackman(DataType (&win)[N]) MF_NOEXCEPT {
    blackman_generic(win, MF_FLOAT_MAX_C(0.16));
}
template<typename DataType, size_t N> void nuttall(DataType (&win)[N]) MF_NOEXCEPT {
    static const float_t a[] = {
        MF_FLOAT_MAX_C(0.3635819),
        MF_FLOAT_MAX_C(0.4891775),
        MF_FLOAT_MAX_C(0.1365995),
        MF_FLOAT_MAX_C(0.0106411),
    };
    cosine_sum(win, a);
}
template<typename DataType, size_t N> void blackmanharris(DataType (&win)[N]) MF_NOEXCEPT {
    static const float_t a[] = {
        MF_FLOAT_MAX_C(0.35875),
        MF_FLOAT_MAX_C(0.48829),
        MF_FLOAT_MAX_C(0.14128),
        MF_FLOAT_MAX_C(0.01168),
    };
    cosine_sum(win, a);
}
template<typename DataType, size_t N> void flattop(DataType (&win)[N]) MF_NOEXCEPT {
    static const float_t a[] = {
        MF_FLOAT_MAX_C(0.21557895),
        MF_FLOAT_MAX_C(0.41663158),
        MF_FLOAT_MAX_C(0.277263158),
        MF_FLOAT_MAX_C(0.083578947),
        MF_FLOAT_MAX_C(0.006947368),
    };
    cosine_sum(win, a);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                 Adjustable windows                                                 //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename DataType, size_t N> void gaussian(DataType (&win)[N], float_t sigma) MF_NOEXCEPT {
    static MF_CONST_OR_CONSTEXPR float_t subtractor = (float_t(N) - ONE) / TWO;
    for(size_t n = 0; n != N; ++n) {
        const float_t x = float_t(n) - subtractor;
        win[n] = exp(-HALF * x * x / (sigma * sigma));
    }
}
template<typename DataType, size_t N> void tukey(DataType (&win)[N], float_t alpha) MF_NOEXCEPT {

    if(alpha <= 0.0) {
        rect(win);
        return;
    } else if(alpha >= ONE) {
        hann(win);
        return;
    }

    size_t n;
    for(n = 0; n != (size_t)(alpha * (float_t(N) - ONE) / TWO + ONE); ++n) {
        win[n] = (ONE - cos(TWO_PI * n / (alpha * (float_t(N) - ONE)))) / TWO;
    }
    for(; n != (size_t)((float_t(N) - ONE) / TWO + ONE); ++n) {
        win[n] = ONE;
    }
    for(; n != N; ++n) {
        win[n] = win[N - n - 1];
    }
}
template<typename DataType, size_t N> void kaiser(DataType (&win)[N], float_t beta) MF_NOEXCEPT {
    for(size_t n = 0; n != N; ++n) {
        const float_t factor = TWO * float_t(n) / (float_t(N) - ONE) - ONE;
        win[n] = bessel::i0(beta * sqrt(ONE - factor * factor)) / bessel::i0(beta);
    }
}
template<typename DataType, size_t N> void kaiser_bessel_derived(DataType (&win)[N], float_t beta) MF_NOEXCEPT {
    kaiser(reinterpret_cast<DataType(&)[N / 2 + 1]>(win), beta);

    for(size_t n = 1; n != N / 2 + 1; ++n) {
        win[n] = win[n - 1] + win[n];
    }
    for(size_t n = 0; n != N / 2 + 1; ++n) {
        win[n] = sqrt(win[n] / win[N / 2]);
    }
    for(size_t n = 0; n != N / 2 + 1; ++n) {
        win[N - 1 - n] = win[n];
    }
}

namespace detail {
size_t clp2(size_t x) MF_NOEXCEPT {
    x -= 1;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    x |= x >> 32;
    return x + 1;
}
void fft_radix2(Complex<float_t> *z, size_t size) MF_NOEXCEPT {
    size_t i, j, ri;
    size_t num_subffts, size_subfft;
    Complex<float_t> *ww;

    /* we start with (size / 2) FFTs of 2 base elements. */
    num_subffts = size / 2;
    size_subfft = 2;

    ww = (Complex<float_t> *)malloc(size / 2 * sizeof(*ww));
    if(!ww) {
        return;
    }

    for(i = 0; i < size / 2; ++i) {
        ww[i] = Complex<float_t>::polar(1, -TWO_PI * i / size);
    }
    /* Permute the input elements (bit-reversal of indices). */
    for(i = 0, ri = 0; i < size; MF_INCR_REV(ri, i, size), ++i) {
        if(i < ri) {
            std::swap(z[i], z[ri]);
        }
    }
    /* Perform FFTs */
    while(num_subffts != 0) {
        for(i = 0; i < num_subffts; ++i) {
            size_t subfft_offset = size_subfft * i;

            for(j = 0; j < size_subfft / 2; ++j) {
                size_t target1 = subfft_offset + j;
                size_t target2 = subfft_offset + j + size_subfft / 2;

                size_t left = target1;
                size_t right = target2;

                const size_t ww_index = (j * num_subffts);

                const Complex<float_t> w = ww[ww_index];

                const Complex<float_t> zleft = z[left];
                const Complex<float_t> w_zright = w * z[right];

                z[target1] = zleft + w_zright;
                z[target2] = zleft - w_zright;
            }
        }

        num_subffts /= 2;
        size_subfft *= 2;
    }
}
void czt(Complex<float_t> *z, size_t n, Complex<float_t> *ztrans, size_t m, Complex<float_t> w, Complex<float_t> a)
    MF_NOEXCEPT {
    size_t k, fft_size;
    Complex<float_t> *zz, *w2;

    fft_size = clp2(n + m - 1);
    zz = (Complex<float_t> *)malloc(fft_size * sizeof(*zz));
    if(!zz) {
        return;
    }
    w2 = (Complex<float_t> *)malloc(fft_size * sizeof(*w2));
    if(!w2) {
        free(zz);
        return;
    }

    /* Initialize zz */
    for(k = 0; k < fft_size; ++k) {
        if(k < n) {
            zz[k] = w.pow(0.5 * k * k) / a.pow(k) * z[k];
        } else {
            zz[k] = 0;
        }
    }
    fft_radix2(zz, fft_size);

    for(k = 0; k < fft_size; ++k) {
        if(k < n + m - 1) {
            const int kshift = k - (n - 1);

            w2[k] = w.pow(-0.5 * kshift * kshift);
        } else {
            w2[k] = 0;
        }
    }
    fft_radix2(w2, fft_size);

    for(k = 0; k < fft_size; ++k) {
        zz[k] *= w2[k];
    }
    fft_radix2(zz, fft_size);

    /* Make an inverse FFT from the forward FFT.
        - scale all elements by 1 / fft_size;
        - reverse elements 1 .. (fft_size - 1).
    */
    for(k = 0; k < fft_size; ++k) {
        zz[k] /= fft_size;
    }
    for(k = 1; k < fft_size - k; ++k) {
        const size_t kswap = fft_size - k;

        const Complex<float_t> temp = zz[k];
        zz[k] = zz[kswap];
        zz[kswap] = temp;
    }

    for(k = 0; k < m; ++k) {
        const Complex<float_t> w3 = w.pow(0.5 * k * k);
        ztrans[k] = w3 * zz[n - 1 + k];
    }
}
} // namespace detail
template<typename DataType, size_t N> void chebyshev(DataType (&win)[N], float_t alpha) MF_NOEXCEPT {
    MF_CONST_OR_CONSTEXPR size_t order = N - 1;
    const float_t amp = pow(float_t(10), abs(alpha) / float_t(20));
    const float_t beta = cosh(acosh(amp) / order);

    Complex<float_t> W[N];
    MF_IF_CONSTEXPR(N % 2) {
        for(size_t n = 0; n < N; ++n) {
            const float_t x = beta * cos(PI * float_t(n) / float_t(N));
            if(x > ONE) {
                W[n] = cosh(order * acosh(x));
            } else if(x < -ONE) {
                W[n] = cosh(order * acosh(-x));
            } else {
                W[n] = cos(order * acos(x));
            }
        }

        detail::czt(W, N, W, N, Complex<float_t>::polar(ONE, -TWO_PI / float_t(N)), ONE);

        /*
        Example: n = 11
            w[0] w[1] w[2] w[3] w[4] w[5] w[6] w[7] w[8] w[9] w[10]
                                    =
            p[5] p[4] p[3] p[2] p[1] p[0] p[1] p[2] p[3] p[4] p[5]
        */
        const size_t h = (N - 1) / 2;
        for(size_t n = 0; n < N; ++n) {
            const size_t k = (n <= h) ? (h - n) : (n - h);
            win[n] = W[k].real();
        }
    } else {
        for(size_t n = 0; n < N; ++n) {
            const float_t x = beta * cos(PI * float_t(n) / float_t(N));
            const Complex<float_t> z = Complex<float_t>::polar(ONE, PI * float_t(n) / float_t(N));
            if(x > ONE) {
                W[n] = z * cosh(order * acosh(x));
            } else if(x < -ONE) {
                W[n] = -z * cosh(order * acosh(-x));
            } else {
                W[n] = z * cos(order * acos(x));
            }
        }

        MF_IF_CONSTEXPR(trait::is_pow_of_2<N>::value) {
            detail::fft_radix2(W, N);
        } else {
            detail::czt(W, N, W, N, Complex<float_t>::polar(ONE, -TWO_PI / float_t(N)), ONE);
        }

        /*
        Example: n = 10
            w[0] w[1] w[2] w[3] w[4] w[5] w[6] w[7] w[8] w[9]
                                    =
            p[5] p[4] p[3] p[2] p[1] p[1] p[2] p[3] p[4] p[5]
        */
        const size_t h = N / 2;
        for(size_t n = 0; n < N; ++n) {
            const size_t k = (n < h) ? (h - n) : (n - h + 1);
            win[n] = W[k].real();
        }
    }

    DataType maxw = win[0];
    for(size_t n = 1; n < N; ++n) {
        maxw = max(maxw, win[n]);
    }
    for(size_t n = 0; n < N; ++n) {
        win[n] /= maxw;
    }
}
template<typename DataType, size_t N> void poisson(DataType (&win)[N], float_t tau) MF_NOEXCEPT {
    static MF_CONST_OR_CONSTEXPR float_t subtractor = (float_t(N) - ONE) / TWO;
    for(size_t n = 0; n != N; ++n) {
        win[n] = exp(-abs(float_t(n) - subtractor) / tau);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                   Hybrid windows                                                   //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename DataType, size_t N> void barthann(DataType (&win)[N]) MF_NOEXCEPT {
    for(size_t n = 0; n != N; ++n) {
        float_t factor = abs(float_t(n) / (float_t(N) - ONE) - HALF);
        win[n] = MF_FLOAT_MAX_C(0.62) - MF_FLOAT_MAX_C(0.48) * factor + MF_FLOAT_MAX_C(0.38) * cos(TWO_PI * factor);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                    Other windows                                                   //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename DataType, size_t N> void lanczos(DataType (&win)[N]) MF_NOEXCEPT {
    for(size_t n = 0; n != N; ++n) {
        win[n] = sinc(TWO * float_t(n) / (float_t(N) - ONE) - ONE);
    }
}
}} // namespace mf::windows

#endif // HPP_MF_WINDOWS
