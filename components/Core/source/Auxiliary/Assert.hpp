#ifndef Geo_Core_Auxiliary_Assert
#define Geo_Core_Auxiliary_Assert

#include "Logging.hpp"

#if !defined (NDEBUG)

namespace DependencyManager {
namespace Core {
inline void
AssertionFailed(char const* expr,
                char const* function,
                char const* file,
                int const&  line) {
  FATAL << "Expression '"
        << expr << "' failed in function '"
        << function << "'";
  exit(-1);
}
}
}

#  define ASSERT(expr)                                          \
  DependencyManager::Core::AssertionFailed(#expr,               \
                                           __PRETTY_FUNCTION__, \
                                           __FILE__,            \
                                           __LINE__)

#else
#  define ASSERT(expr)
#endif

#define ASSERT_PTR(ptr) ASSERT(ptr != 0)

#endif
// vim:ft=cpp:fenc=utf-8:ff=unix:ts=2:sw=2:tw=80:et:
