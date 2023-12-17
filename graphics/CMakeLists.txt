cmake_minimum_required(VERSION 3.20)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/fltk)

add_executable(
    my_exe
    ${CMAKE_CURRENT_SOURCE_DIR}/graphic.cpp
)
target_link_libraries(
    my_exe
    my_lib
    # new_lib
)