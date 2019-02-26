set(PROJECT_NAME srp)

add_subdirectory(entities)
add_subdirectory(repository)
add_subdirectory(payment)
add_subdirectory(time_sheet)

set(PROJECT_SOURCES srp.c)

source_group("Sources" FILES ${PROJECT_SOURCES})

find_package(PkgConfig REQUIRED)
pkg_search_module(GLIB REQUIRED glib-2.0)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 11)
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD_REQUIRED ON)

target_include_directories(${PROJECT_NAME} PRIVATE ${GLIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${GLIB_LDFLAGS} srp-entities srp-repository srp-payment srp-time-sheet)
link_directories(entities repository payment time_sheet)
