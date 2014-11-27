#ifndef Geo_Models_Auxiliary_Visibility
#define Geo_Models_Auxiliary_Visibility

#include <Uni/Platform/visibility>

#ifdef Models_EXPORTS
  #define Geo_Models_PUBLIC Uni_Platform_EXPORT
#else
  #define Geo_Models_PUBLIC Uni_Platform_IMPORT
#endif

#if defined (Models_SHARED) && !defined (Models_STATIC)
  #ifdef Models_EXPORTS
    #define Geo_Models_PUBLIC Uni_Platform_EXPORT
  #else
    #define Geo_Models_PUBLIC Uni_Platform_IMPORT
  #endif
  #define Geo_Models_PRIVATE Uni_Platform_LOCAL
#elif !defined (Models_SHARED) && defined (Models_STATIC)
  #define Geo_Models_PUBLIC
  #define Geo_Models_PRIVATE
#elif defined (Models_SHARED) && defined (Models_STATIC)
  #ifdef Geo_Models_EXPORTS
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

#endif

// vim:ft=cpp:fenc=utf-8:ff=unix:ts=2:sw=2:tw=80:et:
