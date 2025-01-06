#ifndef HPP_MF_WINDOWS
#define HPP_MF_WINDOWS

#include "mf/basic_math.hpp"
#include "mf/config.hpp"
#include "mf/special_math.hpp"
#include "mf/traits.hpp"
#include "mf/types.hpp"

#define WF_INCR_REV(ri, i, size) ((ri) = (ri) ^ ((size) - (((size) / 2) / (~(i) & ((i) + 1)))))

namespace mf {
namespace wf { namespace detail {
static MF_CONST_OR_CONSTEXPR float_max_t PI = pi<float_max_t>::value;
static MF_CONST_OR_CONSTEXPR float_max_t TWO_PI = two_pi<float_max_t>::value;
static MF_CONST_OR_CONSTEXPR float_max_t INV_PI = inv_pi<float_max_t>::value;

template<typename DataType, size_t Size> void fft_radix2(Complex<DataType> (&z)[Size]) {
    Complex<DataType> ww[Size / 2];
    for(size_t i = 0; i < Size / 2; ++i) {
        ww[i] = Complex<DataType>::polar(1, -TWO_PI * i / Size);
    }

    /* Permute the input elements (bit-reversal of indices). */
    for(size_t i = 0, ri = 0; i < Size; WF_INCR_REV(ri, i, Size), ++i) {
        if(i < ri) {
            std::swap(z[i], z[ri]);
        }
    }

    /* Perform FFTs */
    /* we start with (size / 2) FFTs of 2 base elements. */
    size_t num_subffts = Size / 2;
    size_t size_subfft = 2;
    while(num_subffts != 0) {
        for(size_t i = 0; i < num_subffts; ++i) {
            size_t subfft_offset = size_subfft * i;

            for(size_t j = 0; j < size_subfft / 2; ++j) {
                size_t target1 = subfft_offset + j;
                size_t target2 = subfft_offset + j + size_subfft / 2;

                size_t left = target1;
                size_t right = target2;

                const size_t ww_index = (j * num_subffts);

                const Complex<DataType> w = ww[ww_index];

                const Complex<DataType> zleft = z[left];
                const Complex<DataType> w_zright = w * z[right];

                z[target1] = zleft + w_zright;
                z[target2] = zleft - w_zright;
            }
        }

        num_subffts /= 2;
        size_subfft *= 2;
    }
}

template<typename DataType, size_t N, size_t M>
void czt(Complex<DataType> (&z)[N], Complex<DataType> (&ztrans)[M], Complex<DataType> w, Complex<DataType> a) {
    MF_CONST_OR_CONSTEXPR size_t FFT_SIZE = trait::clp2<N + M - 1>::value;

    Complex<DataType> zz[FFT_SIZE];
    for(size_t k = 0; k < FFT_SIZE; ++k) {
        if(k < N) {
            zz[k] = Complex<float_t>::pow(w, 0.5 * k * k) / Complex<float_t>::pow(a, k) * z[k];
        } else {
            zz[k] = 0;
        }
    }
    fft_radix2(zz);

    Complex<DataType> w2[FFT_SIZE];
    for(size_t k = 0; k < FFT_SIZE; ++k) {
        if(k < N + M - 1) {
            const size_t kshift = k - (N - 1);
            w2[k] = Complex<float_t>::pow(w, -0.5 * kshift * kshift);
        } else {
            w2[k] = 0;
        }
    }
    fft_radix2(w2);

    for(size_t k = 0; k < FFT_SIZE; ++k) {
        zz[k] *= w2[k];
    }
    fft_radix2(zz);

    /* Make an inverse FFT from the forward FFT.
        - scale all elements by 1 / fft_size;
        - reverse elements 1 .. (fft_size - 1).
    */
    for(size_t k = 0; k < FFT_SIZE; ++k) {
        zz[k] /= FFT_SIZE;
    }
    for(size_t k = 1; k < FFT_SIZE - k; ++k) {
        const size_t kswap = FFT_SIZE - k;
        std::swap(zz[k], zz[kswap]);
    }

    for(size_t k = 0; k < M; ++k) {
        const Complex<DataType> w3 = Complex<float_t>::pow(w, (0.5 * k * k));
        ztrans[k] = w3 * zz[N - 1 + k];
    }
}
}} // namespace wf::detail
template<typename DataType, size_t N> class Windows {
    typedef float_max_t float_t;
    Windows() MF_DELETED;

public:
    ////////////////////////////////////////////////////////////////////////////
    //                            B-spline windows                            //
    ////////////////////////////////////////////////////////////////////////////
    static void rect(DataType (&win)[N]) MF_NOEXCEPT {
        for(size_t n = 0; n != N; ++n) {
            win[n] = float_t(1);
        }
    }
    static void bartlett(DataType (&win)[N]) MF_NOEXCEPT {
        static MF_CONST_OR_CONSTEXPR DataType subtractor = (float_t(N) - float_t(1)) / float_t(2);
        static MF_CONST_OR_CONSTEXPR DataType divider = (float_t(N) - float_t(1)) / float_t(2);
        for(size_t n = 0; n != N; ++n) {
            win[n] = float_t(1) - abs((float_t(n) - subtractor) / divider);
        }
    }
    static void triang(DataType (&win)[N]) MF_NOEXCEPT {
        static MF_CONST_OR_CONSTEXPR DataType subtractor = (float_t(N) - float_t(1)) / float_t(2);
        static MF_CONST_OR_CONSTEXPR DataType divider =
            N % 2 ? (float_t(N) + float_t(1)) / float_t(2) : float_t(N) / float_t(2);
        for(size_t n = 0; n != N; ++n) {
            win[n] = float_t(1) - abs((float_t(n) - subtractor) / divider);
        }
    }
    static void parzen(DataType (&win)[N]) MF_NOEXCEPT {
        for(size_t n = 0; n != N; ++n) {
            DataType x = abs(float_t(2) * float_t(n) - (float_t(N) - float_t(1))) / float_t(N);
            DataType y = float_t(1) - x;

            x = float_t(1) - float_t(6) * x * x + float_t(6) * x * x * x;
            y = float_t(2) * y * y * y;

            win[n] = min(x, y);
        }
    }

    ////////////////////////////////////////////////////////////////////////////
    //                           Cosine-sum windows                           //
    ////////////////////////////////////////////////////////////////////////////
    static void cosine(DataType (&win)[N]) MF_NOEXCEPT {
        using wf::detail::PI;
        for(size_t n = 0; n != N; ++n) {
            win[n] = sin((PI * (float_t(n) + float_t(1) / float_t(2))) / float_t(N));
        }
    }
    static void bohman(DataType (&win)[N]) MF_NOEXCEPT {
        using wf::detail::PI;
        using wf::detail::INV_PI;
        for(size_t n = 0; n != N; ++n) {
            const float_t factor = abs(float_t(2) * float_t(n) / (N - 1.0) - 1.0);
            win[n] = (float_t(1) - factor) * cos(PI * factor) + INV_PI * sin(PI * factor);
        }
    }
    template<size_t K> static void cosine_sum(DataType (&win)[N], const float_t (&a)[K]) MF_NOEXCEPT {
        using wf::detail::TWO_PI;
        for(size_t n = 0; n != N; ++n) {
            win[n] = a[0];
            int sgn = 1;
            for(size_t k = 1; k != K; ++k) {
                sgn *= -1;
                win[n] += float_t(sgn) * a[k] * cos((TWO_PI * float_t(k) * float_t(n)) / (float_t(N) - float_t(1)));
            }
        }
    }
    static void general_hamming(DataType (&win)[N], float_t alpha) {
        static float_t a[2];
        a[0] = alpha;
        a[1] = float_t(1) - alpha;
        cosine_sum(win, a);
    }
    static void hamming(DataType (&win)[N]) MF_NOEXCEPT {
        general_hamming(win, MF_FLOAT_MAX_C(0.54));
    }
    static void hann(DataType (&win)[N]) MF_NOEXCEPT {
        static const float_t a[] = {0.5, 0.5};
        cosine_sum(win, a);
    }
    static void blackman_generic(DataType (&win)[N], float_t alpha) MF_NOEXCEPT {
        static float_t a[3];
        a[0] = (float_t(1) - alpha) / float_t(2);
        a[1] = float_t(1) / float_t(2);
        a[2] = alpha / float_t(2);
        cosine_sum(win, a);
    }
    static void blackman(DataType (&win)[N]) MF_NOEXCEPT {
        blackman_generic(win, 0.16);
    }
    static void nuttall(DataType (&win)[N]) MF_NOEXCEPT {
        static const float_t a[] = {0.3635819, 0.4891775, 0.1365995, 0.0106411};
        cosine_sum(win, a);
    }
    static void blackmanharris(DataType (&win)[N]) MF_NOEXCEPT {
        static const float_t a[] = {0.35875, 0.48829, 0.14128, 0.01168};
        cosine_sum(win, a);
    }
    static void flattop(DataType (&win)[N]) MF_NOEXCEPT {
        static const float_t a[] = {0.21557895, 0.41663158, 0.277263158, 0.083578947, 0.006947368};
        cosine_sum(win, a);
    }

    ////////////////////////////////////////////////////////////////////////////
    //                           Adjustable windows                           //
    ////////////////////////////////////////////////////////////////////////////
    static void gaussian(DataType (&win)[N], float_t sigma) MF_NOEXCEPT {
        static MF_CONST_OR_CONSTEXPR float_t subtractor = (float_t(N) - float_t(1)) / float_t(2);
        for(size_t n = 0; n != N; ++n) {
            const float_t x = float_t(n) - subtractor;
            win[n] = exp(-(float_t(1) / float_t(2)) * x * x / (sigma * sigma));
        }
    }
    static void tukey(DataType (&win)[N], float_t alpha) MF_NOEXCEPT {
        using wf::detail::TWO_PI;

        if(alpha <= 0.0) {
            rect(win);
            return;
        } else if(alpha >= 1.0) {
            hann(win);
            return;
        }

        size_t n;
        for(n = 0; n != (size_t)(alpha * (N - 1.0) / 2.0 + 1.0); ++n) {
            win[n] = (float_t(1) - cos(TWO_PI * n / (alpha * (float_t(N) - float_t(1))))) / float_t(2);
        }
        for(; n != (size_t)((N - 1.0) / 2.0 + 1.0); ++n) {
            win[n] = float_t(1);
        }
        for(; n != N; ++n) {
            win[n] = win[N - n - 1];
        }
    }
    static void kaiser(DataType (&win)[N], float_t beta) MF_NOEXCEPT {
        for(size_t n = 0; n != N; ++n) {
            const float_t factor = float_t(2) * float_t(n) / (float_t(N) - float_t(1)) - float_t(1);
            win[n] = bessel::i0(beta * sqrt(float_t(1) - factor * factor)) / bessel::i0(beta);
        }
    }
    static void kaiser_bessel_derived(DataType (&win)[N], float_t beta) MF_NOEXCEPT {
        Windows<DataType, N / 2 + 1>::kaiser((DataType(&)[N / 2 + 1]) win, beta);

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
    static void chebyshev(DataType (&win)[N], float_t alpha) {
        using wf::detail::PI;
        using wf::detail::TWO_PI;

        size_t order = N - 1;
        float_t amp = pow(10.0, abs(alpha) / 20.0);
        float_t beta = cosh(acosh(amp) / order);
        Complex<float_t> W[N];
        MF_IF_CONSTEXPR(N % 2) {
            for(size_t n = 0; n < N; ++n) {
                float_t x = beta * cos(PI * n / N);
                if(x > 1.0) {
                    W[n] = (cosh(order * acosh(x)));
                } else if(x < -1.0) {
                    W[n] = (cosh(order * acosh(-x)));
                } else {
                    W[n] = (cos(order * acos(x)));
                }
            }
            wf::detail::czt<float_t, N, N>(W, W, Complex<float_t>::polar(1, -TWO_PI / N), 1.0);

            /*
            Example: n = 11
                w[0] w[1] w[2] w[3] w[4] w[5] w[6] w[7] w[8] w[9] w[10]
                                        =
                p[5] p[4] p[3] p[2] p[1] p[0] p[1] p[2] p[3] p[4] p[5]
            */
            size_t h = (N - 1) / 2;
            for(size_t n = 0; n < N; ++n) {
                size_t k = (n <= h) ? (h - n) : (n - h);
                win[n] = W[k].real();
            }
        } else {
            for(size_t n = 0; n < N; ++n) {
                const float_t x = beta * cos(PI * n / N);
                const Complex<float_t> z = Complex<float_t>::polar(1, PI * n / N);
                if(x > 1) {
                    W[n] = z * cosh(order * acosh(x));
                } else if(x < -1) {
                    W[n] = -z * cosh(order * acosh(-x));
                } else {
                    W[n] = z * cos(order * acos(x));
                }
            }

            MF_IF_CONSTEXPR(trait::is_pow_of_2<N>::value) {
                wf::detail::fft_radix2(W);
            } else {
                wf::detail::czt<float_t, N, N>(W, W, Complex<float_t>::polar(1, -TWO_PI / N), float_t(1));
            }

            /*
            Example: n = 10
                w[0] w[1] w[2] w[3] w[4] w[5] w[6] w[7] w[8] w[9]
                                        =
                p[5] p[4] p[3] p[2] p[1] p[1] p[2] p[3] p[4] p[5]
            */
            size_t h = N / 2;
            for(size_t n = 0; n < N; ++n) {
                size_t k = (n < h) ? (h - n) : (n - h + 1);
                win[n] = W[k].real();
            }
        }

        float_t maxw = win[0];
        for(size_t n = 1; n < N; ++n) {
            maxw = max<float_t>(maxw, win[n]);
        }
        for(size_t n = 0; n < N; ++n) {
            win[n] /= maxw;
        }
    }
    static void poisson(DataType (&win)[N], float_t tau) MF_NOEXCEPT {
        static MF_CONST_OR_CONSTEXPR float_t subtractor = (float_t(N) - float_t(1)) / float_t(2);
        for(size_t n = 0; n != N; ++n) {
            win[n] = exp(-abs(float_t(n) - subtractor) / tau);
        }
    }

    ////////////////////////////////////////////////////////////////////////////
    //                              Hybrid windows                             //
    ////////////////////////////////////////////////////////////////////////////
    static void barthann(DataType (&win)[N]) MF_NOEXCEPT {
        using wf::detail::TWO_PI;
        for(size_t n = 0; n != N; ++n) {
            float_t factor = abs(float_t(n) / (float_t(N) - float_t(1)) - float_t(1) / float_t(2));
            win[n] = MF_FLOAT_MAX_C(0.62) - MF_FLOAT_MAX_C(0.48) * factor + MF_FLOAT_MAX_C(0.38) * cos(TWO_PI * factor);
        }
    }

    ////////////////////////////////////////////////////////////////////////////
    //                              Other windows                             //
    ////////////////////////////////////////////////////////////////////////////
    static void lanczos(DataType (&win)[N]) MF_NOEXCEPT {
        for(size_t n = 0; n != N; ++n) {
            win[n] = sinc(float_t(2) * float_t(n) / (float_t(N) - float_t(1)) - float_t(1));
        }
    }
};
} // namespace mf

#endif // HPP_MF_WINDOWS
