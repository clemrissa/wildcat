SET(CMAKE_FIND_LIBRARY_PREFIXES "lib")
SET(CMAKE_FIND_LIBRARY_SUFFIXES ".so" ".a")

find_library(ODB_LIBRARY
             NAMES odb
             PATHS /lib/odb/
             NO_DEFAULT_PATH)

if(NOT ODB_LIBRARY)
  message(FATAL_ERROR "ODB library not found")
endif()

get_filename_component(ODB_LIBRARY_PATH ${ODB_LIBRARY} DIRECTORY CACHE)

get_filename_component(ODB_ROOT ${ODB_LIBRARY_PATH} DIRECTORY CACHE)

set(ODB_INCLUDE_DIR ${ODB_ROOT}/include)

set(ODB_SQLITE_INCLUDE_DIR ${ODB_INCLUDE_DIR})
set(ODB_QT_INCLUDE_DIR ${ODB_INCLUDE_DIR})


find_library(ODB_SQLITE_LIBRARY 
             PATHS /lib/odb/
             NAMES odb-sqlite)

find_library(ODB_QT_LIBRARY 
             PATHS /lib/odb/
             NAMES odb-qt)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(ODB
                                  DEFAULT_MSG
                                  ODB_LIBRARY)

find_package_handle_standard_args(ODB_SQLITE_LIBRARY
                                  DEFAULT_MSG
                                  ODB_SQLITE_LIBRARY)

find_package_handle_standard_args(ODB_QT_LIBRARY
                                  DEFAULT_MSG
                                  ODB_QT_LIBRARY)

