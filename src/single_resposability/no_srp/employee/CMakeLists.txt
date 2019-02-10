set(PROJECT_NAME employee)

set(PROJECT_SOURCES
    employee.c
    employee_repository.c
    time_sheet.c 
    employee_service.c 
    time_sheet_repository.c)
set(PROJECT_HEADERS
    employee.h
    employee_repository.h
    time_sheet.h
    employee_service.h
    time_sheet_repository.c)

source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Headers" FILES ${PROJECT_HEADERS})

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB2 REQUIRED IMPORTED_TARGET glib-2.0)

add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${GLIB2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${GLIB2_LDFLAGS})
