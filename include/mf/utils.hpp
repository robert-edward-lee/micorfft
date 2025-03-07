#ifndef HPP_MF_UTILS
#define HPP_MF_UTILS

#include "mf/config.hpp"

namespace mf {
namespace detail {
template<typename T, size_t N> char (&countof_helper(T (&)[N]) MF_NOEXCEPT)[N];
}

template<typename T, size_t N> MF_CONSTEXPR size_t countof(T (&a)[N]) MF_NOEXCEPT {
    return sizeof(detail::countof_helper(a));
}

#define MF_COUNTOF(a) (mf::countof(a))

template<size_t Begin, size_t End, typename T, size_t Size>
MF_CONSTEXPR T (&slice_cast(T (&arr)[Size]) MF_NOEXCEPT)[End - Begin] {
    MF_STATIC_ASSERT_MSG(Begin <= End && End <= Size, "Invalid range for slicing");
    return reinterpret_cast<T(&)[End - Begin]>(arr[Begin]);
}
} // namespace mf

#endif // HPP_MF_UTILS
