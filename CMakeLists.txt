project(ProgressBar)

cmake_minimum_required(VERSION 3.0)

set(CURSES_NEED_NCURSES TRUE)
find_package(Curses)
include_directories(${CURSES_INCLUDE_DIRS})

include_directories(include/progressbar)

add_subdirectory(lib)
add_subdirectory(test)
