#ifndef Geo_Widgets_Auxiliary_Visibility
#define Geo_Widgets_Auxiliary_Visibility

#include <Uni/Platform/visibility>

#ifdef Widgets_EXPORTS
  #define Geo_Widgets_PUBLIC Uni_Platform_EXPORT
#else
  #define Geo_Widgets_PUBLIC Uni_Platform_IMPORT
#endif

#if defined (Widgets_SHARED) && !defined (Widgets_STATIC)
  #ifdef Widgets_EXPORTS
    #define Geo_Widgets_PUBLIC Uni_Platform_EXPORT
  #else
    #define Geo_Widgets_PUBLIC Uni_Platform_IMPORT
  #endif
  #define Geo_Widgets_PRIVATE Uni_Platform_LOCAL
#elif !defined (Widgets_SHARED) && defined (Widgets_STATIC)
  #define Geo_Widgets_PUBLIC
  #define Geo_Widgets_PRIVATE
#elif defined (Widgets_SHARED) && defined (Widgets_STATIC)
  #ifdef Geo_Widgets_EXPORTS
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

#endif

// vim:ft=cpp:fenc=utf-8:ff=unix:ts=2:sw=2:tw=80:et:
