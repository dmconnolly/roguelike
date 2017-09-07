cmake_minimum_required(VERSION 3.7)
project(Roguelike)

OPTION(USE_CLANG "build application with clang" ON)

include_directories(include)

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_EXTENSIONS OFF)

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
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_SOURCE_DIR}/glfw)
include_directories(${CMAKE_SOURCE_DIR}/glfw/include)
target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES})

# GLBinding
add_subdirectory(${CMAKE_SOURCE_DIR}/glbinding)
target_link_libraries(${PROJECT_NAME} glbinding)
