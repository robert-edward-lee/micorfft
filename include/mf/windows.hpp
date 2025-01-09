#ifndef HPP_MF_WINDOWS
#define HPP_MF_WINDOWS

#include "mf/basic_math.hpp"
#include "mf/config.hpp"
#include "mf/special_math.hpp"
#include "mf/types.hpp"

namespace mf { namespace windows {
namespace detail {
typedef float_max_t float_t;
static MF_CONST_OR_CONSTEXPR float_t PI = pi<float_t>::value;
static MF_CONST_OR_CONSTEXPR float_t TWO_PI = two_pi<float_t>::value;
static MF_CONST_OR_CONSTEXPR float_t INV_PI = inv_pi<float_t>::value;
} // namespace detail
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                  B-spline windows                                                  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename DataType, size_t N> void rect(DataType (&win)[N]) MF_NOEXCEPT {
    for(size_t n = 0; n != N; ++n) {
        win[n] = detail::float_t(1);
    }
}
template<typename DataType, size_t N> void bartlett(DataType (&win)[N]) MF_NOEXCEPT {
    static MF_CONST_OR_CONSTEXPR DataType subtractor = (detail::float_t(N) - detail::float_t(1)) / detail::float_t(2);
    static MF_CONST_OR_CONSTEXPR DataType divider = (detail::float_t(N) - detail::float_t(1)) / detail::float_t(2);
    for(size_t n = 0; n != N; ++n) {
        win[n] = detail::float_t(1) - abs((detail::float_t(n) - subtractor) / divider);
    }
}
template<typename DataType, size_t N> void triang(DataType (&win)[N]) MF_NOEXCEPT {
    static MF_CONST_OR_CONSTEXPR DataType subtractor = (detail::float_t(N) - detail::float_t(1)) / detail::float_t(2);
    static MF_CONST_OR_CONSTEXPR DataType divider = N % 2
                                                      ? (detail::float_t(N) + detail::float_t(1)) / detail::float_t(2)
                                                      : detail::float_t(N) / detail::float_t(2);
    for(size_t n = 0; n != N; ++n) {
        win[n] = detail::float_t(1) - abs((detail::float_t(n) - subtractor) / divider);
    }
}
template<typename DataType, size_t N> void parzen(DataType (&win)[N]) MF_NOEXCEPT {
    for(size_t n = 0; n != N; ++n) {
        DataType x = abs(detail::float_t(2) * detail::float_t(n) - (detail::float_t(N) - detail::float_t(1)))
                   / detail::float_t(N);
        DataType y = detail::float_t(1) - x;

        x = detail::float_t(1) - detail::float_t(6) * x * x + detail::float_t(6) * x * x * x;
        y = detail::float_t(2) * y * y * y;

        win[n] = min(x, y);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                 Cosine-sum windows                                                 //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename DataType, size_t N> void cosine(DataType (&win)[N]) MF_NOEXCEPT {
    using detail::PI;
    for(size_t n = 0; n != N; ++n) {
        win[n] = sin((PI * (detail::float_t(n) + detail::float_t(1) / detail::float_t(2))) / detail::float_t(N));
    }
}
template<typename DataType, size_t N> void bohman(DataType (&win)[N]) MF_NOEXCEPT {
    using detail::PI;
    using detail::INV_PI;
    for(size_t n = 0; n != N; ++n) {
        const detail::float_t factor = abs(detail::float_t(2) * detail::float_t(n) / (N - 1.0) - 1.0);
        win[n] = (detail::float_t(1) - factor) * cos(PI * factor) + INV_PI * sin(PI * factor);
    }
}
template<typename DataType, size_t N, size_t K>
void cosine_sum(DataType (&win)[N], const detail::float_t (&a)[K]) MF_NOEXCEPT {
    using detail::TWO_PI;
    for(size_t n = 0; n != N; ++n) {
        win[n] = a[0];
        int sgn = 1;
        for(size_t k = 1; k != K; ++k) {
            sgn *= -1;
            win[n] +=
                detail::float_t(sgn) * a[k]
                * cos((TWO_PI * detail::float_t(k) * detail::float_t(n)) / (detail::float_t(N) - detail::float_t(1)));
        }
    }
}
template<typename DataType, size_t N> void general_hamming(DataType (&win)[N], detail::float_t alpha) {
    static detail::float_t a[2];
    a[0] = alpha;
    a[1] = detail::float_t(1) - alpha;
    cosine_sum(win, a);
}
template<typename DataType, size_t N> void hamming(DataType (&win)[N]) MF_NOEXCEPT {
    general_hamming(win, MF_FLOAT_MAX_C(0.54));
}
template<typename DataType, size_t N> void hann(DataType (&win)[N]) MF_NOEXCEPT {
    static const detail::float_t a[] = {0.5, 0.5};
    cosine_sum(win, a);
}
template<typename DataType, size_t N> void blackman_generic(DataType (&win)[N], detail::float_t alpha) MF_NOEXCEPT {
    static detail::float_t a[3];
    a[0] = (detail::float_t(1) - alpha) / detail::float_t(2);
    a[1] = detail::float_t(1) / detail::float_t(2);
    a[2] = alpha / detail::float_t(2);
    cosine_sum(win, a);
}
template<typename DataType, size_t N> void blackman(DataType (&win)[N]) MF_NOEXCEPT {
    blackman_generic(win, 0.16);
}
template<typename DataType, size_t N> void nuttall(DataType (&win)[N]) MF_NOEXCEPT {
    static const detail::float_t a[] = {0.3635819, 0.4891775, 0.1365995, 0.0106411};
    cosine_sum(win, a);
}
template<typename DataType, size_t N> void blackmanharris(DataType (&win)[N]) MF_NOEXCEPT {
    static const detail::float_t a[] = {0.35875, 0.48829, 0.14128, 0.01168};
    cosine_sum(win, a);
}
template<typename DataType, size_t N> void flattop(DataType (&win)[N]) MF_NOEXCEPT {
    static const detail::float_t a[] = {0.21557895, 0.41663158, 0.277263158, 0.083578947, 0.006947368};
    cosine_sum(win, a);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                 Adjustable windows                                                 //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename DataType, size_t N> void gaussian(DataType (&win)[N], detail::float_t sigma) MF_NOEXCEPT {
    static MF_CONST_OR_CONSTEXPR detail::float_t subtractor =
        (detail::float_t(N) - detail::float_t(1)) / detail::float_t(2);
    for(size_t n = 0; n != N; ++n) {
        const detail::float_t x = detail::float_t(n) - subtractor;
        win[n] = exp(-(detail::float_t(1) / detail::float_t(2)) * x * x / (sigma * sigma));
    }
}
template<typename DataType, size_t N> void tukey(DataType (&win)[N], detail::float_t alpha) MF_NOEXCEPT {
    using detail::TWO_PI;

    if(alpha <= 0.0) {
        rect(win);
        return;
    } else if(alpha >= 1.0) {
        hann(win);
        return;
    }

    size_t n;
    for(n = 0; n != (size_t)(alpha * (N - 1.0) / 2.0 + 1.0); ++n) {
        win[n] = (detail::float_t(1) - cos(TWO_PI * n / (alpha * (detail::float_t(N) - detail::float_t(1)))))
               / detail::float_t(2);
    }
    for(; n != (size_t)((N - 1.0) / 2.0 + 1.0); ++n) {
        win[n] = detail::float_t(1);
    }
    for(; n != N; ++n) {
        win[n] = win[N - n - 1];
    }
}
template<typename DataType, size_t N> void kaiser(DataType (&win)[N], detail::float_t beta) MF_NOEXCEPT {
    for(size_t n = 0; n != N; ++n) {
        const detail::float_t factor =
            detail::float_t(2) * detail::float_t(n) / (detail::float_t(N) - detail::float_t(1)) - detail::float_t(1);
        win[n] = bessel::i0(beta * sqrt(detail::float_t(1) - factor * factor)) / bessel::i0(beta);
    }
}
template<typename DataType, size_t N> void kaiser_bessel_derived(DataType (&win)[N], detail::float_t beta) MF_NOEXCEPT {
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
template<typename DataType, size_t N> void poisson(DataType (&win)[N], detail::float_t tau) MF_NOEXCEPT {
    static MF_CONST_OR_CONSTEXPR detail::float_t subtractor =
        (detail::float_t(N) - detail::float_t(1)) / detail::float_t(2);
    for(size_t n = 0; n != N; ++n) {
        win[n] = exp(-abs(detail::float_t(n) - subtractor) / tau);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                   Hybrid windows                                                   //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename DataType, size_t N> void barthann(DataType (&win)[N]) MF_NOEXCEPT {
    using detail::TWO_PI;
    for(size_t n = 0; n != N; ++n) {
        detail::float_t factor = abs(detail::float_t(n) / (detail::float_t(N) - detail::float_t(1))
                                     - detail::float_t(1) / detail::float_t(2));
        win[n] = MF_FLOAT_MAX_C(0.62) - MF_FLOAT_MAX_C(0.48) * factor + MF_FLOAT_MAX_C(0.38) * cos(TWO_PI * factor);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                    Other windows                                                   //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename DataType, size_t N> void lanczos(DataType (&win)[N]) MF_NOEXCEPT {
    for(size_t n = 0; n != N; ++n) {
        win[n] = sinc(detail::float_t(2) * detail::float_t(n) / (detail::float_t(N) - detail::float_t(1))
                      - detail::float_t(1));
    }
}
}} // namespace mf::windows

#endif // HPP_MF_WINDOWS
