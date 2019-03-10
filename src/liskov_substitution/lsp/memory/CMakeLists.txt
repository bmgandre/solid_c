set(PROJECT_NAME lsp-memory)

set(PROJECT_SOURCES
    allocator.c)
set(PROJECT_HEADERS
    allocator.h)

source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Headers" FILES ${PROJECT_HEADERS})

find_package(PkgConfig REQUIRED)
pkg_search_module(CMOCKA REQUIRED cmocka)
pkg_search_module(LIBGC REQUIRED bdw-gc)

add_link_options(-Wl,--wrap=malloc,--wrap=free,--wrap=calloc)
add_library(${PROJECT_NAME} STATIC ${PROJECT_SOURCES})

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 11)
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD_REQUIRED ON)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMOCKA_INCLUDE_DIRS} ${LIBGC_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${CMOCKA_LDFLAGS} ${LIBGC_LDFLAGS})
