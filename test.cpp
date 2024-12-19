#include "mf/fft.hpp"
#include "mf/radix8.hpp"
#include "mf/twiddle.hpp"

using namespace mf;

int main(void) {
    // Transposition<unsigned short, 32, 8> t;
    Rfft<float32_t, uint16_t, 32> rfft;

    rfft.forward();

    // float w[512];
    // fill_twiddle_coeff(w);
    // print_twiddle_coeff(rfft.TwiddleCfft);
    // print_rfft_twiddle_coeff(rfft.TwiddleRfft);
    // print_bit_rev_index_table(rfft.pBitRevTable, rfft.bitRevLength);

    return 0;
}
