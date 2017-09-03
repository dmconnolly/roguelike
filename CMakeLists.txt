cmake_minimum_required(VERSION 3.9)
project(Roguelike)

OPTION(USE_CLANG "build application with clang" ON)

include_directories(include)

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_EXTENSIONS OFF)

# GLEW
add_subdirectory(${CMAKE_SOURCE_DIR}/glew)
include_directories(${CMAKE_SOURCE_DIR}/glew/include)
link_directories(${CMAKE_SOURCE_DIR}/glew/lib)

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_SOURCE_DIR}/glfw)
include_directories(${CMAKE_SOURCE_DIR}/glfw/include)

add_executable(run src/main.cpp src/window.cpp)
target_link_libraries(run glew ${GLEW_LIBRARIES} glfw ${GLFW_LIBRARIES} GL)
