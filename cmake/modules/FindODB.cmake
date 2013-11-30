


find_library(ODB_LIBRARY
             NAMES odb
             PATHS ${ODB_LIBRARY_DIR})


find_library(ODBSQLITE_LIBRARY
             NAMES odb-sqlite
             PATHS ${ODBSQLITE_LIBRARY_DIR})

find_library(ODBQT_LIBRARY
             NAMES odb-qt
             PATHS ${ODBQT_LIBRARY_DIR})

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(ODB
                                  DEFAULT_MSG
                                  ODB_LIBRARY)

find_package_handle_standard_args("ODB Sqlite"
                                  DEFAULT_MSG
                                  ODBSQLITE_LIBRARY)

find_package_handle_standard_args("ODB Qt"
                                  DEFAULT_MSG
                                  ODBQT_LIBRARY)
