set(PROJECT_NAME ocp-screen-presenter)

set(PROJECT_SOURCES
    screen_presenter.c
    screen_view_model.c)
set(PROJECT_HEADERS
    screen_presenter.h
    screen_view_model.h
    screen_view.h)

source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Headers" FILES ${PROJECT_HEADERS})

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB2 REQUIRED IMPORTED_TARGET glib-2.0)

add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${GLIB2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${GLIB2_LDFLAGS})
