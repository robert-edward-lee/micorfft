#ifndef HPP_MF_TRAITS_MAKE_UNSIGNED
#define HPP_MF_TRAITS_MAKE_UNSIGNED

#include "mf/config.hpp"
#include "mf/traits/conditional.hpp"
#include "mf/traits/detail/cv_selector.hpp"
#include "mf/traits/is_cv.hpp"
#include "mf/traits/remove_cv.hpp"

namespace mf {
namespace detail {
template<typename T> struct make_unsigned_typed_helper {
    typedef void type;
};
template<> struct make_unsigned_typed_helper<unsigned char> {
    typedef unsigned char type;
};
template<> struct make_unsigned_typed_helper<signed char> {
    typedef unsigned char type;
};
template<> struct make_unsigned_typed_helper<unsigned short> {
    typedef unsigned short type;
};
template<> struct make_unsigned_typed_helper<signed short> {
    typedef unsigned short type;
};
template<> struct make_unsigned_typed_helper<unsigned int> {
    typedef unsigned int type;
};
template<> struct make_unsigned_typed_helper<signed int> {
    typedef unsigned int type;
};
template<> struct make_unsigned_typed_helper<unsigned long> {
    typedef unsigned long type;
};
template<> struct make_unsigned_typed_helper<signed long> {
    typedef unsigned long type;
};
#if MF_CXX_VER > 199711L
template<> struct make_unsigned_typed_helper<unsigned long long> {
    typedef unsigned long long type;
};
template<> struct make_unsigned_typed_helper<signed long long> {
    typedef unsigned long long type;
};
#endif

template<typename T> class make_unsigned_helper {
    typedef typename make_unsigned_typed_helper<typename remove_cv<T>::type>::type pure_type;

public:
    typedef typename cv_selector<pure_type, is_const<T>::value, is_volatile<T>::value>::type type;
};
} // namespace detail

template<typename T> struct make_unsigned: detail::make_unsigned_helper<T> {};
} // namespace mf

#endif // HPP_MF_TRAITS_MAKE_UNSIGNED
