#include <stdint.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include "dsp/transform_functions.h"
#include "print_hist.h"

arm_rfft_fast_instance_f32 rfft_inst;

int main(void) {
    static const uint16_t N = 64;
    static const float F = 10;

    float signal_t[N];
    float signal_f[2 * N];
    float mag[N];

    for(uint16_t i = 0; i < N; ++i) {
        signal_t[i] = 1 + (sin(i * 2 * M_PI * F / N));
    }

    print_hist_horiz(signal_t, N, 60);

    arm_rfft_fast_init_f32(&rfft_inst, 64);
    arm_rfft_fast_f32(&rfft_inst, signal_t, signal_f, 0);

    for(uint16_t i = 0; i < N; ++i) {
        mag[i] = sqrt(signal_f[2 * i] * signal_f[2 * i] + signal_f[2 * i + 1] * signal_f[2 * i + 1]);
    }
    printf("\n\n");
    print_hist_horiz(mag, N / 2, 60);

    return 0;
}
