#ifndef HPP_MF_WINDOWS
#define HPP_MF_WINDOWS

#include "mf/basic_math.hpp"
#include "mf/config.hpp"
#include "mf/special_math.hpp"
#include "mf/types.hpp"

namespace mf { namespace windows {
typedef float_max_t float_t;

static MF_CONST_OR_CONSTEXPR float_t ONE = MF_FLOAT_MAX_C(1);
static MF_CONST_OR_CONSTEXPR float_t TWO = MF_FLOAT_MAX_C(2);
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
