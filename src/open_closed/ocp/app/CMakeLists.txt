set(PROJECT_NAME ocp)

set(PROJECT_SOURCES 
    ocp.c
    container_register.c)
set(PROJECT_HEADERS
    container_register.h)

source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Headers" FILES ${PROJECT_HEADERS})

find_package(PkgConfig REQUIRED)
pkg_search_module(GLIB REQUIRED glib-2.0)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 11)
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD_REQUIRED ON)

target_include_directories(${PROJECT_NAME} PRIVATE ${GLIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME}
    ${GLIB_LDFLAGS}
    ocp-ioc-container
    ocp-database
    ocp-interactor
    ocp-controller
    ocp-screen-presenter
    ocp-console-view
    ocp-colored-console-view)
link_directories(
    ../ioc_container
    ../database
    ../interactor
    ../controller
    ../screen_presenter
    ../console_view
    ../colored_console_view)
