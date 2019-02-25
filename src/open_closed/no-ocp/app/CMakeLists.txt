set(PROJECT_NAME no-ocp)

set(PROJECT_SOURCES no_ocp.c)

source_group("Sources" FILES ${PROJECT_SOURCES})

find_package(PkgConfig REQUIRED)
pkg_search_module(GLIB REQUIRED glib-2.0)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${GLIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${GLIB_LDFLAGS} no-ocp-entities no-ocp-repository no-ocp-financial-report)
link_directories(../entities ../repository ../financial_report)
