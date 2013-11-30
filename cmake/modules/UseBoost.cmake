# Macros {{{
# ==============================================================================
# Public {{{
# ==============================================================================
if (NOT CMAKE_VERSION VERSION_LESS 2.8.12)
  macro (target_use_boost _TARGET _MODE)
    if (NOT TARGET ${_TARGET})
      message(FATAL_ERROR "Argument #1 must be an existing target.")
    endif ()

    if ("${_MODE}" STREQUAL "PUBLIC"                                          OR
        "${_MODE}" STREQUAL "PRIVATE"                                         OR
        "${_MODE}" STREQUAL "INTERFACE"                                       OR

        "${_MODE}" STREQUAL "LINK_PUBLIC"                                     OR
        "${_MODE}" STREQUAL "LINK_PRIVATE")
      set(_COMPONENTS ${ARGN})
    else ()
      set(_COMPONENTS ${_MODE} ${ARGN})
      unset(_MODE)
    endif ()

    if ("${_COMPONENTS}" STREQUAL "")
      if (NOT Boost_FOUND)
        find_package(Boost REQUIRED)
      endif()
      target_include_directories(${_TARGET} SYSTEM ${_MODE} ${Boost_INCLUDE_DIRS})
    endif ()

    foreach (_COMPONENT ${_COMPONENTS})
      string(TOUPPER "${_COMPONENT}" _C)

      if (NOT Boost_${_C}_FOUND)
        find_package(Boost COMPONENTS ${_COMPONENT} REQUIRED)
      endif ()

      target_include_directories(${_TARGET} SYSTEM ${_MODE} ${Boost_INCLUDE_DIRS})

      if ("${_COMPONENT}" STREQUAL "filesystem")
        target_compile_definitions(${_TARGET} ${_MODE} BOOST_FILESYSTEM_NO_DEPRECATED)
      endif ()

      if ("${_COMPONENT}" STREQUAL "thread")
        target_compile_definitions(${_TARGET} ${_MODE} BOOST_THREAD_VERSION=3)
      endif ()

      target_link_libraries(${_TARGET} ${_MODE} ${Boost_${_C}_LIBRARY})
    endforeach ()
  endmacro ()
endif ()
# ==============================================================================
# }}} Public
# ==============================================================================
# }}} Macros

# vim:ft=cmake:fenc=utf-8:ff=unix:ts=2:sw=2:tw=80:et:
