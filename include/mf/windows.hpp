#ifndef HPP_MF_WINDOWS
#define HPP_MF_WINDOWS

#include "mf/basic_math.hpp"
#include "mf/config.hpp"
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
};
} // namespace mf

#endif // HPP_MF_WINDOWS
