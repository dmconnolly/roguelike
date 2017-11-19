cmake_minimum_required(VERSION 3.7)
project(Roguelike)

OPTION(USE_CLANG "build application with clang" ON)

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    # Force to always compile with W4
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    # Update if necessary
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
endif()

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/window.cpp
    src/controller.cpp
    src/renderer.cpp
    src/game_controller.cpp
    src/game.cpp
    src/tile_map.cpp
    src/tile.cpp
)

# GLFW
set(GLFW_BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_SOURCE_DIR}/glfw)
include_directories(${CMAKE_SOURCE_DIR}/glfw/include)
target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES})

# GLM
include_directories(${CMAKE_SOURCE_DIR}/glm)

# GLBinding
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(OPTION_SELF_CONTAINED ON CACHE BOOL "" FORCE)
set(OPTION_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(OPTION_BUILD_GPU_TESTS OFF CACHE BOOL "" FORCE)
set(OPTION_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(OPTION_BUILD_TOOLS OFF CACHE BOOL "" FORCE)
set(OPTION_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_SOURCE_DIR}/glbinding)
target_link_libraries(${PROJECT_NAME} glbinding)

# PCG
include_directories(${CMAKE_SOURCE_DIR}/pcg/include)
