cmake_minimum_required(VERSION 3.25)

project(cpp-test LANGUAGES CXX C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_COLOR_DIAGNOSTICS ON)
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/Modules")

# Global settings
include(cpp-test/ToolchainSetup)
include(cpp-test/CompileOptions)
include(cpp-test/ThirdParty)

# cpp-test
include_directories("${PROJECT_SOURCE_DIR}")
add_subdirectory(cpp-test)
