#ifndef HPP_MF_COMPLEX
#define HPP_MF_COMPLEX

#include "mf/config.hpp"
#include "mf/types/integral.hpp"

#define CUSTOM_COMPLEX 1
#if CUSTOM_COMPLEX
#include <sstream>
namespace mf {
template<typename T> class Complex {
public:
    /* ctors */
    MF_CONSTEXPR Complex(T x = T(0), T y = T(0)) MF_NOEXCEPT: re(x), im(y) {}
    MF_CONSTEXPR_14 Complex &operator=(const T &rhs) MF_NOEXCEPT {
        re = rhs;
        im = 0;
        return *this;
    }
    static MF_CONSTEXPR Complex polar(const T &mag, const T &phase) MF_NOEXCEPT {
        return Complex(mag * cos(phase), mag * sin(phase));
    }
    /* getters/setters */
    MF_CONSTEXPR_14 T real() const MF_NOEXCEPT {
        return re;
    }
    MF_CONSTEXPR_14 T &real() MF_NOEXCEPT {
        return re;
    }
    MF_CONSTEXPR_14 T imag() const MF_NOEXCEPT {
        return im;
    }
    MF_CONSTEXPR_14 T &imag() MF_NOEXCEPT {
        return im;
    }
    MF_CONSTEXPR Complex conj() const MF_NOEXCEPT {
        return Complex(re, -im);
    }
    MF_CONSTEXPR T mag_sqr() const MF_NOEXCEPT {
        return re * re + im * im;
    }
    MF_CONSTEXPR T mag() const MF_NOEXCEPT {
        return sqrt(mag_sqr());
    }
    MF_CONSTEXPR T phase() const MF_NOEXCEPT {
        return atan2(im, re);
    }
    /*  */
    MF_CONSTEXPR bool operator==(const Complex &rhs) const MF_NOEXCEPT {
        return re == rhs.re && im == rhs.im;
    }
    MF_CONSTEXPR bool operator==(const T &rhs) const MF_NOEXCEPT {
        return re == rhs && im == 0;
    }
    MF_CONSTEXPR bool operator!=(const Complex &rhs) const MF_NOEXCEPT {
        return re != rhs.re || im != rhs.im;
    }
    MF_CONSTEXPR bool operator!=(const T &rhs) const MF_NOEXCEPT {
        return re != rhs || im != 0;
    }
    /* arithmetic */
    MF_CONSTEXPR_14 Complex &operator+=(const Complex &rhs) MF_NOEXCEPT {
        re += rhs.re;
        im += rhs.im;
        return *this;
    }
    MF_CONSTEXPR_14 Complex &operator+=(const T &rhs) MF_NOEXCEPT {
        re += rhs;
        return *this;
    }
    MF_CONSTEXPR Complex operator+(const Complex &rhs) const MF_NOEXCEPT {
        return Complex(re + rhs.re, im + rhs.im);
    }
    MF_CONSTEXPR Complex operator+(const T &rhs) const MF_NOEXCEPT {
        return Complex(re + rhs, im);
    }
    MF_CONSTEXPR Complex operator+() const MF_NOEXCEPT {
        return *this;
    }

    MF_CONSTEXPR_14 Complex &operator-=(const Complex &rhs) MF_NOEXCEPT {
        re -= rhs.re;
        im -= rhs.im;
        return *this;
    }
    MF_CONSTEXPR_14 Complex &operator-=(const T &rhs) MF_NOEXCEPT {
        re -= rhs;
        return *this;
    }
    MF_CONSTEXPR Complex operator-(const Complex &rhs) const MF_NOEXCEPT {
        return Complex(re - rhs.re, im - rhs.im);
    }
    MF_CONSTEXPR Complex operator-(const T &rhs) const MF_NOEXCEPT {
        return Complex(re - rhs, im);
    }
    MF_CONSTEXPR Complex operator-() const MF_NOEXCEPT {
        return Complex(-re, -im);
    }

    MF_CONSTEXPR_14 Complex &operator*=(const Complex &rhs) MF_NOEXCEPT {
        const T tmp = re * rhs.im + im * rhs.re;
        re = re * rhs.re - im * rhs.im;
        im = tmp;
        return *this;
    }
    MF_CONSTEXPR_14 Complex &operator*=(const T &rhs) MF_NOEXCEPT {
        re *= rhs;
        im *= rhs;
        return *this;
    }
    MF_CONSTEXPR_14 Complex operator*(const Complex &rhs) const MF_NOEXCEPT {
        const T tmp = re * rhs.im + im * rhs.re;
        return Complex(re * rhs.re - im * rhs.im, tmp);
    }
    MF_CONSTEXPR Complex operator*(const T &rhs) const MF_NOEXCEPT {
        return Complex(re * rhs, im * rhs);
    }

    MF_CONSTEXPR_14 Complex &operator/=(const T &rhs) MF_NOEXCEPT {
        re /= rhs;
        im /= rhs;
        return *this;
    }
    MF_CONSTEXPR_14 Complex &operator/=(const Complex &rhs) MF_NOEXCEPT {
        *this *= rhs.conj();
        *this /= rhs.mag_sqr();
        return *this;
    }
    MF_CONSTEXPR_14 Complex operator/(const Complex &rhs) MF_NOEXCEPT {
        Complex tmp(*this);
        tmp /= rhs;
        return tmp;
    }
    MF_CONSTEXPR Complex operator/(const T &rhs) const MF_NOEXCEPT {
        return Complex(re / rhs, im / rhs);
    }

private:
    T re;
    T im;
};

template<class T, class CharT, class Traits>
std::basic_ostream<CharT, Traits> &operator<<(std::basic_ostream<CharT, Traits> &o, const Complex<T> &x) {
    std::basic_ostringstream<CharT, Traits> s;
    s.flags(o.flags());
    s.imbue(o.getloc());
    s.precision(o.precision());
    s << "(" << x.real() << (x.imag() < 0 ? " - j" : " + j") << abs(x.imag()) << ")";
    return o << s.str();
}
} // namespace mf
#else
#include <complex>
namespace mf {
template<typename T> class Complex: public std::complex<T> {
public:
    MF_CONSTEXPR_14 Complex(const T &x, const T &y) MF_NOEXCEPT: std::complex<T>(x, y) {}
    MF_CONSTEXPR_14 Complex(const std::complex<T> &other) MF_NOEXCEPT: std::complex<T>(other) {}
    static MF_CONSTEXPR Complex polar(const T &mag, const T &phase) MF_NOEXCEPT {
        return std::polar(mag, phase);
    }
};
} // namespace mf
#endif

namespace mf {
template<typename DataType, size_t Size>
MF_OPTIMIZE(3) MF_CONSTEXPR_14 void magnitude_sqr(const DataType (&src)[Size * 2], DataType (&dst)[Size]) {
    typedef typename uint_fast<typename idx_type_chooser<Size>::type>::type idx_t;

    MF_CONST_OR_CONSTEXPR idx_t BLK_SIZE = 4;
    MF_CONST_OR_CONSTEXPR idx_t BLKS = Size / BLK_SIZE;
    MF_CONST_OR_CONSTEXPR idx_t RESIDUE = Size % BLK_SIZE;

    for(idx_t i = 0; i != BLKS; ++i) {
        dst[4 * i + 0] = src[8 * i + 0] * src[8 * i + 0] + src[8 * i + 1] * src[8 * i + 1];
        dst[4 * i + 1] = src[8 * i + 2] * src[8 * i + 2] + src[8 * i + 3] * src[8 * i + 3];
        dst[4 * i + 2] = src[8 * i + 4] * src[8 * i + 4] + src[8 * i + 5] * src[8 * i + 5];
        dst[4 * i + 3] = src[8 * i + 6] * src[8 * i + 6] + src[8 * i + 7] * src[8 * i + 7];
    }

    MF_IF_CONSTEXPR(RESIDUE != 0) {
        for(idx_t i = BLKS * BLK_SIZE; i != Size; ++i) {
            dst[i] = src[2 * i] * src[2 * i] + src[2 * i + 1] * src[2 * i + 1];
        }
    }
}

template<typename DataType, size_t Size>
MF_OPTIMIZE(3) MF_CONSTEXPR_14 void magnitude_sqr(const Complex<DataType> (&csrc)[Size], DataType (&dst)[Size]) {
    typedef typename uint_fast<typename idx_type_chooser<Size>::type>::type idx_t;

    MF_CONST_OR_CONSTEXPR idx_t BLK_SIZE = 4;
    MF_CONST_OR_CONSTEXPR idx_t BLKS = Size / BLK_SIZE;
    MF_CONST_OR_CONSTEXPR idx_t RESIDUE = Size % BLK_SIZE;

    const DataType(&src)[Size * 2] = (const DataType(&)[Size * 2]) csrc;
    for(idx_t i = 0; i != BLKS; ++i) {
        dst[4 * i + 0] = src[8 * i + 0] * src[8 * i + 0] + src[8 * i + 1] * src[8 * i + 1];
        dst[4 * i + 1] = src[8 * i + 2] * src[8 * i + 2] + src[8 * i + 3] * src[8 * i + 3];
        dst[4 * i + 2] = src[8 * i + 4] * src[8 * i + 4] + src[8 * i + 5] * src[8 * i + 5];
        dst[4 * i + 3] = src[8 * i + 6] * src[8 * i + 6] + src[8 * i + 7] * src[8 * i + 7];
    }

    MF_IF_CONSTEXPR(RESIDUE != 0) {
        for(idx_t i = BLKS * BLK_SIZE; i != Size; ++i) {
            dst[i] = src[2 * i] * src[2 * i] + src[2 * i + 1] * src[2 * i + 1];
        }
    }
}

template<typename DataType, size_t Size> MF_OPTIMIZE(3) MF_CONSTEXPR_14 void conjugate(DataType (&data)[Size * 2]) {
    typedef typename uint_fast<typename idx_type_chooser<Size>::type>::type idx_t;

    MF_CONST_OR_CONSTEXPR idx_t BLK_SIZE = 4;
    MF_CONST_OR_CONSTEXPR idx_t BLKS = Size / BLK_SIZE;
    MF_CONST_OR_CONSTEXPR idx_t RESIDUE = Size % BLK_SIZE;

    for(idx_t i = 0; i != BLKS; ++i) {
        data[8 * i + 1] = -data[8 * i + 1];
        data[8 * i + 3] = -data[8 * i + 3];
        data[8 * i + 5] = -data[8 * i + 5];
        data[8 * i + 7] = -data[8 * i + 7];
    }

    MF_IF_CONSTEXPR(RESIDUE != 0) {
        for(idx_t i = BLKS * BLK_SIZE; i != Size; ++i) {
            data[2 * i + 1] = -data[2 * i + 1];
        }
    }
}

template<typename DataType, size_t Size>
MF_OPTIMIZE(3) MF_CONSTEXPR_14 void conjugate(Complex<DataType> (&cdata)[Size]) {
    typedef typename uint_fast<typename idx_type_chooser<Size>::type>::type idx_t;

    MF_CONST_OR_CONSTEXPR idx_t BLK_SIZE = 4;
    MF_CONST_OR_CONSTEXPR idx_t BLKS = Size / BLK_SIZE;
    MF_CONST_OR_CONSTEXPR idx_t RESIDUE = Size % BLK_SIZE;

    DataType(&data)[Size * 2] = (DataType(&)[Size * 2]) cdata;
    for(idx_t i = 0; i != BLKS; ++i) {
        data[8 * i + 1] = -data[8 * i + 1];
        data[8 * i + 3] = -data[8 * i + 3];
        data[8 * i + 5] = -data[8 * i + 5];
        data[8 * i + 7] = -data[8 * i + 7];
    }

    MF_IF_CONSTEXPR(RESIDUE != 0) {
        for(idx_t i = BLKS * BLK_SIZE; i != Size; ++i) {
            data[2 * i + 1] = -data[2 * i + 1];
        }
    }
}

template<typename DataType, size_t Size, bool Inverse>
MF_OPTIMIZE(3) MF_CONSTEXPR_14 void scale(DataType (&data)[Size * 2], DataType factor) {
    typedef typename uint_fast<typename idx_type_chooser<Size>::type>::type idx_t;

    MF_CONST_OR_CONSTEXPR idx_t BLK_SIZE = 4;
    MF_CONST_OR_CONSTEXPR idx_t BLKS = Size / BLK_SIZE;
    MF_CONST_OR_CONSTEXPR idx_t RESIDUE = Size % BLK_SIZE;

    MF_IF_CONSTEXPR(Inverse) {
        for(idx_t i = 0; i != BLKS; ++i) {
            data[8 * i + 0] = factor * data[8 * i + 0];
            data[8 * i + 1] = factor * -data[8 * i + 1];
            data[8 * i + 2] = factor * data[8 * i + 2];
            data[8 * i + 3] = factor * -data[8 * i + 3];
            data[8 * i + 4] = factor * data[8 * i + 4];
            data[8 * i + 5] = factor * -data[8 * i + 5];
            data[8 * i + 6] = factor * data[8 * i + 6];
            data[8 * i + 7] = factor * -data[8 * i + 7];
        }
    } else {
        for(idx_t i = 0; i != BLKS; ++i) {
            data[8 * i + 0] = factor * data[8 * i + 0];
            data[8 * i + 1] = factor * data[8 * i + 1];
            data[8 * i + 2] = factor * data[8 * i + 2];
            data[8 * i + 3] = factor * data[8 * i + 3];
            data[8 * i + 4] = factor * data[8 * i + 4];
            data[8 * i + 5] = factor * data[8 * i + 5];
            data[8 * i + 6] = factor * data[8 * i + 6];
            data[8 * i + 7] = factor * data[8 * i + 7];
        }
    }

    MF_IF_CONSTEXPR(Inverse) {
        MF_IF_CONSTEXPR(RESIDUE != 0) {
            for(idx_t i = BLKS * BLK_SIZE; i != Size; ++i) {
                data[2 * i + 0] = factor * data[2 * i + 0];
                data[2 * i + 1] = factor * -data[2 * i + 1];
            }
        }
    } else {
        MF_IF_CONSTEXPR(RESIDUE != 0) {
            for(idx_t i = BLKS * BLK_SIZE; i != Size; ++i) {
                data[2 * i + 0] = factor * data[2 * i + 0];
                data[2 * i + 1] = factor * data[2 * i + 1];
            }
        }
    }
}

template<typename DataType, size_t Size, bool Inverse>
MF_OPTIMIZE(3) MF_CONSTEXPR_14 void scale(Complex<DataType> (&cdata)[Size], DataType factor) {
    typedef typename uint_fast<typename idx_type_chooser<Size>::type>::type idx_t;

    MF_CONST_OR_CONSTEXPR idx_t BLK_SIZE = 4;
    MF_CONST_OR_CONSTEXPR idx_t BLKS = Size / BLK_SIZE;
    MF_CONST_OR_CONSTEXPR idx_t RESIDUE = Size % BLK_SIZE;

    DataType(&data)[Size * 2] = (DataType(&)[Size * 2]) cdata;
    MF_IF_CONSTEXPR(Inverse) {
        for(idx_t i = 0; i != BLKS; ++i) {
            data[8 * i + 0] = factor * data[8 * i + 0];
            data[8 * i + 1] = factor * -data[8 * i + 1];
            data[8 * i + 2] = factor * data[8 * i + 2];
            data[8 * i + 3] = factor * -data[8 * i + 3];
            data[8 * i + 4] = factor * data[8 * i + 4];
            data[8 * i + 5] = factor * -data[8 * i + 5];
            data[8 * i + 6] = factor * data[8 * i + 6];
            data[8 * i + 7] = factor * -data[8 * i + 7];
        }
    } else {
        for(idx_t i = 0; i != BLKS; ++i) {
            data[8 * i + 0] = factor * data[8 * i + 0];
            data[8 * i + 1] = factor * data[8 * i + 1];
            data[8 * i + 2] = factor * data[8 * i + 2];
            data[8 * i + 3] = factor * data[8 * i + 3];
            data[8 * i + 4] = factor * data[8 * i + 4];
            data[8 * i + 5] = factor * data[8 * i + 5];
            data[8 * i + 6] = factor * data[8 * i + 6];
            data[8 * i + 7] = factor * data[8 * i + 7];
        }
    }

    MF_IF_CONSTEXPR(RESIDUE != 0) {
        MF_IF_CONSTEXPR(Inverse) {
            for(idx_t i = BLKS * BLK_SIZE; i != Size; ++i) {
                data[2 * i + 0] = factor * data[2 * i + 0];
                data[2 * i + 1] = factor * -data[2 * i + 1];
            }
        } else {
            for(idx_t i = BLKS * BLK_SIZE; i != Size; ++i) {
                data[2 * i + 0] = factor * data[2 * i + 0];
                data[2 * i + 1] = factor * data[2 * i + 1];
            }
        }
    }
}
} // namespace mf

#endif // HPP_MF_COMPLEX
