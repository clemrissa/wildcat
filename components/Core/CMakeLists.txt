cmake_minimum_required(VERSION 2.8.12)

# Define project {{{
# -----------------------------------------------------------------------------
project(Core CXX)
# -----------------------------------------------------------------------------
# }}} Define project

# Targets {{{
# ==============================================================================
set(TARGET_NAME ${PROJECT_NAME})

file(GLOB_RECURSE CPP_FILES source/*.cpp)

add_library(${TARGET_NAME} SHARED ${CPP_FILES})
set_target_properties(${TARGET_NAME} PROPERTIES PREFIX "")

target_link_libraries(${TARGET_NAME} PRIVATE
                      Uni
                      DependencyManager)

target_include_directories(${TARGET_NAME} INTERFACE "include")
target_include_directories(${TARGET_NAME} PRIVATE "source")

target_compile_definitions(${TARGET_NAME} PUBLIC "-D${TARGET_NAME}_SHARED")
target_compile_definitions(${TARGET_NAME} PRIVATE "-D${TARGET_NAME}_EXPORTS")


target_use_qt5(${TARGET_NAME} PRIVATE Core Widgets Qml Quick)
target_use_boost(${TARGET_NAME} PRIVATE)

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
