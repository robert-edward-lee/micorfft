#ifndef HPP_MF_WINDOWS
#define HPP_MF_WINDOWS

#include "mf/basic_math.hpp"
#include "mf/config.hpp"
#include "mf/special_math.hpp"
#include "mf/types.hpp"

namespace mf {
namespace wf { namespace detail {
static MF_CONST_OR_CONSTEXPR float_max_t PI = pi<float_max_t>::value;
static MF_CONST_OR_CONSTEXPR float_max_t TWO_PI = two_pi<float_max_t>::value;
static MF_CONST_OR_CONSTEXPR float_max_t INV_PI = inv_pi<float_max_t>::value;
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
    static void cosine(DataType (&win)[N]) {
        using wf::detail::PI;
        for(size_t n = 0; n != N; ++n) {
            win[n] = sin((PI * (float_t(n) + float_t(1) / float_t(2))) / float_t(N));
        }
    }
    static void bohman(DataType (&win)[N]) {
        using wf::detail::PI;
        using wf::detail::INV_PI;
        for(size_t n = 0; n != N; ++n) {
            const float_t factor = abs(float_t(2) * float_t(n) / (N - 1.0) - 1.0);
            win[n] = (float_t(1) - factor) * cos(PI * factor) + INV_PI * sin(PI * factor);
        }
    }
    template<size_t K> static void cosine_sum(DataType (&win)[N], const float_t (&a)[K]) {
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
    static void hamming(DataType (&win)[N]) {
        general_hamming(win, MF_FLOAT_MAX_C(0.54));
    }
    static void hann(DataType (&win)[N]) {
        static const float_t a[] = {0.5, 0.5};
        cosine_sum(win, a);
    }
    static void blackman_generic(DataType (&win)[N], float_t alpha) {
        static float_t a[3];
        a[0] = (float_t(1) - alpha) / float_t(2);
        a[1] = float_t(1) / float_t(2);
        a[2] = alpha / float_t(2);
        cosine_sum(win, a);
    }
    static void blackman(DataType (&win)[N]) {
        blackman_generic(win, 0.16);
    }
    static void nuttall(DataType (&win)[N]) {
        static const float_t a[] = {0.3635819, 0.4891775, 0.1365995, 0.0106411};
        cosine_sum(win, a);
    }
    static void blackmanharris(DataType (&win)[N]) {
        static const float_t a[] = {0.35875, 0.48829, 0.14128, 0.01168};
        cosine_sum(win, a);
    }
    static void flattop(DataType (&win)[N]) {
        static const float_t a[] = {0.21557895, 0.41663158, 0.277263158, 0.083578947, 0.006947368};
        cosine_sum(win, a);
    }

    ////////////////////////////////////////////////////////////////////////////
    //                           Adjustable windows                           //
    ////////////////////////////////////////////////////////////////////////////
    static void gaussian(DataType (&win)[N], float_t sigma) {
        static MF_CONST_OR_CONSTEXPR float_t subtractor = (float_t(N) - float_t(1)) / float_t(2);
        for(size_t n = 0; n != N; ++n) {
            const float_t x = float_t(n) - subtractor;
            win[n] = exp(-(float_t(1) / float_t(2)) * x * x / (sigma * sigma));
        }
    }
    static void tukey(DataType (&win)[N], float_t alpha) {
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
    static void kaiser(DataType (&win)[N], float_t beta) {
        for(size_t n = 0; n != N; ++n) {
            const float_t factor = float_t(2) * float_t(n) / (float_t(N) - float_t(1)) - float_t(1);
            win[n] = bessel::i0(beta * sqrt(float_t(1) - factor * factor)) / bessel::i0(beta);
        }
    }
    static void kaiser_bessel_derived(DataType (&win)[N], float_t beta) {
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
    static void poisson(DataType (&win)[N], float_t tau) {
        static MF_CONST_OR_CONSTEXPR float_t subtractor = (float_t(N) - float_t(1)) / float_t(2);
        for(size_t n = 0; n != N; ++n) {
            win[n] = exp(-abs(float_t(n) - subtractor) / tau);
        }
    }

    ////////////////////////////////////////////////////////////////////////////
    //                              Hybrid windows                             //
    ////////////////////////////////////////////////////////////////////////////
    static void barthann(DataType (&win)[N]) {
        using wf::detail::TWO_PI;
        for(size_t n = 0; n != N; ++n) {
            float_t factor = abs(float_t(n) / (float_t(N) - float_t(1)) - float_t(1) / float_t(2));
            win[n] = MF_FLOAT_MAX_C(0.62) - MF_FLOAT_MAX_C(0.48) * factor + MF_FLOAT_MAX_C(0.38) * cos(TWO_PI * factor);
        }
    }

    ////////////////////////////////////////////////////////////////////////////
    //                              Other windows                             //
    ////////////////////////////////////////////////////////////////////////////
    static void lanczos(DataType (&win)[N]) {
        for(size_t n = 0; n != N; ++n) {
            win[n] = sinc(float_t(2) * float_t(n) / (float_t(N) - float_t(1)) - float_t(1));
        }
    }
};
} // namespace mf

#endif // HPP_MF_WINDOWS
