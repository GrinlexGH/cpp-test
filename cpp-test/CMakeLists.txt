set(PROJECTS
    bitfields
    fast
    locales
    qt-test
    win32xx
    wxwidgets-test
)

set(OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/.output/$<CONFIG>)

set(CMAKE_PDB_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})
set(CMAKE_COMPILE_PDB_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

set(CMAKE_SKIP_RPATH FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH FALSE)
set(CMAKE_INSTALL_RPATH "$ORIGIN")

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Warnings
if(IS_GNU_LIKE)
    add_compile_options(
        "-Wall" "-Wextra" "-Wpedantic"
        #"$<$<CONFIG:Release>:-Werror>"
    )
elseif(IS_MSVC_LIKE)
    add_compile_options(
        "/W4"
        #"$<$<CONFIG:Release>:/WX>"
    )
endif()

# All global macros
add_compile_definitions(
    NOMINMAX
    $<$<CONFIG:Debug>:DEBUG> $<$<CONFIG:RelWithDebInfo>:DEBUG>
    VULKAN_HPP_DISPATCH_LOADER_DYNAMIC=1
    VULKAN_HPP_TYPESAFE_CONVERSION=1
    VMA_STATIC_VULKAN_FUNCTIONS=0
    VMA_DYNAMIC_VULKAN_FUNCTIONS=0
)

if(WIN32)
    add_compile_definitions(VK_USE_PLATFORM_WIN32_KHR)
endif()

include(cpp-test/ProjectBase)

foreach(PROJECT ${PROJECTS})
    add_subdirectory("${PROJECT}")
    if((TARGET ${PROJECT}) AND WIN32)
        set_target_properties(${PROJECT} PROPERTIES PREFIX "")
    endif()
endforeach()
