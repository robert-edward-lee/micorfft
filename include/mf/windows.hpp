#ifndef HPP_MF_WINDOWS
#define HPP_MF_WINDOWS

#include "mf/basic_math.hpp"
#include "mf/config.hpp"
#include "mf/special_math.hpp"
#include "mf/traits/math.hpp"
#include "mf/types.hpp"

namespace mf { namespace windows {
typedef float_max_t float_t;

static MF_CONST_OR_CONSTEXPR float_t ONE = MF_FLOAT_MAX_C(1.0);
static MF_CONST_OR_CONSTEXPR float_t TWO = MF_FLOAT_MAX_C(2.0);
static MF_CONST_OR_CONSTEXPR float_t HALF = ONE / TWO;
static MF_CONST_OR_CONSTEXPR float_t PI = pi<float_t>::value;
static MF_CONST_OR_CONSTEXPR float_t TWO_PI = two_pi<float_t>::value;
static MF_CONST_OR_CONSTEXPR float_t INV_PI = inv_pi<float_t>::value;

namespace detail {
template<typename T, T N> class FftIdx {
public:
    MF_CONSTEXPR FftIdx() MF_NOEXCEPT: forward(T(0)), reverse(T(0)) {}

    MF_CONSTEXPR_14 FftIdx &operator++() MF_NOEXCEPT {
        reverse ^= N - ((N / 2) / (~forward & (forward + 1)));
        ++forward;
        return *this;
    }
    MF_CONSTEXPR bool operator!=(const T &other) const MF_NOEXCEPT {
        return forward != other;
    }

    MF_CONSTEXPR const T &i() const MF_NOEXCEPT {
        return forward;
    }
    MF_CONSTEXPR const T &r() const MF_NOEXCEPT {
        return reverse;
    }

private:
    T forward;
    T reverse;
};

template<size_t N> void fft_radix2(Complex<float_t> (&z)[N]) MF_NOEXCEPT {
    /* поворотные коэффициенты */
    Complex<float_t> ww[N / 2 ? N / 2 : 1];
    for(size_t i = 0; i < N / 2; ++i) {
        ww[i] = Complex<float_t>::polar(ONE, -TWO_PI * float_t(i) / float_t(N));
    }

    /* перестановка элементов */
    for(FftIdx<size_t, N> fft_idx; fft_idx != N; ++fft_idx) {
        if(fft_idx.i() < fft_idx.r()) {
            std::swap(z[fft_idx.i()], z[fft_idx.r()]);
        }
    }

    /* преобразование */
    size_t num_subffts = N / 2;
    size_t size_subfft = 2;
    while(num_subffts) {
        for(size_t i = 0; i < num_subffts; ++i) {
            const size_t subfft_offset = size_subfft * i;

            for(size_t j = 0; j < size_subfft / 2; ++j) {
                const size_t target1 = subfft_offset + j;
                const size_t target2 = subfft_offset + j + size_subfft / 2;

                const size_t left = target1;
                const size_t right = target2;

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
template<size_t N, size_t M>
void czt(Complex<float_t> (&z)[N], Complex<float_t> (&ztrans)[M], Complex<float_t> w, Complex<float_t> a) MF_NOEXCEPT {
    MF_CONST_OR_CONSTEXPR size_t fft_size = trait::clp2<N + M - 1>::value;

    Complex<float_t> zz[fft_size];
    for(size_t k = 0; k < fft_size; ++k) {
        if(k < N) {
            zz[k] = w.pow(HALF * float_t(k) * float_t(k)) / a.pow(k) * z[k];
        } else {
            zz[k] = 0;
        }
    }
    fft_radix2(zz);

    Complex<float_t> w2[fft_size];
    for(size_t k = 0; k < fft_size; ++k) {
        if(k < N + M - 1) {
            const int kshift = k - (N - 1);

            w2[k] = w.pow(-HALF * float_t(kshift) * float_t(kshift));
        } else {
            w2[k] = 0;
        }
    }
    fft_radix2(w2);

    for(size_t k = 0; k < fft_size; ++k) {
        zz[k] *= w2[k];
    }
    fft_radix2(zz);

    /* обратное БПФ из прямого */
    for(size_t k = 0; k < fft_size; ++k) {
        zz[k] /= fft_size;
    }
    for(size_t k = 1; k < fft_size - k; ++k) {
        const size_t kswap = fft_size - k;
        std::swap(zz[k], zz[kswap]);
    }

    for(size_t k = 0; k < M; ++k) {
        const Complex<float_t> w3 = w.pow(HALF * float_t(k) * float_t(k));
        ztrans[k] = w3 * zz[N - 1 + k];
    }
}
} // namespace detail

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
    MF_CONST_OR_CONSTEXPR float_t factor = PI / float_t(N);
    for(size_t n = 0; n != N; ++n) {
        win[n] = sin(factor * (float_t(n) + HALF));
    }
}
template<typename DataType, size_t N> void bohman(DataType (&win)[N]) MF_NOEXCEPT {
    for(size_t n = 0; n != N; ++n) {
        const float_t factor = abs(TWO * float_t(n) / (float_t(N) - ONE) - ONE);
        win[n] = (ONE - factor) * cos(PI * factor) + INV_PI * sin(PI * factor);
    }
}
template<typename DataType, size_t N, size_t K> void cosine_sum(DataType (&win)[N], const float_t (&a)[K]) MF_NOEXCEPT {
    MF_CONST_OR_CONSTEXPR float_t factor = TWO_PI / (float_t(N) - ONE);
    for(size_t n = 0; n != N; ++n) {
        win[n] = a[0];
        int sgn = 1;
        for(size_t k = 1; k != K; ++k) {
            sgn *= -1;
            win[n] += float_t(sgn) * a[k] * cos(factor * float_t(k) * float_t(n));
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
    general_hamming(win, HALF);
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
template<typename DataType, size_t N> void hft70(DataType (&win)[N]) MF_NOEXCEPT {
    static const float_t a[] = {
        MF_FLOAT_MAX_C(1.0),
        MF_FLOAT_MAX_C(1.90796),
        MF_FLOAT_MAX_C(1.07349),
        MF_FLOAT_MAX_C(0.18199),
    };
    cosine_sum(win, a);
}
template<typename DataType, size_t N> void hft95(DataType (&win)[N]) MF_NOEXCEPT {
    static const float_t a[] = {
        MF_FLOAT_MAX_C(1.0),
        MF_FLOAT_MAX_C(1.9383379),
        MF_FLOAT_MAX_C(1.3045202),
        MF_FLOAT_MAX_C(0.4028270),
        MF_FLOAT_MAX_C(0.0350665),
    };
    cosine_sum(win, a);
}
template<typename DataType, size_t N> void hft90d(DataType (&win)[N]) MF_NOEXCEPT {
    static const float_t a[] = {
        MF_FLOAT_MAX_C(1.0),
        MF_FLOAT_MAX_C(1.942604),
        MF_FLOAT_MAX_C(1.340318),
        MF_FLOAT_MAX_C(0.440811),
        MF_FLOAT_MAX_C(0.043097),
    };
    cosine_sum(win, a);
}
template<typename DataType, size_t N> void hft116d(DataType (&win)[N]) MF_NOEXCEPT {
    static const float_t a[] = {
        MF_FLOAT_MAX_C(1.0),
        MF_FLOAT_MAX_C(1.9575375),
        MF_FLOAT_MAX_C(1.4780705),
        MF_FLOAT_MAX_C(0.6367431),
        MF_FLOAT_MAX_C(0.1228389),
        MF_FLOAT_MAX_C(0.0066288),
    };
    cosine_sum(win, a);
}
template<typename DataType, size_t N> void hft144d(DataType (&win)[N]) MF_NOEXCEPT {
    static const float_t a[] = {
        MF_FLOAT_MAX_C(1.0),
        MF_FLOAT_MAX_C(1.96760033),
        MF_FLOAT_MAX_C(1.57983607),
        MF_FLOAT_MAX_C(0.81123644),
        MF_FLOAT_MAX_C(0.22583558),
        MF_FLOAT_MAX_C(0.02773848),
        MF_FLOAT_MAX_C(0.00090360),
    };
    cosine_sum(win, a);
}
template<typename DataType, size_t N> void hft169d(DataType (&win)[N]) MF_NOEXCEPT {
    static const float_t a[] = {
        MF_FLOAT_MAX_C(1.0),
        MF_FLOAT_MAX_C(1.97441843),
        MF_FLOAT_MAX_C(1.65409889),
        MF_FLOAT_MAX_C(0.95788187),
        MF_FLOAT_MAX_C(0.33673420),
        MF_FLOAT_MAX_C(0.06364622),
        MF_FLOAT_MAX_C(0.00521942),
        MF_FLOAT_MAX_C(0.00010599),
    };
    cosine_sum(win, a);
}
template<typename DataType, size_t N> void hft196d(DataType (&win)[N]) MF_NOEXCEPT {
    static const float_t a[] = {
        MF_FLOAT_MAX_C(1.0),
        MF_FLOAT_MAX_C(1.979280420),
        MF_FLOAT_MAX_C(1.710288951),
        MF_FLOAT_MAX_C(1.081629853),
        MF_FLOAT_MAX_C(0.448734314),
        MF_FLOAT_MAX_C(0.112376628),
        MF_FLOAT_MAX_C(0.015122992),
        MF_FLOAT_MAX_C(0.000871252),
        MF_FLOAT_MAX_C(0.000011896),
    };
    cosine_sum(win, a);
}
template<typename DataType, size_t N> void hft223d(DataType (&win)[N]) MF_NOEXCEPT {
    static const float_t a[] = {
        MF_FLOAT_MAX_C(1.0),
        MF_FLOAT_MAX_C(1.98298997309),
        MF_FLOAT_MAX_C(1.75556083063),
        MF_FLOAT_MAX_C(1.19037717712),
        MF_FLOAT_MAX_C(0.56155440797),
        MF_FLOAT_MAX_C(0.17296769663),
        MF_FLOAT_MAX_C(0.03233247087),
        MF_FLOAT_MAX_C(0.00324954578),
        MF_FLOAT_MAX_C(0.00013801040),
        MF_FLOAT_MAX_C(0.00000132725),
    };
    cosine_sum(win, a);
}
template<typename DataType, size_t N> void hft248d(DataType (&win)[N]) MF_NOEXCEPT {
    static const float_t a[] = {
        MF_FLOAT_MAX_C(1.0),
        MF_FLOAT_MAX_C(1.985844164102),
        MF_FLOAT_MAX_C(1.791176438506),
        MF_FLOAT_MAX_C(1.282075284005),
        MF_FLOAT_MAX_C(0.667777530266),
        MF_FLOAT_MAX_C(0.240160796576),
        MF_FLOAT_MAX_C(0.056656381764),
        MF_FLOAT_MAX_C(0.008134974479),
        MF_FLOAT_MAX_C(0.000624544650),
        MF_FLOAT_MAX_C(0.000019808998),
        MF_FLOAT_MAX_C(0.000000132974),
    };
    cosine_sum(win, a);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                 Adjustable windows                                                 //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename DataType, size_t N> void gaussian(DataType (&win)[N], float_t sigma) MF_NOEXCEPT {
    MF_CONST_OR_CONSTEXPR float_t subtractor = (float_t(N) - ONE) / TWO;
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

    const float_t factor = TWO_PI / (alpha * (float_t(N) - ONE));
    size_t n;
    for(n = 0; n != (size_t)(alpha * (float_t(N) - ONE) / TWO + ONE); ++n) {
        win[n] = (ONE - cos(factor * n)) / TWO;
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

        detail::czt(W, W, Complex<float_t>::polar(ONE, -TWO_PI / float_t(N)), ONE);

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
            detail::fft_radix2(W);
        } else {
            detail::czt(W, W, Complex<float_t>::polar(ONE, -TWO_PI / float_t(N)), ONE);
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
        const float_t factor = abs(float_t(n) / (float_t(N) - ONE) - HALF);
        win[n] = MF_FLOAT_MAX_C(0.62) - MF_FLOAT_MAX_C(0.48) * factor + MF_FLOAT_MAX_C(0.38) * cos(TWO_PI * factor);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                    Other windows                                                   //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename DataType, size_t N> void lanczos(DataType (&win)[N]) MF_NOEXCEPT {
    MF_CONST_OR_CONSTEXPR float_t factor = TWO / (float_t(N) - ONE);
    for(size_t n = 0; n != N; ++n) {
        win[n] = sinc(factor * float_t(n) - ONE);
    }
}
}} // namespace mf::windows

#endif // HPP_MF_WINDOWS
