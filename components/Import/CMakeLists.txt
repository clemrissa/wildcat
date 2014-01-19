cmake_minimum_required(VERSION 2.8.12)

# Define project {{{
# -----------------------------------------------------------------------------
project(Import CXX)
# -----------------------------------------------------------------------------
# Define project}}}

# Targets {{{
# ==============================================================================
set(TARGET_NAME ${PROJECT_NAME})

file(GLOB_RECURSE CPP_FILES source/*.cpp)
file(GLOB_RECURSE CPP_TEST_FILES tests/*.cpp)

add_library(${TARGET_NAME} SHARED ${CPP_FILES} ${CPP_TEST_FILES})
set_target_properties(${TARGET_NAME} PROPERTIES PREFIX "")

target_link_libraries(${TARGET_NAME} PRIVATE
  Uni
  DependencyManager
  Domain)

target_link_libraries(${TARGET_NAME} PUBLIC
                      ${SQLITE_LIBRARY}
                      ${ODB_LIBRARY}
                      ${ODBSQLITE_LIBRARY}
                      ${ODBQT_LIBRARY}
                      GTest)

#target_include_directories(${TARGET_NAME} PUBLIC "${SQLite_INCLUDE_DIR}")
#target_include_directories(${TARGET_NAME} PUBLIC "${ODB_INCLUDE_DIR}")
#target_include_directories(${TARGET_NAME} PUBLIC "${ODBSQLITE_INCLUDE_DIR}")
#target_include_directories(${TARGET_NAME} PUBLIC "${ODBQT_INCLUDE_DIR}")

target_include_directories(${TARGET_NAME} PUBLIC "include")
target_include_directories(${TARGET_NAME} PRIVATE "source")
target_include_directories(${TARGET_NAME} PRIVATE "tests")

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

#file(GLOB qmlFiles resource/*.qml)
#install(FILES ${qmlFiles} DESTINATION "${INSTALL_COMPONENT_DIR}/${PROJECT_NAME}")
#file(GLOB jsFiles resource/*.js)
#install(FILES ${jsFiles} DESTINATION "${INSTALL_COMPONENT_DIR}/${PROJECT_NAME}")
#install(DIRECTORY resource/imgs DESTINATION "${INSTALL_COMPONENT_DIR}/${PROJECT_NAME}")

install(FILES resource/${TARGET_NAME}.xml DESTINATION "${INSTALL_COMPONENT_DIR}")

file(GLOB lasFiles tests/data/*.las)
install(FILES ${lasFiles} DESTINATION "${INSTALL_COMPONENT_DIR}/../tests")
# ==============================================================================
# }}} Install
