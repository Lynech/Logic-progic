cmake_minimum_required(VERSION 3.20)

set(FLTK_SKIP_FLUID True)
set(FLTK_SKIP_FORMS True)

find_package(FLTK REQUIRED)
find_package(OpenGL REQUIRED)

set(HEADERS
    classes/fltk.h
    graph_elems/graph_elems.h
    classes/mapgroup.h
    classes/logicmap.h
    classes/elemlist.h
    classes/createbutton.h
    classes/logicwindow.h
    classes/add_elem_impl.h
    graph_elems/logic_elems.h
    # ${LIB_DIR}/logic_elems/logic_elems.h
)
set(SOURCES
    classes/fltk.cpp
    graph_elems/graph_elems.cpp
    classes/mapgroup.cpp 
    classes/logicmap.cpp 
    classes/elemlist.cpp
    classes/createbutton.cpp
    classes/logicwindow.cpp
    graph_elems/logic_elems.cpp
    # ${LIB_DIR}/logic_elems/logic_elems.cpp
)

add_library(my_lib ${HEADERS} ${SOURCES})

target_precompile_headers(my_lib PRIVATE graph_elems/graph_elems.h graph_elems/logic_elems.h)
target_precompile_headers(my_lib PUBLIC ${HEADERS})

target_include_directories(
    my_lib
    SYSTEM
    PUBLIC
    ${FLTK_INCLUDE_DIR}
)

target_include_directories(
    my_lib
    PUBLIC
    classes/
    graph_elems/
    # ${LIB_DIR}/logic_elems/
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
