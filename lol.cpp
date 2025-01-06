#include "mf/windows.hpp"

using namespace mf;

#define SIZE 31
double win[SIZE];

void chebyshev_31_float64_t(void *p, double alpha) {
    Windows<float64_t, 31>::chebyshev(*(float64_t (*)[31])p, alpha);
}

int main(void) {
    mf::Windows<double, SIZE>::chebyshev(win, 40);

    // chebyshev_31_float64_t(win, 40);

    return 0;
}
