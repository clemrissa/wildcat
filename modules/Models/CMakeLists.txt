cmake_minimum_required(VERSION 2.8.12)

# Define project {{{
# -----------------------------------------------------------------------------
project(Models CXX)
# -----------------------------------------------------------------------------
# Define project}}}

# Targets {{{
# ==============================================================================
set(TARGET_NAME ${PROJECT_NAME})

file(GLOB_RECURSE CPP_FILES source/*.cpp)
file(GLOB_RECURSE CPP_TEST_FILES tests/*.cpp)

add_library(${TARGET_NAME} SHARED ${CPP_FILES})
set_target_properties(${TARGET_NAME} PROPERTIES PREFIX "")

target_link_libraries(${TARGET_NAME} PRIVATE
                      DependencyManager
                      Domain
                      Qt5::Core
                      Qt5::Widgets
                      Qt5::Gui
                      Qt5::Qml
                      Qt5::Quick
                      Qt5::Xml)

target_include_directories(${TARGET_NAME} PUBLIC "include")
target_include_directories(${TARGET_NAME} PRIVATE "source")
target_include_directories(${TARGET_NAME} PRIVATE $<TARGET_PROPERTY:Database,INTERFACE_INCLUDE_DIRECTORIES>)

target_compile_definitions(${TARGET_NAME} PUBLIC "-D${TARGET_NAME}_SHARED")
target_compile_definitions(${TARGET_NAME} PRIVATE "-D${TARGET_NAME}_EXPORTS")

# ==============================================================================
# }}} Targets

# Install {{{
# ==============================================================================
install(TARGETS ${TARGET_NAME}
        LIBRARY DESTINATION ${INSTALL_COMPONENT_DIR}
        RUNTIME DESTINATION ${INSTALL_COMPONENT_DIR})

install(FILES resource/${TARGET_NAME}.xml DESTINATION "${INSTALL_COMPONENT_DIR}")
# ==============================================================================

# }}} Install

