#ifndef HPP_MF_TYPES_FIXED
#define HPP_MF_TYPES_FIXED

#include "mf/config.hpp"
#include "mf/traits/enable_if.hpp"
#include "mf/traits/is_integral.hpp"
#include "mf/traits/is_signed.hpp"
#include "mf/traits/is_unsigned.hpp"
#include "mf/traits/make_signed.hpp"
#include "mf/types/integral.hpp"

namespace mf {
template<size_t Bit, typename T> MF_CONSTEXPR T ssat(T x) MF_NOEXCEPT {
    MF_IF_CONSTEXPR((size_t(1) <= Bit) && (Bit <= sizeof(T) * 8)) {
        MF_CONST_OR_CONSTEXPR T max = (T(1) << (Bit - T(1))) - T(1);
        MF_CONST_OR_CONSTEXPR T min = T(-1) - max;

        std::cout << "[" << min << ";" << max << "]\n";

        if(x > max) {
            return max;
        } else if(x < min) {
            return min;
        }
    }

    return x;
}
template<size_t Bit, typename T> MF_CONSTEXPR T usat(T x) MF_NOEXCEPT {
    typedef typename make_signed<T>::type signed_t;

    MF_IF_CONSTEXPR(Bit <= sizeof(T) * 8) {
        MF_CONST_OR_CONSTEXPR T max = (T(1) << Bit) - T(1);
        if(signed_t(x) > signed_t(max)) {
            return max;
        } else if(signed_t(x) < 0) {
            return 0;
        }
    }

    return x;
}

template<typename BaseType, size_t FractionBits> class FixedPoint {
    MF_STATIC_ASSERT((is_integral<BaseType>::value));
    MF_STATIC_ASSERT((0 < FractionBits && FractionBits < sizeof(BaseType) * 8));

    typedef typename make_signed<typename smallest_integral_type<(size_t(1) << sizeof(BaseType) * 8) + 1>::type>::type
        IntermediateType;

    static MF_CONST_OR_CONSTEXPR bool IS_SIGNED = is_signed<BaseType>::value;
    static MF_CONST_OR_CONSTEXPR size_t BITS = sizeof(BaseType) * 8;
    static MF_CONST_OR_CONSTEXPR IntermediateType FRACTION_MULT = IntermediateType(1) << FractionBits;

public:
    MF_CONSTEXPR FixedPoint(BaseType init = BaseType(0)) MF_NOEXCEPT: value(init) {}

    MF_CONSTEXPR FixedPoint &operator+=(const FixedPoint &rhs) MF_NOEXCEPT {
        value = ssat<16>(IntermediateType(value) + IntermediateType(rhs.value));
        return *this;
    }
    MF_CONSTEXPR FixedPoint &operator-=(const FixedPoint &rhs) MF_NOEXCEPT {
        value = sat(IntermediateType(value) - IntermediateType(rhs.value));
        return *this;
    }
    MF_CONSTEXPR FixedPoint &operator*=(const FixedPoint &rhs) MF_NOEXCEPT {
        MF_CONST_OR_CONSTEXPR IntermediateType K = (IntermediateType(1) << (FractionBits - IntermediateType(1)));
        value = sat((IntermediateType(value) * IntermediateType(rhs.value) + K) >> FractionBits);
        return *this;
    }
    MF_CONSTEXPR FixedPoint &operator/=(const FixedPoint &rhs) MF_NOEXCEPT {
#if 0
        /* pre-multiply by the base (Upscale to Q16 so that the result will be in Q8 format) */
        IntermediateType temp = IntermediateType(value) << FractionBits;
        /* Rounding: mid values are rounded up (down for negative values). */
        /* OR compare most significant bits i.e. if (((temp >> 31) & 1) == ((b >> 15) & 1)) */
        if((temp >= 0 && rhs.value >= 0) || (temp < 0 && rhs.value < 0)) {
            temp += rhs.value / 2; /* OR shift 1 bit i.e. temp += (b >> 1); */
        } else {
            temp -= rhs.value / 2; /* OR shift 1 bit i.e. temp -= (b >> 1); */
        }
        value = temp / rhs.value;
#else
        bool EnableRounding = 0;
        if(EnableRounding) {
            // Normal fixed-point division is: x * 2**FractionBits / y.
            // To correctly round the last bit in the result, we need one more bit of information.
            // We do this by multiplying by two before dividing and adding the LSB to the real result.
            IntermediateType tmp = (static_cast<IntermediateType>(value) * FRACTION_MULT * 2) / rhs.value;
            value = sat((tmp / 2) + (tmp % 2));
        } else {
            IntermediateType tmp = (static_cast<IntermediateType>(value) * FRACTION_MULT) / rhs.value;
            value = sat(tmp);
        }
#endif
        return *this;
    }

    MF_CONSTEXPR operator BaseType() const MF_NOEXCEPT {
        return value;
    }

private:
    MF_CONSTEXPR IntermediateType sat(IntermediateType x) const MF_NOEXCEPT {
        MF_IF_CONSTEXPR(IS_SIGNED) {
            return ssat<BITS>(x);
        } else {
            return usat<BITS>(x);
        }
    }

    BaseType value;
};

template<typename BaseType, size_t FractionBits, class CharT, class Traits>
std::basic_ostream<CharT, Traits> &operator<<(std::basic_ostream<CharT, Traits> &o,
                                              const FixedPoint<BaseType, FractionBits> &x) {
    std::basic_ostringstream<CharT, Traits> s;
    s.flags(o.flags());
    s.imbue(o.getloc());
    s.precision(o.precision());

    BaseType c = abs(BaseType(x));
    int sign = 1;
    if(x < 0) {
        c = x - 1;
        c = ~c;
        sign = -1;
    }
    const float_max_t f = float_max_t(sign) * c / pow(float_max_t(2), FractionBits);

    s << f;
    return o << s.str();
}
} // namespace mf

#endif // HPP_MF_TYPES_FIXED
