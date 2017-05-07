cmake_minimum_required(VERSION 3.2)

# ==============================================================================

# Define project

project(Wildcat CXX)

# ==============================================================================

# Targets

set(TARGET_NAME ${PROJECT_NAME})

file(GLOB_RECURSE CPP_FILES source/*.cpp)

add_executable(${TARGET_NAME} ${CPP_FILES})

target_link_libraries(${TARGET_NAME}
                      PRIVATE ComponentManager
                      PRIVATE Boost::filesystem
                      PRIVATE Boost::system
                      PRIVATE Qt5::Core
                      PRIVATE Qt5::Widgets
                      PRIVATE Qt5::Qml
                      PRIVATE Qt5::Quick)

target_include_directories(${TARGET_NAME} PRIVATE "${PROJECT_DIR}/source")
target_include_directories(${TARGET_NAME} PRIVATE $<TARGET_PROPERTY:Core,INTERFACE_INCLUDE_DIRECTORIES>)

# ==============================================================================

# Install

install(TARGETS ${TARGET_NAME}
        ARCHIVE DESTINATION ${INSTALL_LIBRARY_DIR}
        LIBRARY DESTINATION ${INSTALL_LIBRARY_DIR}
        RUNTIME DESTINATION ${INSTALL_BINARY_DIR})
