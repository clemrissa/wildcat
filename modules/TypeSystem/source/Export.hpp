#pragma once

#include <ComponentManager/Export>

#ifdef TypeSystem_EXPORTS
  #define TypeSystem_PUBLIC CM_EXPORT
#else
  #define TypeSystem_PUBLIC CM_IMPORT
#endif

#if defined (TypeSystem_SHARED) && !defined (TypeSystem_STATIC)
  #ifdef TypeSystem_EXPORTS
    #define TypeSystem_PUBLIC CM_EXPORT
  #else
    #define TypeSystem_PUBLIC CM_IMPORT
  #endif
  #define TypeSystem_PRIVATE CM_LOCAL
#elif !defined (TypeSystem_SHARED) && defined (TypeSystem_STATIC)
  #define TypeSystem_PUBLIC
  #define TypeSystem_PRIVATE
#elif defined (TypeSystem_SHARED) && defined (TypeSystem_STATIC)
  #ifdef TypeSystem_EXPORTS
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


// vim:ft=cpp:fenc=utf-8:ff=unix:ts=2:sw=2:tw=80:et:
