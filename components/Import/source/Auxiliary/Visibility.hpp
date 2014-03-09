#ifndef Geo_Import_Auxiliary_Visibility
#define Geo_Import_Auxiliary_Visibility

#include <Uni/Platform/visibility>

#ifdef Import_EXPORTS
  #define Geo_Import_PUBLIC Uni_Platform_EXPORT
#else
  #define Geo_Import_PUBLIC Uni_Platform_IMPORT
#endif

#if defined (Import_SHARED) && !defined (Import_STATIC)
  #ifdef Import_EXPORTS
    #define Geo_Import_PUBLIC Uni_Platform_EXPORT
  #else
    #define Geo_Import_PUBLIC Uni_Platform_IMPORT
  #endif
  #define Geo_Import_PRIVATE Uni_Platform_LOCAL
#elif !defined (Import_SHARED) && defined (Import_STATIC)
  #define Geo_Import_PUBLIC
  #define Geo_Import_PRIVATE
#elif defined (Import_SHARED) && defined (Import_STATIC)
  #ifdef Geo_Import_EXPORTS
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

#endif

// vim:ft=cpp:fenc=utf-8:ff=unix:ts=2:sw=2:tw=80:et:
