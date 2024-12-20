#include <stdint.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include "config.h"
#include "dsp/transform_functions.h"
#include "print_hist.h"

arm_rfft_fast_instance_f32 rfft_inst;

int main(void) {
    float signal_t[TEST_N];
    float signal_f[2 * TEST_N];
    float mag[TEST_N];

    for(uint16_t i = 0; i < TEST_N; ++i) {
        signal_t[i] = 2 + sin(i * 2 * M_PI * TEST_F / TEST_N);
        signal_t[i] += sin(i * 2 * M_PI * TEST_F1 / TEST_N);
    }

    // print_hist_horiz(signal_t, TEST_N, 60);

    arm_rfft_fast_init_f32(&rfft_inst, TEST_N);
    arm_rfft_fast_f32(&rfft_inst, signal_t, signal_f, TEST_INVERSE);

    for(uint16_t i = 0; i < TEST_N / 2; ++i) {
        mag[i] = sqrt(signal_f[2 * i] * signal_f[2 * i] + signal_f[2 * i + 1] * signal_f[2 * i + 1]);
    }
    // printf("\n\n");
    print_hist_horiz(mag, TEST_N / 2, 60);

    return 0;
}
