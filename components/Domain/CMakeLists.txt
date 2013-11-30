cmake_minimum_required(VERSION 2.8.12)

# Define project {{{
# -----------------------------------------------------------------------------
project(Domain CXX)
# -----------------------------------------------------------------------------
# Define project}}}

# Targets {{{
# ==============================================================================
set(TARGET_NAME ${PROJECT_NAME})

file(GLOB_RECURSE CPP_FILES source/*.cpp)

set(ODB_HEADERS ${PROJECT_SOURCE_DIR}/source/Well.hpp
                ${PROJECT_SOURCE_DIR}/source/Log.hpp)

find_qt5_component(Core)

odb_compile(HEADER ${ODB_HEADERS}
  DB sqlite
  STANDARD c++11
  GENERATE_QUERY GENERATE_SESSION GENERATE_SCHEMA
  PROFILE qt
  INCLUDE
  ${Qt5Core_INCLUDE_DIRS}
  ${SQLite_INCLUDE_DIR}
  ${ODB_INCLUDE_DIR}
  ${ODBSQLITE_INCLUDE_DIR}
  ${ODBQT_INCLUDE_DIR}
  source
  HEADER_SUFFIX ".hpp"
  SOURCE_SUFFIX ".cpp"
  INLINE_SUFFIX ".inline.hpp"
  FILE_SUFFIX ".odb"
  OUTPUT "CPP_FILES")

add_library(${TARGET_NAME} STATIC ${CPP_FILES})

target_link_libraries(${TARGET_NAME} PUBLIC
  Uni
  ${SQLITE_LIBRARY}
  ${ODB_LIBRARY}
  ${ODBSQLITE_LIBRARY}
  ${ODBQT_LIBRARY})

target_include_directories(${TARGET_NAME} PUBLIC "${SQLite_INCLUDE_DIR}")
target_include_directories(${TARGET_NAME} PUBLIC "${ODB_INCLUDE_DIR}")
target_include_directories(${TARGET_NAME} PUBLIC "${ODBSQLITE_INCLUDE_DIR}")
target_include_directories(${TARGET_NAME} PUBLIC "${ODBQT_INCLUDE_DIR}")

target_include_directories(${TARGET_NAME} PUBLIC "include")
target_include_directories(${TARGET_NAME} PRIVATE "source")

target_use_qt5(${TARGET_NAME} PUBLIC Core)
target_use_boost(${TARGET_NAME} PUBLIC)

# ==============================================================================
# }}} Targets

# Install {{{
# -----------------------------------------------------------------------------
install(TARGETS ${PROJECT_NAME}
        ARCHIVE DESTINATION ${INSTALL_LIBRARY_DIR})
# -----------------------------------------------------------------------------
# }}} Install
