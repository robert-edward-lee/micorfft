#ifndef HPP_MF_COMPLEX
#define HPP_MF_COMPLEX

#include <sstream>

#include "mf/basic_math.hpp"
#include "mf/config.hpp"
#include "mf/types/integral.hpp"

namespace mf {
template<typename T> class Complex {
public:
    /* ctors */
    MF_CONSTEXPR Complex(T x = T(0), T y = T(0)) MF_NOEXCEPT: re(x), im(y) {}
    template<typename U>
    MF_CONSTEXPR Complex(const Complex<U> &other) MF_NOEXCEPT: re(other.real()), im(other.imag()) {}

    MF_CONSTEXPR_14 Complex &operator=(const T &rhs) MF_NOEXCEPT {
        re = rhs;
        im = 0;
        return *this;
    }
    static MF_CONSTEXPR Complex polar(const T &mag, const T &phase) MF_NOEXCEPT {
        return Complex(mag * cos(phase), mag * sin(phase));
    }
    /* getters/setters */
    MF_NODISCARD MF_CONSTEXPR_14 T real() const MF_NOEXCEPT {
        return re;
    }
    MF_NODISCARD MF_CONSTEXPR_14 T &real() MF_NOEXCEPT {
        return re;
    }
    MF_NODISCARD MF_CONSTEXPR_14 T imag() const MF_NOEXCEPT {
        return im;
    }
    MF_NODISCARD MF_CONSTEXPR_14 T &imag() MF_NOEXCEPT {
        return im;
    }
    MF_NODISCARD MF_CONSTEXPR Complex conj() const MF_NOEXCEPT {
        return Complex(re, -im);
    }
    MF_NODISCARD MF_CONSTEXPR T mag_sqr() const MF_NOEXCEPT {
        return re * re + im * im;
    }
    MF_NODISCARD MF_CONSTEXPR T mag() const MF_NOEXCEPT {
        return sqrt(mag_sqr());
    }
    MF_NODISCARD MF_CONSTEXPR T phase() const MF_NOEXCEPT {
        return atan2(im, re);
    }
    MF_NODISCARD MF_CONSTEXPR_14 Complex pow(const Complex &z) const MF_NOEXCEPT {
        if(re == T(0) && im == T(0)) {
            return Complex();
        }

        T abs = mag();
        T arg = phase();
        T r = ::pow(abs, z.re);
        T theta = z.re * arg;
        if(im != T(0)) {
            r = r * exp(-z.im * arg);
            theta = theta + z.im * log(abs);
        }

        return Complex(r * cos(theta), r * sin(theta));
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
    MF_CONSTEXPR Complex operator~() const MF_NOEXCEPT {
        return conj();
    }

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

#endif // HPP_MF_COMPLEX
