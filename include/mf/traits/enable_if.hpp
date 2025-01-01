#ifndef HPP_MF_TRAITS_ENABLE_IF
#define HPP_MF_TRAITS_ENABLE_IF

namespace mf {
template<bool Cond, typename T = void> struct enable_if {};
template<typename T> struct enable_if<true, T> {
    typedef T type;
};
} // namespace mf

#endif // HPP_MF_TRAITS_ENABLE_IF
