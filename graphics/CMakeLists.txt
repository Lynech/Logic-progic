cmake_minimum_required(VERSION 3.20)

set(TARGET "graphics")

set(HEADERS
# fltk.h
# logicmap.h
# mapgroup.h
# logicwindow.h
)
set(SOURCES
    graphic.cpp
    fltk.cpp
    # logicmap.cpp 
    # logicwindow.cpp
    # mapgroup.cpp 
)

project(${TARGET} CXX)

set(FLTK_SKIP_FLUID True)
set(FLTK_SKIP_FORMS True)

find_package(FLTK 1.3.8 EXACT REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(SYSTEM ${FLTK_INCLUDE_DIR})
link_directories(${FLTK_INCLUDE_DIR}/../lib)

add_executable(${TARGET} ${HEADERS} ${SOURCES})

target_link_libraries(${TARGET} ${FLTK_LIBRARIES} ${OPENGL_LIBRARIES})
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_link_libraries(${TARGET} fltk_jpeg fltk_png fltk_z)
endif()

install(TARGETS ${TARGET})