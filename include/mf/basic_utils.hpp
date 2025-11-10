#ifndef HPP_MF_BASIC_UTILS
#define HPP_MF_BASIC_UTILS

#define MF_DO_CONCAT(x, y) x##y
#define MF_CONCAT(x, y) MF_DO_CONCAT(x, y)

#define MF_DO_TRICAT(x, y, z) x##y##z
#define MF_TRICAT(x, y, z) MF_DO_TRICAT(x, y, z)

#define MF_DO_STR(x) #x
#define MF_STR(x) MF_DO_STR(x)

#endif /* HPP_MF_BASIC_UTILS */
