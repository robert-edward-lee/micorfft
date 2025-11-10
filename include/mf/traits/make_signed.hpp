#ifndef HPP_MF_TRAITS_MAKE_SIGNED
#define HPP_MF_TRAITS_MAKE_SIGNED

#include "mf/config.hpp"
#include "mf/traits/conditional.hpp"
#include "mf/traits/detail/cv_selector.hpp"
#include "mf/traits/is_cv.hpp"
#include "mf/traits/remove_cv.hpp"

namespace mf {
namespace detail {
template<typename T> struct make_signed_typed_helper {
    typedef void type;
};
template<> struct make_signed_typed_helper<unsigned char> {
    typedef signed char type;
};
template<> struct make_signed_typed_helper<signed char> {
    typedef signed char type;
};
template<> struct make_signed_typed_helper<unsigned short> {
    typedef signed short type;
};
template<> struct make_signed_typed_helper<signed short> {
    typedef signed short type;
};
template<> struct make_signed_typed_helper<unsigned int> {
    typedef signed int type;
};
template<> struct make_signed_typed_helper<signed int> {
    typedef signed int type;
};
template<> struct make_signed_typed_helper<unsigned long> {
    typedef signed long type;
};
template<> struct make_signed_typed_helper<signed long> {
    typedef signed long type;
};
#if MF_CXX_VER > 199711L
template<> struct make_signed_typed_helper<unsigned long long> {
    typedef signed long long type;
};
template<> struct make_signed_typed_helper<signed long long> {
    typedef signed long long type;
};
#endif
template<typename T> class make_signed_helper {
    typedef typename make_signed_typed_helper<typename remove_cv<T>::type>::type pure_type;

public:
    typedef typename cv_selector<pure_type, is_const<T>::value, is_volatile<T>::value>::type type;
};
} /* namespace detail */

template<typename T> struct make_signed: detail::make_signed_helper<T> {};
} /* namespace mf */

#endif /* HPP_MF_TRAITS_MAKE_SIGNED */
