cmake_minimum_required(VERSION 3.20)

set(FLTK_SKIP_FLUID True)
set(FLTK_SKIP_FORMS True)

find_package(FLTK REQUIRED)
find_package(OpenGL REQUIRED)

set(HEADERS
fltk.h
# logicmap.h
# mapgroup.h
# logicwindow.h
graph_elems/graph_elems.cpp
)
set(SOURCES
    # graphic.cpp
    fltk.cpp
    # logicmap.cpp 
    # logicwindow.cpp
    # mapgroup.cpp 
)

add_library(my_lib ${HEADERS} ${SOURCES})

target_include_directories(
    my_lib
    SYSTEM
    PUBLIC
    ${FLTK_INCLUDE_DIR}
)

target_include_directories(
    my_lib
    PUBLIC
    ../
)

target_link_directories(
    my_lib
    PUBLIC
    ${FLTK_INCLUDE_DIR}/../lib
)

target_link_libraries(
    my_lib
    ${FLTK_LIBRARIES}
    ${OPENGL_LIBRARIES}
)

target_link_libraries(my_lib fltk fltk_jpeg fltk_png fltk_z)

add_executable(
    my_exe
    ${CMAKE_CURRENT_SOURCE_DIR}/graphic.cpp
)
target_link_libraries(
    my_exe
    my_lib
)