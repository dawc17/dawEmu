cmake_minimum_required(VERSION 3.24)

project(dawEmu VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(DAWEMU_BUILD_TESTS "Build dawEmu test targets" ON)

include(FetchContent)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)

FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG v2.0.8
    SOURCE_SUBDIR cmake
)

FetchContent_MakeAvailable(glfw glad)

glad_add_library(glad_gl_core_33 REPRODUCIBLE API gl:core=3.3)

find_package(OpenGL REQUIRED)

function(dawemu_set_warnings target_name)
    if(MSVC)
        target_compile_options(${target_name} PRIVATE /W4 /permissive-)
    else()
        target_compile_options(${target_name} PRIVATE -Wall -Wextra -Wpedantic)
    endif()
endfunction()

add_library(dawEmu_core STATIC
    src/core/Emulator.cpp
    src/core/cart/Cartridge.cpp
    src/core/memory/Bus.cpp
    src/core/cpu/Cpu.cpp
)

target_include_directories(dawEmu_core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(dawEmu_core PUBLIC cxx_std_20)
dawemu_set_warnings(dawEmu_core)

add_executable(dawEmu
    src/main.cpp
)

target_link_libraries(dawEmu
    PRIVATE
        dawEmu_core
        glfw
        glad_gl_core_33
        OpenGL::GL
)

target_compile_features(dawEmu PRIVATE cxx_std_20)
dawemu_set_warnings(dawEmu)

if(DAWEMU_BUILD_TESTS)
    enable_testing()

    FetchContent_Declare(
        catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.6.0
    )

    FetchContent_MakeAvailable(catch2)

    add_executable(dawEmu_tests
        tests/smoke_test.cpp
        tests/cpu/cpu_nop_test.cpp
        tests/integration/bus_map_test.cpp
    )

    target_link_libraries(dawEmu_tests
        PRIVATE
            dawEmu_core
            Catch2::Catch2WithMain
    )

    target_compile_features(dawEmu_tests PRIVATE cxx_std_20)
    dawemu_set_warnings(dawEmu_tests)

    include(${catch2_SOURCE_DIR}/extras/Catch.cmake)
    catch_discover_tests(dawEmu_tests)
endif()