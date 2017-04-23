add_executable(demo demo.c)
target_link_libraries(demo progressbar statusbar ${CURSES_LIBRARIES})
