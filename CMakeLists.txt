cmake_minimum_required(VERSION 3.20)

project(GGSTEnhancer LANGUAGES CXX)

if (NOT CMAKE_SYSTEM_NAME STREQUAL "Windows")
    message(FATAL_ERROR "Configure this project with a Windows target, for example via MinGW-w64 on Linux.")
endif()

add_library(GGSTEnhancer SHARED
    GGSTEnhancer/GGSTEnhancer/dllmain.cpp
    GGSTEnhancer/GGSTEnhancer/Features.cpp
    GGSTEnhancer/GGSTEnhancer/Helpers.cpp
)

target_compile_features(GGSTEnhancer PRIVATE cxx_std_20)
target_include_directories(GGSTEnhancer PRIVATE GGSTEnhancer/GGSTEnhancer)
target_link_options(GGSTEnhancer PRIVATE -static -static-libgcc -static-libstdc++)

set_target_properties(GGSTEnhancer PROPERTIES
    OUTPUT_NAME "UMPDC"
    PREFIX ""
)
