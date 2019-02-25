set(PROJECT_NAME ocp-colored-console-view)

set(PROJECT_SOURCES
    colored_console_view.c)
set(PROJECT_HEADERS
    colored_console_view.h)

source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Headers" FILES ${PROJECT_HEADERS})

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB2 REQUIRED IMPORTED_TARGET glib-2.0)
pkg_check_modules(CURSES REQUIRED IMPORTED_TARGET ncursesw)

add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${GLIB2_INCLUDE_DIRS} ${CURSES_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${GLIB2_LDFLAGS} ${CURSES_LDFLAGS} ocp-interactor)
link_directories(../interactor)
