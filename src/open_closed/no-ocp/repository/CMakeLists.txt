set(PROJECT_NAME no-ocp-repository)

set(PROJECT_SOURCES
    financial_transaction_repository.c)
set(PROJECT_HEADERS
    financial_transaction_repository.h)

source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Headers" FILES ${PROJECT_HEADERS})

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB2 REQUIRED IMPORTED_TARGET glib-2.0)

add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${GLIB2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${GLIB2_LDFLAGS} no-ocp-entities)
link_directories(../entities)