#ifndef Geo_LogViewer_Auxiliary_Visibility
#define Geo_LogViewer_Auxiliary_Visibility

#include <Uni/Platform/Visibility>

#ifdef LogViewer_EXPORTS
#  define Geo_LogViewer_PUBLIC Uni_Platform_EXPORT
#else
#  define Geo_LogViewer_PUBLIC Uni_Platform_IMPORT
#endif

#if defined (LogViewer_SHARED) && !defined (LogViewer_STATIC)
#  ifdef LogViewer_EXPORTS
#    define Geo_LogViewer_PUBLIC Uni_Platform_EXPORT
#  else
#    define Geo_LogViewer_PUBLIC Uni_Platform_IMPORT
#  endif
#  define Geo_LogViewer_PRIVATE Uni_Platform_LOCAL
#elif !defined (LogViewer_SHARED) && defined (LogViewer_STATIC)
#  define Geo_LogViewer_PUBLIC
#  define Geo_LogViewer_PRIVATE
#elif defined (LogViewer_SHARED) && defined (LogViewer_STATIC)
#  ifdef Geo_LogViewer_EXPORTS
#    error "Cannot build as shared and static simultaneously."
#  else
#    error "Cannot link against shared and static simultaneously."
#  endif
#else
#  ifdef LogViewer_EXPORTS
#    error "Choose whether to build as shared or static."
#  else
#    error "Choose whether to link against shared or static."
#  endif
#endif

#endif

// vim:ft=cpp:fenc=utf-8:ff=unix:ts=2:sw=2:tw=80:et:
