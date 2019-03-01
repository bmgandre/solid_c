set(PROJECT_NAME no-lsp)

set(PROJECT_SOURCES no_lsp.c)

source_group("Sources" FILES ${PROJECT_SOURCES})

find_package(PkgConfig REQUIRED)
pkg_search_module(GLIB REQUIRED glib-2.0)
pkg_search_module(CMOCKA REQUIRED cmocka)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
add_test(${PROJECT_NAME} ${PROJECT_NAME})

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 11)
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD_REQUIRED ON)

target_include_directories(${PROJECT_NAME} PRIVATE ${GLIB_INCLUDE_DIRS} ${CMOCKA_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${GLIB_LDFLAGS} ${CMOCKA_LDFLAGS} no-lsp-entities)
link_directories(../entities)
