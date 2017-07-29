cmake_minimum_required(VERSION 2.8.10)

# ==============================================================================

# Define project

project(Tests CXX)

# ==============================================================================

# Targets

set(TARGET_NAME ${PROJECT_NAME})

file(GLOB_RECURSE CPP_FILES "source/*.cpp")

add_executable(${TARGET_NAME} ${CPP_FILES})

target_link_libraries(${TARGET_NAME} PRIVATE
                      catch
                      ComponentManager
                      Import
                      ImportTests
                      Database
                      Qt5::Core
                      Qt5::Widgets
                      Qt5::Qml
                      Qt5::Quick)

target_include_directories(${TARGET_NAME} PRIVATE "${PROJECT_DIR}/source")

# ==============================================================================

# Install

install(TARGETS ${TARGET_NAME}
        ARCHIVE DESTINATION ${INSTALL_LIBRARY_DIR}
        LIBRARY DESTINATION ${INSTALL_LIBRARY_DIR}
        RUNTIME DESTINATION ${INSTALL_BINARY_DIR})
