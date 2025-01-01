#ifndef HPP_MF_BASIC_MATH_LOG2
#define HPP_MF_BASIC_MATH_LOG2

#include "mf/config.hpp"
#include "mf/traits/enable_if.hpp"

#define MF_LOG2_SPECIALIZATION_ONE(type) \
    template<> struct log2<type, 1> { \
        static MF_CONST_OR_CONSTEXPR type value = 0; \
    }

namespace mf {
template<typename T, T x> struct log2 {
    static MF_CONST_OR_CONSTEXPR typename enable_if<(x > 0), T>::type value = 1 + log2<T, (x >> 1)>::value;
};

MF_LOG2_SPECIALIZATION_ONE(unsigned char);
MF_LOG2_SPECIALIZATION_ONE(signed char);
MF_LOG2_SPECIALIZATION_ONE(char);
MF_LOG2_SPECIALIZATION_ONE(unsigned short);
MF_LOG2_SPECIALIZATION_ONE(signed short);
MF_LOG2_SPECIALIZATION_ONE(unsigned int);
MF_LOG2_SPECIALIZATION_ONE(signed int);
MF_LOG2_SPECIALIZATION_ONE(unsigned long);
MF_LOG2_SPECIALIZATION_ONE(signed long);
#if MF_CXX_VER > 199711L
MF_LOG2_SPECIALIZATION_ONE(unsigned long long);
MF_LOG2_SPECIALIZATION_ONE(signed long long);
#endif
} // namespace mf

#endif // HPP_MF_BASIC_MATH_LOG2
