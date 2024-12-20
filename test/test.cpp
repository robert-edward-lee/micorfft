#include <cstdint>

#define _USE_MATH_DEFINES
#include <cmath>

#include "mf/fft.hpp"
#include "print_hist.h"

int main(void) {
    static const uint16_t N = 64;
    static const float F = 10;

    float signal_t[N];
    float signal_f[2 * N];
    float mag[N];

    for(auto i = 0; i < N; ++i) {
        signal_t[i] = 1 + (std::sin(i * 2 * M_PI * F / N));
    }

    print_hist_horiz(signal_t, N, 60);

    mf::Rfft<float, uint16_t, 64> rfft;
    rfft.forward(signal_t, signal_f);

    for(auto i = 0; i < N; ++i) {
        mag[i] = std::sqrt(signal_f[2 * i] * signal_f[2 * i] + signal_f[2 * i + 1] * signal_f[2 * i + 1]);
    }
    printf("\n\n");
    print_hist_horiz(mag, N / 2, 60);

    return 0;
}
