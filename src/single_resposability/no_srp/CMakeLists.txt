set(PROJECT_NAME no_srp)

option(SRP_MODIFICATION "Enable code modification which break bussiness rules for HR" OFF)

if(SRP_MODIFICATION)
    add_definitions(-DNEW_HOURS_THRESHOLD)
    message("SRP MODIFICATION ENABLED")
endif(SRP_MODIFICATION)

add_subdirectory(employee)

set(PROJECT_SOURCES no_srp.c)

source_group("Sources" FILES ${PROJECT_SOURCES})

find_package(PkgConfig REQUIRED)
pkg_search_module(GLIB REQUIRED glib-2.0)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${GLIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${GLIB_LDFLAGS} employee)
