set(PROJECT_NAME no-ocp-financial-report)

set(PROJECT_SOURCES
    financial_report_generator.c
    financial_console_reporter.c
    financial_colored_console_reporter.c)
set(PROJECT_HEADERS
    financial_report_generator.h
    financial_console_reporter.h
    financial_colored_console_reporter.h)

source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Headers" FILES ${PROJECT_HEADERS})

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB2 REQUIRED IMPORTED_TARGET glib-2.0)
find_package(Curses REQUIRED)

if(WIN32)
    set(CURSES_INCLUDE_DIRS "${CURSES_INCLUDE_DIRS}/ncurses")
endif()

add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES})

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 11)
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD_REQUIRED ON)

target_include_directories(${PROJECT_NAME} PRIVATE ${GLIB2_INCLUDE_DIRS} ${CURSES_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${GLIB2_LDFLAGS} ${CURSES_LIBRARIES} no-ocp-entities no-ocp-repository)
link_directories(../entities ../repository)
