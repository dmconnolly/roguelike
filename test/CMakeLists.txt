add_executable(tests
    test.cpp
)
target_link_libraries(tests roguelike_src_lib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/catch/include)

set(OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
