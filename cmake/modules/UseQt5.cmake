# Macros {{{
# ==============================================================================
# Public {{{
# ==============================================================================
if (NOT CMAKE_VERSION VERSION_LESS 2.8.0)
  macro (find_qt5_component)
    set(_COMPONENTS ${ARGN})
    foreach (_COMPONENT ${_COMPONENTS})
      if (NOT Qt5${_COMPONENT}_FOUND)
        find_package(Qt5${_COMPONENT} REQUIRED)
        get_target_property(_LOCATION Qt5::${_COMPONENT} LOCATION)
        message(STATUS "Found Qt5${_COMPONENT}: ${_LOCATION}")
      endif ()
    endforeach()
  endmacro()
endif ()

if (NOT CMAKE_VERSION VERSION_LESS 2.8.12)
  macro (target_use_qt5 _TARGET _MODE)
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
      message(FATAL_ERROR "Specify at least one Qt component.")
    endif ()

    foreach (_COMPONENT ${_COMPONENTS})
      find_qt5_component(${_COMPONENT})

      target_include_directories(${_TARGET} SYSTEM ${_MODE} ${Qt5${_COMPONENT}_INCLUDE_DIRS})

      target_compile_definitions(${_TARGET} ${_MODE} ${Qt5${_COMPONENT}_COMPILE_DEFINITIONS})
      target_compile_definitions(${_TARGET} ${_MODE} $<$<NOT:$<CONFIG:debug>>:QT_NO_DEBUG>)

      if (Qt5_POSITION_INDEPENDENT_CODE)
        set_target_properties(${_TARGET}
                              PROPERTIES POSITION_INDEPENDENT_CODE ${Qt5_POSITION_INDEPENDENT_CODE})
      endif ()

      target_link_libraries(${_TARGET} ${_MODE} ${Qt5${_COMPONENT}_LIBRARIES})
    endforeach ()
  endmacro ()
endif ()
# ==============================================================================
# }}} Public
# ==============================================================================
# }}} Macros

# vim:ft=cmake:fenc=utf-8:ff=unix:ts=2:sw=2:tw=80:et:
