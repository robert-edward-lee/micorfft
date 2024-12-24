#include "mf/fft.hpp"

#if defined(_MSC_VER)
#define EXPORT_DLL_C extern "C" __declspec(dllexport)
#else
#define EXPORT_DLL_C extern "C"
#endif

using namespace mf;

////////////////////////////////////////////////////////////////////////////////
//                                FLOAT32 CFFT                                //
////////////////////////////////////////////////////////////////////////////////
EXPORT_DLL_C void cfft_forward_16_f32(float32_t *p) {
    Cfft<float32_t, 16> cfft;
    cfft.forward(p);
}

EXPORT_DLL_C void cfft_forward_32_f32(float32_t *p) {
    Cfft<float32_t, 32> cfft;
    cfft.forward(p);
}

EXPORT_DLL_C void cfft_forward_64_f32(float32_t *p) {
    Cfft<float32_t, 64> cfft;
    cfft.forward(p);
}

EXPORT_DLL_C void cfft_forward_128_f32(float32_t *p) {
    Cfft<float32_t, 128> cfft;
    cfft.forward(p);
}

EXPORT_DLL_C void cfft_forward_256_f32(float32_t *p) {
    Cfft<float32_t, 256> cfft;
    cfft.forward(p);
}

EXPORT_DLL_C void cfft_forward_512_f32(float32_t *p) {
    Cfft<float32_t, 512> cfft;
    cfft.forward(p);
}

EXPORT_DLL_C void cfft_forward_1024_f32(float32_t *p) {
    Cfft<float32_t, 1024> cfft;
    cfft.forward(p);
}

EXPORT_DLL_C void cfft_forward_2048_f32(float32_t *p) {
    Cfft<float32_t, 2048> cfft;
    cfft.forward(p);
}

EXPORT_DLL_C void cfft_forward_4096_f32(float32_t *p) {
    Cfft<float32_t, 4096> cfft;
    cfft.forward(p);
}

EXPORT_DLL_C void cfft_inverse_16_f32(float32_t *p) {
    Cfft<float32_t, 16> cfft;
    cfft.inverse(p);
}

EXPORT_DLL_C void cfft_inverse_32_f32(float32_t *p) {
    Cfft<float32_t, 32> cfft;
    cfft.inverse(p);
}

EXPORT_DLL_C void cfft_inverse_64_f32(float32_t *p) {
    Cfft<float32_t, 64> cfft;
    cfft.inverse(p);
}

EXPORT_DLL_C void cfft_inverse_128_f32(float32_t *p) {
    Cfft<float32_t, 128> cfft;
    cfft.inverse(p);
}

EXPORT_DLL_C void cfft_inverse_256_f32(float32_t *p) {
    Cfft<float32_t, 256> cfft;
    cfft.inverse(p);
}

EXPORT_DLL_C void cfft_inverse_512_f32(float32_t *p) {
    Cfft<float32_t, 512> cfft;
    cfft.inverse(p);
}

EXPORT_DLL_C void cfft_inverse_1024_f32(float32_t *p) {
    Cfft<float32_t, 1024> cfft;
    cfft.inverse(p);
}

EXPORT_DLL_C void cfft_inverse_2048_f32(float32_t *p) {
    Cfft<float32_t, 2048> cfft;
    cfft.inverse(p);
}

EXPORT_DLL_C void cfft_inverse_4096_f32(float32_t *p) {
    Cfft<float32_t, 4096> cfft;
    cfft.inverse(p);
}

////////////////////////////////////////////////////////////////////////////////
//                                FLOAT32 RFFT                                //
////////////////////////////////////////////////////////////////////////////////
EXPORT_DLL_C void rfft_forward_32_f32(float32_t *pIn, float32_t *pOut) {
    Rfft<float32_t, 32> rfft;
    rfft.forward(pIn, pOut);
}

EXPORT_DLL_C void rfft_forward_64_f32(float32_t *pIn, float32_t *pOut) {
    Rfft<float32_t, 64> rfft;
    rfft.forward(pIn, pOut);
}

EXPORT_DLL_C void rfft_forward_128_f32(float32_t *pIn, float32_t *pOut) {
    Rfft<float32_t, 128> rfft;
    rfft.forward(pIn, pOut);
}

EXPORT_DLL_C void rfft_forward_256_f32(float32_t *pIn, float32_t *pOut) {
    Rfft<float32_t, 256> rfft;
    rfft.forward(pIn, pOut);
}

EXPORT_DLL_C void rfft_forward_512_f32(float32_t *pIn, float32_t *pOut) {
    Rfft<float32_t, 512> rfft;
    rfft.forward(pIn, pOut);
}

EXPORT_DLL_C void rfft_forward_1024_f32(float32_t *pIn, float32_t *pOut) {
    Rfft<float32_t, 1024> rfft;
    rfft.forward(pIn, pOut);
}

EXPORT_DLL_C void rfft_forward_2048_f32(float32_t *pIn, float32_t *pOut) {
    Rfft<float32_t, 2048> rfft;
    rfft.forward(pIn, pOut);
}

EXPORT_DLL_C void rfft_forward_4096_f32(float32_t *pIn, float32_t *pOut) {
    Rfft<float32_t, 4096> rfft;
    rfft.forward(pIn, pOut);
}

EXPORT_DLL_C void rfft_forward_8192_f32(float32_t *pIn, float32_t *pOut) {
    Rfft<float32_t, 8192> rfft;
    rfft.forward(pIn, pOut);
}

EXPORT_DLL_C void rfft_inverse_32_f32(float32_t *pIn, float32_t *pOut) {
    Rfft<float32_t, 32> rfft;
    rfft.inverse(pIn, pOut);
}

EXPORT_DLL_C void rfft_inverse_64_f32(float32_t *pIn, float32_t *pOut) {
    Rfft<float32_t, 64> rfft;
    rfft.inverse(pIn, pOut);
}

EXPORT_DLL_C void rfft_inverse_128_f32(float32_t *pIn, float32_t *pOut) {
    Rfft<float32_t, 128> rfft;
    rfft.inverse(pIn, pOut);
}

EXPORT_DLL_C void rfft_inverse_256_f32(float32_t *pIn, float32_t *pOut) {
    Rfft<float32_t, 256> rfft;
    rfft.inverse(pIn, pOut);
}

EXPORT_DLL_C void rfft_inverse_512_f32(float32_t *pIn, float32_t *pOut) {
    Rfft<float32_t, 512> rfft;
    rfft.inverse(pIn, pOut);
}

EXPORT_DLL_C void rfft_inverse_1024_f32(float32_t *pIn, float32_t *pOut) {
    Rfft<float32_t, 1024> rfft;
    rfft.inverse(pIn, pOut);
}

EXPORT_DLL_C void rfft_inverse_2048_f32(float32_t *pIn, float32_t *pOut) {
    Rfft<float32_t, 2048> rfft;
    rfft.inverse(pIn, pOut);
}

EXPORT_DLL_C void rfft_inverse_4096_f32(float32_t *pIn, float32_t *pOut) {
    Rfft<float32_t, 4096> rfft;
    rfft.inverse(pIn, pOut);
}

EXPORT_DLL_C void rfft_inverse_8192_f32(float32_t *pIn, float32_t *pOut) {
    Rfft<float32_t, 8192> rfft;
    rfft.inverse(pIn, pOut);
}

////////////////////////////////////////////////////////////////////////////////
//                                FLOAT32 CFFT                                //
////////////////////////////////////////////////////////////////////////////////
EXPORT_DLL_C void cfft_forward_16_f64(float64_t *p) {
    Cfft<float64_t, 16> cfft;
    cfft.forward(p);
}

EXPORT_DLL_C void cfft_forward_32_f64(float64_t *p) {
    Cfft<float64_t, 32> cfft;
    cfft.forward(p);
}

EXPORT_DLL_C void cfft_forward_64_f64(float64_t *p) {
    Cfft<float64_t, 64> cfft;
    cfft.forward(p);
}

EXPORT_DLL_C void cfft_forward_128_f64(float64_t *p) {
    Cfft<float64_t, 128> cfft;
    cfft.forward(p);
}

EXPORT_DLL_C void cfft_forward_256_f64(float64_t *p) {
    Cfft<float64_t, 256> cfft;
    cfft.forward(p);
}

EXPORT_DLL_C void cfft_forward_512_f64(float64_t *p) {
    Cfft<float64_t, 512> cfft;
    cfft.forward(p);
}

EXPORT_DLL_C void cfft_forward_1024_f64(float64_t *p) {
    Cfft<float64_t, 1024> cfft;
    cfft.forward(p);
}

EXPORT_DLL_C void cfft_forward_2048_f64(float64_t *p) {
    Cfft<float64_t, 2048> cfft;
    cfft.forward(p);
}

EXPORT_DLL_C void cfft_forward_4096_f64(float64_t *p) {
    Cfft<float64_t, 4096> cfft;
    cfft.forward(p);
}

EXPORT_DLL_C void cfft_inverse_16_f64(float64_t *p) {
    Cfft<float64_t, 16> cfft;
    cfft.inverse(p);
}

EXPORT_DLL_C void cfft_inverse_32_f64(float64_t *p) {
    Cfft<float64_t, 32> cfft;
    cfft.inverse(p);
}

EXPORT_DLL_C void cfft_inverse_64_f64(float64_t *p) {
    Cfft<float64_t, 64> cfft;
    cfft.inverse(p);
}

EXPORT_DLL_C void cfft_inverse_128_f64(float64_t *p) {
    Cfft<float64_t, 128> cfft;
    cfft.inverse(p);
}

EXPORT_DLL_C void cfft_inverse_256_f64(float64_t *p) {
    Cfft<float64_t, 256> cfft;
    cfft.inverse(p);
}

EXPORT_DLL_C void cfft_inverse_512_f64(float64_t *p) {
    Cfft<float64_t, 512> cfft;
    cfft.inverse(p);
}

EXPORT_DLL_C void cfft_inverse_1024_f64(float64_t *p) {
    Cfft<float64_t, 1024> cfft;
    cfft.inverse(p);
}

EXPORT_DLL_C void cfft_inverse_2048_f64(float64_t *p) {
    Cfft<float64_t, 2048> cfft;
    cfft.inverse(p);
}

EXPORT_DLL_C void cfft_inverse_4096_f64(float64_t *p) {
    Cfft<float64_t, 4096> cfft;
    cfft.inverse(p);
}

////////////////////////////////////////////////////////////////////////////////
//                                FLOAT64 RFFT                                //
////////////////////////////////////////////////////////////////////////////////
EXPORT_DLL_C void rfft_forward_32_f64(float64_t *pIn, float64_t *pOut) {
    Rfft<float64_t, 32> rfft;
    rfft.forward(pIn, pOut);
}

EXPORT_DLL_C void rfft_forward_64_f64(float64_t *pIn, float64_t *pOut) {
    Rfft<float64_t, 64> rfft;
    rfft.forward(pIn, pOut);
}

EXPORT_DLL_C void rfft_forward_128_f64(float64_t *pIn, float64_t *pOut) {
    Rfft<float64_t, 128> rfft;
    rfft.forward(pIn, pOut);
}

EXPORT_DLL_C void rfft_forward_256_f64(float64_t *pIn, float64_t *pOut) {
    Rfft<float64_t, 256> rfft;
    rfft.forward(pIn, pOut);
}

EXPORT_DLL_C void rfft_forward_512_f64(float64_t *pIn, float64_t *pOut) {
    Rfft<float64_t, 512> rfft;
    rfft.forward(pIn, pOut);
}

EXPORT_DLL_C void rfft_forward_1024_f64(float64_t *pIn, float64_t *pOut) {
    Rfft<float64_t, 1024> rfft;
    rfft.forward(pIn, pOut);
}

EXPORT_DLL_C void rfft_forward_2048_f64(float64_t *pIn, float64_t *pOut) {
    Rfft<float64_t, 2048> rfft;
    rfft.forward(pIn, pOut);
}

EXPORT_DLL_C void rfft_forward_4096_f64(float64_t *pIn, float64_t *pOut) {
    Rfft<float64_t, 4096> rfft;
    rfft.forward(pIn, pOut);
}

EXPORT_DLL_C void rfft_forward_8192_f64(float64_t *pIn, float64_t *pOut) {
    Rfft<float64_t, 8192> rfft;
    rfft.forward(pIn, pOut);
}

EXPORT_DLL_C void rfft_inverse_32_f64(float64_t *pIn, float64_t *pOut) {
    Rfft<float64_t, 32> rfft;
    rfft.inverse(pIn, pOut);
}

EXPORT_DLL_C void rfft_inverse_64_f64(float64_t *pIn, float64_t *pOut) {
    Rfft<float64_t, 64> rfft;
    rfft.inverse(pIn, pOut);
}

EXPORT_DLL_C void rfft_inverse_128_f64(float64_t *pIn, float64_t *pOut) {
    Rfft<float64_t, 128> rfft;
    rfft.inverse(pIn, pOut);
}

EXPORT_DLL_C void rfft_inverse_256_f64(float64_t *pIn, float64_t *pOut) {
    Rfft<float64_t, 256> rfft;
    rfft.inverse(pIn, pOut);
}

EXPORT_DLL_C void rfft_inverse_512_f64(float64_t *pIn, float64_t *pOut) {
    Rfft<float64_t, 512> rfft;
    rfft.inverse(pIn, pOut);
}

EXPORT_DLL_C void rfft_inverse_1024_f64(float64_t *pIn, float64_t *pOut) {
    Rfft<float64_t, 1024> rfft;
    rfft.inverse(pIn, pOut);
}

EXPORT_DLL_C void rfft_inverse_2048_f64(float64_t *pIn, float64_t *pOut) {
    Rfft<float64_t, 2048> rfft;
    rfft.inverse(pIn, pOut);
}

EXPORT_DLL_C void rfft_inverse_4096_f64(float64_t *pIn, float64_t *pOut) {
    Rfft<float64_t, 4096> rfft;
    rfft.inverse(pIn, pOut);
}

EXPORT_DLL_C void rfft_inverse_8192_f64(float64_t *pIn, float64_t *pOut) {
    Rfft<float64_t, 8192> rfft;
    rfft.inverse(pIn, pOut);
}
