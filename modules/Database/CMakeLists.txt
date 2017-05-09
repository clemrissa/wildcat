cmake_minimum_required(VERSION 3.2)

# ==============================================================================

# Define project

project(Database CXX)

# ==============================================================================

# Targets

set(TARGET_NAME ${PROJECT_NAME})

#file(GLOB_RECURSE CPP_FILES source/*.cpp)
file(GLOB CPP_FILES source/*.cpp)
file(GLOB CPP_FILES_C source/Connections/*.cpp)

#file(GLOB CPP_FILES_G_C source//*.cpp)

#file(GLOB_RECURSE CPP_TEST_FILES tests/*.cpp)
#file(GLOB_RECURSE RESOURCES resource/*.qrc)

#qt5_add_resources(RESOURCE_SOURCES ${RESOURCES})

add_library(${TARGET_NAME} SHARED ${CPP_FILES}  ${CPP_FILES_C}
  #${CPP_TEST_FILES} 
  #${RESOURCE_SOURCES}
  )

set_target_properties(${TARGET_NAME} PROPERTIES PREFIX "")

target_link_libraries(${TARGET_NAME} PRIVATE
                      ComponentManager
                      Domain
                      Qt5::Core
                      Qt5::Widgets
                      Qt5::Qml
                      Qt5::Quick
                      #Qt5::Xml
                      )

target_link_libraries(${TARGET_NAME} PUBLIC
                      ${SQLITE_LIBRARY}
                      ${ODB_LIBRARY}
                      ${ODBSQLITE_LIBRARY}
                      ${ODBQT_LIBRARY}
                      #GTest
                      )


target_include_directories(${TARGET_NAME} PUBLIC "${SQLite_INCLUDE_DIR}")
target_include_directories(${TARGET_NAME} PUBLIC "${ODB_INCLUDE_DIR}")
target_include_directories(${TARGET_NAME} PUBLIC "${ODBSQLITE_INCLUDE_DIR}")
target_include_directories(${TARGET_NAME} PUBLIC "${ODBQT_INCLUDE_DIR}")

target_include_directories(${TARGET_NAME} PUBLIC "include")
target_include_directories(${TARGET_NAME} PRIVATE "source")
target_include_directories(${TARGET_NAME} PRIVATE $<TARGET_PROPERTY:Core,INTERFACE_INCLUDE_DIRECTORIES>)
target_include_directories(${TARGET_NAME} PRIVATE $<TARGET_PROPERTY:Import,INTERFACE_INCLUDE_DIRECTORIES>)
target_include_directories(${TARGET_NAME} PRIVATE $<TARGET_PROPERTY:Widgets,INTERFACE_INCLUDE_DIRECTORIES>)
target_include_directories(${TARGET_NAME} PRIVATE $<TARGET_PROPERTY:Models,INTERFACE_INCLUDE_DIRECTORIES>)

target_compile_definitions(${TARGET_NAME} PUBLIC ${TARGET_NAME}_SHARED)
target_compile_definitions(${TARGET_NAME} PRIVATE ${TARGET_NAME}_EXPORTS)

# ==============================================================================

# Install

install(TARGETS ${TARGET_NAME}
        LIBRARY DESTINATION ${INSTALL_COMPONENT_DIR}
        RUNTIME DESTINATION ${INSTALL_COMPONENT_DIR})


#file(GLOB qmlFiles resource/*.qml)
#install(FILES ${qmlFiles} DESTINATION "${INSTALL_COMPONENT_DIR}/${PROJECT_NAME}")
#file(GLOB jsFiles resource/*.js)
#install(FILES ${jsFiles} DESTINATION "${INSTALL_COMPONENT_DIR}/${PROJECT_NAME}")
#install(DIRECTORY resource/imgs DESTINATION "${INSTALL_COMPONENT_DIR}/${PROJECT_NAME}")

#install(FILES resource/${TARGET_NAME}.xml DESTINATION "${INSTALL_COMPONENT_DIR}")
install(FILES resource/${TARGET_NAME}.json DESTINATION "${INSTALL_COMPONENT_DIR}")
