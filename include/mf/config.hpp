#ifndef HPP_MF_UTILS_CONFIG
#define HPP_MF_UTILS_CONFIG

#include "mf/basic_utils.hpp"

////////////////////////////////////////////////////////////////////////////////
//                            Compiler Detect Test                            //
////////////////////////////////////////////////////////////////////////////////
#if defined(__GNUC__) && !defined(__clang__)
#define MF_GCC_VERSION_VALUE(maj, min, patch) (10000 * (maj) + 100 * (min) + (patch))
#define MF_GCC_VERSION_CURRENT MF_GCC_VERSION_VALUE(__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__)
#define MF_GCC_VERSION_CHECK(maj, min, patch) (MF_GCC_VERSION_CURRENT >= MF_GCC_VERSION_VALUE(maj, min, patch))
#define MF_GCC_VERSION_CHECK_STRICT(maj, min, patch) (MF_GCC_VERSION_CURRENT > MF_GCC_VERSION_VALUE(maj, min, patch))
#else
#define MF_GCC_VERSION_VALUE(maj, min, patch) 0
#define MF_GCC_VERSION_CURRENT 0
#define MF_GCC_VERSION_CHECK(maj, min, patch) 0
#define MF_GCC_VERSION_CHECK_STRICT(maj, min, patch) 0
#endif

#if defined(_MSC_VER) && !defined(__clang__)
#define MF_MSC_VERSION_CHECK(v) (_MSC_VER >= (v))
#define MF_MSC_VERSION_CHECK_STRICT(v) (_MSC_VER > (v))
#else
#define MF_MSC_VERSION_CHECK(v) 0
#define MF_MSC_VERSION_CHECK_STRICT(v) 0
#endif

#if defined(_MSC_VER)
#define MF_CXX_VER _MSVC_LANG
#define MF_CXX_VER_CHECK(v) (_MSVC_LANG >= (v))
#else
#define MF_CXX_VER __cplusplus
#define MF_CXX_VER_CHECK(v) (__cplusplus >= (v))
#endif

#if defined(__has_attribute)
#define MF_HAS_ATTRIBUTE(a) __has_attribute(a)
#else
#define MF_HAS_ATTRIBUTE(a) 0
#endif

#if defined(__STRICT_ANSI__)
#define MF_HAS_CXX_ATTRIBUTE(a) 0
#define MF_HAS_CXX_ATTRIBUTE_VER(a, v) 0
#elif defined(__has_cpp_attribute)
#define MF_HAS_CXX_ATTRIBUTE(a) __has_cpp_attribute(a)
#define MF_HAS_CXX_ATTRIBUTE_VER(a, v) (__has_cpp_attribute(a) >= (v))
#else
#define MF_HAS_CXX_ATTRIBUTE(a) 0
#define MF_HAS_CXX_ATTRIBUTE_VER(a, v) 0
#endif

#if defined(__has_builtin)
#define MF_HAS_BUILTIN(a) __has_builtin(a)
#else
#define MF_HAS_BUILTIN(a) 0
#endif

////////////////////////////////////////////////////////////////////////////////
//                           Language Feature-Test                            //
////////////////////////////////////////////////////////////////////////////////
#if defined(__cpp_constexpr)
#if __cpp_constexpr >= 201304
#define MF_CONST_OR_CONSTEXPR constexpr
#define MF_CONSTEXPR constexpr
#define MF_CONSTEXPR_14 constexpr
#else
#define MF_CONST_OR_CONSTEXPR constexpr
#define MF_CONSTEXPR constexpr
#define MF_CONSTEXPR_14 inline
#endif
#else
#define MF_CONST_OR_CONSTEXPR const
#define MF_CONSTEXPR inline
#define MF_CONSTEXPR_14 inline
#endif

#if MF_CXX_VER >= 201103
#define MF_DELETED = delete
#else
#define MF_DELETED
#endif

#if defined(__cpp_if_constexpr)
#define MF_IF_CONSTEXPR if constexpr
#else
#define MF_IF_CONSTEXPR if
#endif

#if MF_CXX_VER >= 201103
#define MF_NOEXCEPT noexcept
#else
#define MF_NOEXCEPT throw()
#endif

#if defined(__cpp_static_assert)
#if __cpp_static_assert >= 201411
#define MF_STATIC_ASSERT(expr) static_assert(expr)
#define MF_STATIC_ASSERT_MSG(expr, msg) static_assert(expr, msg)
#else
#define MF_STATIC_ASSERT(expr) static_assert(expr, MF_STR(expr))
#define MF_STATIC_ASSERT_MSG(expr, msg) static_assert(expr, msg)
#endif
#else
#define MF_MAKE_ASSERT_NAME(a) MF_CONCAT(a, __COUNTER__)
#define MF_STATIC_ASSERT(expr) typedef char MF_MAKE_ASSERT_NAME(static_assertion_)[(expr) ? 1 : -1] MF_MAYBE_UNUSED
#define MF_STATIC_ASSERT_MSG(expr, msg) MF_STATIC_ASSERT(expr)
#endif

////////////////////////////////////////////////////////////////////////////////
//                           Attribute Feature-Test                           //
////////////////////////////////////////////////////////////////////////////////
#if MF_HAS_CXX_ATTRIBUTE_VER(nodiscard, 201907) // nodiscard
#define MF_NODISCARD [[nodiscard]]
#define MF_NODISCARD_MSG(msg) [[nodiscard(msg)]]
#elif MF_HAS_CXX_ATTRIBUTE_VER(nodiscard, 201603)
#elif MF_GCC_VERSION_CHECK(3, 4, 0) || defined(__clang__)
#define MF_NODISCARD __attribute__((warn_unused_result))
#elif MF_MSC_VERSION_CHECK(1700)
#define MF_NODISCARD _Check_return_
#else
#define MF_NODISCARD
#endif // nodiscard

#if !defined(MF_NODISCARD_MSG)
#define MF_NODISCARD_MSG(msg) MF_NODISCARD
#endif

#if(defined(__GNUC__) && !defined(__clang__)) || MF_HAS_ATTRIBUTE(optimize) // optimize
#define MF_OPTIMIZE(lvl) __attribute__((optimize(MF_STR(MF_CONCAT(-O, lvl)))))
#else
#define MF_OPTIMIZE(lvl)
#endif // optimize

#if MF_HAS_CXX_ATTRIBUTE(maybe_unused)
#define MF_MAYBE_UNUSED [[maybe_unused]]
#elif MF_GCC_VERSION_CHECK(2, 7, 0) || MF_HAS_ATTRIBUTE(unused)
#define MF_MAYBE_UNUSED __attribute__((unused))
#else
#define MF_MAYBE_UNUSED
#endif

////////////////////////////////////////////////////////////////////////////////
//                            Compiler Intrinsics                             //
////////////////////////////////////////////////////////////////////////////////
#if MF_HAS_BUILTIN(__builtin_clz) || MF_GCC_VERSION_CHECK(3, 4, 0) // clz
#define MF_HAS_BUILTIN_CLZ
#endif // clz

#if MF_GCC_VERSION_CHECK(2, 96, 0) || MF_HAS_BUILTIN(__builtin_expect) // likely
#define MF_LIKELY(a) __builtin_expect(!!(a), 1)
#define MF_UNLIKELY(a) __builtin_expect(!!(a), 0)
#elif MF_HAS_CXX_ATTRIBUTE(likely)
#define MF_LIKELY(a) \
    (([](bool value) { \
        switch(value) { \
            [[likely]] case true: \
                return true; \
            [[unlikely]] case false: \
                return false; \
        } \
    })(!!(a)))
#define MF_UNLIKELY(a) \
    (([](bool value) { \
        switch(value) { \
            [[unlikely]] case true: \
                return true; \
            [[likely]] case false: \
                return false; \
        } \
    })(!!(a)))
#else
#define MF_LIKELY(a) (a)
#define MF_UNLIKELY(a) (a)
#endif // likely

#endif // HPP_MF_UTILS_CONFIG
