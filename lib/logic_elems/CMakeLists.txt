# cmake_minimum_required(VERSION 3.20)

# set(HEADERS
#     logic_elems.h

# )
# set(SOURCES
#     logic_elems.cpp
# )

# add_library(new_lib ${HEADERS} ${SOURCES})

# target_include_directories(
#     new_lib
#     PUBLIC
#     ../../fltk/classes/
#     ../../fltk/graph_elems/
# )


# # add_library(my_lib ${HEADERS} ${SOURCES})

# target_precompile_headers(new_lib PUBLIC fltk.h graph_elems.h mapgroup.h logicmap.h logicwindow.h elemlist.h createbutton.h add_elem_impl.h)

# # target_include_directories(
# #     my_lib
# #     SYSTEM
# #     PUBLIC
# #     ${FLTK_INCLUDE_DIR}
# # )


# # target_link_directories(
# #     new_lib
# #     PUBLIC
# #     ../../fltk/classes/
# #     ../../fltk/graph_elems/
# # )

# target_link_libraries(
#     new_lib
#     my_lib
#     # ${FLTK_LIBRARIES}
#     # ${OPENGL_LIBRARIES}
# )


# # target_link_libraries(my_lib fltk fltk_jpeg fltk_png fltk_z)
