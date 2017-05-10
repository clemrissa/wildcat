cmake_minimum_required(VERSION 3.2)

# ==============================================================================

# Define project

project(Import CXX)

# ==============================================================================

# Targets

set(TARGET_NAME ${PROJECT_NAME})

file(GLOB_RECURSE CPP_FILES source/*.cpp)

add_library(${TARGET_NAME} SHARED ${CPP_FILES} ${CPP_TEST_FILES})

set_target_properties(${TARGET_NAME} PROPERTIES PREFIX "")

target_link_libraries(${TARGET_NAME} PRIVATE
                      ComponentManager
                      Domain)

target_link_libraries(${TARGET_NAME} PUBLIC
                      Qt5::Core
                      Qt5::Widgets
                      Qt5::Qml
                      Qt5::Quick
                      Qt5::Xml)

target_link_libraries(${TARGET_NAME} PUBLIC
                      ${SQLITE_LIBRARY}
                      ${ODB_LIBRARY}
                      ${ODBSQLITE_LIBRARY}
                      ${ODBQT_LIBRARY}
                      #GTest
                      )

target_include_directories(${TARGET_NAME} PUBLIC "include")
target_include_directories(${TARGET_NAME} PRIVATE "source")
target_include_directories(${TARGET_NAME} PRIVATE "tests")
target_include_directories(${TARGET_NAME} PRIVATE $<TARGET_PROPERTY:Core,INTERFACE_INCLUDE_DIRECTORIES>)
target_include_directories(${TARGET_NAME} PRIVATE $<TARGET_PROPERTY:Database,INTERFACE_INCLUDE_DIRECTORIES>)
target_include_directories(${TARGET_NAME} PRIVATE $<TARGET_PROPERTY:Models,INTERFACE_INCLUDE_DIRECTORIES>)

target_compile_definitions(${TARGET_NAME} PUBLIC ${TARGET_NAME}_SHARED)
target_compile_definitions(${TARGET_NAME} PRIVATE ${TARGET_NAME}_EXPORTS)

# ==============================================================================

file(GLOB_RECURSE CPP_TEST_FILES tests/*.cpp)

set(TARGET_TESTS_NAME ${PROJECT_NAME}Tests)

#add_library(${TARGET_TESTS_NAME} STATIC ${CPP_TEST_FILES})
add_library(${TARGET_TESTS_NAME} SHARED ${CPP_TEST_FILES})

target_link_libraries(${TARGET_TESTS_NAME} PRIVATE catch)
target_link_libraries(${TARGET_TESTS_NAME} PRIVATE ${PROJECT_NAME})

target_include_directories(${TARGET_TESTS_NAME} PUBLIC "include")

# ==============================================================================

# Install

install(TARGETS ${TARGET_TESTS_NAME}
        LIBRARY DESTINATION ${INSTALL_LIBRARY_DIR}
        RUNTIME DESTINATION ${INSTALL_LIBRARY_DIR})


install(TARGETS ${TARGET_NAME}
        LIBRARY DESTINATION ${INSTALL_COMPONENT_DIR}
        RUNTIME DESTINATION ${INSTALL_COMPONENT_DIR})

#file(GLOB qmlFiles resource/*.qml)
#install(FILES ${qmlFiles} DESTINATION "${INSTALL_COMPONENT_DIR}/${PROJECT_NAME}")
#file(GLOB jsFiles resource/*.js)
#install(FILES ${jsFiles} DESTINATION "${INSTALL_COMPONENT_DIR}/${PROJECT_NAME}")
#install(DIRECTORY resource/imgs DESTINATION "${INSTALL_COMPONENT_DIR}/${PROJECT_NAME}")

install(FILES resource/${TARGET_NAME}.json DESTINATION "${INSTALL_COMPONENT_DIR}")

file(GLOB lasFiles tests/data/*.las)
install(FILES ${lasFiles} DESTINATION "${INSTALL_COMPONENT_DIR}/../tests")
