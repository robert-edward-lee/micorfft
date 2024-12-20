#ifndef HPP_MF_UTILS_TYPES
#define HPP_MF_UTILS_TYPES

#include <cstdint>

namespace mf {
using std::uint16_t;
using std::uint32_t;

template<typename IdxType> struct uint_fast {
    using type = void;
};
template<> struct uint_fast<uint16_t> {
    using type = std::uint_fast16_t;
};
template<> struct uint_fast<uint32_t> {
    using type = std::uint_fast32_t;
};
template<typename IdxType> using uint_fast_t = typename uint_fast<IdxType>::type;

using float32_t = float;
using float64_t = double;
using float_max_t = long double;

} // namespace mf

#endif // HPP_MF_UTILS_TYPES
