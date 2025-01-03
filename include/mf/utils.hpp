#ifndef HPP_MF_UTILS
#define HPP_MF_UTILS

#include <cstddef>

#define MF_DO_CONCAT(x, y) x##y
#define MF_CONCAT(x, y) MF_DO_CONCAT(x, y)

#define MF_DO_TRICAT(x, y, z) x##y##z
#define MF_TRICAT(x, y, z) MF_DO_TRICAT(x, y, z)

#define MF_DO_STR(x) #x
#define MF_STR(x) MF_DO_STR(x)

namespace mf { namespace detail {
template<typename T, std::size_t N> char (&countof_helper(T (&)[N]))[N];
}} // namespace mf::detail

#define MF_COUNTOF(a) sizeof(mf::detail::countof_helper(a))

#endif // HPP_MF_UTILS
