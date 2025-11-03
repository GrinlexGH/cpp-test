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

    foreach(source IN LISTS SOURCES)
        cmake_path(GET source PARENT_PATH source_directory)
        source_group("Source Files/${source_directory}" FILES "${source}")
    endforeach()

    set_property(DIRECTORY ${PROJECT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${NAME})
endfunction()
