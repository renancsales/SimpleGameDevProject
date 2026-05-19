cmake_minimum_required(VERSION "3.19.2")

set(CMAKE_CXX_STANDARD 20)

set(PRODUCTION_BUILD OFF CACHE BOOL "Make this a production build" FORCE)

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug")
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release")
    add_compile_options(/arch:AVX2) # SIMD optimizations
else()
    if(APPLE)
        #add_link_options(-static-libstdc++ -static-libgcc)
        add_compile_options(-mcpu=apple-m1) # SIMD optimizations
    else ()
        add_link_options(-static-libstdc++ -static-libgcc)
        add_compile_options(-mavx2 -mfma) # SIMD optimizations
    endif ()

endif()


# ensure raylib is built as static libraries
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build Raylib as statis libraries" FORCE)

project(game)

# add raylib
add_subdirectory(externals/raylib)
add_subdirectory(externals/imgui-docking)
add_subdirectory(externals/rlimgui)

# define MY_SOURCES to be a list if all source files for my project
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable("${CMAKE_PROJECT_NAME}")

set_property(TARGET "${CMAKE_PROJECT_NAME}" PROPERTY CXX_STANDARD 20)

if(PRODUCTION_BUILD)
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="./resources/")
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=1)
else ()
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/")
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=0)
endif ()

target_sources("${CMAKE_PROJECT_NAME}" PRIVATE ${MY_SOURCES})

if(MSVC) # VS compiler
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC _CRT_SECURE_NO_WARNINGS)
    if(PRODUCTION_BUILD)
        set_target_properties("${CMAKE_PROJECT_NAME}" PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup") # no console
    endif ()
elseif (MINGW)
    if(PRODUCTION_BUILD)
        # remove console on windows under mingw
        target_link_options("${CMAKE_PROJECT_NAME}" PRIVATE -mwindows)
    endif ()
elseif (APPLE OR UNIX)
    if(PRODUCTION_BUILD)
        target_link_options("${CMAKE_PROJECT_NAME}" PRIVATE -s)
    endif ()
endif ()

target_include_directories(game PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/")

# Link raylib library statically
target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE raylib_static imgui rlimgui)

#target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/")

#target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="./")


# target_link_libraries(project_setup PRIVATE fem_lib)