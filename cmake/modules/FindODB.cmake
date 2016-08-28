find_library(ODB_LIBRARY
             NAMES odb)

get_filename_component(ODB_LIBRARY_PATH ${ODB_LIBRARY} DIRECTORY CACHE)

get_filename_component(ODB_ROOT ${ODB_LIBRARY_PATH} DIRECTORY CACHE)

set(ODB_INCLUDE_DIR ${ODB_ROOT}/include)

set(ODBSQLITE_INCLUDE_DIR ${ODB_INCLUDE_DIR})
set(ODBQT_INCLUDE_DIR ${ODB_INCLUDE_DIR})


find_library(ODBSQLITE_LIBRARY
             NAMES odb-sqlite)

find_library(ODBQT_LIBRARY
             NAMES odb-qt)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(ODB
                                  DEFAULT_MSG
                                  ODB_LIBRARY)

find_package_handle_standard_args(ODBSQLITE_LIBRARY
                                  DEFAULT_MSG
                                  ODBSQLITE_LIBRARY)

find_package_handle_standard_args(ODBQT_LIBRARY
                                  DEFAULT_MSG
                                  ODBQT_LIBRARY)

