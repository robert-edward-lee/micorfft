#include <cstdint>

#define _USE_MATH_DEFINES
#include <cmath>

#include "mf/fft.hpp"
#include "print_hist.h"
#include "config.h"

int main(void) {
    float signal_t[TEST_N];
    float signal_f[2 * TEST_N];
    float mag[TEST_N];

    for(auto i = 0; i < TEST_N; ++i) {
        signal_t[i] = 1 + std::sin(i * 2 * M_PI * TEST_F / TEST_N);
        signal_t[i] += std::sin(i * 2 * M_PI * TEST_F1 / TEST_N);
    }

    // print_hist_horiz(signal_t, TEST_N, 60);

    mf::Rfft<float, uint16_t, TEST_N> rfft;
    rfft.forward(signal_t, signal_f);

    for(auto i = 0; i < TEST_N / 2; ++i) {
        mag[i] = std::sqrt(signal_f[2 * i] * signal_f[2 * i] + signal_f[2 * i + 1] * signal_f[2 * i + 1]);
    }
    // printf("\n\n");
    print_hist_horiz(mag, TEST_N / 2, 60);

    return 0;
}
