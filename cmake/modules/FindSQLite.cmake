find_library(SQLITE_LIBRARY
             NAMES sqlite3
             PATHS ${SQLite_LIBRARY_DIR})

set(SQLITE_INCLUDE_DIR ${SQLite_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args("SQLite"
                                  DEFAULT_MSG
                                  SQLITE_LIBRARY)
