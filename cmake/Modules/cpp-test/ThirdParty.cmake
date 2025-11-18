# Third party shared libraries
include(Deps)

if(ANDROID)
    deps_append_cmake_define(ANDROID_ABI)
    deps_append_cmake_define(CMAKE_ANDROID_ARCH_ABI)
endif()

# Compilation of libraries
deps_add_cmake_project(
    "VulkanMemoryAllocator-Hpp/Vulkan-Headers" INSTALL_SUBDIR "VulkanHeaders"
    CMAKE_ARGS
    "-DVULKAN_HEADERS_ENABLE_TESTS=OFF -DVULKAN_HEADERS_ENABLE_INSTALL=ON"
)
deps_add_cmake_project(
    "VulkanMemoryAllocator-Hpp/VulkanMemoryAllocator"
    CMAKE_ARGS
    "-DVMA_BUILD_DOCUMENTATION=OFF -DVMA_BUILD_SAMPLES=OFF -DVMA_ENABLE_INSTALL=ON"
)
deps_add_cmake_project(
    "VulkanMemoryAllocator-Hpp"
    CMAKE_ARGS
    "-DVMA_HPP_ENABLE_INSTALL=ON -DVMA_HPP_ENABLE_MODULE=OFF"
    "-DVMA_HPP_GENERATOR_BUILD=OFF -DVMA_HPP_RUN_GENERATOR=OFF -DVMA_HPP_SAMPLES_BUILD=OFF"
)
deps_add_cmake_project("SDL" INSTALL_SUBDIR "SDL3" CMAKE_ARGS "-DSDL_TEST_LIBRARY=OFF")
deps_add_cmake_project(
    "SDL_image" INSTALL_SUBDIR "SDL3_image"
    CMAKE_ARGS
    "-DSDLIMAGE_AVIF=OFF -DSDLIMAGE_LBM=OFF -DSDLIMAGE_PCX=OFF -DSDLIMAGE_TIF=OFF"
    "-DSDLIMAGE_XCF=OFF -DSDLIMAGE_XPM=OFF -DSDLIMAGE_XV=OFF -DSDLIMAGE_WEBP=OFF"
)

deps_add_cmake_project(
    "wxWidgets" BUILD_DEBUG BUILD_FOLDER "cmake-build"
    CMAKE_ARGS
    "-DwxBUILD_SHARED=OFF -DwxBUILD_INSTALL=ON -DwxBUILD_INSTALL_PDB=ON"
)
deps_add_cmake_project(
    "benchmark" BUILD_DEBUG
    CMAKE_ARGS
    "-DBENCHMARK_ENABLE_TESTING=OFF -DBENCHMARK_ENABLE_WERROR=OFF -DBENCHMARK_ENABLE_LTO=ON"
)
deps_add_cmake_project("googletest" BUILD_DEBUG INSTALL_SUBDIR "GTest")
deps_add_cmake_project("nowide" BUILD_DEBUG)
deps_add_cmake_project("glm" BUILD_DEBUG CMAKE_ARGS "-DGLM_ENABLE_CXX_20=ON")

deps_add_header_only("tinyobjloader" HEADERS "tiny_obj_loader.h")
deps_add_header_only("simple_term_colors" HEADERS "include/stc.hpp")

deps_add_manual_install(
    "SteamworksSDK"
    RULES
    "redistributable_bin/**/*.dll"      "bin"
    "public/steam/lib/**/*.dll"         "bin"
    "public/steam/*.h"                  "include/steam"
    "redistributable_bin/**/*.lib"      "lib"
    "redistributable_bin/**/*.so"       "lib"
    "redistributable_bin/**/*.dylib"    "lib"
    "public/steam/lib/**/*.lib"         "lib"
    "public/steam/lib/**/*.so"          "lib"
    "public/steam/lib/**/*.dylib"       "lib"
)
deps_add_manual_install(
    "Win32xx"
    RULES
    "include/*.h"                       "include"
    "include/*.rc"                      "include"
)

deps_build_all()

# Find these libraries
include_directories(SYSTEM "${DEPS_HEADER_ONLY_INCLUDE_DIR}")

find_package(SteamworksSDK OPTIONAL)
find_package(Win32xx OPTIONAL)
find_package(SDL3 OPTIONAL)
find_package(SDL3_image OPTIONAL)
find_package(VulkanHeaders OPTIONAL)
find_package(VulkanMemoryAllocator OPTIONAL)
find_package(VulkanMemoryAllocator-Hpp OPTIONAL)
find_package(Qt6 OPTIONAL COMPONENTS Core Widgets)
find_package(wxWidgets CONFIG OPTIONAL) # FindwxWidgets module cant handle clang...
find_package(nowide OPTIONAL)
find_package(glm OPTIONAL)
find_package(benchmark OPTIONAL)
find_package(GTest OPTIONAL)
