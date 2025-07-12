function(add_executable_)
    set(NAME ${ARGV0})

    set(options WIN32)
    cmake_parse_arguments(PARSE_ARGV 1 ARG "${options}" "" "")

    set(SOURCES ${ARG_UNPARSED_ARGUMENTS})

    if(ARG_WIN32)
        add_executable(${NAME} WIN32 ${SOURCES})
    else()
        add_executable(${NAME} ${SOURCES})
    endif()

    foreach(FILE IN LISTS SOURCES)
        get_filename_component(SOURCE_PATH "${FILE}" PATH)
        string(REPLACE "/" "\\" SOURCE_PATH_GROUP "${SOURCE_PATH}")
        source_group("Source Files\\${SOURCE_PATH_GROUP}" FILES "${FILE}")
    endforeach()

    set_target_properties(${NAME}
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${LIBS_OUTPUT_DIRECTORY}/
        RUNTIME_OUTPUT_DIRECTORY ${ROOT_OUTPUT_DIRECTORY}/
        LIBRARY_OUTPUT_DIRECTORY ${DLLS_OUTPUT_DIRECTORY}/
    )

    set_property(DIRECTORY ${PROJECT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${NAME})
endfunction()
