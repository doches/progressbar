add_library(progressbar progressbar.c)
add_library(statusbar statusbar.c)

set_target_properties(progressbar PROPERTIES PUBLIC_HEADER
    ${PROJECT_SOURCE_DIR}/include/progressbar/progressbar.h)
set_target_properties(statusbar PROPERTIES PUBLIC_HEADER
    ${PROJECT_SOURCE_DIR}/include/progressbar/statusbar.h)

install(
    TARGETS progressbar statusbar
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include/progressbar
)
