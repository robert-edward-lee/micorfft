#include <cstdint>

#define _USE_MATH_DEFINES
#include <cmath>

#include "mf/fft.hpp"
#include "print_hist.h"

int main(void) {
    static const mf::uint16_t N = 64;
    static const mf::float_max_t F = 10;

    mf::float32_t signal_t[N];
    mf::float32_t signal_f[2 * N];
    mf::float32_t mag[N];

    for(auto i = 0; i < N; ++i) {
        signal_t[i] = 1 + (std::sin(i * 2 * M_PI * F / N));
    }

    print_hist_horiz(signal_t, N, 60);

    mf::Rfft<mf::float32_t, mf::uint16_t, 64> rfft;
    rfft.forward(signal_t, signal_f);

    for(auto i = 0; i < N; ++i) {
        // std::cout << "(" << signal_f[2 * i] << ", " << signal_f[2 * i + 1] << ")\n";
        mag[i] = std::sqrt(signal_f[2 * i] * signal_f[2 * i] + signal_f[2 * i + 1] * signal_f[2 * i + 1]);
        // std::cout << "(" << mag[i] << ")\n";
    }
    print_hist_horiz(mag, N, 60);

    return 0;
}
