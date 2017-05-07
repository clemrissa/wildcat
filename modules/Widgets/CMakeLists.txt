cmake_minimum_required(VERSION 3.2)

# ==============================================================================

# Define project

project(Widgets CXX)

# ==============================================================================

# Targets

set(TARGET_NAME ${PROJECT_NAME})

file(GLOB_RECURSE CPP_FILES source/*.cpp)

file(GLOB_RECURSE CPP_TEST_FILES tests/*.cpp)


add_library(${TARGET_NAME} SHARED ${CPP_FILES})

set_target_properties(${TARGET_NAME} PROPERTIES PREFIX "")

target_link_libraries(${TARGET_NAME} PRIVATE
                      ComponentManager
                      Domain
                      Qt5::Core
                      Qt5::Widgets
                      Qt5::Qml
                      Qt5::Quick)

target_include_directories(${TARGET_NAME} PUBLIC "include")
target_include_directories(${TARGET_NAME} PRIVATE "source")
target_include_directories(${TARGET_NAME} PRIVATE $<TARGET_PROPERTY:Database,INTERFACE_INCLUDE_DIRECTORIES>)
target_include_directories(${TARGET_NAME} PRIVATE $<TARGET_PROPERTY:Models,INTERFACE_INCLUDE_DIRECTORIES>)

target_compile_definitions(${TARGET_NAME} PUBLIC "-D${TARGET_NAME}_SHARED")
target_compile_definitions(${TARGET_NAME} PRIVATE "-D${TARGET_NAME}_EXPORTS")

# ==============================================================================

# Install

install(TARGETS ${TARGET_NAME}
        LIBRARY DESTINATION ${INSTALL_COMPONENT_DIR}
        RUNTIME DESTINATION ${INSTALL_COMPONENT_DIR})

install(FILES resource/${TARGET_NAME}.xml DESTINATION "${INSTALL_COMPONENT_DIR}")
