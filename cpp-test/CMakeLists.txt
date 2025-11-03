set(PROJECTS
    locales
    bitfields
    fast
)

if(WIN32 AND TARGET SDL3::SDL3 AND TARGET Qt6::Core AND TARGET Qt6::Widgets AND TARGET nowide::nowide)
    list(APPEND PROJECTS visual_styles)
endif()

if(WIN32 AND TARGET Win32xx::Win32xx)
    list(APPEND PROJECTS win32xx)
endif()

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ROOT_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/.output/$<CONFIG>/)
set(DLLS_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/.output/$<CONFIG>/bin)
set(LIBS_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/.output/$<CONFIG>/libs)
set(SHADER_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/.output/$<CONFIG>/shaders)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(
        "-Wall" "-Wextra" "-Wpedantic"
        #"$<$<CONFIG:Release>:-Werror>"
        "$<$<OR:$<CONFIG:Release>,$<CONFIG:RelWithDebInfo>>:-O3>"
        "-march=native" "-mtune=native"
        "-masm=intel"
    )
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_options(
        "/W4" "/utf-8" "/Zc:__cplusplus" "/MP"
        "$<$<CONFIG:Release>:/WX;/Ox>"
    )
endif()

add_compile_definitions(
    NOMINMAX
    $<$<CONFIG:Debug>:DEBUG>
    $<$<CONFIG:RelWithDebInfo>:DEBUG>
    VULKAN_HPP_DISPATCH_LOADER_DYNAMIC=1
    VMA_STATIC_VULKAN_FUNCTIONS=0
    VMA_DYNAMIC_VULKAN_FUNCTIONS=0
)

if(WIN32)
    add_compile_definitions(VK_USE_PLATFORM_WIN32_KHR)
endif()

include(cpp-test/ProjectBase)

foreach(PROJECT ${PROJECTS})
    add_subdirectory("${PROJECT}")
endforeach()

if(WIN32)
    foreach(PROJECT ${PROJECTS})
        set_target_properties(${PROJECT} PROPERTIES PREFIX "")
    endforeach()
endif()
