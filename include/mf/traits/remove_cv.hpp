#ifndef HPP_MF_TRAITS_REMOVE_CV
#define HPP_MF_TRAITS_REMOVE_CV

namespace mf {
template<typename T> struct remove_cv {
    typedef T type;
};
template<typename T> struct remove_cv<const T> {
    typedef T type;
};
template<typename T> struct remove_cv<volatile T> {
    typedef T type;
};
template<typename T> struct remove_cv<const volatile T> {
    typedef T type;
};
} // namespace mf

#endif // HPP_MF_TRAITS_REMOVE_CV
