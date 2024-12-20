#ifndef HPP_MF_UTILS_CONFIG
#define HPP_MF_UTILS_CONFIG

#define MF_DO_CONCAT(x, y) a##y
#define MF_CONCAT(x, y) MF_DO_CONCAT(x, y)

#define MF_DO_STR(x) #x
#define MF_STR(x) MF_DO_STR(x)

////////////////////////////////////////////////////////////////////////////////
//                            Compiler Detect Test                            //
////////////////////////////////////////////////////////////////////////////////
#if defined(__GNUC__) && !defined(__clang__)
#define MF_GCC_VERSION_VALUE(maj, min, patch) (10000 * (maj) + 100 * (min) + (patch))
#define MF_GCC_VERSION_CURRENT MF_GCC_VERSION_VALUE(__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__)
#define MF_GCC_VERSION_CHECK(maj, min, patch) (MF_GCC_VERSION_CURRENT >= MF_GCC_VERSION_VALUE(maj, min, patch))
#define MF_GCC_VERSION_CHECK_STRICT(maj, min, patch) (MF_GCC_VERSION_CURRENT > MF_GCC_VERSION_VALUE(maj, min, patch))
#else
#define MF_GCC_VERSION_VALUE(maj, min, patch)
#define MF_GCC_VERSION_CURRENT
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

#if defined(__has_cpp_attribute)
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
#if __cpp_constexpr >= 201907
#define MF_CONST_OR_CONSTEXPR constexpr
#define MF_CONSTEXPR constexpr
#define MF_CONSTEXPR_14 constexpr
#define MF_CONSTEXPR_20 constexpr
#elif __cpp_constexpr >= 201304
#define MF_CONST_OR_CONSTEXPR constexpr
#define MF_CONSTEXPR constexpr
#define MF_CONSTEXPR_14 constexpr
#define MF_CONSTEXPR_20
#else
#define MF_CONST_OR_CONSTEXPR constexpr
#define MF_CONSTEXPR constexpr
#define MF_CONSTEXPR_14
#define MF_CONSTEXPR_20
#endif
#else
#define MF_CONST_OR_CONSTEXPR const
#define MF_CONSTEXPR
#define MF_CONSTEXPR_14
#define MF_CONSTEXPR_20
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
#define MF_STATIC_ASSERT(expr) typedef char MF_MAKE_ASSERT_NAME(static_assertion_)[(expr) ? 1 : -1]
#define MF_STATIC_ASSERT_MSG(expr, msg) MF_STATIC_ASSERT(expr)
#endif

////////////////////////////////////////////////////////////////////////////////
//                           Attribute Feature-Test                           //
////////////////////////////////////////////////////////////////////////////////
#if MF_HAS_CXX_ATTRIBUTE_VER(nodiscard, 201907)
#define MF_NODISCARD [[nodiscard]]
#define MF_NODISCARD_MSG(msg) [[nodiscard(msg)]]
#elif MF_HAS_CXX_ATTRIBUTE_VER(nodiscard, 201603)
#define MF_NODISCARD [[nodiscard]]
#define MF_NODISCARD_MSG(msg) MF_NODISCARD
#elif MF_GCC_VERSION_CHECK(3, 4, 0) || defined(__clang__)
#define MF_NODISCARD __attribute__((warn_unused_result))
#define MF_NODISCARD_MSG(msg) MF_NODISCARD
#elif MF_MSC_VERSION_CHECK(1700)
#define MF_NODISCARD _Check_return_
#define MF_NODISCARD_MSG(msg) MF_NODISCARD
#else
#define MF_NODISCARD
#define MF_NODISCARD_MSG(msg) MF_NODISCARD
#endif

////////////////////////////////////////////////////////////////////////////////
//                            Compiler Intrinsics                             //
////////////////////////////////////////////////////////////////////////////////
#if MF_HAS_BUILTIN(__builtin_clz) || MF_GCC_VERSION_CHECK(3, 4, 0)
#define MF_HAS_BUILTIN_CLZ
#endif

#endif // HPP_MF_UTILS_CONFIG
