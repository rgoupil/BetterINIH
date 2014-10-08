cmake_minimum_required(VERSION 2.8)

project(INIH)

option(INIH_BUILD_CPP "Build INIH c++ version" ON)

set(SOURCES)
set(HEADERS)

include_directories(".")
list(APPEND SOURCES "ini.c")
list(APPEND HEADERS "ini.h")

if (INIH_BUILD_CPP)
	include_directories("cpp")
	list(APPEND SOURCES "cpp/INIReader.cpp" "cpp/AINIReader.cpp")
	list(APPEND HEADERS "cpp/INIReader.h" "cpp/AINIReader.h")
endif(INIH_BUILD_CPP)

#TODO: Examples + (unit) testing

add_library(INIH ${SOURCES} ${HEADERS})

#TODO: This is sooo dirty, need to find a cleaner way to do that
set(INIH_BUILD_INCLUDE_DIR "${PROJECT_BINARY_DIR}/include/")
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${INIH_BUILD_INCLUDE_DIR})
configure_file(ini.h "${INIH_BUILD_INCLUDE_DIR}ini.h")
if (INIH_BUILD_CPP)
	configure_file(cpp/INIReader.h "${INIH_BUILD_INCLUDE_DIR}INIReader.h")
	configure_file(cpp/AINIReader.h "${INIH_BUILD_INCLUDE_DIR}AINIReader.h")
endif(INIH_BUILD_CPP)