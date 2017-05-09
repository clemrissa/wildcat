cmake_minimum_required(VERSION 3.2)

# ==============================================================================

# CMake flags

set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES  ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_ERROR_DEPRECATED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_COLOR_MAKEFILE   ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
if (WIN32)
  set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif ()

set(CMAKE_BUILD_TYPE Debug)

# ==============================================================================

# Dependencies

set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# search modules in a folder located next to the geoqt5 root

#set(THIRDPARTY_ROOT_PATH ${CMAKE_SOURCE_DIR}/../thirdparty/${CMAKE_SYSTEM_NAME})

#set(THIRDPARTY_LIB_PATH
    #${THIRDPARTY_ROOT_PATH}/boost/1.61
    #${THIRDPARTY_ROOT_PATH}/hdf5
    #${THIRDPARTY_ROOT_PATH}/dependency_manager
    #${THIRDPARTY_ROOT_PATH}/Qt
    #${THIRDPARTY_ROOT_PATH}/odb-2.4.0
    #${THIRDPARTY_ROOT_PATH}/uni
    #)

#set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH}
    #/home/paceholder/projects/geoqt5_thirdparty/odb/lib
#)

# paths for seaching FindXXX.cmake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/modules)

# this populates thirdparty paths with ./shared/lib or ./shared/cmake etc
# so that we can find different FindXXX.cmake modules
#set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${THIRDPARTY_LIB_PATH})

# ==============================================================================

# Find Packages

find_package(ODB REQUIRED)
include(ODB)


find_package(Qt5 COMPONENTS
             Core
             Widgets
             Qml
             Quick
             Xml
             REQUIRED)

find_package(HDF5 REQUIRED)


set(Boost_USE_STATIC_LIBS    OFF)
set(Boost_USE_MULTITHREADED  ON)

find_package(Boost 1.6 REQUIRED
             COMPONENTS filesystem system)

# Configure SQLite

#set(SQLite_INCLUDE_DIR $ENV{SQLite_INCLUDE_DIR})
#set(SQLite_LIBRARY_DIR $ENV{SQLite_LIBRARY_DIR})
#find_package(SQLite REQUIRED)


# Definitions

add_definitions(-DMOC)
add_definitions(-DUNICODE)

# ==============================================================================

# Install rules

set(INSTALL_BINARY_DIR  bin)
set(INSTALL_INCLUDE_DIR include)
set(INSTALL_LIBRARY_DIR lib)
set(INSTALL_COMPONENT_DIR modules)
set(INSTALL_SOURCE_DIR  source)
if (WIN32)
  set(INSTALL_CMAKE_DIR cmake)
else()
  set(INSTALL_CMAKE_DIR lib/cmake)
endif ()


# vim:ft=cmake:fenc=utf-8:ff=unix:ts=2:sw=2:tw=80:et:

# ==============================================================================

# Modules

add_subdirectory("${CMAKE_SOURCE_DIR}/modules/Application" ./Application)
add_subdirectory("${CMAKE_SOURCE_DIR}/modules/Core" ./Core)
add_subdirectory("${CMAKE_SOURCE_DIR}/modules/LogViewer" ./LogViewer)
#add_subdirectory("${CMAKE_SOURCE_DIR}/modules/Widgets" ./Widgets)
add_subdirectory("${CMAKE_SOURCE_DIR}/modules/Domain" ./Domain)
#add_subdirectory("${CMAKE_SOURCE_DIR}/modules/Database" ./Database)
#add_subdirectory("${CMAKE_SOURCE_DIR}/modules/TypeSystem" ./TypeSystem)
#add_subdirectory("${CMAKE_SOURCE_DIR}/modules/Import" ./Import)
#add_subdirectory("${CMAKE_SOURCE_DIR}/modules/Models" ./Models)
#add_subdirectory("${CMAKE_SOURCE_DIR}/modules/Tests" ./Tests)

add_subdirectory("${CMAKE_SOURCE_DIR}/thirdparty" ./thirdparty)

