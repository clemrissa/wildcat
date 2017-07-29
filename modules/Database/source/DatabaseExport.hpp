#pragma once

#include <ComponentManager/Export>

#ifdef Database_EXPORTS
  #define Database_PUBLIC CM_EXPORT
#else
  #define Database_PUBLIC CM_IMPORT
#endif

#if defined (Database_SHARED) && !defined (Database_STATIC)
  #ifdef Database_EXPORTS
    #define Database_PUBLIC CM_EXPORT
  #else
    #define Database_PUBLIC CM_IMPORT
  #endif
  #define Database_PRIVATE CM_LOCAL
#elif !defined (Database_SHARED) && defined (Database_STATIC)
  #define Database_PUBLIC
  #define Database_PRIVATE
#elif defined (Database_SHARED) && defined (Database_STATIC)
  #ifdef Database_EXPORTS
    #error "Cannot build as shared and static simultaneously."
  #else
    #error "Cannot link against shared and static simultaneously."
  #endif
#else
  #ifdef Database_EXPORTS
    #error "Choose whether to build as shared or static."
  #else
    #error "Choose whether to link against shared or static."
  #endif
#endif

// vim:ft=cpp:fenc=utf-8:ff=unix:ts=2:sw=2:tw=80:et:
