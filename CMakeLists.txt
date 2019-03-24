cmake_minimum_required(VERSION 3.9)

OPTION(USE_CLANG "build application with clang" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif()

# Turn on warnings
if(MSVC)
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
endif()

set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/install CACHE PATH "Cmake prefix" FORCE)

project(roguelike)

# GLFW
set(GLFW_BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_SOURCE_DIR}/glfw)

# GLBinding
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(OPTION_SELF_CONTAINED ON CACHE BOOL "" FORCE)
set(OPTION_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(OPTION_BUILD_GPU_TESTS OFF CACHE BOOL "" FORCE)
set(OPTION_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(OPTION_BUILD_TOOLS OFF CACHE BOOL "" FORCE)
set(OPTION_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_SOURCE_DIR}/glbinding)

# Source
add_library(roguelike_src_lib
    src/fastnoise/FastNoise.h
    src/fastnoise/FastNoise.cpp
    src/window.hpp
    src/window.cpp
    src/controller.hpp
    src/controller.cpp
    src/renderer.hpp
    src/renderer.cpp
    src/game_controller.hpp
    src/game_controller.cpp
    src/game.hpp
    src/game.cpp
    src/terrain.hpp
    src/terrain.cpp
    src/tile.hpp
    src/tile.cpp
    src/tile_map_base.hpp
    src/tile_map_base.cpp
    src/tile_map.hpp
    src/tile_map.cpp
    src/room.hpp
    src/room.cpp
    src/map_generator.hpp
    src/map_generator.cpp
    src/random.hpp
    src/random.cpp
)

include_directories(
    ${GLBINDING_INCLUDES}
    ${CMAKE_SOURCE_DIR}/glfw/include
    ${CMAKE_SOURCE_DIR}/glm
    ${CMAKE_SOURCE_DIR}/pcg/include
)

target_link_libraries(roguelike_src_lib PUBLIC
    glbinding
    glfw
)

add_executable(roguelike src/main.cpp)
target_link_libraries(roguelike roguelike_src_lib)

# Set startup project
if(MSVC)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT roguelike)
endif()

# Tests
add_subdirectory(${CMAKE_SOURCE_DIR}/test)
