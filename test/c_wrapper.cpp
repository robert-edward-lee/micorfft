#include "mf/fft.hpp"

using namespace mf;

////////////////////////////////////////////////////////////////////////////////
//                                FLOAT32 RFFT                                //
////////////////////////////////////////////////////////////////////////////////
extern "C" void rfft_forward_32_f32(float32_t *pIn, float32_t *pOut) {
    Rfft<float32_t, uint16_t, 32> rfft;
    rfft.forward(pIn, pOut);
}

extern "C" void rfft_forward_64_f32(float32_t *pIn, float32_t *pOut) {
    Rfft<float32_t, uint16_t, 64> rfft;
    rfft.forward(pIn, pOut);
}

extern "C" void rfft_forward_128_f32(float32_t *pIn, float32_t *pOut) {
    Rfft<float32_t, uint16_t, 128> rfft;
    rfft.forward(pIn, pOut);
}

extern "C" void rfft_forward_256_f32(float32_t *pIn, float32_t *pOut) {
    Rfft<float32_t, uint16_t, 256> rfft;
    rfft.forward(pIn, pOut);
}

extern "C" void rfft_forward_512_f32(float32_t *pIn, float32_t *pOut) {
    Rfft<float32_t, uint16_t, 512> rfft;
    rfft.forward(pIn, pOut);
}

extern "C" void rfft_forward_1024_f32(float32_t *pIn, float32_t *pOut) {
    Rfft<float32_t, uint16_t, 1024> rfft;
    rfft.forward(pIn, pOut);
}

extern "C" void rfft_forward_2048_f32(float32_t *pIn, float32_t *pOut) {
    Rfft<float32_t, uint16_t, 2048> rfft;
    rfft.forward(pIn, pOut);
}

extern "C" void rfft_forward_4096_f32(float32_t *pIn, float32_t *pOut) {
    Rfft<float32_t, uint16_t, 4096> rfft;
    rfft.forward(pIn, pOut);
}

extern "C" void rfft_inverse_32_f32(float32_t *pIn, float32_t *pOut) {
    Rfft<float32_t, uint16_t, 32> rfft;
    rfft.inverse(pIn, pOut);
}

extern "C" void rfft_inverse_64_f32(float32_t *pIn, float32_t *pOut) {
    Rfft<float32_t, uint16_t, 64> rfft;
    rfft.inverse(pIn, pOut);
}

extern "C" void rfft_inverse_128_f32(float32_t *pIn, float32_t *pOut) {
    Rfft<float32_t, uint16_t, 128> rfft;
    rfft.inverse(pIn, pOut);
}

extern "C" void rfft_inverse_256_f32(float32_t *pIn, float32_t *pOut) {
    Rfft<float32_t, uint16_t, 256> rfft;
    rfft.inverse(pIn, pOut);
}

extern "C" void rfft_inverse_512_f32(float32_t *pIn, float32_t *pOut) {
    Rfft<float32_t, uint16_t, 512> rfft;
    rfft.inverse(pIn, pOut);
}

extern "C" void rfft_inverse_1024_f32(float32_t *pIn, float32_t *pOut) {
    Rfft<float32_t, uint16_t, 1024> rfft;
    rfft.inverse(pIn, pOut);
}

extern "C" void rfft_inverse_2048_f32(float32_t *pIn, float32_t *pOut) {
    Rfft<float32_t, uint16_t, 2048> rfft;
    rfft.inverse(pIn, pOut);
}

extern "C" void rfft_inverse_4096_f32(float32_t *pIn, float32_t *pOut) {
    Rfft<float32_t, uint16_t, 4096> rfft;
    rfft.inverse(pIn, pOut);
}

////////////////////////////////////////////////////////////////////////////////
//                                FLOAT64 RFFT                                //
////////////////////////////////////////////////////////////////////////////////
extern "C" void rfft_forward_32_f64(float64_t *pIn, float64_t *pOut) {
    Rfft<float64_t, uint16_t, 32> rfft;
    rfft.forward(pIn, pOut);
}

extern "C" void rfft_forward_64_f64(float64_t *pIn, float64_t *pOut) {
    Rfft<float64_t, uint16_t, 64> rfft;
    rfft.forward(pIn, pOut);
}

extern "C" void rfft_forward_128_f64(float64_t *pIn, float64_t *pOut) {
    Rfft<float64_t, uint16_t, 128> rfft;
    rfft.forward(pIn, pOut);
}

extern "C" void rfft_forward_256_f64(float64_t *pIn, float64_t *pOut) {
    Rfft<float64_t, uint16_t, 256> rfft;
    rfft.forward(pIn, pOut);
}

extern "C" void rfft_forward_512_f64(float64_t *pIn, float64_t *pOut) {
    Rfft<float64_t, uint16_t, 512> rfft;
    rfft.forward(pIn, pOut);
}

extern "C" void rfft_forward_1024_f64(float64_t *pIn, float64_t *pOut) {
    Rfft<float64_t, uint16_t, 1024> rfft;
    rfft.forward(pIn, pOut);
}

extern "C" void rfft_forward_2048_f64(float64_t *pIn, float64_t *pOut) {
    Rfft<float64_t, uint16_t, 2048> rfft;
    rfft.forward(pIn, pOut);
}

extern "C" void rfft_forward_4096_f64(float64_t *pIn, float64_t *pOut) {
    Rfft<float64_t, uint16_t, 4096> rfft;
    rfft.forward(pIn, pOut);
}

extern "C" void rfft_inverse_32_f64(float64_t *pIn, float64_t *pOut) {
    Rfft<float64_t, uint16_t, 32> rfft;
    rfft.inverse(pIn, pOut);
}

extern "C" void rfft_inverse_64_f64(float64_t *pIn, float64_t *pOut) {
    Rfft<float64_t, uint16_t, 64> rfft;
    rfft.inverse(pIn, pOut);
}

extern "C" void rfft_inverse_128_f64(float64_t *pIn, float64_t *pOut) {
    Rfft<float64_t, uint16_t, 128> rfft;
    rfft.inverse(pIn, pOut);
}

extern "C" void rfft_inverse_256_f64(float64_t *pIn, float64_t *pOut) {
    Rfft<float64_t, uint16_t, 256> rfft;
    rfft.inverse(pIn, pOut);
}

extern "C" void rfft_inverse_512_f64(float64_t *pIn, float64_t *pOut) {
    Rfft<float64_t, uint16_t, 512> rfft;
    rfft.inverse(pIn, pOut);
}

extern "C" void rfft_inverse_1024_f64(float64_t *pIn, float64_t *pOut) {
    Rfft<float64_t, uint16_t, 1024> rfft;
    rfft.inverse(pIn, pOut);
}

extern "C" void rfft_inverse_2048_f64(float64_t *pIn, float64_t *pOut) {
    Rfft<float64_t, uint16_t, 2048> rfft;
    rfft.inverse(pIn, pOut);
}

extern "C" void rfft_inverse_4096_f64(float64_t *pIn, float64_t *pOut) {
    Rfft<float64_t, uint16_t, 4096> rfft;
    rfft.inverse(pIn, pOut);
}
