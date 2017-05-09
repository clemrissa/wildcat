#pragma once

#include <ComponentManager/Export>

#ifdef Import_EXPORTS
  #define Import_PUBLIC CM_EXPORT
#else
  #define Import_PUBLIC CM_IMPORT
#endif

#if defined (Import_SHARED) && !defined (Import_STATIC)
  #ifdef Import_EXPORTS
    #define Import_PUBLIC CM_EXPORT
  #else
    #define Import_PUBLIC CM_IMPORT
  #endif
  #define Import_PRIVATE CM_LOCAL
#elif !defined (Import_SHARED) && defined (Import_STATIC)
  #define Import_PUBLIC
  #define Import_PRIVATE
#elif defined (Import_SHARED) && defined (Import_STATIC)
  #ifdef Import_EXPORTS
    #error "Cannot build as shared and static simultaneously."
  #else
    #error "Cannot link against shared and static simultaneously."
  #endif
#else
  #ifdef Import_EXPORTS
    #error "Choose whether to build as shared or static."
  #else
    #error "Choose whether to link against shared or static."
  #endif
#endif

// vim:ft=cpp:fenc=utf-8:ff=unix:ts=2:sw=2:tw=80:et:
