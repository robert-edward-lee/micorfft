#define _USE_MATH_DEFINES
#include <cmath>

#include "config.h"
#include "mf/fft.hpp"
#include "print_hist.h"

int main(void) {
    TEST_FLOAT_T signal_t[TEST_N] = TEST_FLOAT_32;
    TEST_FLOAT_T signal_f[2 * TEST_N];
    TEST_FLOAT_T mag[TEST_N];

    TEST_FLOAT_T csignal[TEST_N * 2];
    TEST_FLOAT_T cmag[TEST_N];

    for(int i = 0; i < TEST_N; ++i) {
        // signal_t[i] = 2 + std::sin(i * 2 * M_PI * TEST_F / TEST_N);
        // signal_t[i] += std::sin(i * 2 * M_PI * TEST_F1 / TEST_N);

        csignal[2 * i] = signal_t[i];
        csignal[2 * i + 1] = 0;
    }
    // printf("signal(%d):\n", TEST_N);
    // print_hist_horiz(signal_t, TEST_N, 60);

    /* rfft */
    printf("mf rfft(%d):\n", TEST_N);
    mf::Rfft<TEST_FLOAT_T, TEST_N> rfft;
    (void)sizeof(rfft);
#if TEST_INVERSE
    rfft.inverse(signal_t, signal_f);
    // for(auto i = 0; i < TEST_N; ++i) {
    //     printf("%g\n", signal_f[i]);
    // }
    print_hist_horiz(signal_f, TEST_N, 60);

    printf("scipy rfft(%d):\n", TEST_N);
    TEST_FLOAT_T scipy[TEST_N] = {
        0.6666667,   0.6593825,   0.6378485,  0.6030057,   0.55637693, 0.5,         0.43633902,  0.36817616,
        0.2984905,   0.23032768,  0.16666667, 0.110289805, 0.06366101, 0.028818175, 0.007284149, 0.0,
        0.007284133, 0.028818196, 0.06366101, 0.11028979,  0.16666669, 0.23032768,  0.2984905,   0.36817616,
        0.43633902,  0.5,         0.55637693, 0.6030057,   0.6378485,  0.6593825,
    };
    print_hist_horiz(scipy, TEST_N, 60);
#else
    rfft.forward(signal_t, signal_f);
    for(int i = 0; i < TEST_N / 2; ++i) {
        printf("%g, %g\n", signal_f[2 * i], signal_f[2 * i + 1]);
        mag[i] = std::sqrt(signal_f[2 * i] * signal_f[2 * i] + signal_f[2 * i + 1] * signal_f[2 * i + 1]);
    }
    // print_hist_horiz((const TEST_FLOAT_T *)mag, TEST_N / 2, 60);
#endif

    /* cfft */
    //     printf("cfft(%d):\n", TEST_N);
    //     mf::Cfft<TEST_FLOAT_T, unsigned, TEST_N> cfft;
    // #if TEST_INVERSE
    //     cfft.inverse(csignal);
    // #else
    //     cfft.forward(csignal);
    // #endif
    //     for(int i = 0; i < TEST_N; ++i) {
    //         cmag[i] = sqrt(csignal[2 * i] * csignal[2 * i] + csignal[2 * i + 1] * csignal[2 * i + 1]);
    //     }
    //     print_hist_horiz(cmag, TEST_N / 1, 60);

    return 0;
}
