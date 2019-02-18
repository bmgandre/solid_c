set(PROJECT_NAME ocp-interactor)

set(PROJECT_SOURCES
    financial_transaction.c
    financial_report_request.c
    financial_report_response.c
    financial_report_generator.c)
set(PROJECT_HEADERS
    financial_transaction.h
    financial_data_gateway.h
    financial_report_request.h
    financial_report_response.h
    financial_report_generator.h)

source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Headers" FILES ${PROJECT_HEADERS})

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB2 REQUIRED IMPORTED_TARGET glib-2.0)

add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${GLIB2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${GLIB2_LDFLAGS})
