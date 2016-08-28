# General {{{
# ==============================================================================
cmake_minimum_required(VERSION 3.1)
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

#set(CMAKE_INSTALL_RPATH "/usr/local/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# search modules in a folder located next to the geoqt5 root

set(THIRDPARTY_ROOT_PATH ${CMAKE_SOURCE_DIR}/../thirdparty/${CMAKE_SYSTEM_NAME})

set(THIRDPARTY_LIB_PATH
    ${THIRDPARTY_ROOT_PATH}/boost/1.61
    ${THIRDPARTY_ROOT_PATH}/hdf5
    ${THIRDPARTY_ROOT_PATH}/dependency_manager
    ${THIRDPARTY_ROOT_PATH}/Qt
    ${THIRDPARTY_ROOT_PATH}/odb-2.4.0
    ${THIRDPARTY_ROOT_PATH}/uni
    )

set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH}
/home/paceholder/projects/geoqt5_thirdparty/odb/lib
)

# paths for seaching FindXXX.cmake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/modules)

# this populates thirdparty paths with ./shared/lib or ./shared/cmake etc
# so that we can find different FindXXX.cmake modules
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${THIRDPARTY_LIB_PATH})

#---------------------------------------

find_package(ODB REQUIRED)
include(ODB)

#---------------------------------------

find_package(Qt5 COMPONENTS
             Core
             Widgets
             Qml
             Quick
             Xml
             REQUIRED)

find_package(DependencyManager REQUIRED)
find_package(Uni REQUIRED)
find_package(HDF5 REQUIRED)

#---------------------------------------

set(Boost_USE_STATIC_LIBS    OFF)
set(Boost_USE_STATIC_RUNTIME ON)
set(Boost_USE_MULTITHREADED  ON)

set(BOOST_ROOT ${THIRDPARTY})

find_package(Boost 1.55.0 COMPONENTS filesystem system REQUIRED)

if(Boost_FOUND)
  #message("******** Boost_INCLUDE_DIRS ${Boost_INCLUDE_DIRS}")
  #message("******** Boost_FILESYSTEM ${Boost_FILESYSTEM_LIBRARY}")
  #message("******** Boost_SYSTEM ${Boost_SYSTEM_LIBRARY}")
endif()

# ==============================================================================
# }}} Modules

# Configure SQLite {{{
# -----------------------------------------------------------------------------
#set(SQLite_INCLUDE_DIR $ENV{SQLite_INCLUDE_DIR})
#set(SQLite_LIBRARY_DIR $ENV{SQLite_LIBRARY_DIR})

#find_package(SQLite REQUIRED)
# -----------------------------------------------------------------------------
# }}} Configure SQLite


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

  # to compile boost with c++11
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fext-numeric-literals")

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


# Components {{{
# ==============================================================================
add_subdirectory("${CMAKE_SOURCE_DIR}/components/Widgets" ./Widgets)
add_subdirectory("${CMAKE_SOURCE_DIR}/components/Models" ./Models)
add_subdirectory("${CMAKE_SOURCE_DIR}/components/Domain" ./Domain)
add_subdirectory("${CMAKE_SOURCE_DIR}/components/Core" ./Core)
add_subdirectory("${CMAKE_SOURCE_DIR}/components/Database" ./Database)
add_subdirectory("${CMAKE_SOURCE_DIR}/components/TypeSystem" ./TypeSystem)
add_subdirectory("${CMAKE_SOURCE_DIR}/components/LogViewer" ./LogViewer)
add_subdirectory("${CMAKE_SOURCE_DIR}/components/Import" ./Import)
add_subdirectory("${CMAKE_SOURCE_DIR}/components/Application" ./Application)
add_subdirectory("${CMAKE_SOURCE_DIR}/components/Tests" ./Tests)
# ==============================================================================
# }}} Components

# vim:ft=cmake:fenc=utf-8:ff=unix:ts=2:sw=2:tw=80:et:
