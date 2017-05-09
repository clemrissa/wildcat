#pragma once

#include <ComponentManager/Export>

#ifdef Models_EXPORTS
  #define Models_PUBLIC CM_EXPORT
#else
  #define Models_PUBLIC CM_IMPORT
#endif

#if defined (Models_SHARED) && !defined (Models_STATIC)
  #ifdef Models_EXPORTS
    #define Models_PUBLIC CM_EXPORT
  #else
    #define Models_PUBLIC CM_IMPORT
  #endif
  #define Models_PRIVATE CM_LOCAL
#elif !defined (Models_SHARED) && defined (Models_STATIC)
  #define Models_PUBLIC
  #define Models_PRIVATE
#elif defined (Models_SHARED) && defined (Models_STATIC)
  #ifdef Models_EXPORTS
    #error "Cannot build as shared and static simultaneously."
  #else
    #error "Cannot link against shared and static simultaneously."
  #endif
#else
  #ifdef Models_EXPORTS
    #error "Choose whether to build as shared or static."
  #else
    #error "Choose whether to link against shared or static."
  #endif
#endif


// vim:ft=cpp:fenc=utf-8:ff=unix:ts=2:sw=2:tw=80:et:
