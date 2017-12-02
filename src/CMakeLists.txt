add_library(roguelike_src_lib
    window.hpp
    window.cpp
    controller.hpp
    controller.cpp
    renderer.hpp
    renderer.cpp
    game_controller.hpp
    game_controller.cpp
    game.hpp
    game.cpp
    terrain.hpp
    terrain.cpp
    tile.hpp
    tile.cpp
    tile_map_base.hpp
    tile_map_base.cpp
    tile_map.hpp
    tile_map.cpp
    feature.hpp
    feature.cpp
    map_generator.hpp
    map_generator.cpp
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

add_executable(Roguelike main.cpp)
target_link_libraries(Roguelike roguelike_src_lib)

set(OUTPUT_DIR ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR})
foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${OUTPUT_DIR})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${OUTPUT_DIR})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${OUTPUT_DIR})
endforeach(OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES)
