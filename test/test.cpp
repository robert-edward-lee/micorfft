#include <cstdint>

#define _USE_MATH_DEFINES
#include <cmath>

#include "config.h"
#include "mf/fft.hpp"
#include "print_hist.h"

int main(void) {
    TEST_FLOAT_T signal_t[TEST_N];
    TEST_FLOAT_T signal_f[2 * TEST_N];
    TEST_FLOAT_T mag[TEST_N];

    TEST_FLOAT_T csignal[TEST_N * 2];
    TEST_FLOAT_T cmag[TEST_N];

    for(auto i = 0; i < TEST_N; ++i) {
        signal_t[i] = 2 + std::sin(i * 2 * M_PI * TEST_F / TEST_N);
        signal_t[i] += std::sin(i * 2 * M_PI * TEST_F1 / TEST_N);

        csignal[2 * i] = signal_t[i];
        csignal[2 * i + 1] = 0;
    }

    // print_hist_horiz(signal_t, TEST_N, 60);

    /* rfft */
    mf::Rfft<TEST_FLOAT_T, unsigned, TEST_N> rfft;
    (void)sizeof(rfft);
#if TEST_INVERSE
    rfft.inverse(signal_t, signal_f);
#else
    rfft.forward(signal_t, signal_f);
#endif

    for(auto i = 0; i < TEST_N / 2; ++i) {
        mag[i] = std::sqrt(signal_f[2 * i] * signal_f[2 * i] + signal_f[2 * i + 1] * signal_f[2 * i + 1]);
    }
    printf("rfft(%d):\n", TEST_N);
    print_hist_horiz((const TEST_FLOAT_T *)mag, TEST_N / 2, 60);

    /* cfft */
    mf::Cfft<TEST_FLOAT_T, unsigned, TEST_N> cfft;
#if TEST_INVERSE
    cfft.inverse(csignal);
#else
    cfft.forward(csignal);
#endif
    for(auto i = 0; i < TEST_N; ++i) {
        cmag[i] = sqrt(csignal[2 * i] * csignal[2 * i] + csignal[2 * i + 1] * csignal[2 * i + 1]);
    }
    printf("cfft(%d):\n", TEST_N);
    print_hist_horiz(cmag, TEST_N / 1, 60);

    return 0;
}
