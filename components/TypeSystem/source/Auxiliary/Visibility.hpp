#ifndef Geo_TypeSystem_Auxiliary_Visibility
#define Geo_TypeSystem_Auxiliary_Visibility

#include <Uni/Platform/visibility>

#ifdef TypeSystem_EXPORTS
  #define Geo_TypeSystem_PUBLIC Uni_Platform_EXPORT
#else
  #define Geo_TypeSystem_PUBLIC Uni_Platform_IMPORT
#endif

#if defined (TypeSystem_SHARED) && !defined (TypeSystem_STATIC)
  #ifdef TypeSystem_EXPORTS
    #define Geo_TypeSystem_PUBLIC Uni_Platform_EXPORT
  #else
    #define Geo_TypeSystem_PUBLIC Uni_Platform_IMPORT
  #endif
  #define Geo_TypeSystem_PRIVATE Uni_Platform_LOCAL
#elif !defined (TypeSystem_SHARED) && defined (TypeSystem_STATIC)
  #define Geo_TypeSystem_PUBLIC
  #define Geo_TypeSystem_PRIVATE
#elif defined (TypeSystem_SHARED) && defined (TypeSystem_STATIC)
  #ifdef Geo_TypeSystem_EXPORTS
    #error "Cannot build as shared and static simultaneously."
  #else
    #error "Cannot link against shared and static simultaneously."
  #endif
#else
  #ifdef TypeSystem_EXPORTS
    #error "Choose whether to build as shared or static."
  #else
    #error "Choose whether to link against shared or static."
  #endif
#endif

#endif

// vim:ft=cpp:fenc=utf-8:ff=unix:ts=2:sw=2:tw=80:et:
