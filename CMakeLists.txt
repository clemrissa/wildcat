# General {{{
# ==============================================================================
cmake_minimum_required(VERSION 2.8.12)
# ------------------------------------------------------------------------------
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES  ON)

if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
  message(SEND_ERROR "In-source builds are not allowed.")
endif ()
# ------------------------------------------------------------------------------
set(CMAKE_ERROR_DEPRECATED ON)
# ------------------------------------------------------------------------------
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_COLOR_MAKEFILE   ON)
# ------------------------------------------------------------------------------
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# ------------------------------------------------------------------------------
set(CMAKE_AUTOMOC ON)
# ------------------------------------------------------------------------------
if (WIN32)
  set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif ()
# ------------------------------------------------------------------------------
set(INSTALL_BINARY_DIR  bin)
set(INSTALL_INCLUDE_DIR include)
set(INSTALL_LIBRARY_DIR lib)
set(INSTALL_COMPONENT_DIR components)
set(INSTALL_SOURCE_DIR  source)
if (WIN32)
  set(INSTALL_CMAKE_DIR cmake)
else()
  set(INSTALL_CMAKE_DIR lib/cmake)
endif ()
# ==============================================================================
# }}} General

# Modules {{{
# ==============================================================================
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/modules)
# ------------------------------------------------------------------------------
include(UseQt5)
include(UseBoost)
find_package(DependencyManager REQUIRED)
find_package(Uni REQUIRED)
# ==============================================================================
# }}} Modules

# Configure SQLite {{{
# -----------------------------------------------------------------------------
set(SQLite_INCLUDE_DIR $ENV{SQLite_INCLUDE_DIR})
set(SQLite_LIBRARY_DIR $ENV{SQLite_LIBRARY_DIR})

find_package(SQLite REQUIRED)
# -----------------------------------------------------------------------------
# }}} Configure SQLite

# Configure ODB {{{
# -----------------------------------------------------------------------------
set(ODB_INCLUDE_DIR $ENV{ODB_INCLUDE_DIR})
set(ODB_LIBRARY_DIR $ENV{ODB_LIBRARY_DIR})

set(ODBSQLITE_INCLUDE_DIR $ENV{ODBSQLITE_INCLUDE_DIR})
set(ODBSQLITE_LIBRARY_DIR $ENV{ODBSQLITE_LIBRARY_DIR})

set(ODBQT_INCLUDE_DIR $ENV{ODBQT_INCLUDE_DIR})
set(ODBQT_LIBRARY_DIR $ENV{ODBQT_LIBRARY_DIR})

find_package(ODB REQUIRED)
include(ODB)
# -----------------------------------------------------------------------------
# }}} Configure ODB


# Compilers {{{
# ==============================================================================
if (CMAKE_COMPILER_IS_GNUCXX)
  set(COMPILER_IS_G++ TRUE)
  set(LINKER_IS_LD    TRUE)
endif ()
# ==============================================================================
# }}} Compilers

# Definitions {{{
# ==============================================================================
add_definitions(-DMOC)
add_definitions(-DUNICODE)
# ==============================================================================
# }}} Definitions

# Flags {{{
# ==============================================================================
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
if (COMPILER_IS_G++)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pipe")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
  #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")# -Wpedantic")
  # Again because of Loki such a pain
  #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmessage-length=0")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

  #set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fomit-frame-pointer")
  #set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -funroll-loops")
endif ()
# ------------------------------------------------------------------------------
if (LINKER_IS_LD)
  if (WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
  endif ()

  set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -Wl,-O5")
  # ----------------------------------------------------------------------------
  if (WIN32)
    set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -static-libgcc")
    set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -static-libstdc++")
    set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -static")
  endif ()

  set(CMAKE_MODULE_LINKER_FLAGS_RELEASE "${CMAKE_MODULE_LINKER_FLAGS_RELEASE} -Wl,-O5")
  # ----------------------------------------------------------------------------
  if (WIN32)
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -static-libgcc")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -static-libstdc++")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -static")
  endif ()

  set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} -Wl,-O5")
  # ----------------------------------------------------------------------------
  #set(CMAKE_STATIC_LINKER_FLAGS_RELEASE "${CMAKE_STATIC_LINKER_FLAGS_RELEASE} -Wl,-O5")
endif ()
# ==============================================================================
# }}} Flags

# Boost {{{
# ==============================================================================
set(Boost_USE_STATIC_LIBS    OFF)
set(Boost_USE_STATIC_RUNTIME ON)
set(Boost_USE_MULTITHREADED  ON)
# ==============================================================================
# }}} Boost

# Components {{{
# ==============================================================================
add_subdirectory("${CMAKE_SOURCE_DIR}/components/Domain" ./Domain)
add_subdirectory("${CMAKE_SOURCE_DIR}/components/Core" ./Core)
add_subdirectory("${CMAKE_SOURCE_DIR}/components/Database" ./Database)
#add_subdirectory("${CMAKE_SOURCE_DIR}/components/LogViewer" ./LogViewer)
add_subdirectory("${CMAKE_SOURCE_DIR}/components/Application" ./Application)
add_subdirectory("${CMAKE_SOURCE_DIR}/libs/gtest" ./GTest)
add_subdirectory("${CMAKE_SOURCE_DIR}/components/Tests" ./Tests)
# ==============================================================================
# }}} Components

# vim:ft=cmake:fenc=utf-8:ff=unix:ts=2:sw=2:tw=80:et:
