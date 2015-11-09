cmake_minimum_required(VERSION 2.8.10)

# Define project {{{
# -----------------------------------------------------------------------------
project(Tests CXX)
# -----------------------------------------------------------------------------
# Define project}}}

# Targets {{{
# ==============================================================================
set(TARGET_NAME "Tests")
file(GLOB_RECURSE CPP_FILES source/*.cpp)

add_executable(${TARGET_NAME} ${CPP_FILES})

target_link_libraries(${TARGET_NAME} PRIVATE
                      Uni
                      DependencyManager
                      GTest
                      Qt5::Core
                      Qt5::Widgets
                      Qt5::Qml
                      Qt5::Quick)

target_include_directories(${TARGET_NAME} PRIVATE "${PROJECT_DIR}/source")
target_include_directories(${TARGET_NAME} PUBLIC ${GTEST_INCLUDE_DIR})

target_use_boost(${TARGET_NAME} PRIVATE)
# ==============================================================================
# }}} Targets

# Install {{{
# -----------------------------------------------------------------------------
install(TARGETS ${TARGET_NAME}
        ARCHIVE DESTINATION ${INSTALL_LIBRARY_DIR}
        LIBRARY DESTINATION ${INSTALL_LIBRARY_DIR}
        RUNTIME DESTINATION ${INSTALL_BINARY_DIR})
# -----------------------------------------------------------------------------
# }}} Install
