#pragma once

#include <ComponentManager/Export>

#ifdef Widgets_EXPORTS
  #define Widgets_PUBLIC CM_EXPORT
#else
  #define Widgets_PUBLIC CM_IMPORT
#endif

#if defined (Widgets_SHARED) && !defined (Widgets_STATIC)
  #ifdef Widgets_EXPORTS
    #define Widgets_PUBLIC CM_EXPORT
  #else
    #define Widgets_PUBLIC CM_IMPORT
  #endif
  #define Widgets_PRIVATE CM_LOCAL
#elif !defined (Widgets_SHARED) && defined (Widgets_STATIC)
  #define Widgets_PUBLIC
  #define Widgets_PRIVATE
#elif defined (Widgets_SHARED) && defined (Widgets_STATIC)
  #ifdef Widgets_EXPORTS
    #error "Cannot build as shared and static simultaneously."
  #else
    #error "Cannot link against shared and static simultaneously."
  #endif
#else
  #ifdef Widgets_EXPORTS
    #error "Choose whether to build as shared or static."
  #else
    #error "Choose whether to link against shared or static."
  #endif
#endif

// vim:ft=cpp:fenc=utf-8:ff=unix:ts=2:sw=2:tw=80:et:
