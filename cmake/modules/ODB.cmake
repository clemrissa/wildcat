include(CMakeParseArguments)

find_program(ODB_EXECUTABLE NAMES odb DOC "ODB executable")
mark_as_advanced(ODB_EXECUTABLE)

function(odb_compile)
    if(NOT ODB_EXECUTABLE)
        message(SEND_ERROR "odb compiler not found")
    endif()

    # Parse arguments passed
    set(options GENERATE_QUERY GENERATE_SESSION GENERATE_SCHEMA)
    set(oneValueParams DB SCHEMA_FORMAT SCHEMA_NAME TABLE_PREFIX
        STANDARD OUTPUT_DIRECTORY SLOC_LIMIT
        HEADER_SUFFIX INLINE_SUFFIX SOURCE_SUFFIX FILE_SUFFIX
        HEADER_PROLOGUE INLINE_PROLOGUE SOURCE_PROLOGUE
        HEADER_EPILOGUE INLINE_EPILOGUE SOURCE_EPILOGUE
    PROFILE OUTPUT INCLUDE_PREFIX)
    set(multiValueParams HEADER INCLUDE)

    cmake_parse_arguments(PARAM "${options}"
        "${oneValueParams}" "${multiValueParams}" ${ARGN})

    if (PARAM_UNPARSED_ARGUMENTS)
        message(FATAL_ERROR "Unknown keywords given to ODB_COMPILE(): \"${PARAM_UNPARSED_ARGUMENTS}\"")
    endif()

    if (NOT PARAM_HEADER)
        message(FATAL_ERROR "HEADER parameter missing")
    endif()

    if (NOT PARAM_OUTPUT)
        message(FATAL_ERROR "OUTPUT parameter missing")
    endif()

    # We need some defaults for this to work in a nice way.
    # These differ from the odb defaults, simply because
    # I find these more common than the odb .?xx extensions.
    set(odb_output_directory ${CMAKE_CURRENT_BINARY_DIR})
    set(odb_header_suffix ".hpp")
    set(odb_inline_suffix ".inline.hpp")
    set(odb_source_suffix ".cpp")
    set(odb_file_suffix ".odb")

    # This variable contains the command line arguments
    # passed to odb.
    set(ODB_ARGS -DODB -x -fPIC)

    if(PARAM_GENERATE_QUERY)
        list(APPEND ODB_ARGS --generate-query)
    endif()

    if(PARAM_GENERATE_SESSION)
        list(APPEND ODB_ARGS --generate-session)
    endif()

    if(PARAM_GENERATE_SCHEMA)
        list(APPEND ODB_ARGS --generate-schema)
    endif()

    if(PARAM_DB)
        list(APPEND ODB_ARGS --database ${PARAM_DB})
    endif()

    if(PARAM_SCHEMA_FORMAT)
        list(APPEND ODB_ARGS --schema-format ${PARAM_SCHEMA_FORMAT})
    endif()

    if(PARAM_SCHEMA_NAME)
        list(APPEND ODB_ARGS --schema-name ${PARAM_SCHEMA_NAME})
    endif()

    if(PARAM_TABLE_PREFIX)
        list(APPEND ODB_ARGS --table-prefix ${PARAM_TABLE_PREFIX})
    endif()

    if(PARAM_STANDARD)
        list(APPEND ODB_ARGS --std ${PARAM_STANDARD})
     endif()

    if(PARAM_OUTPUT_DIRECTORY)
        set(odb_output_directory ${PARAM_OUTPUT_DIRECTORY})
    endif()

    if(PARAM_SLOC_LIMIT)
        list(APPEND ODB_ARGS --sloc-limit {PARAM_SLOC_LIMIT})
    endif()

    if(PARAM_HEADER_SUFFIX)
        set(odb_header_suffix ${PARAM_HEADER_SUFFIX})
    endif()

    if(PARAM_INLINE_SUFFIX)
        set(odb_inline_suffix ${PARAM_INLINE_SUFFIX})
    endif()

    if(PARAM_SOURCE_SUFFIX)
        set(odb_source_suffix ${PARAM_SOURCE_SUFFIX})
    endif()

    if(PARAM_FILE_SUFFIX)
        set(odb_file_suffix ${PARAM_FILE_SUFFIX})
    endif()

    if(PARAM_HEADER_PROLOGUE)
        list(APPEND ODB_ARGS --hxx-prologue-file ${PARAM_HEADER_PROLOGUE})
    endif()
    if(PARAM_INLINE_PROLOGUE)
        list(APPEND ODB_ARGS --ixx-prologue-file ${PARAM_INLINE_PROLOGUE})
    endif()
    if(PARAM_SOURCE_PROLOGUE)
        list(APPEND ODB_ARGS --cxx-prologue-file ${PARAM_SOURCE_PROLOGUE})
    endif()
    if(PARAM_HEADER_EPILOGUE)
        list(APPEND ODB_ARGS --hxx-epilogue-file ${PARAM_HEADER_EPILOGUE})
    endif()
    if(PARAM_INLINE_EPILOGUE)
        list(APPEND ODB_ARGS --ixx-epilogue-file ${PARAM_INLINE_EPILOGUE})
    endif()
    if(PARAM_SOURCE_EPILOGUE)
        list(APPEND ODB_ARGS --cxx-epilogue-file ${PARAM_SOURCE_EPILOGUE})
    endif()

    if(PARAM_PROFILE)
        list(APPEND ODB_ARGS --profile ${PARAM_PROFILE})
    endif()

  if(PARAM_INCLUDE_PREFIX)
        list(APPEND ODB_ARGS --include-prefix ${PARAM_INCLUDE_PREFIX})
    endif()


    list(APPEND ODB_ARGS --output-dir ${odb_output_directory})
    list(APPEND ODB_ARGS --hxx-suffix ${odb_header_suffix})
    list(APPEND ODB_ARGS --ixx-suffix ${odb_inline_suffix})
    list(APPEND ODB_ARGS --cxx-suffix ${odb_source_suffix})
    list(APPEND ODB_ARGS --odb-file-suffix ${odb_file_suffix})

    foreach(dir ${PARAM_INCLUDE})
        list(APPEND ODB_ARGS -I${dir})
    endforeach()

  #file(MAKE_DIRECTORY "${odb_output_directory}")

    set(output_files)
    foreach(input ${PARAM_HEADER})
        get_filename_component(output ${input} NAME_WE)
        set(output "${output}${odb_file_suffix}${odb_source_suffix}")

        list(APPEND output_files "${odb_output_directory}/${output}")
    endforeach()

    add_custom_command(
        OUTPUT ${output_files}
        #COMMAND "LD_LIBRARY_PATH=${ODB_LIBRARY_PATH} 
        COMMAND ${ODB_EXECUTABLE} ${ODB_ARGS} ${PARAM_HEADER}
        DEPENDS ${PARAM_HEADER}
    )
  set(${PARAM_OUTPUT} ${${PARAM_OUTPUT}} ${output_files} PARENT_SCOPE)
endfunction()

# OCB.cmake - ODB Support for CMake
