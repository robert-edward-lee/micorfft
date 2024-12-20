#include <cstdint>

#define _USE_MATH_DEFINES
#include <cmath>

#include "config.h"
#include "mf/fft.hpp"
#include "print_hist.h"

int main(void) {
    mf::float32_t signal_t[TEST_N];
    mf::float32_t signal_f[2 * TEST_N];
    mf::float32_t mag[TEST_N];

    for(auto i = 0; i < TEST_N; ++i) {
        signal_t[i] = 2 + std::sin(i * 2 * M_PI * TEST_F / TEST_N);
        signal_t[i] += std::sin(i * 2 * M_PI * TEST_F1 / TEST_N);
    }

    // print_hist_horiz(signal_t, TEST_N, 60);

    mf::Rfft<mf::float32_t, mf::uint16_t, TEST_N> rfft;
#if TEST_INVERSE
    rfft.inverse(signal_t, signal_f);
#else
    rfft.forward(signal_t, signal_f);
#endif

    for(auto i = 0; i < TEST_N / 2; ++i) {
        mag[i] = std::sqrt(signal_f[2 * i] * signal_f[2 * i] + signal_f[2 * i + 1] * signal_f[2 * i + 1]);
    }
    // printf("\n\n");
    print_hist_horiz((const float *)mag, TEST_N / 2, 60);

    return 0;
}
