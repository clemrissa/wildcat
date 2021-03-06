cmake_minimum_required(VERSION 3.2)

# ==============================================================================

# Define project

project(Domain CXX)

# ==============================================================================

# Targets

set(TARGET_NAME ${PROJECT_NAME})

file(GLOB_RECURSE CPP_FILES source/*.cpp)

set(ODB_HEADERS ${PROJECT_SOURCE_DIR}/source/Well.hpp
                ${PROJECT_SOURCE_DIR}/source/Log.hpp
                ${PROJECT_SOURCE_DIR}/source/WellTrait.hpp
                ${PROJECT_SOURCE_DIR}/source/WellTraitValue.hpp
                ${PROJECT_SOURCE_DIR}/source/LogParameter.hpp
                ${PROJECT_SOURCE_DIR}/source/LogParameterGroup.hpp
                ${PROJECT_SOURCE_DIR}/source/CurveType.hpp
                ${PROJECT_SOURCE_DIR}/source/Dimensions.hpp
                ${PROJECT_SOURCE_DIR}/source/Unit.hpp
                )


odb_compile(HEADER ${ODB_HEADERS}
            DB sqlite
            STANDARD c++11
            GENERATE_QUERY GENERATE_SESSION GENERATE_SCHEMA
            PROFILE qt
            INCLUDE
            ${Qt5Core_INCLUDE_DIRS}
            ${SQLite_INCLUDE_DIR}
            ${ODB_INCLUDE_DIR}
            ${ODB_SQLITE_INCLUDE_DIR}
            ${ODB_QT_INCLUDE_DIR}
            source
            HEADER_SUFFIX ".hpp"
            SOURCE_SUFFIX ".cpp"
            INLINE_SUFFIX ".inline.hpp"
            FILE_SUFFIX ".odb"
            OUTPUT "CPP_FILES")

add_library(${TARGET_NAME} SHARED ${CPP_FILES})

target_link_libraries(${TARGET_NAME} PUBLIC
                      ${SQLITE_LIBRARY}
                      ${ODB__LIBRARY}
                      ${ODB_SQLITE_LIBRARY}
                      ${ODB_QT_LIBRARY})


target_link_libraries(${TARGET_NAME} PRIVATE
                      Qt5::Core)

target_include_directories(${TARGET_NAME} PUBLIC "${SQLite_INCLUDE_DIR}")
target_include_directories(${TARGET_NAME} PUBLIC "${ODB_INCLUDE_DIR}")
target_include_directories(${TARGET_NAME} PUBLIC "${ODB_SQLITE_INCLUDE_DIR}")
target_include_directories(${TARGET_NAME} PUBLIC "${ODB_QT_INCLUDE_DIR}")

target_include_directories(${TARGET_NAME} PUBLIC "include")
target_include_directories(${TARGET_NAME} PRIVATE "source")

target_include_directories(${TARGET_NAME} SYSTEM PUBLIC "${Boost_INCLUDE_DIRS}")

# ==============================================================================

# Install

install(TARGETS ${PROJECT_NAME}
        ARCHIVE DESTINATION ${INSTALL_LIBRARY_DIR}
        LIBRARY DESTINATION ${INSTALL_LIBRARY_DIR})
