#ifndef Geo_Core_Auxiliary_Visibility
#define Geo_Core_Auxiliary_Visibility

#include <Uni/Platform/Visibility>

#ifdef Core_EXPORTS
#  define Geo_Core_PUBLIC Uni_Platform_EXPORT
#else
#  define Geo_Core_PUBLIC Uni_Platform_IMPORT
#endif

#if defined (Core_SHARED) && !defined (Core_STATIC)
#  ifdef Core_EXPORTS
#    define Geo_Core_PUBLIC Uni_Platform_EXPORT
#  else
#    define Geo_Core_PUBLIC Uni_Platform_IMPORT
#  endif
#  define Geo_Core_PRIVATE Uni_Platform_LOCAL
#elif !defined (Core_SHARED) && defined (Core_STATIC)
#  define Geo_Core_PUBLIC
#  define Geo_Core_PRIVATE
#elif defined (Core_SHARED) && defined (Core_STATIC)
#  ifdef Geo_Core_EXPORTS
#    error "Cannot build as shared and static simultaneously."
#  else
#    error "Cannot link against shared and static simultaneously."
#  endif
#else
#  ifdef Core_EXPORTS
#    error "Choose whether to build as shared or static."
#  else
#    error "Choose whether to link against shared or static."
#  endif
#endif

#endif

// vim:ft=cpp:fenc=utf-8:ff=unix:ts=2:sw=2:tw=80:et:
