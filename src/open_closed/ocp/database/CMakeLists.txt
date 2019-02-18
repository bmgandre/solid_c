set(PROJECT_NAME ocp-database)

set(PROJECT_SOURCES
    financial_data_mapper.c)
set(PROJECT_HEADERS
    financial_data_mapper.h)

source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Headers" FILES ${PROJECT_HEADERS})

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB2 REQUIRED IMPORTED_TARGET glib-2.0)

add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${GLIB2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${GLIB2_LDFLAGS})
