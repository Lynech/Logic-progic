set(TARGET "logic")

project(${TARGET} LANGUAGES CXX)

add_executable(
    ${TARGET} 
    main.cpp
    read.cpp
    ${LIB_DIR}/logic_elems/logic_elems.cpp
)

install(TARGETS ${TARGET})
