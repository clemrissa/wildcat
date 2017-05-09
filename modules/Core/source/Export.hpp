#pragma once

#include <ComponentManager/Export>

#ifdef Core_EXPORTS
  #define Core_PUBLIC CM_EXPORT
#else
  #define Core_PUBLIC CM_IMPORT
#endif

#if defined (Core_SHARED) && !defined (Core_STATIC)
  #ifdef Core_EXPORTS
    #define Core_PUBLIC CM_EXPORT
  #else
    #define Core_PUBLIC CM_IMPORT
  #endif
  #define Core_PRIVATE CM_LOCAL
#elif !defined (Core_SHARED) && defined (Core_STATIC)
  #define Core_PUBLIC
  #define Core_PRIVATE
#elif defined (Core_SHARED) && defined (Core_STATIC)
  #ifdef Core_EXPORTS
    #error "Cannot build as shared and static simultaneously."
  #else
    #error "Cannot link against shared and static simultaneously."
  #endif
#else
  #ifdef Core_EXPORTS
    #error "Choose whether to build as shared or static."
  #else
    #error "Choose whether to link against shared or static."
  #endif
#endif

// vim:ft=cpp:fenc=utf-8:ff=unix:ts=2:sw=2:tw=80:et:
