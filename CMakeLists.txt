set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDSARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-pedantic -Wall -Wextra")

cmake_path(SET LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")

include_directories(
    ${LIB_DIR}
)

add_subdirectory("07/calculator")
add_subdirectory("08")
add_subdirectory("09")
add_subdirectory("10")

add_subdirectory("11/shape_primitives")
add_subdirectory("12")
add_subdirectory("13")
add_subdirectory("14/spiral")
add_subdirectory("14/hexagon")