set(PROJECT_NAME ocp)

set(PROJECT_SOURCES ocp.c)

source_group("Sources" FILES ${PROJECT_SOURCES})

find_package(PkgConfig REQUIRED)
pkg_search_module(GLIB REQUIRED glib-2.0)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${GLIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${GLIB_LDFLAGS} ocp-ioc-container ocp-database ocp-interactor)
link_directories(../ioc_container ../database ../interactor)
