#ifndef Geo_Database_Auxiliary_Visibility
#define Geo_Database_Auxiliary_Visibility

#include <Uni/Platform/visibility>

#ifdef Database_EXPORTS
  #define Geo_Database_PUBLIC Uni_Platform_EXPORT
#else
  #define Geo_Database_PUBLIC Uni_Platform_IMPORT
#endif

#if defined (Database_SHARED) && !defined (Database_STATIC)
  #ifdef Database_EXPORTS
    #define Geo_Database_PUBLIC Uni_Platform_EXPORT
  #else
    #define Geo_Database_PUBLIC Uni_Platform_IMPORT
  #endif
  #define Geo_Database_PRIVATE Uni_Platform_LOCAL
#elif !defined (Database_SHARED) && defined (Database_STATIC)
  #define Geo_Database_PUBLIC
  #define Geo_Database_PRIVATE
#elif defined (Database_SHARED) && defined (Database_STATIC)
  #ifdef Geo_Database_EXPORTS
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

#endif

// vim:ft=cpp:fenc=utf-8:ff=unix:ts=2:sw=2:tw=80:et:
