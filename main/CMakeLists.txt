set(TARGET "logic")

project(${TARGET} LANGUAGES CXX)

add_executable(
    ${TARGET} 
    main.cpp
    drawing_elems.cpp
    functions.cpp
    ${LIB_DIR}/logic_elems/logic_elems.cpp
)

install(TARGETS ${TARGET})
