#ifndef HPP_MF_UTILS
#define HPP_MF_UTILS

#include "mf/config.hpp"
#include "mf/types/integral.hpp"

namespace mf {
namespace detail {
template<typename T, size_t N> char (&countof_helper(T (&)[N]) MF_NOEXCEPT)[N];
}
#define MF_COUNTOF(a) sizeof(mf::countof_helper(a))

template<typename T, size_t N> MF_CONSTEXPR size_t countof(T (&)[N]) MF_NOEXCEPT {
    return N;
}

template<size_t Begin, size_t End, typename T, size_t Size>
MF_CONSTEXPR T (&slice_cast(T (&arr)[Size]) MF_NOEXCEPT)[End - Begin] {
    MF_STATIC_ASSERT_MSG(Begin <= End && End <= Size, "Invalid range for slicing");
    return reinterpret_cast<T(&)[End - Begin]>(arr[Begin]);
}
template<size_t Begin, typename T, size_t Size> MF_CONSTEXPR T (&slice_cast(T (&arr)[Size]) MF_NOEXCEPT)[Size - Begin] {
    MF_STATIC_ASSERT_MSG(Begin < Size, "Invalid range for slicing");
    return reinterpret_cast<T(&)[Size - Begin]>(arr[Begin]);
}
} /* namespace mf */

#endif /* HPP_MF_UTILS */
