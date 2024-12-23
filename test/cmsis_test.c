#include <stdint.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include "config.h"
#include "dsp/transform_functions.h"
#include "print_hist.h"

arm_rfft_fast_instance_f32 rfft_inst;
arm_cfft_instance_f32 cfft_inst;

#define DO_TRICONCAT(a, b, c) a##b##c
#define TRICONCAT(a, b, c) DO_TRICONCAT(a, b, c)
#define ARM_CFFT_FN(w) TRICONCAT(arm_cfft_init_, w, _f32)
extern void print_f32(const float *p, size_t size);
int main(void) {
    int i;

    TEST_FLOAT_T signal_t[TEST_N];
    TEST_FLOAT_T signal_f[2 * TEST_N];
    TEST_FLOAT_T mag[TEST_N];

    TEST_FLOAT_T csignal[TEST_N * 2];
    TEST_FLOAT_T cmag[TEST_N];

    for(i = 0; i < TEST_N; ++i) {
        signal_t[i] = 2 + sin(i * 2 * M_PI * TEST_F / TEST_N);
        signal_t[i] += sin(i * 2 * M_PI * TEST_F1 / TEST_N);

        csignal[2 * i] = signal_t[i];
        csignal[2 * i + 1] = 0;
    }
    // print_hist_horiz(signal_t, TEST_N, 60);

    /* rfft */
    arm_rfft_fast_init_f32(&rfft_inst, TEST_N);
    arm_rfft_fast_f32(&rfft_inst, signal_t, signal_f, TEST_INVERSE);

    for(i = 0; i < TEST_N / 2; ++i) {
        mag[i] = sqrt(signal_f[2 * i] * signal_f[2 * i] + signal_f[2 * i + 1] * signal_f[2 * i + 1]);
    }
    printf("rfft(%d):\n", TEST_N);
    print_hist_horiz(mag, TEST_N / 2, 60);

    /* cfft */
    ARM_CFFT_FN(TEST_N)(&cfft_inst);
    arm_cfft_f32(&cfft_inst, csignal, TEST_INVERSE, 1);

    for(i = 0; i < TEST_N; ++i) {
        cmag[i] = sqrt(csignal[2 * i] * csignal[2 * i] + csignal[2 * i + 1] * csignal[2 * i + 1]);
    }
    printf("cfft(%d):\n", TEST_N);
    print_hist_horiz(cmag, TEST_N, 60);

    return 0;
}
