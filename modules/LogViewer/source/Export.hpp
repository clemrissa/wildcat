#pragma once

#include <ComponentManager/Export>

#ifdef LogViewer_EXPORTS
  #define LogViewer_PUBLIC CM_EXPORT
#else
  #define LogViewer_PUBLIC CM_IMPORT
#endif

#if defined (LogViewer_SHARED) && !defined (LogViewer_STATIC)
  #ifdef LogViewer_EXPORTS
    #define LogViewer_PUBLIC CM_EXPORT
  #else
    #define LogViewer_PUBLIC CM_IMPORT
  #endif
  #define LogViewer_PRIVATE CM_LOCAL
#elif !defined (LogViewer_SHARED) && defined (LogViewer_STATIC)
  #define LogViewer_PUBLIC
  #define LogViewer_PRIVATE
#elif defined (LogViewer_SHARED) && defined (LogViewer_STATIC)
  #ifdef LogViewer_EXPORTS
    #error "Cannot build as shared and static simultaneously."
  #else
    #error "Cannot link against shared and static simultaneously."
  #endif
#else
  #ifdef LogViewer_EXPORTS
    #error "Choose whether to build as shared or static."
  #else
    #error "Choose whether to link against shared or static."
  #endif
#endif


// vim:ft=cpp:fenc=utf-8:ff=unix:ts=2:sw=2:tw=80:et:
