#ifndef HPP_MF_TRAITS_CONDITIONAL
#define HPP_MF_TRAITS_CONDITIONAL

namespace mf {
template<bool Cond, class T1, class T2> struct conditional {
    typedef T1 type;
};
template<class T1, class T2> struct conditional<false, T1, T2> {
    typedef T2 type;
};
} /* namespace mf */

#endif /* HPP_MF_TRAITS_CONDITIONAL */
